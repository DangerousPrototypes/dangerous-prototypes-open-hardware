/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
#ifndef IRIO_H
#define IRIO_H

unsigned char irIOservice(void);
void irIOsetup(void);
void irIOInterruptHandlerHigh(void);


#define RcIf	PIR1bits.RCIF
#define TxIf	PIR1bits.TXIF

#define LAT_LED_PIN		LATAbits.LATA0

#define UsbRxDataBuffer  irToy.s

#define USBUARTBUFCTRMASK 0x07
#define BUFSZ	10

#define ResetUsbUartTxBuffers() TxBufferCtrIn=0;TxBufferCtrOut=0;
#define ResetUsbUartRxBuffers() RxBufferCtrIn=0;RxBufferCtrOut=0;

#define FlushUsbRx() getsUSBUSART(irToy.s,64)

#endif
