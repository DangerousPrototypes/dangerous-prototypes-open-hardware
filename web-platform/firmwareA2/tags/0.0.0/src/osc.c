/*****************************************************************************
 *  Oscilator Setup
 *****************************************************************************
 * FileName:        osc.c
 * Processor:       dsPIC33
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Eric Walker			20090405	Initial File Creation
 *****************************************************************************/

#include "proc.h"

void SetupOscilator( void )
{
	// To run at 40MIPS with 7.37MHz internal RC the PLL must be configured
	// and run in FRC w/ PLL mode.  The PLL can not be changed if in use so,
	// start in FRC mode without the PLL, configure the PLL, then
	// switch modes to FRC with PLL.
	// Fosc = Fin * ( M /(N1*N2) ) = 7.37MHz * (43/(2*2)) = 79.2MHz
	// Fcy  = Fosc / 2 = 79.2MHz / 2 = 39.6MHz, or 39.6 MIPS, or 25.2ns
	PLLFBD = 41; 				// M  = 43
	CLKDIVbits.PLLPRE = 0;		// N1 = 2
	CLKDIVbits.PLLPOST = 0;		// N2 = 2
	// the upper byte of OSCCON selects the New oscillator mode
	// use built in function to execute unlock sequence before writing
	__builtin_write_OSCCONH(0b00000001); // NOSC = 0b001, FRC w/ PLL
	// the lsb of the lower byte of OSCCON executes the mode switch
	// use built in function to execute unlock sequence before writing
	__builtin_write_OSCCONL(0b00000001); // OSWEN = 1, execute switch
	while(OSCCONbits.LOCK != 1) // check to see if PLL has locked
		; // wait here till PLL has locked with new oscillator settings
	// Now running at full speed
} //
