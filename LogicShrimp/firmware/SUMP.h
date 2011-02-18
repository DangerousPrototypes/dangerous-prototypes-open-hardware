/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
#ifndef SUMP_H
#define SUMP_H

void SUMPlogicCommand(unsigned char inByte);
unsigned char SUMPlogicService(void);
void SUMPInterruptHandlerHigh (void);


#endif
