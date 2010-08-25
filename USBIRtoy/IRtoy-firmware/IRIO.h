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

#endif
