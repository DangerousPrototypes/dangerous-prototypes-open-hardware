/*
	Test program for DOSFS
	Kister Genesis Jimenez
*/

#include <stdio.h>

#include "HardwareProfile.h"
#include "dsPICSDRoutines.h"
#include "dosfs.h"

_FOSCSEL(FNOSC_FRCPLL)		//INT OSC with PLL (always keep this setting)
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)	//disable external OSC (always keep this setting)
_FWDT(FWDTEN_OFF)				//watchdog timer off
_FICD(JTAGEN_OFF & ICS_PGD1);//JTAG debugging off, debugging on PG1 pins enabled


int main(void)
{
	uint8_t sector[SECTOR_SIZE], sector2[SECTOR_SIZE];
	uint32_t pstart, psize, i;
	uint8_t pactive, ptype;
	VOLINFO vi;
	DIRINFO di;
	DIRENT de;
	uint32_t cache;
	FILEINFO fi;
	uint8_t *p;
    
    AD1PCFGL = 0xFFFF; //digital pins

	//setup internal clock for 80MHz/40MIPS
	//7.37/2=3.685*43=158.455/2=79.2275
	CLKDIVbits.PLLPRE=0; // PLLPRE (N2) 0=/2 
	PLLFBD=41; //pll multiplier (M) = +2
	CLKDIVbits.PLLPOST=0;// PLLPOST (N1) 0=/2
    
    
    while(!OSCCONbits.LOCK);//wait for PLL ready

    initSD();
	
	while(1)
	{
	
	}
	return 0;
}
