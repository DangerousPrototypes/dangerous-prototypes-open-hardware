#include <stdio.h>

#include "HardwareProfile.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

#include "uip_task.h"
#include "logger.h"
#include "rtcc.h"
#include "nic.h"
#include "ff.h"
#include "diskio.h"



/*
 * Set config fuses
 */
//it's important to keep configuration bits that are compatibale with the bootloader
//if you change it from the internall/PLL clock, the bootloader won't run correctly
_FOSCSEL(FNOSC_FRCPLL)          //INT OSC with PLL (always keep this setting)
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)       //disable external OSC (always keep this setting)
_FWDT(FWDTEN_OFF)                               //watchdog timer off
_FICD(JTAGEN_OFF & ICS_PGD1);//JTAG debugging off, debugging on PG1 pins enabled



FATFS FatFS;

static void prvSetupHardware( void );
static void prvSetupSDCard( void );
static void prvInitializeUART1( void );
char last_failure_reason __attribute__((persistent));


int main( void )
{

	prvSetupHardware();

	printf("Last reset was %04x ", RCON);
	if (_TRAPR) printf("trap conflict\n");
	if (_IOPUWR) printf("Illegal Opcode or Uninitialized W Access\n");
	if (_EXTR) printf("external\n");
	if (_POR) printf("power on\n");
	if (_BOR) printf("brown-out\n");
	if (_SWR) {
		printf("software reset reason %c. Need hard reset\n", last_failure_reason);
		RCON=0;
		for(;;);
	}

	RCON=0;
	prvSetupSDCard();
	/* Initialise the logger */
	log_init();

	/* Start the UIP task */
	xTaskCreate( vUipTask, ( signed char * ) "UIP", configMINIMAL_STACK_SIZE * 2, NULL, tskIDLE_PRIORITY, NULL);

	/* Finally start the scheduler. */
	vTaskStartScheduler();

	/* Will only reach here if there is insufficient heap available to start
	the scheduler. */
	printf("FAILED TO START SCHEDULER!!!\n");
	return 0;
}

/*
Initialize the terminal UART for stdin/stdout
NOTE: Configures with TX disabled, and RX in Auto-baud rate mode
This will require the sync char 'U' to be received
before the TX is enabled and ANYTHING is sent 
*/ 
static void prvInitializeUART1(void){
        //setup UART
        //U1BRG = 0x270; //9600 @ Fcy=24Mhz
        //U1BRG = 0x137; //19200 @ Fcy=24Mhz
        //U1BRG = 0x0204;  //19200 @ Fcy=40Mhz
        //U1BRG = 0x00ab;  //57600 @ Fcy=40Mhz
        U1BRG = 0x0055;  //115200 @ Fcy=40Mhz
    U1MODE = 0;
    U1MODEbits.BRGH = 1;
    U1STA = 0;
    U1MODEbits.UARTEN = 1;
    IFS0bits.U1RXIF = 0;
        U1STAbits.UTXEN = 0;    //disable TX to avoid backpowering FTDI chip when no USB attached
//auto baud disabled for now
//      U1MODEbits.ABAUD = 1;
}


