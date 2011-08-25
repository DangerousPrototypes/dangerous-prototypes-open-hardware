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

//void SUMPlogicCommand(void);
//unsigned char SUMPlogicService(void);
void SUMPInterruptHandlerHigh (void);

#define SUMP_8CH

#ifdef SUMP_8CH
#define SUMP_SAMPLE_SIZExx 0x1000 //0x0080 //(SAMPLE_ARRAY_SIZE*0x0008)
#endif

#ifndef SUMP_8CH
#define SUMP_SAMPLE_ARRAY_SIZE 0x0080 //0x0010
#define SUMP_SAMPLE_SIZE 0x0400 //0x0080 //(SAMPLE_ARRAY_SIZE*0x0008)
#endif
#endif
