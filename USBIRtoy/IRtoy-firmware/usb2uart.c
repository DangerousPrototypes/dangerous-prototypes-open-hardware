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



void Usb2UartSetup(void){

	//send version string
  	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
		irToy.usbOut[0]='U';//answer OK
		irToy.usbOut[1]='0';
		irToy.usbOut[2]='1';
		putUSBUSART(irToy.usbOut,3);
	}

	//setup for USB UART


}


u8 Usb2UartService(void)
{
// this will contain the routine for receiving and transmit
	return 0;//CONTINUE
}



//high priority interrupt routine
#pragma interrupt Usb2UartInterruptHandlerHigh
void Usb2UartInterruptHandlerHigh (void)
{
// this will contain the RX interrupt FIFO Buffering
}


