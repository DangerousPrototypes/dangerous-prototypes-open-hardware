/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
#ifndef RCDECODER_H
#define RCDECODER_H

void ProcessIR(void);
void IRdecoderInterruptHandlerHigh (void);
void SetupRC5(void);

#endif
