/* header */

#include <pic.h>
#include "./adc.h"

// do an adc conversion on specific adc
// 1-32
// AN3= analogue in * 3/3
// AN8= analogue in * 2/3
// AN9= analogue in * 1/3
// AN29= temperature
// AN30= DAC
// AN31= FVR buffer
// function assumes analoge inputs setup 
unsigned int getADC(unsigned char adc)
{
	unsigned char temp;
	int i;
	switch (adc)
	{
		case 0:
			adc=3;
			break;
		case 1:
			adc=8;
			break;
		case 2:
			adc =9;
			break;
		case 3:
			adc=0b11101;
			break;
		default:
			return 0;
	}


	ADCON1=0b11000000;		// left justified, fosc/4, v-=vss, v+=vdd
	adc&=0x1F;				// only 32 channels
	ADCON0=0x01|(adc<<2);	// select proper channel, turn on adc

	for(i=0; i<4; i++) asm("nop");		// some sort of delay needed? arounf 4.4us

	ADCON0bits.ADGO=1;
	while(ADCON0bits.ADGO);

	ADCON0&=0xFE;			// turn off adc
	temp = (ADRESH<<6)|(ADRESL>>2);
	return temp;
}

// enable on-die temperature sensor
void enableTS(void)
{
	FVRCON|=0b00100000;			// TSEN=1
	FVRCON&=0b11101111;			// TSRNG=0 (my compiler didn't had a define for it)
}

unsigned int startADC16(unsigned char adc)
{
	unsigned char temp;
	int i;
	switch (adc)
	{
		case 0:
			adc=3;
			break;
		case 1:
			adc=8;
			break;
		case 2:
			adc =9;
			break;
		case 3:
			adc=0b11101;
			break;
		default:
			return 0;
	}


	ADCON1=0b11000000;		// left justified, fosc/4, v-=vss, v+=vdd
	adc&=0x1F;				// only 32 channels
	ADCON0=0x01|(adc<<2);	// select proper channel, turn on adc

	for(i=0; i<4; i++) asm("nop");		// some sort of delay needed? arounf 4.4us
}