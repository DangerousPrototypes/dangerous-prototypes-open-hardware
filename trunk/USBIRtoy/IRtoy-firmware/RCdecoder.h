/*
*
*	USB infrared remote control receiver transmitter firmware
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
void ProcessIR(void);
void IRdecoderInterruptHandlerHigh (void);
void SetupRC5(void);
void IRmanString(void);
