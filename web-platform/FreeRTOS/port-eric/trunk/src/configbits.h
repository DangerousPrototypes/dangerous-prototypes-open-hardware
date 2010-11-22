// Set configuration bits
#ifndef __dsPIC33FJ128GP204__
	#error Configuration bits set on dsPIC33FJ128GP204 only!
#endif //

#include "p33FJ128GP204.h" 

// Register FBS (0xf80000)                               
//   Boot Segment Data Ram: 		RBS_NO_RAM: No Boot Ram
//   Boot Segment Program Memory: 	BSS_NO_FLASH: No Boot Segment Program Memory
//   Write Protect :				BWRP_WRPROTECT_OFF: Disabled 
_FBS( RBS_NO_RAM & BSS_NO_FLASH & BWRP_WRPROTECT_OFF )


// Register FSS (0xf80002)                               
//   Secure Segment Data Ram:		RSS_NO_RAM: No Secure Ram
//   Secure Segment Program Memory:	SSS_NO_FLASH: No Secure Segment
//   Write Protect :				SWRP_WRPROTECT_OFF: Disabled 
_FSS( RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF )


// Register FGS (0xf80004)                               
//   Code Protect:					GSS_OFF: code protect off
//   Code Protect:					GCP_OFF: Disabled
//   Write Protect:					GWRP_OFF: Disabled
_FGS( GSS_OFF & GCP_OFF & GWRP_OFF )


// Register FOSCSEL (0xf80006)                               
//   Oscillator Source Selection:	FNOSC_FRC: Fast RC oscillator
//   Two-speed Oscillator Startup:	IESO_OFF: Disabled
_FOSCSEL( FNOSC_FRC & IESO_OFF )


// Register FOSC (0xf80008)                               
//   Clock switching and monitor:	FCKSM_CSECMD: Only clock switching enabled
//   Single config for pin select:	IOL1WAY_ON: Allow only one re-configuration
//   OSC2 Pin function:             OSCIOFNC_ON: Digital I/O
//   Oscillator Selection:			POSCMD_NONE: Primary oscillator disabled
_FOSC( FCKSM_CSECMD & IOL1WAY_ON & OSCIOFNC_ON & POSCMD_NONE )


// Register FWDT (0xf8000a)                               
//   Watchdog Timer:				FWDTEN_OFF: Disabled
//   Windowed WDT:					WINDIS_OFF: Disabled
//   Watchdog prescaler:			(N/A) WDTPRE_PR128: 1:128
//   Watchdog postscaler:			(N/A) WDTPOST_PS32768: 1:32,768
_FWDT( FWDTEN_OFF & WINDIS_OFF & WDTPRE_PR128 & WDTPOST_PS32768 )


// Register FPOR (0xf8000c)                               
//   Alternate I2C pins:			ALTI2C_OFF: I2C mapped to SDA1/SCL1
//   Power-on Reset Value:			FPWRT_PWR128: 128ms
_FPOR( ALTI2C_OFF & FPWRT_PWR128 )


// Register FICD (0xf8000e)                               
//   Background Debug Enable Bit:	(set by MPLAB IDE)
//   Debugger/Emulator Enable Bit:	(set by MPLAB IDE)
//   JTAG Enable Bit:				JTAGEN_OFF: JTAG is disabled
//   ICD channel select bits:		ICS_PGD1: use PGC1/EMUC1 and PGD1/EMUD1
_FICD( JTAGEN_OFF & ICS_PGD1 )

//EOF
