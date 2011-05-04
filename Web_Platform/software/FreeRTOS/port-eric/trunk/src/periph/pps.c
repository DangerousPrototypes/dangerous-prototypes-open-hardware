/*****************************************************************************
 *  Peripheral Pin Select
 *****************************************************************************
 * FileName:        pps.c
 * Processor:       dsPIC33
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Eric Walker			20090405	Initial File Creation
 * Eric Walker			20101112	Update for Web Platform Project HWv1.1
 *****************************************************************************/

#include "../proc.h"
#include "ppsdef.h"


void SetupPeripheralPinSelect(void)
{
	PPSUnLock; /* Unlock PPS Registers */
	
	/* Configure UART 1 Pins for the Console */
	PPSInput( PPS_U1RX, PPS_RP14);
	PPSOutput(PPS_U1TX, PPS_RP15);
	
	/* Configure SSP 1 Pins for the Ethernet nic */
	PPSInput( PPS_SDI1, PPS_RP18);
	PPSOutput(PPS_SDO1, PPS_RP17);
	PPSOutput(PPS_SCK1, PPS_RP16);

	/*********************************************
	* Serial Peripheral Interface (SPI) 2 can not
	* be used for the SD Card and the EEPROM at 
	* the same time.  It must be assigned to one
	* or the other.  Uncomment only one below.
	*********************************************/

	/* Configure SSP 2 Pins for the SD Card */
	PPSInput( PPS_SDI2, PPS_RP10);
	PPSOutput(PPS_SDO2, PPS_RP12);
	PPSOutput(PPS_SCK2, PPS_RP11);

	/* Configure SSP 2 Pins for the EEPROM */
/*	PPSInput( PPS_SDI2, PPS_RP24);
	PPSOutput(PPS_SDO2, PPS_RP9);
	PPSOutput(PPS_SCK2, PPS_RP22);
*/
	PPSLock; /* Lock PPS Registers */
}
/*EOF*/
