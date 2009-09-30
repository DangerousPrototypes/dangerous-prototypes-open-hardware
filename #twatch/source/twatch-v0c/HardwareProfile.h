/*
 * This file is part of the #twatch project (dangerousprototypes.com).
 * NOTE: this code requires the Microchip TCP/IP stack, which is released under the Microchip license.
 *       Code written by the #twatch project is released into the public domain, 
 *		 The Microchip license still applies to the Microchip TCP/IP stack.
 *
 * Originally written by Ian Lesnet <ian@dangerousprototypes.com>
 *
 * To the extent possible under law, Ian Lesnet <ian@dangerousprototypes.com> has
 * waived all copyright and related or neighboring rights to this code. This
 * work is published from United States.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

//we define hardware for 18F (v2 twatch) and 24F (v1a/b twatch)

//set config fuses
#if defined(THIS_IS_STACK_APPLICATION)
	#if defined(__18CXX)
		// PIC18F97J60 family device
		//WDT is 4ms + postscaler
		/*WDTPS bits:
		1111 = 1:32,768 131 seconds
		1110 = 1:16,384 65
		1101 = 1:8,192	32
		1100 = 1:4,096	16
		1011 = 1:2,048	8
		1010 = 1:1,024	4
		1001 = 1:512	2
		1000 = 1:256	1
		0111 = 1:128	0.5 */
		#pragma config WDT=ON, WDTPS=8192, FOSC2=ON, FOSC=HSPLL, ETHLED=ON, XINST=OFF
	#elif defined(__PIC24F__)
		_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE)		//internal FRC OSC with 4x PLL
		_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1) // PGx pair 1
	#endif
#endif // Prevent more than one set of config fuse definitions

#if defined(__18CXX) //twatch v2, 18F
	//clock frequency value
	//PIC18 processor
	#define GetSystemClock()		(41666667ul)     
	#define GetInstructionClock()	(GetSystemClock()/4) //used in delay.h
	#define GetPeripheralClock()	GetInstructionClock()
	
#elif defined(__PIC24F__)//v1 twatch, 24fj
//Clock frequency value
// PIC24F processor
	#define GetSystemClock()		(32000000ul)  
	#define GetInstructionClock()	(GetSystemClock()/2) //used in delay.h
	#define GetPeripheralClock()	GetInstructionClock()

//Hardware mappings
//make custom pin assignments for ENC28J60
	//mapping:
	//B3 MISO
	//B2 MOSI
	//B12 CLK
	//A1 CS
	//A3/CN29 INT
	//A0 RST
	#define ENC_RST_TRIS		(TRISAbits.TRISA0)	// Not connected by default
	#define ENC_RST_IO			(PORTAbits.RA0)
	#define ENC_CS_TRIS			(TRISAbits.TRISA1)
	#define ENC_CS_IO			(PORTAbits.RA1)
	// SPI SCK, SDI, SDO pins are automatically controlled by the 
	// PIC24/dsPIC/PIC32 SPI module 
	#define ENC_SPI_IF			(IFS0bits.SPI1IF)
	#define ENC_SSPBUF			(SPI1BUF)
	#define ENC_SPISTAT			(SPI1STAT)
	#define ENC_SPISTATbits		(SPI1STATbits)
	#define ENC_SPICON1			(SPI1CON1)
	#define ENC_SPICON1bits		(SPI1CON1bits)
	#define ENC_SPICON2			(SPI1CON2)

//peripheral Pin Select Outputs
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

#endif
