#include "globals.h"


static u8 BoolLoadBitmap=FALSE;
static u8 BitMapRam[BITMAP_RAM_SZ];

static const u8 * const BitMapPtr=BitMapRam;


u8 *hal_pov_GetBitMapArray()
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


void hal_pov_loadBitmapFromEeToRam()
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

