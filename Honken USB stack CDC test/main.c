/*
Main program, implements an echo service on a USB CDC ACM connection.
$Id$

This work is licensed under the Creative Commons Attribution 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/
or send a letter to
	Creative Commons,
	171 Second Street,
	Suite 300,
	San Francisco,
	California,
	94105,
	USA.
*/

#include "config.h"
#include "usb_stack.h"
#include "cdc.h"
//#include "globals.h"

#if defined(__18f2550)
// IRtoy
#define USB_LED(x)
#define STA_LED(x)
#define STA_LED_TOGGLE
#elif defined(__18F24J50)
// OLS
#define USB_LED(x)
#define STA_LED(x)
#define STA_LED_TOGGLE
#elif defined(__18F14K50)
// Someones
#define USB_LED(x)
#define STA_LED(x)		(LATBbits.LATB6 = (x))
#define STA_LED_TOGGLE	(LATBbits.LATB6 ^= 1)
#elif defined(__PIC24FJ256GB106__)
// BPv4
#define USB_LED(x)		(LATBbits.LATB10 = (x))
#define STA_LED(x)		(LATBbits.LATB8 = (x))
#define STA_LED_TOGGLE	(LATBbits.LATB8 ^= 1)
#else
// Everyting else
#define USB_LED(x)
#define STA_LED(x)
#define STA_LED_TOGGLE
#endif

void init(void);		//hardware init

MAIN_T main( void )
{
	unsigned char c;
	unsigned int i;

	init();				// Init the hardware platform
	DINIT();			// Init debug messages on stderr (if debug build selected)
	DPRINTF("\n\nCDC Echo test program\n");

	InitCDC();			// Init the CDC/ACM driver, which in turn start the usb stack
	USB_LED(1);			// Turn on USB LED, if there is one :-)

	while(1) {
//		usb_handler();	

		if(DataRdyCDC()) {
			c=getcCDC();
			putcCDC(c);
		}

		if(!++i) {
//			STA_LED_TOGGLE;
		}
	}
}

// hardware init
void init(void)
{	
// init of pic18 platforms
#if defined(PIC_18F)

	#if defined(__18F14K50)//
		PORTA=0x00;
		PORTB=0x00;		// init port
		TRISA=0xFF;
		TRISB=0x00;		// RB6 = debug LED(tm)
		LATB=0xFF;
	#endif
	
	#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
		//disable some defaults
	    ADCON1 |= 0b1111;   	//all pins digital
		CVRCON=0b00000000;	
	#endif
	
	#if defined(__18F24J50)//OLS
		unsigned int cnt = 2048;
	
		//all pins digital
	    ANCON0 = 0xFF;                  
	    ANCON1 = 0b00011111;// updated for lower power consumption. See datasheet page 343                  
	
		//make sure everything is input (should be on startup, but just in case)
		TRISA=0xff;
		TRISB=0xff;
		TRISC=0xff;
	
		//on 18f24j50 we must manually enable PLL and wait at least 2ms for a lock
		OSCTUNEbits.PLLEN = 1;  //enable PLL
		while(cnt--); //wait for lock

	#endif

	// pic18 interrupts
	//setup USB as interrupt service
	RCONbits.IPEN = 1;		// enable interrupt priorities
	PIR1 = PIR2 = 0;
	PIE2bits.USBIE = 1;		// Enable USB interrupts
	IPR2bits.USBIP = 0;		// USB interrupt low priority
   	INTCONbits.GIEL = 1;	// enable peripheral interrupts
   	INTCONbits.GIE = 1;		// enable interrupts
#endif

// pic24 inits
#if defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)
    CLKDIV = 0x0000;		// Set PLL prescaler (1:1) 32 Mhz Fcy
	AD1PCFG = 0xFFFF;		// Default all pins to digital
	OSCCONbits.SOSCEN=0;	// Disable secondary oscillator

	TRISBbits.TRISB8 = 0;	// MODE LED on BPv4
	TRISBbits.TRISB10 = 0;	// USB LED on BDv4

	IPC21bits.USB1IP = 4;
#endif

}


#if defined(PIC_18F)

#pragma interrupt High_ISR
void High_ISR (void)
{	
}

#pragma interrupt Low_ISR
void Low_ISR (void)
{
	if (PIR2bits.USBIF)
	{
		usb_handler();
		PIR2bits.USBIF = 0;
	}
}

#pragma code HIGH_INTERRUPT_VECTOR = 0x08
void interrupt_high( void ) {
	_asm GOTO High_ISR _endasm
}

#pragma code LOW_INTERRUPT_VECTOR = 0x18
void interrupt_low( void ) {
	_asm GOTO Low_ISR _endasm
}
	
#elif defined(PIC_24F)
void __attribute__((interrupt,no_auto_psv)) _USB1Interrupt( void ){
	//USB interrupt
	//IRQ enable IEC5bits.USB1IE
	//IRQ flag	IFS5bits.USB1IF
	//IRQ priority IPC21<10:8>
	STA_LED(1);
	usb_handler();
	IFS5bits.USB1IF=0;
	STA_LED(0);
}

#pragma code
#endif
