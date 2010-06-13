//The compiled firmware can be used 'as-is' with the ds30 Loader bootloader
//you may need to locate your own p33FJ128gp204.gld file.
//   It's in the C30 compiler directory:
/* \C30\support\dsPIC33F\gld\ */

#include "hardware/HardwareProfile.h"
#include "lib/multitasker.h"
#include "uipsockettask.h"
#include "telnettask.h"
#include "lib/uip.h"
#include "lib/uip_arp.h"
#include "libConfig/nic.h"
#include "hardware/nic_dma.h"
#include "hardware/rtcc.h"
#include "lib/socket.h"
#include <stdio.h>

//it's important to keep configuration bits that are compatibale with the bootloader
//if you change it from the internall/PLL clock, the bootloader won't run correctly
_FOSCSEL(FNOSC_FRCPLL)		//INT OSC with PLL (always keep this setting)
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)	//disable external OSC (always keep this setting)
_FWDT(FWDTEN_OFF)				//watchdog timer off
_FICD(JTAGEN_OFF & ICS_PGD1);//JTAG debugging off, debugging on PG1 pins enabled



/*
Initialize the terminal UART for stdin/stdout
NOTE: Configures with TX disabled, and RX in Auto-baud rate mode
This will require the sync char 'U' to be received
before the TX is enabled and ANYTHING is sent 
*/ 
void InitializeUART1(void){
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
	U1STAbits.UTXEN = 0;	//disable TX to avoid backpowering FTDI chip when no USB attached
//auto baud disabled for now
//	U1MODEbits.ABAUD = 1;
}


//configures the PIC hardware
void InitHardware(void){	
	AD1PCFGL = 0xFFFF; //digital pins


	//setup internal clock for 80MHz/40MIPS
	//7.37/2=3.685*43=158.455/2=79.2275
	PLLFBD=41; //pll multiplier (M) = +2
	CLKDIVbits.PLLPOST=0;// PLLPOST (N1) 0=/2
	CLKDIVbits.PLLPRE=0; // PLLPRE (N2) 0=/2 
    
    while(!OSCCONbits.LOCK);//wait for PLL ready



	//setup LEDs
	LD1_TRIS = 0;
//	LD2_TRIS = 0;
	LD1_O=1;
//	LD2_O=1;

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
	RP11_O = SCK2OUT_O; 	
	//MOSI1 B12/RP12 (output)
	RP12_O = SDO2_O;
	
/*	//EEPROM PPS
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

	InitializeUART1();

	//lock PPS
/*
asm volatile (	"mov #OSCCON,w1 \n"
					"mov #0x46, w2 \n"
					"mov #0x57, w3 \n"
					"mov.b w2,[w1] \n"
					"mov.b w3,[w1] \n"
					"bset OSCCON, #6");
*/

	
}

//setup a logger for uip
//Just sends the msg to stdout ( UART 1 )
void uip_log(char *msg){
	puts( msg );
	putchar('\n');
}

extern struct buffer_t rxbuf;
extern struct buffer_t txbuf;
char c1;

