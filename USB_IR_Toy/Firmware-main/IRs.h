/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/

#ifndef IRS_H
#define IRS_H

BYTE irsService(void);
void irsSetup(void);
void irsInterruptHandlerHigh(void);
void IRs_HandleParms(BYTE cnt, BYTE cmd);
void Usb2Uart_InitUart(void);
void Usb2Uart_CloseUart(void);
void cleanup(void);

#endif
