/*****************************************************************************
 *  Serial UART Configuration
 *****************************************************************************
 * FileName:        serialconfig.h
 * Processor:       dsPIC33
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Eric Walker			20090405	Initial File Creation
 * Eric Walker			20101112	Update for Web Platform Project HWv1.1
 * Eric Walker			20101117	Changed configuration format
 *****************************************************************************/

#include "uart.h"

/*****************************************************************************
 * Serial Port UART Configurations Settings
 *****************************************************************************/

#define UART_NUMBER		( 1 )		/* 1 or 2			: use UART1 or UART2  */

#define UART_EN			( ENABLE )	/* ENABLE|DISABLE	:UART Module          */
#define UART_IDLE		( HALT )	/* HALT|CONTIN		:Module durring idle  */
#define UART_IREN		( DISABLE )	/* ENABLE|DISABLE	:IrDA Mode            */
#define UART_RTS		( SIMPLX )	/* SIMPLX|FLOWCTL	:RTS Pin Mode         */

#define UART_UEN		( 0 )		/* 0 = Tx,Rx Enabled; CTS,RTS digital IO  */
									/* 1 = Tx,Rx,RTS Enabled; CTS digital IO  */
									/* 2 = Tx,Rx,RTS,CTS Enabled              */
									/* 3 = Tx,Rx,BCLK Enabled; CTS digital IO */

#define UART_WAKE		( NOWAKE )	/* WAKE|NOWAKE		:UART wake from sleep */
#define UART_LOOP		( DISABLE )	/* ENABLE|DISABLE	:Loopback mode        */
#define UART_ABAUD		( DISABLE )	/* ENABLE|DISABLE	:Auto-baud mode       */
#define UART_RXIDL		( HIGH )	/* HIGH|LOW			:Rx idle state, low=0 */

#define UART_BRGH		( BRGHx4 )	/* BRGHx4|BRGHx16	:High speed baud rate */
									/* See calculations below                 */

#define UART_PARITY		( 0 )		/* 0 = 8 bit data, No parity              */
									/* 1 = 8 bit data, Odd parity             */
									/* 2 = 8 bit data, Even parity            */
									/* 3 = 9 bit data, No parity              */

#define UART_STOP		( 1 )		/* 1|2				:Number of stop bits  */

#define UART_TX_INT		( 2 )		/* 0 = Interupt on one free buffer slot   */
									/* 1 = Interupt on all Tx bytes sent      */
									/* 2 = Interupt on buffer empty           */
									/* 3 = Reserved, Do Not Use               */
#define UART_TXIDL		( HIGH )	/* HIGH|LOW			:Tx idle state, low=0 */
									/* In IrDA mode Tx idle state low = 1     */

#define UART_TXEN		( DISABLE )	/* ENABLE|DISABLE	:Tranmiter function   */

#define UART_RX_INT		( 0 )		/* 0 = Interupt on one byte in buffer     */
									/* 1 = Same as above                      */
									/* 2 = Interupt on one free buffer slot   */
									/* 3 = Interupt on buffer full            */

#define UART_ADDEN		( DISABLE )	/* ENABLE|DISABLE	:Address detect (9bit)*/

#define UART_BRG		( 86 )		/* Baud Rate Generator prescaler value    */
									/* See calculations below                 */

#define UART_TX_INT_PR	( 2 )		/* 0 - 7 			:Tx Interupt priority */
#define UART_RX_INT_PR	( 1 )		/* 0 - 7 			:Rx Interupt priority */
									/* Priority 0 effectivly disables interupt*/
									
#define UART_TX_INT_EN	( DISABLE )	/* ENABLE|DISABLE :Tx Interupt            */
#define UART_RX_INT_EN	( ENABLE  )	/* ENABLE|DISABLE :Rx Interupt            */

/*****************************************************************************
 * Serial Port UART Baud Rate Generator Calculations
 *****************************************************************************

	BRGHx4		BRG generates 4 clocks per bit period
	BRGHx16		BRG generates 16 clocks per bit period
	
	BRG   = ((( FCY / Desired Baud Rate ) / BRGH ) - 1 )
          = ((( 40M / 115200            ) / 4    ) - 1 )           
          = 86

    Baud  = ( FCY / ( 4 * ( BRG + 1 )))
          = ( 40M / ( 4 * ( 86  + 1 )))
          =  114943

    Error = (( 115200 - 114943 ) / 115200 )
          = 0.22%
          
 *****************************************************************************
 * Do not edit below this line.
 *****************************************************************************/

#define UART_MODE	( (UART_EN     << 15)	| 	(UART_IDLE  << 13) \
					| (UART_IREN   << 12) 	|	(UART_RTS   << 11) \
					| (UART_UEN    << 8 ) 	|	(UART_WAKE  << 7 ) \
					| (UART_LOOP   << 6 ) 	|	(UART_ABAUD << 5 ) \
					| (UART_RXIDL  << 4 ) 	|	(UART_BRGH  << 3 ) \
					| (UART_PARITY << 1 ) 	|	(UART_STOP  -  1 ) )

#define UART_STATUS	( ((UART_TX_INT & 0x2) << 14) \
					| ((UART_TX_INT & 0x1) << 13) \
					| (UART_TXIDL  << 14) 	|	(UART_TXEN  << 10) \
					| (UART_RX_INT << 6 ) 	|	(UART_ADDEN << 5 ) )


/*EOF*/
