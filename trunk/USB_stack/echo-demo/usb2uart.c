/*
 *
 *	USB infrared remote control receiver transmitter firmware v1.0
 *	License: creative commons - attribution, share-alike
 *	Copyright Ian Lesnet 2010
 *	http://dangerousprototypes.com
 *
 */

#include "globals.h"

extern BYTE cdc_In_buffer[64];
extern BDentry *Inbdp;

typedef enum {
    SM_USB_UART_CONFIG_MODE = 0,
    SM_USB_UART_CONFIG_MODE_OK,
    SM_USB_UART_RUN_MODE,
    SM_USB_UART_FLUSH_BUFFER

} _Sm_Usb_Uart;

static _Sm_Usb_Uart Sm_Usb_Uart;
static BYTE Configbuffctr;


static BYTE TxBuffer[BUFSZ], TxBufferCtrIn, TxBufferCtrOut;
static volatile BYTE RxBuffer[BUFSZ], RxBufferCtrIn, RxBufferCtrOut;


//setup for USB UART

void Usb2UartSetup(void) {
    //  if (WaitInReady()) {
    WaitInReady();
    cdc_In_buffer[0] = 'U'; //answer OK
    cdc_In_buffer[1] = '0';
    cdc_In_buffer[2] = '1';
    putUnsignedCharArrayUsbUsart(cdc_In_buffer, 3);
    // }
    Sm_Usb_Uart = SM_USB_UART_CONFIG_MODE;
    Configbuffctr = 0;
}

void Usb2Uart_InitUart(BYTE InitRx) {
    TRISC |= 0xC0;
    TXSTA = 0x24; //baudrate high
    RCSTA = (InitRx == TRUE) ? 0x90 : 0x00;
    //RCSTA=		0x90;
    BAUDCON = 0x08; // baud16
    PIE1 = 0x20;
    ResetUsbUartTxBuffers();
    ResetUsbUartRxBuffers();
}

void Usb2Uart_CloseUart(void) {
    TXSTA = 0;
    RCSTA = 0;
}

#if 0

u8 Usb2UartPrepareTxData(void) {
    if (getUnsignedCharArrayUsbUart(UsbRxDataBuffer, 1)) {
        TxBuffer[TxBufferCtrIn] = UsbRxDataBuffer[0];
        TxBufferCtrIn++;
        TxBufferCtrIn &= USBUARTBUFCTRMASK;
        return TRUE;
    }
    return FALSE;
}

void Usb2UartSendTxDataFromBuff(void) {
    if ((TxIf) && (TxBufferCtrIn != TxBufferCtrOut)) // If Uart is not full and no data to be sent
    {
        TXREG = TxBuffer[TxBufferCtrOut];
        TxBufferCtrOut++;
        TxBufferCtrOut &= USBUARTBUFCTRMASK;
    }
}
#endif


// to go back to the other default, user must unplug USB IR Toy

BYTE Usb2UartService(void) {
    switch (Sm_Usb_Uart) {
            // get configuration data
        case SM_USB_UART_CONFIG_MODE:
        {
            usbbufflush();
            Usb2Uart_InitUart(TRUE);
            Sm_Usb_Uart = SM_USB_UART_CONFIG_MODE_OK;
            break;
        }

        case SM_USB_UART_CONFIG_MODE_OK:
        {
            Sm_Usb_Uart = SM_USB_UART_RUN_MODE;
            break;
        }

        case SM_USB_UART_RUN_MODE:
        {
#if 1
            if (getUnsignedCharArrayUsbUart(UsbRxDataBuffer, 1)) {
                TxBuffer[TxBufferCtrIn] = UsbRxDataBuffer[0];
                TxBufferCtrIn++;
                TxBufferCtrIn &= USBUARTBUFCTRMASK;
            }
#endif

            if (RxBufferCtrIn != RxBufferCtrOut)
                //if ((Usb2UartPrepareTxData()==FALSE) && (RxBufferCtrIn!=RxBufferCtrOut))
            {
                //if( WaitInReady() )				{
                WaitInReady();
                LedToggle(); // toggle led every sending
                cdc_In_buffer[0] = RxBuffer[RxBufferCtrOut]; //answer OK
                putUnsignedCharArrayUsbUsart(cdc_In_buffer, 1);

                RxBufferCtrOut++;
                RxBufferCtrOut &= USBUARTBUFCTRMASK;
                //}
            }
            break;
        }
    } // end of switch

#if 1
    if ((TxIf) && (TxBufferCtrIn != TxBufferCtrOut)) // If Uart is not full and no data to be sent
    {
        TXREG = TxBuffer[TxBufferCtrOut];
        TxBufferCtrOut++;
        TxBufferCtrOut &= USBUARTBUFCTRMASK;
    }
#endif
    if (RCSTA & 0x06) // error handling
    {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }

    // this will contain the routine for receiving and transmit
    return 0; //CONTINUE
}

//high priority interrupt routine
// #pragma interrupt Usb2UartInterruptHandlerHigh

void Usb2UartInterruptHandlerHigh(void) {
    // this will contain the RX interrupt FIFO Buffering
    if (RcIf) {
        RxBuffer[RxBufferCtrIn] = RCREG;
        RxBufferCtrIn++;
        RxBufferCtrIn &= USBUARTBUFCTRMASK;
    }
}


