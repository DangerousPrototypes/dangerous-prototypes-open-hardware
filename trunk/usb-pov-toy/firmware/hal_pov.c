#include "globals.h"

volatile u8 hal_pov_u8endflag=FALSE;

static u8 hal_pov_pixelctr=0;

static u8 BoolLoadBitmap=FALSE;
static u8 BitMapRam[BITMAP_RAM_SZ];

static const u8 * const BitMapPtr=BitMapRam;

static volatile HAL_ACL_DIRECTION forward_reverse_state=ACL_FORWARD;

// store all the image data in program memory (ROM)
// instead of RAM (the default)
static volatile u8 POV_HELLO[]={ //35
	0b00000000,
	0b00000000,
	0b11111111,
	0b00011000,
	0b00011000,
	0b00011000,
	0b11111111,
	0b00000000,
	0b00000000,
	0b11111111,
	0b10011001,
	0b10011001,
	0b10011001,
	0b10000000,
	0b00000000,
	0b11111111,
	0b00000001,
	0b00000001,
	0b00000001,
	0b00000001,
	0b00000000,
	0b00000000,
	0b11111111,
	0b00000001,
	0b00000001,
	0b00000001,
	0b00000001,
	0b00000001,
	0b00000000,
	0b11111111,
	0b10000001,
	0b10000001,
	0b10000001,
	0b10000001,
	0b11111111,
};



void hal_pov_SetState(HAL_ACL_DIRECTION state)
{
forward_reverse_state=state;
}

void hal_pov_StartCycle(void)
{
hal_pov_pixelctr=0;
}

void hal_pov_setupTmr0(void)
{
//setup timer 0
T0CON=0;
//configure prescaler
//bit 2-0 T0PS2:T0PS0: Timer0 Prescaler Select bits
//111 = 1:256 Prescale value
//110 = 1:128 Prescale value
//101 = 1:64 Prescale value
//100 = 1:32 Prescale value
//011 = 1:16 Prescale value
//010 = 1:8 Prescale value
//001 = 1:4 Prescale value
//000 = 1:2 Prescale value
T0CON=0b100;
//T0CONbits.T08BIT=1; //16bit mode
//internal clock
//low to high
T0CONbits.PSA=0; //1=not assigned

TMR0H=0;//first set the high byte
TMR0L=0;//set low byte copies high byte too
TM0IE=0;
TM0IF=0;
TM0ON=1;//enable the timer
}


void hal_pov_setupTmr1(void)
{

//bit 5-4 T1CKPS<1:0>: Timer1 Input
//11 = 1:8 Prescale value
//10 = 1:4 Prescale value
//01 = 1:2 Prescale value
//00 = 1:1 Prescale value
T1CON=0b00000000;//8x prescaler
T1IF=0;
T1IE=1;
}


u8 *hal_pov_GetBitMapArray(void)
{
return BitMapPtr;
}


u8 hal_pov_LoadBitmapCheck(void)
{
return BoolLoadBitmap;
}


void hal_pov_adjustTimerRefresh()
{
//TODO
}


#if 0
void hal_pov_setupIntFromAclPin(void)
{
// TODO this is for the interrupt of accelerometer
}
#endif


void hal_pov_loadBitmapFromEeToRam(u8 num)
{
// TODO
}


void hal_pov_displayBitmap()
{
// TODO this will use
}


void hal_pov_checkButtonAndChangeBitmap(void)
{
// TODO
}

/////////////////////// INTERRUPT ROUTINE /////////////////////////////
// TODO TO BE ADJUSTED, RENAMED and FILLED IN


#pragma interrupt POVInterrupt
void POVInterrupt(void)
{
if(INTCONbits.TMR0IE&&INTCONbits.TMR0IF)
	{
	//code here
	INTCONbits.TMR0IF=0;
	}
if(PIE1bits.TMR1IE&&PIR1bits.TMR1IF)
	{
	//code here
		hal_pov_pixelctr++;
		if(hal_pov_pixelctr>=sizeof(POV_HELLO))
			{
			hal_pov_pixelctr=0; //sizeof(POV_HELLO)-1; // put it in safe index (not to overflow or underflow the array)
			HAL_POV_PORT=0x00;
			T1ON=0;
			}else{
			HAL_POV_PORT=POV_HELLO[hal_pov_pixelctr];
			}

	//end of code

	PIR1bits.TMR1IF=0;
	}
INTCONbits.GIEH = 1;
}

