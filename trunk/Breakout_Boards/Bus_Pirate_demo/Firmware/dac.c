/* header */

#include <pic.h>
#include "./dac.h"


void enableDAC(void)
{
	DACCON0=0b11100000;		// dacen, !lps, dacout, v+=vdd, v-=vss
				//76543210
	//DACCON1=	0b00000111;
	
}

void disableDAC(void)
{
	DACCON1=0x00;
}

void setDAC(unsigned char dac)
{
	DACCON1=dac&0x1F;
}
