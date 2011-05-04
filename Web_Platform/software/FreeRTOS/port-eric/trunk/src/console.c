/*****************************************************************************
 *  Console interface task
 *****************************************************************************
 * FileName:        console.c
 * Processor:       dsPIC33
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Eric Walker			20101113	Initial File Creation
 *****************************************************************************/

/* includes */
#if 1

#include "console.h" 
#include "periph/serial.h" 

/* Scheduler includes. */
#include "rtos/FreeRTOS.h"
#include "rtos/task.h"
#include "rtos/queue.h"

#endif /* includes */

/* prototypes */
#if 1

static void ConsoleTask( void *pvParameters );

#endif //

/* file scope */
#if 1

xTaskHandle ConsoleTaskHandle;

/* The handle of the queue used to send images to the LCD task. */
//static xQueueHandle queueHandle;
/* This has file scope so it can be seen by both the StartGraphicLCDTask 
   and the GraphicLCDTask.  This could potentially be done using the 
   void *pvParameters passed from the task creation function to the task. */
   
//char cmdbuf[CMDBUFLEN];
unsigned int cmdend;
unsigned int cmdstart;
int cmderror;

#endif //

/*********************************************************************
* Function Name     : CreateConsoleTask                              *
* Description       : This function... 
* Arguments         : None                                           *
* Return Value      : Task creation status                           *
*********************************************************************/
int CreateConsoleTask( void )
{
	/* Start the console task, return creation status */
	return	xTaskCreate( ConsoleTask, ( signed portCHAR * ) "CON", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &ConsoleTaskHandle );
} /* CreateConsoleTask() */

/*********************************************************************
* Function Name     : ResumeConsoleTaskFromISR                       *
* Description       : This function resumes the console task from    *
*                     and ISR.                                       *
* Arguments         : None                                           *
* Return Value      : None                                           *
*********************************************************************/
void ResumeConsoleTaskFromISR( void )
{
portBASE_TYPE xYieldRequired;

     // Resume the suspended task.
     xYieldRequired = xTaskResumeFromISR( ConsoleTaskHandle );

     if( xYieldRequired == pdTRUE )
     {
         taskYIELD();
     }

} /* ResumeConsoleTaskFromISR() */

/*********************************************************************
* Function Name     : ConsoleTask                                    *
* Description       : This function... 
*                     Actual console task thread function, never returns
* Arguments         : None                                           *
* Return Value      : Task creation status                           *
*********************************************************************/
static void ConsoleTask( void *pvParameters )
{
	char c;
	unsigned char cmd;

//	int stop;
//	int newstart;
//	int oldstart;
//	unsigned int sendw,received;
//	int repeat;
//	int temp;
//	int temp2;
//	int binmodecnt;
//	int numbits;
//	unsigned int tmpcmdend, histcnt, tmphistcnt;

	cmd = 0;
//	cmdstart=0;
//	cmdend=0;
//	tmpcmdend = cmdend;
//	histcnt = 0;
//	tmphistcnt = 0;
//	cmderror=0;
//	binmodecnt=0;

	for( ;; ){
//		SerialPutString("# ");
		while(!cmd){
			if(SerialGetChar(&c)){
				switch(c){
					
					
					
					
					default:
						SerialPutChar(c);
				}	
			} else {
				vTaskSuspend( NULL );
			}	
		}	
		
		
	}
} /* ConsoleTask() */


//static void SerialProtoTask( void *pvParameters )
//{
//	Uint8	ui8RxData,		// Received data
//			ui8Status;		// Function status
//	
//	while(1)
//	{
//		if (CommGetRxPendingCount() > 0) 	// Check if any data received
//			{
//			ui8Status = CommGetRxChar(&ui8RxData);  // Read in the received data
//			if (ui8Status == ST_OK) 		// Check if data received corrrectly
//				{
//				if (!g_bSuspendOutput)		// Check if output is already suspended
//					{
////					CommPutChar('\r');		// If output not suspended, send a
//					CommPutChar('\n');		// CR and LF to clear the line.
//					g_bSuspendOutput = TRUE;// Then suspend further output.
//					}
//				CommPutChar(ui8RxData);     // Echo the character
//				ProtProcRxData(ui8RxData);  // Process received char
//				}
//			}
//		// Probably need to add a task yield call here so we're not waisting
//		// cycles if there's nothing to do.  But, as long as this task is at 
//		// the idle priority it doens't really matter, I think.
//	}
//} //
//

/*EOF*/
