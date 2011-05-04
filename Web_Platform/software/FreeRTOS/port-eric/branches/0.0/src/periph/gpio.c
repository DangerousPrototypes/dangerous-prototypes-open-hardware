/*****************************************************************************
 *  General purpous digital input/output pin functions
 *****************************************************************************
 * FileName:        gpio.c
 * Processor:       dsPIC33
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Eric Walker			20101120	Initial File Creation
 *****************************************************************************/

#include "../proc.h"
#include "gpio.h"

void SetupGPIO(void)
{
		/* Disable ADC peripheral module setting all pins to digital IO */
		PMD1bits.AD1MD = 1;

        /* ADC Port Configuration, set individual pins if using ADC module */
        AD1PCFGL = 0xFFFF;

        /* Configure LED port pins as outputs */
        LD1_TRIS = 0;
		LD2_TRIS = 0;
		SD_TRIS = 0;
 
        /* Set LED power-on defult states */
        LD1_IO = 1; /* On */
		LD2_IO = 0;
		SD_IO = 0;

		/* Set SD card CS as output and inactive(high) */
		SD_CS_TRIS = 0;
		SD_CS = 1;

		/* Set EEPROM CS as output and inactive(high) */
		EEPROM_CS_TRIS = 0;
		EEPROM_CS_IO = 1;
	
} /* SetupGPIO() */

/*EOF*/
