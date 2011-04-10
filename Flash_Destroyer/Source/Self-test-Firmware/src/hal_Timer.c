/*
*
*	Dangerous Prototypes Flash Destroyer firmware
*	License: creative commons - attribution, share-alike
* 	http://creativecommons.org/licenses/by-sa/2.0/
*	Copyright 2010
*	http://dangerousprototypes.com
*/
#include "globals.h"


#if 1
void hal_Timer_Init(void)
{
RCON=0;
INTCON2=0xFF;
INTCON=0xA0;
T0CON=HAL_TIMER_T0CON_VAL;
}
#endif

#if 0
void hal_Timer_Disable(void)
{
INTCONbits.TMR0IE=0;
}
#endif

/////////////