static void prvSetupHardware( void )
{
        AD1PCFGL = 0xFFFF; //digital pins
		_AD1MD = 1; // disable ADC

        //setup internal clock for 80MHz/40MIPS
        //7.37/2=3.685*43=158.455/2=79.2275
        PLLFBD=41; //pll multiplier (M) = +2
        CLKDIVbits.PLLPOST=0;// PLLPOST (N1) 0=/2
        CLKDIVbits.PLLPRE=0; // PLLPRE (N2) 0=/2 
    
    while(!OSCCONbits.LOCK);//wait for PLL ready



        //setup LEDs
        LD1_TRIS = 0;
		LD2_TRIS = 0;
		SD_TRIS=0;
        LD1_IO=1;
		LD2_IO=1;
		SD_IO=0;

        //custom pin assignments for our hardware
        // ENC28J60 I/O pins
        //mapping:
        //A2 ETH-INT
        //C2 MISO
        //C1 MOSI
        //C0 CLK
        //B3 CS
        //B2 RST
        //CS and RST pins
        //MISO1 C2/RP18 (input)
        SDI1R_I = 18;                   
        //CLK1 C0/RP16 (output)
        RP16_O = SCK1OUT_O;     
        //MOSI1 C1/RP17 (output)
        RP17_O = SDO1_O;                

        //SD CARD PPS
        //MISO1 B10/RP10 (input)
        SDI2R_I = 10;                   
        //CLK1 B11/RP11 (output)
        _RP11R = SCK2OUT_O;     
        //MOSI1 B12/RP12 (output)
		_RP12R  = SDO2_O;
		// Set SD card CS as output
		SD_CS_TRIS = 0;
		SD_CS = 1;


/*      //EEPROM PPS
        //MISO2 C8/RP24 (input)
        SDI2R_I = 24;                   
        //CLK2 C6/RP22 (output)
        RP22_O = SCK2OUT_O;     
        //MOSI2 B9/RP9 (output)
        RP9_O = SDO2_O;         
        XEEInit();
*/
        //uart
        //RX PR14 (input)
        U1RXR_I = 14;
        //TX RP15 (output)
        RP15_O=U1TX_O;

        prvInitializeUART1();
		printf("Web Platform\n");

		rtcc_init();
	//vParTestInitialise();
}

void prvSetupSDCard(void)
{
   
	const unsigned long ulCompareMatch = ( configCPU_CLOCK_HZ / 8 ) / configTICK_RATE_HZ;
	int ret;
	portBASE_TYPE i;

	/* Prescale of 8. */
	T2CON = 0;	TMR2 = 0;
	PR2 = ( unsigned short ) ulCompareMatch;

	/* Setup timer 1 interrupt priority. */
	_T2IP = configKERNEL_INTERRUPT_PRIORITY;

	/* Clear the interrupt as a starting condition. */
	IFS0bits.T2IF = 0;

	/* Enable the interrupt. */	_T2IE = 1;
	/* Setup the prescale value. */
	T2CONbits.TCKPS0 = 1;
	T2CONbits.TCKPS1 = 0;
	/* Start the timer. */	T2CONbits.TON = 1;

		for (i=0;i<3;i++) {
			ret = disk_initialize(0);
			printf("%d disk_initialize(0) returns %d\n", i, ret);
			if (ret == 0) break;
	}
	if (ret == 0) {
		// mount does not populate the fatfs structure...
		printf("f_mount(0) returns %d\n",f_mount(0, &FatFS));
	}
	_T2IE = 0;
	T2CONbits.TON = 0;
}
	
void __attribute__((interrupt, auto_psv)) _T2Interrupt (void){
	_T2IF=0;
	disk_timerproc();
}


void vApplicationIdleHook( void )
{
	/* If we had any co-routines, this is where we schedule them */
	//vCoRoutineSchedule();
}

void vApplicationTickHook (void )
{
	disk_timerproc();
}

int ff_cre_syncobj (BYTE drv, _SYNC_t* mutex)
{
	*mutex = xSemaphoreCreateMutex();
	if (*mutex != NULL) return 1;
	return 0;
}

int ff_del_syncobj (_SYNC_t mutex) 
{
	// can't delete?
	return pdTRUE;
}

int ff_req_grant (_SYNC_t mutex) 
{
	return xSemaphoreTake(mutex,  _FS_TIMEOUT );
}
void ff_rel_grant (_SYNC_t mutex) 
{
	xSemaphoreGive(mutex);
}


/*
 * Error handling 
 */
void __attribute__((interrupt, auto_psv)) _StackError (void) {
	last_failure_reason='S';
	U1TXREG=last_failure_reason;
	asm("RESET");
}

void __attribute__((interrupt, auto_psv)) _AddressError (void) {
	last_failure_reason='A';
	U1TXREG=last_failure_reason;
	asm("RESET");
}

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName ) {

	last_failure_reason='R';
	U1TXREG=last_failure_reason;
	asm("RESET");
}
