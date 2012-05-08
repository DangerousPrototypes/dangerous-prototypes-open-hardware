
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
void Usb2UartService(void);
void Usb2UartInterruptHandlerHigh (void);

#define RcIf                PIR1bits.RCIF
#define TxIf                PIR1bits.TXIF
#define RTSTRISpin          TRISAbits.TRISA1
#define DTRTRISpin          TRISAbits.TRISA2
#define RTSpin              LATAbits.LATA1
#define DTRpin              LATAbits.LATA2
#define HNDSHK_INV_TRISpin  TRISBbits.TRISB5
#define TXRX_INV_TRISpin    TRISBbits.TRISB3
#define HNDSHK_INV_PORTpin  PORTBbits.RB5
#define TXRX_INV_PORTpin    PORTBbits.RB3

#endif
