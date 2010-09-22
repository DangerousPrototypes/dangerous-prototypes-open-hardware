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
	//putUSBUSART(irToy.usbOut,3);
	putUnsignedCharArrayUsbUsart(irToy.usbOut,3);
	}
Sm_Usb_Uart=SM_USB_UART_FLUSH_BUFFER;
Configbuffctr=0;
}



#if defined(USB_CDC_SET_LINE_CODING_HANDLER)
void mySetLineCodingHandler(void)
{
    //If the request is not in a valid range
    if(cdc_notice.GetLineCoding.dwDTERate.Val > 115200)
    {
        //NOTE: There are two ways that an unsupported baud rate could be
        //handled.  The first is just to ignore the request and don't change
        //the values.  That is what is currently implemented in this function.
        //The second possible method is to stall the STATUS stage of the request.
        //STALLing the STATUS stage will cause an exception to be thrown in the
        //requesting application.  Some programs, like HyperTerminal, handle the
        //exception properly and give a pop-up box indicating that the request
        //settings are not valid.  Any application that does not handle the
        //exception correctly will likely crash when this requiest fails.  For
        //the sake of example the code required to STALL the status stage of the
        //request is provided below.  It has been left out so that this demo
        //does not cause applications without the required exception handling
        //to crash.
        //---------------------------------------
        USBStallEndpoint(0,1);
    }
    else
    {
        DWORD_VAL dwBaud;

        //Update the baudrate info in the CDC driver
        CDCSetBaudRate(cdc_notice.GetLineCoding.dwDTERate.Val);

        //Update the baudrate of the UART
        //FOSC/[4 (n + 1)]
        //MyBaudRate=line_coding.dwDTERate.Val;

		dwBaud.Val = (CLOCK_FREQ/4)/line_coding.dwDTERate.Val-1; // TODO: must check this...

		SPBRG = dwBaud.v[0];
		SPBRGH = dwBaud.v[1];
    }
}
#endif


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
	case SM_USB_UART_FLUSH_BUFFER:
		{
		FlushUsbRx();
		Sm_Usb_Uart=SM_USB_UART_CONFIG_MODE;
		break;
		}

	// get configuration data
	case SM_USB_UART_CONFIG_MODE:
#if 0
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
		}
		break;
#else
		{
		//DWORD_VAL dwBaud;

		//mySer.write(chr(0)) #SPBRGH
		//mySer.write(chr(0x0F)) #SPBRG

		TRISC|=		0xC0;
		TXSTA=		0x24;
		RCSTA=		0x90;
		BAUDCON=	0;
		//SPBRGH=		buff_config[3];
		//SPBRG=		buff_config[4];
		//CDCSetBaudRate(cdc_notice.GetLineCoding.dwDTERate.Val);
		//dwBaud.Val = (CLOCK_FREQ/4)/line_coding.dwDTERate.Val-1;
		//SPBRG = dwBaud.v[0];
		//SPBRGH = dwBaud.v[1];
//        SPBRG = 0x71;
//        SPBRGH = 0x02;      	// 0x0271 for 48MHz -> 19200 baud
		PIE1=		0x20;
		Sm_Usb_Uart=SM_USB_UART_CONFIG_MODE_OK;
		ResetUsbUartTxBuffers();
		ResetUsbUartRxBuffers();
		break;
		}
#endif

	case SM_USB_UART_CONFIG_MODE_OK:
		{
		Sm_Usb_Uart=SM_USB_UART_RUN_MODE;
		if(mUSBUSARTIsTxTrfReady())
			{
			//putrsUSBUSART("OK");
#if 0
			irToy.usbOut[0]='O';//answer OK
			irToy.usbOut[1]='K';
			//irToy.usbOut[2]=SPBRG; // for debugging purpose
			//irToy.usbOut[3]=SPBRGH;
			irToy.usbOut[2]=MyBaudRate; // for debugging purpose
			irToy.usbOut[3]=MyBaudRate>>8;
			irToy.usbOut[2]=MyBaudRate>>16; // for debugging purpose
			irToy.usbOut[3]=MyBaudRate>>24;


			putUnsignedCharArrayUsbUsart(irToy.usbOut,6);
#else
			irToy.usbOut[0]='O';//answer OK
			irToy.usbOut[1]='K';
			putUnsignedCharArrayUsbUsart(irToy.usbOut,2);
#endif

			}
		break;
		}

	case SM_USB_UART_RUN_MODE:
		{
		if(getUnsignedCharArrayUsbUart(UsbRxDataBuffer,1))
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
				putUnsignedCharArrayUsbUsart(irToy.usbOut,1);

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


