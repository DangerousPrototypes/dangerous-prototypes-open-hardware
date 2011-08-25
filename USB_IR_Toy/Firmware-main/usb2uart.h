


/*
*
*       USB infrared remote control receiver transmitter firmware v1.0
*       License: creative commons - attribution, share-alike
*       Copyright Ian Lesnet 2010
*       http://dangerousprototypes.com
*
*/
#ifndef USB2UART_H
#define USB2UART_H

void Usb2UartSetup(void);
BYTE Usb2UartService(void);
void Usb2UartInterruptHandlerHigh (void);

void Usb2Uart_InitUart(BYTE InitRx);
void Usb2Uart_CloseUart(void);

#define RcIf    PIR1bits.RCIF
#define TxIf    PIR1bits.TXIF

#define UsbRxDataBuffer  irToy.s

#define USBUARTBUFCTRMASK 0x07
#define BUFSZ   10

#define ResetUsbUartTxBuffers() TxBufferCtrIn=0;TxBufferCtrOut=0;
#define ResetUsbUartRxBuffers() RxBufferCtrIn=0;RxBufferCtrOut=0;

#define FlushUsbRx() getUnsignedCharArrayUsbUart(irToy.s,64)

#endif