//A "debugger" task that takes command characters from the serial
//port and prints debugging info out.
//Would be good to expand this into a general "debugger" tool
//(eg, read/write memory; show uIP statistics; set ip params; set rtcc, etc )
void debug_task_main()
{
	while(1)
	{
	
		int x ;
		do{
			task_yield();
			x = _mon_getc();
		}while( x == -1 );
		
		if( (char) x == 'r' ){
			u16_t i;
			printf("\nlast rx: %u bytes:\n", uip_dma_rx_last_packet_length);
			for( i = 0; i < uip_dma_rx_last_packet_length ; i++ ){
				printf("%02hhx ", uip_buf[i]);
			}
			puts("\n");
		}
		if( (char) x == 't' ){
			u16_t i;
			printf("\nlast tx: %u bytes:\n", uip_dma_tx_last_packet_length);
			for( i = 0; i < uip_dma_tx_last_packet_length ; i++ ){
				printf("%02hhx ", uip_buf[i]);
			}
			puts("\n");
		}
		if( (char) x == 's' ){
			printf("\nUIP_DMA_STATUS: %04x ", UIP_DMA_STATUS.value);
			printf("\nlast tx: %u ", uip_dma_tx_last_packet_length);
			printf("\nlast rx: %u ", uip_dma_rx_last_packet_length);
			printf("\nrx pending count: %u ", uip_dma_rx_pending_packets);
			printf("\nDMA0CON (DUMMY): %04x ", DMA0CON);
			printf("\nDMA1CON: %04x ", DMA1CON);
			puts("\n");
		}
		if( (char) x == 'x' ){
			puts("\nbuf status reset");
			UIP_DMA_BUFFER_FREE=0;
			
			CS_DIS();
			Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
			nic_rx_maybe();
		}
		if( (char)x == 'f' )
		{
			file_debug();
		}
		if( (char)x == 'm' )
		{
			puts("\r\nTask stack report:");
			u16_t i;
			for( i = 0; i < TASK_COUNT; i++ )
			{
				int hwm = task_stack_high_water_mark(i);
				printf("\r\nTask %u: Stack HWM: %d bytes.(%d words)", i, hwm, hwm/2 );			
			}
			puts("\r\n");
		}
/*		if( (char)x == 'p' ){
			int av = buffer_available( &rxbuf );
			int i;
			printf("\nrx buffer available: %d\n", av );
			for( i = 0 ; i < av; i++ )
			{
				buffer_read( &rxbuf, &c1, 1 );
				putchar(c1);
			}			
		}
		if( (char)x == 'o' ){
			int av = buffer_free( &txbuf );
			int i;
			printf("\ntx buffer free: %d\n", av );
			puts("enter data to send. CR to end.\n");
			while( (char)x != '\n' )
			{
				do{
					x = _mon_getc();
				}while( x == -1 );
				c1 = (char)x;
				putchar( c1 );
				buffer_write( &txbuf, &c1, 1);
			}
					
		}	  
*/	}
}


//main function, execution starts here
int main(void){

	InitHardware();
	rtcc_init();

	//TODO: set some sensible rtcc defaults until we can do NTP
	struct tm time;
	time.tm_year = 2010 - 1900;
	time.tm_mon = 5;
	time.tm_mday = 16;
	time.tm_hour = 15;
	time.tm_min = 34;
	time.tm_sec = 0;
	time.tm_wday = 0;
	rtcc_set_tm( time );
	

	puts("READY\n");

	// Initialize ENC28j60. At this point uIP is not used yet
    nic_init(); 
    puts("nic init\n");

    // init uIP
    uip_init();
    puts("uip init\n");

    // init ARP cache
    uip_arp_init();
    puts("arp init\n");

    // init periodic timer
    rtcc_set_alarm( time, 0, 0, true );
	rtcc_enable_alarm();
    puts("timer init\n");

	//all configuration done

	file_init();

	//task setup
	task_init( 0 , &uip_task_main );
	task_init( 1, &debug_task_main );
	task_init( 2, &telnet_task_main );
	//start task scheduler execution
	task_schedule();

	return 0; //will never get here
} //end main



//This occurs every half second, driven by the RTCC chime
//This is being used to drive the uip periodic processing
void __attribute__ ((interrupt, auto_psv)) _RTCCInterrupt()
{
	UIP_DMA_PERIODIC_TIMEOUT=1;
	IFS3bits.RTCIF = 0;
}

//Address Error Trap
union DWORD
{
	struct
	{
		unsigned short low;
		unsigned short high;
	} word;
	unsigned long value;
};

static union DWORD StkAddress;
void __attribute__((no_auto_psv,__interrupt__(__preprologue__( \
	"mov #_StkAddress+2,w1\n 	\
	pop [w1--]\n			\
	pop [w1]\n			\
	push [w1]\n			\
	push [++w1]")))) _AddressError(){
	
	INTCON1bits.ADDRERR = 0;
	StkAddress.value -= 2;
	printf("\nAddress Error @ %08lx",StkAddress.value );
}


void __attribute__((no_auto_psv,__interrupt__(__preprologue__( \
	"mov #_StkAddress+2,w1\n 	\
	pop [w1--]\n			\
	pop [w1]\n			\
	push [w1]\n			\
	push [++w1]")))) _StackError(){
	
	INTCON1bits.STKERR = 0;
	StkAddress.value -= 2;
	printf("\nStack Error @ %08lx",StkAddress.value );
}

