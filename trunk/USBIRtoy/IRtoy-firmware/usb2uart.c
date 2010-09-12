/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
//
//	IR IO
//
//#ifdef IR_IO
//#define RXtest

#include "globals.h"

//extern struct _irtoy irToy;

typedef enum
{
	SM_USB_UART_CONFIG_MODE=0,
	SM_USB_UART_CONFIG_MODE_OK,
	SM_USB_UART_RUN_MODE,
	SM_USB_UART_FLUSH_BUFFER

}_Sm_Usb_Uart;

static _Sm_Usb_Uart  Sm_Usb_Uart;
static u8 Configbuffctr;


static u8 TxBuffer[BUFSZ],TxBufferCtrIn,TxBufferCtrOut;
static volatile u8 RxBuffer[BUFSZ],RxBufferCtrIn,RxBufferCtrOut;


void Usb2UartSetup(void){
//send version string
if( mUSBUSARTIsTxTrfReady() )
	{
	irToy.usbOut[0]='U';//answer OK
	irToy.usbOut[1]='0';
	irToy.usbOut[2]='1';
	putUSBUSART(irToy.usbOut,3);
	}

//setup for USB UART

Sm_Usb_Uart=SM_USB_UART_FLUSH_BUFFER;
Configbuffctr=0;
}







u8 Usb2UartService(void)
{
static u8 buff_config[5];
/*
 * 0 = TXSTA
 * 1 = RCSTA
 * 2 = BAUDCON
 * 3 = SPBRGH
 * 4 = SPBRG
 */


// TODO enhancement: convert to switch case
if(SM_USB_UART_FLUSH_BUFFER==Sm_Usb_Uart)
	{
	FlushUsbRx();
	Sm_Usb_Uart=SM_USB_UART_CONFIG_MODE;
	}

// get configuration data
else if(SM_USB_UART_CONFIG_MODE==Sm_Usb_Uart)
	{
	if(getsUSBUSART(UsbRxDataBuffer,1))
		{
		buff_config[Configbuffctr]=UsbRxDataBuffer[0];
		Configbuffctr++;
		if(Configbuffctr==5)
			{
			//execute config data here
			TRISC|=0xC0;
			TXSTA=		buff_config[0];
			RCSTA=		buff_config[1];
			BAUDCON=	buff_config[2];
			SPBRGH=		buff_config[3];
			SPBRG=		buff_config[4];
			PIE1=	0x20;
			Sm_Usb_Uart=SM_USB_UART_CONFIG_MODE_OK;
			ResetUsbUartTxBuffers();
			ResetUsbUartRxBuffers();
			}
		}
	}
else if(SM_USB_UART_CONFIG_MODE_OK==Sm_Usb_Uart)
	{
	Sm_Usb_Uart=SM_USB_UART_RUN_MODE;
	if(mUSBUSARTIsTxTrfReady())
		putrsUSBUSART("OK");
	}

else if(SM_USB_UART_RUN_MODE==Sm_Usb_Uart)
	{

	if(getsUSBUSART(UsbRxDataBuffer,1))
		{
		TxBuffer[TxBufferCtrIn]=UsbRxDataBuffer[0];
		TxBufferCtrIn++;
		TxBufferCtrIn&=USBUARTBUFCTRMASK;
		}

	else if(RxBufferCtrIn!=RxBufferCtrOut)
		{
		if( mUSBUSARTIsTxTrfReady() )
			{
			LAT_LED_PIN^=1;
			irToy.usbOut[0]=RxBuffer[RxBufferCtrOut];//answer OK
			putUSBUSART(irToy.usbOut,1);

			RxBufferCtrOut++;
			RxBufferCtrOut&=USBUARTBUFCTRMASK;
			}
		}

	if((TxIf)&&(TxBufferCtrIn!=TxBufferCtrOut))  // If Uart is not full
		{
		TXREG=TxBuffer[TxBufferCtrOut];
		TxBufferCtrOut++;
		TxBufferCtrOut&=USBUARTBUFCTRMASK;
		}

	if(RCSTA&0x06) // error handling
		{
		RCSTAbits.CREN=0;
		RCSTAbits.CREN=1;
		}
	}

// this will contain the routine for receiving and transmit
	return 0;//CONTINUE
}





//high priority interrupt routine
#pragma interrupt Usb2UartInterruptHandlerHigh
void Usb2UartInterruptHandlerHigh (void)
{
// this will contain the RX interrupt FIFO Buffering
if(RcIf)
	{
	RxBuffer[RxBufferCtrIn]=RCREG;
	RxBufferCtrIn++;
	RxBufferCtrIn&=USBUARTBUFCTRMASK;
	}
}


