/*****************************************************************************
 *  Serial UART and buffer functions
 *****************************************************************************
 * FileName:        main.c
 * Processor:       dsPIC33
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Matt Callow			20101010	Initial File Creation
 * Eric Walker			20101112	Rewrote and Reformated
 *****************************************************************************/

/* includes */
#if 1

/* Standard library includes */
#include <stdio.h>

/* Project includes */
#include "project.h"

/* Hardware setup includes */
#include "configbits.h"
#include "osc.h"
#include "periph/gpio.h"
#include "periph/pps.h"
#include "periph/serial.h"
#include "periph/rtcc.h"

/* FreeRTOS Scheduler includes */
#include "rtos/FreeRTOS.h"
#include "rtos/task.h"
#include "rtos/queue.h"
#include "rtos/semphr.h"
#include "rtos/croutine.h"

/* FATFS File system includes */
#include "ff/ff.h"
#include "ff/diskio.h"

/* uIP network includes */
#include "nic/nic.h"
#include "uip/uip_task.h"
#include "logger.h"

/* Serial console includes */
#include "console.h"

#endif /* includes */

/* defines */
#if 1

#endif /* defines */

/* prototypes */
#if 1

#endif /* prototypes */

/* globals */
#if 1

FATFS FatFS;

/*****************************************************************************
 * Error handling and debugging, could be removed if space is needed.
 *****************************************************************************/
size_t g_FreeHeapSize; /* read with debugger */
unsigned char g_resetcode __attribute__((persistent));
/*****************************************************************************/

#endif /* globals */

/* file scope */
#if 1

static void prvSetupSDCard( void );

#endif /* file scope */

int main( void )
{
	SetupOscilator();
	SetupPeripheralPinSelect();
	SetupSerial();
	SetupGPIO();

	SerialPutString("\r\n\r\nDangerous Prototypes Web Platform\r\nHardware v");
	SerialPutString(WEB_PLATFORM_HARDWARE_VERS);
	SerialPutString(", Firmware A2 v");
	SerialPutString(WEB_PLATFORM_FIRMWARE_VERS);
	SerialPutString(" built at ");
	SerialPutString(WEB_PLATFORM_FIRMWARE_TIME);
	SerialPutString(".\r\n");
	SerialPutString("Last system reset caused by one or more of: ");
	if (RCON & 0x8082) SerialPutString("\r\n");
	if (RCONbits.POR) SerialPutString(" Power On reset,");
	if (RCONbits.BOR) SerialPutString(" Brown Out reset,");
	if (RCONbits.EXTR) SerialPutString(" Reset Button press,");
	if (RCONbits.TRAPR) SerialPutString(" Trap Conflict reset,");
	if (RCONbits.IOPUWR) SerialPutString("\r\n Illegal Opcode or Uninitialized indirect memory access reset,");
	if (RCONbits.SWR){
		SerialPutString("\r\n Software initiated reset due to ");
		switch(g_resetcode){
			case STACK_ERROR:
				SerialPutString("a Stack Error.");
				break;
			case ADDRS_ERROR:
				SerialPutString("an Address Error.");
				break;
			case RTOS_STACK:
				SerialPutString("an RTOS Stack overflow.");
				break;
			case RTOS_MALLOC:
				SerialPutString("an RTOS out of memory error.");
				break;
			default:
				SerialPutString("an unknown reason.");
				break;
		}
		SerialPutString("\r\nSystem halted.");
		ClearResetCode();
		SetErrorLED()
		while(1);
	}
	SerialPutString("\x08.\r\n");
	RCON = 0;
	ClearResetCode();




	rtcc_init();



	prvSetupSDCard();
	/* Initialise the logger */
	log_init();

	/* Start the UIP task */
	xTaskCreate( vUipTask, ( signed char * ) "UIP", configUIP_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

// induce test RTOS stack overflow
//	xTaskCreate( vUipTask, ( signed char * ) "UIP", 115, NULL, tskIDLE_PRIORITY, NULL);

	CreateConsoleTask();

	/* Finally start the scheduler. */
	vTaskStartScheduler();

	/* Will only reach here if there is insufficient heap available to start
	the scheduler. */
	printf("FAILED TO START SCHEDULER!!!\n");
	return 0;
} /* main() */


void prvSetupSDCard(void)
{
   
	const unsigned long ulCompareMatch = ( configCPU_CLOCK_HZ / 8 ) / configTICK_RATE_HZ;

	int ret;
	portBASE_TYPE i;


	/* Prescale of 8. */

	T2CON = 0;
	TMR2 = 0;


	PR2 = ( unsigned short ) ulCompareMatch;



	/* Setup timer 1 interrupt priority. */

	_T2IP = configKERNEL_INTERRUPT_PRIORITY;



	/* Clear the interrupt as a starting condition. */

	IFS0bits.T2IF = 0;



	/* Enable the interrupt. */
	_T2IE = 1;

	/* Setup the prescale value. */

	T2CONbits.TCKPS0 = 1;

	T2CONbits.TCKPS1 = 0;

	/* Start the timer. */
	T2CONbits.TON = 1;

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
}/**/
	
void __attribute__((interrupt, auto_psv)) _T2Interrupt (void)
{
	_T2IF=0;
	disk_timerproc();
}/**/



void vApplicationTickHook (void )
{
	disk_timerproc();
}/**/

int ff_cre_syncobj (BYTE drv, _SYNC_t* mutex)
{
	*mutex = xSemaphoreCreateMutex();
	if (*mutex != NULL) return 1;
	return 0;
}/**/

int ff_del_syncobj (_SYNC_t mutex) 
{
	// can't delete?
	return pdTRUE;
}/**/

int ff_req_grant (_SYNC_t mutex) 
{
	return xSemaphoreTake(mutex,  _FS_TIMEOUT );
}/**/

void ff_rel_grant (_SYNC_t mutex) 
{
	xSemaphoreGive(mutex);
}/**/




void vApplicationIdleHook( void )
{
	/* schedule co-routines if used */
	//vCoRoutineSchedule();

/*****************************************************************************
 * Error handling and debugging, could be removed if space is needed.
 *****************************************************************************/
	g_FreeHeapSize = xPortGetFreeHeapSize();
/*****************************************************************************/

} /* vApplicationIdleHook() */

/*****************************************************************************
 * Error handling and debugging, could be removed if space is needed.
 *****************************************************************************/
 void __attribute__((interrupt, auto_psv)) _StackError (void) {
	g_resetcode = STACK_ERROR;
	asm("RESET");
} /* _StackError() */

void __attribute__((interrupt, auto_psv)) _AddressError (void) {
	g_resetcode = ADDRS_ERROR;
	asm("RESET");
} /* _StackError() */

/* Hook function used if RTOS stack overflow checking enabled */
#if( configCHECK_FOR_STACK_OVERFLOW > 0 )
void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName ) {
	g_resetcode = RTOS_STACK;
	asm("RESET");
}
#endif /* configCHECK_FOR_STACK_OVERFLOW > 0 */

/* Hook function used if RTOS memory allocation checking enabled */
#if( configUSE_MALLOC_FAILED_HOOK == 1 )
void vApplicationMallocFailedHook( void )
{
	g_resetcode = RTOS_MALLOC;
	asm("RESET");
}
#endif /* configUSE_MALLOC_FAILED_HOOK */
/*****************************************************************************
 * END: Error handling and debugging, could be removed if space is needed.
 *****************************************************************************/

/*EOF*/
