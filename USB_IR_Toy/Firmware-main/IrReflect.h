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


#define RBINTERRUPTCOUNTLIMIT	10

#define IsRbCountExceeded()	(RBInterruptCount>RBINTERRUPTCOUNTLIMIT)

#define EnablePortbChangeInterrupt() IRRX_IF=0; IRRX_IE=1;
#define DisablePortbChangeInterrupt() IRRX_IE=0;

#define IrTxTurnOn()  			TRIS_IRTX=0
#define IrTxTurnOff()			TRIS_IRTX=1

typedef enum
{
	TX_LED_TURN_OFF=0,
	TX_LED_TURN_ON
}SM_TX_LED_STATE;

u8 IrReflectService(void);
void IrReflectSetup(void);
void IrReflectionInterruptHandlerHigh (void);

#endif
