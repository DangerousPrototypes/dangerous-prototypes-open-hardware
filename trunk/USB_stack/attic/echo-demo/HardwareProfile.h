/*
 *
 *       USB infrared remote control receiver transmitter firmware v1.0
 *       License: creative commons - attribution, share-alike
 *       Copyright Ian Lesnet 2010
 *       http://dangerousprototypes.com
 *
 */

#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

//#define BUSPIRATEV4
//#define IRTOY
//#define EA14k //Embedded adventures PIC18F14K50 module
//#define JTR_PIC24GB002        // JTR's PIC24..GB002 mockup
#define IANS18FJ      //Ian's PIC18F24J50 test bed
//#define LPC14K  // Microchip low pin count demo board
//JTR_18FXXJ53 // JTR PIC18F27J53

#ifdef IRTOY
	// LED A0 (2)
	#define LED_LAT  LATA
	#define LED_TRIS TRISA
	#define LED_PIN  0b1

	#define LedOff()  LED_LAT &=(~LED_PIN)  //JTR TODO uncomment
	#define LedOn() LED_LAT|=LED_PIN //JTR TODO uncomment
	#define LedToggle() LED_LAT ^=LED_PIN

#endif

#ifdef BUSPIRATEV4
	//RB10
	#define LED_LAT  LATB
	#define LED_TRIS TRISB
	#define LED_PIN  0b10000000000

	#define LedOn()  LED_TRIS &=(~LED_PIN)  //JTR TODO uncomment
	#define LedOff() LED_TRIS|=LED_PIN //JTR TODO uncomment
	#define LedToggle() LED_LAT ^=LED_PIN

#endif



#endif
