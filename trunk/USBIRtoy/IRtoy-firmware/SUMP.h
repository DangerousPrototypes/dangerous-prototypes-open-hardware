/*
*
*	USB infrared remote control receiver transmitter firmware
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
void SUMPlogicCommand(unsigned char inByte);
unsigned char SUMPlogicService(void);
void SUMPInterruptHandlerHigh (void);
