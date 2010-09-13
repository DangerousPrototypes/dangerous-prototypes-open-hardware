/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/

#include "globals.h"


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


//setup for USB UART
void Usb2UartSetup(void){
if(mUSBUSARTIsTxTrfReady())
	{
	irToy.usbOut[0]='U';//answer OK
	irToy.usbOut[1]='0';
	irToy.usbOut[2]='1';
	putUSBUSART(irToy.usbOut,3);
	}
Sm_Usb_Uart=SM_USB_UART_FLUSH_BUFFER;
Configbuffctr=0;
}



// to go back to the other default, user must unplug USB IR Toy
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

switch (Sm_Usb_Uart)
	{
	// TODO enhancement: convert to switch case
	case SM_USB_UART_FLUSH_BUFFER:
		{
		FlushUsbRx();
		Sm_Usb_Uart=SM_USB_UART_CONFIG_MODE;
		break;
		}

	// get configuration data
	case SM_USB_UART_CONFIG_MODE:
		{
		if(getsUSBUSART(UsbRxDataBuffer,1))
			{
			buff_config[Configbuffctr]=UsbRxDataBuffer[0];
			Configbuffctr++;
			if(Configbuffctr==5)
				{
				//execute config data here
				TRISC|=		0xC0;
				TXSTA=		buff_config[0];
				RCSTA=		buff_config[1];
				BAUDCON=	buff_config[2];
				SPBRGH=		buff_config[3];
				SPBRG=		buff_config[4];
				PIE1=		0x20;
				Sm_Usb_Uart=SM_USB_UART_CONFIG_MODE_OK;
				ResetUsbUartTxBuffers();
				ResetUsbUartRxBuffers();
				}
			}
		break;
		}

	case SM_USB_UART_CONFIG_MODE_OK:
		{
		Sm_Usb_Uart=SM_USB_UART_RUN_MODE;
		if(mUSBUSARTIsTxTrfReady())
			putrsUSBUSART("OK");
		break;
		}

	case SM_USB_UART_RUN_MODE:
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
				LAT_LED_PIN^=1; // toggle led every sending
				irToy.usbOut[0]=RxBuffer[RxBufferCtrOut];//answer OK
				putUSBUSART(irToy.usbOut,1);

				RxBufferCtrOut++;
				RxBufferCtrOut&=USBUARTBUFCTRMASK;
				}
			}
		break;
		}
	} // end of switch

	if((TxIf)&&(TxBufferCtrIn!=TxBufferCtrOut))  // If Uart is not full and no data to be sent
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


