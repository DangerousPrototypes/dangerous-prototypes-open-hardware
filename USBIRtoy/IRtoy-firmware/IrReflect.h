/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
#ifndef IRREFLECT_H
#define IRREFLECT_H

#define TRIS_IRTX	TRISCbits.TRISC2
#define LAT_IRTX	LATCbits.LATC2


u8 IrReflectService(void);
void IrReflectSetup(void);
void IrReflectionInterruptHandlerHigh (void);
//void irIOInterruptHandlerHigh(void);

#endif
