/* header */

#include <pic.h>
#include "./eeprom.h"


void EEPROMwrite (unsigned char addr, unsigned char data)
{
	EEADRL=addr;
	EEDATL=data;
	EECON1bits.CFGS=0;				// data eeprom/flash selected
	EECON1bits.EEPGD=0;				// data eeprom
	EECON1bits.WREN=1;				// start write

	GIE=0;							// disable interrupts
	EECON2=0x55;
	EECON2=0xAA;					// magic sequence
	EECON1bits.WR=1;				// start writing
	GIE=1;	
	while(EECON1bits.WR);			// wait untill finished
}

unsigned char EEPROMread(unsigned char addr)
{
	EEADRL=addr;
	EECON1bits.CFGS=0;				// data eeprom/flash selected
	EECON1bits.EEPGD=0;				// data eeprom
	EECON1bits.RD=1;				// start read

	return EEDATL;
}