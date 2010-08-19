#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

//configuration fuse setting
#if defined(THIS_IS_STACK_APPLICATION)
_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE)		//HACKADAY: this is our custom oscillator configuration
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx3) //HACKADAY: define debugging pin pair 3, watchdog, jtag disabled.
#endif

//processor speed
#define GetSystemClock()		(32000000ul)
#define GetInstructionClock()	(GetSystemClock()/2)
#define GetPeripheralClock()	GetInstructionClock()

//HACKADAY:we use a SPI interface. hardware is setup below....
#define USE_SD_INTERFACE_WITH_SPI       // SD-SPI.c and .h

//HACKADAY:	define the SPI interface to use with the SD card
#define SD_CS				LATBbits.LATB8
#define SD_CS_TRIS			TRISBbits.TRISB8
#define SD_CD				PORTBbits.RB12
#define SD_CD_TRIS			TRISBbits.TRISB12

//No write enable on uSD hardware
#define SD_WE			PORTBbits.RB7
#define SD_WE_TRIS		TRISBbits.TRISB7
        
//SPI module setup
#define SPICON1				SPI2CON1
#define SPISTAT				SPI2STAT
#define SPIBUF				SPI2BUF
#define SPISTAT_RBF			SPI2STATbits.SPIRBF
#define SPICON1bits			SPI2CON1bits
#define SPISTATbits			SPI2STATbits
#define SPIENABLE           SPI2STATbits.SPIEN

//TRIS for SCK/SDI/SDO lines
#define SPICLOCK			TRISBbits.TRISB10
#define SPIIN				TRISBbits.TRISB11
#define SPIOUT				TRISBbits.TRISB9

// Peripheral Pin Select Outputs
#define NULL_IO		0
#define C1OUT_IO	1
#define C2OUT_IO	2
#define U1TX_IO		3
#define U1RTS_IO	4
#define U2TX_IO		5
#define U2RTS_IO	6
#define SDO1_IO		7
#define SCK1OUT_IO	8
#define SS1OUT_IO	9
#define SDO2_IO		10
#define SCK2OUT_IO	11
#define SS2OUT_IO	12
#define OC1_IO		18
#define OC2_IO		19
#define OC3_IO		20
#define OC4_IO		21
#define OC5_IO		22

#endif
