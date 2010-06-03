/*
*
*	Dangerous Prototypes Flash Destroyer firmware
*	License: creative commons - attribution, share-alike
* 	http://creativecommons.org/licenses/by-sa/2.0/
*	Copyright 2010
*	http://dangerousprototypes.com
*/

#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_


#define HAL_TIMER_T0CON_VAL 0xC4 // 20MHz, prescaler value=32, TMR0 overflow @ 0.003277 seconds


#if 0
#define hal_Timer_Init()	RCON=0; \
	INTCON2=0xFF; \
	INTCON=0xA0; \
	T0CON=HAL_TIMER_T0CON_VAL;
#endif


#if 1
void hal_Timer_Init(void);
void hal_Timer_Disable(void);
#endif


#endif /* HAL_TIMER_H_ */

///////////////////////
