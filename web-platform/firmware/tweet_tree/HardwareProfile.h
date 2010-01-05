#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

//configuration fuse setting
#if defined(THIS_IS_STACK_APPLICATION)
_FOSCSEL(FNOSC_FRCPLL)			// PLL enabled
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)	// XT Osc
_FWDT(FWDTEN_OFF)				// Disable Watchdog timer
_FICD(JTAGEN_OFF & 0b11);//0b11=ICD_PGx1
//_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE)		//HACKADAY: this is our custom oscillator configuration
//_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx3) //HACKADAY: define debugging pin pair 3, watchdog, jtag disabled.
#endif

// dsPIC33F processor
#define GetSystemClock()		(40000000ul)      // Hz
#define GetInstructionClock()	(GetSystemClock()/2)
#define GetPeripheralClock()	GetInstructionClock()

//HACKADAY: LED0 is server status LED,
// LED1 is SD card activity LED
// Hardware mappings
// LED I/O pins
//LED on RA2 and RB7
#define LED0_TRIS			TRISAbits.TRISA8		// LD1
#define LED0_IO				LATAbits.LATA8
#define LED1_TRIS			TRISAbits.TRISA9		// LD2
#define LED1_IO				LATAbits.LATA9		
#define LED2_TRIS			TRISAbits.TRISA10 		//SD LED		
#define LED2_IO				LATAbits.LATA10

#define LED_GET() (0)
#define LED_PUT(a)					

//custom pin assignments for our hardware
// ENC28J60 I/O pins
//mapping:
//A2 ETH-INT
//C2 MISO
//C1 MOSI
//C0 CLK
//B3 CS
//B2 RST
//CS and RST pins
#define ENC_RST_TRIS		(TRISBbits.TRISB2)	
#define ENC_RST_IO			(PORTBbits.RB2)
#define ENC_CS_TRIS			(TRISBbits.TRISB3)
#define ENC_CS_IO			(PORTBbits.RB3)
//assign SPI module to ENC28J60
#define ENC_SPI_IF			(IFS0bits.SPI1IF)
#define ENC_SSPBUF			(SPI1BUF)
#define ENC_SPISTAT			(SPI1STAT)
#define ENC_SPISTATbits		(SPI1STATbits)
#define ENC_SPICON1			(SPI1CON1)
#define ENC_SPICON1bits		(SPI1CON1bits)
#define ENC_SPICON2			(SPI1CON2)

#define USE_SD_INTERFACE_WITH_SPI       // SD-SPI.c and .h

//define the SPI interface to use with the SD card
#define SD_CS				LATBbits.LATB13
#define SD_CS_TRIS			TRISBbits.TRISB13
//#define SD_CD				PORTAbits.RA2
//#define SD_CD_TRIS			TRISAbits.TRISA2

//No write enable on this hardware
//#define SD_WE				PORTBbits.RB4
//#define SD_WE_TRIS			TRISBbits.TRISB4

//SPI module setup
#define SPICON1				SPI2CON1
#define SPISTAT				SPI2STAT
#define SPIBUF				SPI2BUF
#define SPISTAT_RBF			SPI2STATbits.SPIRBF
#define SPICON1bits			SPI2CON1bits
#define SPISTATbits			SPI2STATbits
#define SPIENABLE           SPI2STATbits.SPIEN

//TRIS for SCK/SDI/SDO lines
#define SPICLOCK			TRISBbits.TRISB11
#define SPIIN				TRISBbits.TRISB10
#define SPIOUT				TRISBbits.TRISB12

//EEPROM setup
#define EE_CS				LATCbits.LATC7
#define EE_CS_TRIS			TRISCbits.TRISC7

// PPS input registers RPINR20bits.SDI1R
#define INT1R_I	RPINR0bits.INT1R
#define INT2R_I RPINR1bits.INT2R
#define T2CKR_I RPINR3bits.T2CKR
#define T3CKR_I RPINR3bits.T3CKR
#define T4CKR_I RPINR4bits.T4CKR
#define T5CKR_I RPINR4bits.T5CKR
#define IC1R_I RPINR7bits.IC1R
#define IC2R_I RPINR7bits.IC2R
#define IC7R_I RPINR10bits.IC7R
#define IC8R_I RPINR10bits.IC8R
#define OCFAR_I RPINR11bits.OCFAR
#define U1CTSR_I RPINR18bits.U1CTSR
#define U1RXR_I RPINR18bits.U1RXR
#define U2CTSR_I RPINR19bits.U2CTSR
#define U2RXR_I RPINR19bits.U2RXR
#define SDI1R_I RPINR20bits.SDI1R
#define SCK1R_I RPINR20bits.SCK1R
#define SS1R_I RPINR21bits.SS1R
#define SDI2R_I RPINR22bits.SDI2R
#define SCK2R_I RPINR22bits.SCK2R
#define SS2R_I RPINR23bits.SS2R


// Peripheral Pin Select Outputs
#define NULL_O		0
#define C1OUT_O		1
#define C2OUT_O		2
#define U1TX_O		3
#define U1RTS_O		4
#define U2TX_O		5
#define U2RTS_O		6
#define SDO1_O		7
#define SCK1OUT_O	8
#define SS1OUT_O	9
#define SDO2_O		10
#define SCK2OUT_O	11
#define SS2OUT_O	12
#define OC1_O		18
#define OC2_O		19
#define OC3_O		20
#define OC4_O		21
#define OC5_O		22

// Peripheral Pin Select pin output registers
#define RP0_O RPOR0bits.RP0R
#define RP1_O RPOR0bits.RP1R
#define RP2_O RPOR1bits.RP2R
#define RP3_O RPOR1bits.RP3R
#define RP4_O RPOR2bits.RP4R
#define RP5_O RPOR2bits.RP5R
#define RP6_O RPOR3bits.RP6R
#define RP7_O RPOR3bits.RP7R
#define RP8_O RPOR4bits.RP8R
#define RP9_O RPOR4bits.RP9R
#define RP10_O RPOR5bits.RP10R
#define RP11_O RPOR5bits.RP11R
#define RP12_O RPOR6bits.RP12R
#define RP13_O RPOR6bits.RP13R
#define RP14_O RPOR7bits.RP14R
#define RP15_O RPOR7bits.RP15R
#define RP16_O RPOR8bits.RP16R
#define RP17_O RPOR8bits.RP17R
#define RP18_O RPOR9bits.RP18R
#define RP19_O RPOR9bits.RP19R
#define RP20_O RPOR10bits.RP20R
#define RP21_O RPOR10bits.RP21R
#define RP22_O RPOR11bits.RP22R
#define RP23_O RPOR11bits.RP23R
#define RP24_O RPOR12bits.RP24R




#endif
