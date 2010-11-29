#include "globals.h"


static u8 BoolLoadBitmap=FALSE;
static u8 BitMapRam[BITMAP_RAM_SZ];

static const u8 * const BitMapPtr=BitMapRam;

// store all the image data in program memory (ROM)
// instead of RAM (the default)
static u8 pov[]={ //35
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
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b00000000,
	0b00000000,
	0b11111111,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b00000000,
	0b11111111,
	0b10000001,
	0b10000001,
	0b10000001,
	0b10000001,
	0b11111111,
};


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
void MyInterrupt(void);

#pragma interrupt MyInterrupt
void MyInterrupt(void)
{
  /* perform interrupt function here */
}

