/* header */

#include <pic.h>
#include "./dac.h"


void enableDAC(void)
{
	DACCON0=0b10100000;		// dacen, !lps, dacout, v+=vdd, v-=vss
}

void disableDAC(void)
{
	DACCON1=0x00;
}

void setDAC(unsigned char dac)
{
	DACCON1=dac&0x1F;
}
