/*
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

Influence and inspiration taken from http://pe.ece.olin.edu/ece/projects.html
*/

// JTR v0.1a

// JTR Note.! Different versions of the BPv4 may have different PICs.
// Select the correct PIC for your version in MPLAB. This stack as
// arranged will allow for the differences.

#include "globals.h"

#include "cdc_config.h"
#include "usb_stack.h"
#include "configwords.h"	// JTR only included in main.c
#include "descriptors.h"	// JTR Only included in main.c
//#include "cdc.h"                // JTR This file has prototypes for the CDC functions that are not currently in operation.

void user_configured_init( void );
void init( void );		//hardware init
void usb_start( void );   //JTR added prototype was missing or something else funny or altered that I cannot remember??
/* Initialize usb cdc acm subsystem */
void initCDC( void );
void usb_init ( ROMPTR const unsigned char*, ROMPTR const unsigned char*, ROMPTR const unsigned char*, int );
void CDCService(void);		// JTR for debugging only

extern volatile unsigned char usb_device_state;	// JTR added
extern unsigned char CDC_trf_state;

#pragma udata
// MAIN LOOP STARTS HERE

#if defined(PIC_18F)
void main( void )
#elif defined(PIC_24F)

void _USB1Interrupt(void);
int main(void)
#endif
{	// JTR N/A unsigned char c;

CDC_trf_state = 0;
	init();			// These Two Init functions really can be rolled into one.
	initCDC();		// JTR this function has been highly modified It no longer sets up CDC endpoints.

	usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS);	// TODO: Remove magic with macro
	usb_start();

	while(usb_device_state == 0);   // JTR addition. Do not proceed until device is configured.


 // USBLEDON();	// JTR BPv4 USB LED active low.
	while(1)
	{
		if (usb_device_state != 0)   // JTR addition
		{
			LATC |= 1;
			//if(DataRdyCDC())
			//{	c=getcCDC();
			//	putcCDC(c);
			//}
			CDCService();
		} else {
		LATC &= 0xE;
		}
	}
}

// hardware init
void init(void)
{
// JTR. The init() function block is in two sections. The first is for PIC18 devices
// while PIC24 devices follow afterward.

#if defined(PIC_18F)

// JTR removed this
//	Delay10KTCYx(0);	// wait to stabilize everything?
//	Delay10KTCYx(0);	// wait 1s to stabilize everything?

	#if defined(__18F14K50) || defined(__18F13K50)//
        ANSELH=0x00;
        ANSEL=0x00;
        WPUBbits.WPUB7 = 1;
        INTCON2bits.RABPU = 0;
	PORTA=0x00;
	PORTB=0x00;		// init port
	LATC=0x00;

	TRISA=0xFF;
	TRISB=0x00;		// RB6 = debug LED(tm)
	TRISC=0x00;		// RBC = debug LED(tm)

	#endif

	#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
		//disable some defaults
	ADCON1 |= 0b1111;   	//all pins digital
	CVRCON=0b00000000;
	#endif

	#if defined(__IS_18J)   // JTR additions for 18FxxJ See PICUSB.h

            #if defined(USE_ALT_ANCON) // JTR addition for 18FxxJ See PICUSB.h
                //Configure all I/O pins to use digital input buffers.  Some PIC18FxxJ Family devices
                //use the ANCONx registers to control this, which is different from other devices which
                //use the ADCON1 register for this purpose.
                WDTCONbits.ADSHR = 1;			// Select alternate SFR location to access ANCONx registers
                ANCON0 = 0xFF;                  // Default all pins to digital
                ANCON1 = 0xFF;                  // Default all pins to digital
                WDTCONbits.ADSHR = 0;			// Select normal SFR locations
            #else

                ANCON0 = 0xFF;                  // Default all pins to digital
                ANCON1 = 0b00011111;// updated for lower power consumption. See datasheet page 343
            #endif

		//make sure everything is input (should be on startup, but just in case)
	TRISA=0xff;
	TRISB=0xff;
	TRISC=0xff;

        #endif

	#if defined(PLLEN_REQD)	// JTR addition for 18FxxJ See PICUSB.h
		// With some PICS we must manually enable PLL and wait at least 2ms for a lock
		unsigned int cnt = 2048;
		OSCTUNEbits.PLLEN = 1;  //enable PLL
		while(cnt--); //wait for lock
	#endif

// pic18 interrupts
// JTR Added macro to do this see PICUSB.h
	//setup USB as interrupt service
//	PIE2bits.USBIE = 1;	// Enable USB interrupts
//   	INTCONbits.GIEL = 1;//enable peripheral interrupts
//   	INTCONbits.GIEH = 1;//enable high proirity interrupts
}
#endif	// JTR end if PIC18 init section

#if defined(PIC_24F)
// pic24 inits

#if defined(BPv4)
	CORCONbits.PSV = 1;	// JTR PIC24 fixup ?? PSV not being initialized. May have been done by c_init though.
	PSVPAG = 0;			//
        CLKDIV = 0x0000;        // Set PLL prescaler (1:1)
        AD1PCFGL = 0x7FD8;	//BPv4 has five analog pins b0, b1, b2, b5, b15
	AD1PCFGH = 0x2;
	TRISB = 0x8027;		// JTR Analog pins as inputs.
	TRISC = 0x0000;
	TRISD = 0x0000;
	TRISE = 0x0000;
	TRISF = 0x0000;
	TRISG = 0x0000;
	LATB = 0x0400;          // JTR USB LED is active LOW.
	LATC = 0x0000;
	LATD = 0x0000;
	LATE = 0x0000;
	LATF = 0x0000;
	LATG = 0x0000;
	OSCCONbits.SOSCEN=0;
#endif


	#if defined(PLLEN_REQD)	// JTR addition for PIC24FJxxGB00x See PICUSB.h

	// On the PIC24FJxxGB00x and PIC24xxxDAxxx Family of USB microcontrollers, the PLL will
        // not power up and be enabled by default.
        // On these devices, user firmware needs to manually set the CLKDIV<PLLEN> bit to
	// power up the PLL.
    {
        unsigned int pll_startup_counter = 600;
        CLKDIVbits.PLLEN = 1;
        while(pll_startup_counter--);

      	AD1PCFG = 0xFFFF;                 // Default all pins to digital
    }
	#endif

    	#if defined(USE_ANS)
            ANSA = 0x0000;
            ANSB = 0x0000;
            ANSC = 0x0000;
            ANSD = 0x0000;
            ANSE = 0x0000;
            ANSF = 0x0000;
            ANSG = 0x0000;
        #endif
}

#endif  // End of init()


// Now define the ISRs for the PIC18 and PIC24

#if defined(PIC_18F)
void myhigh_isr(void);
void mylow_isr(void);
// JTR changed and corrected.
// On the version of the stack I received the interrupts for the PIC18 were
// not setup correctly. Currently they have been setup to use high priority mode
// and the interrupt vector is @ 0x0008. Priority interrupts are enabled
// This can be modified to suit users requirements.

	#pragma code HIGH_INTERRUPT_VECTOR = 0x08
	void interrupt_at_high_vector (void)
	{
	     _asm goto myhigh_isr _endasm
	}
	#pragma code LOW_INTERRUPT_VECTOR = 0x18
	void interrupt_at_low_vector (void)
	{
	     _asm goto mylow_isr _endasm
	}

#pragma code

#pragma interrupt myhigh_isr
void myhigh_isr()
{
if (PIR2bits.USBIF)
	{
		usb_handler();
		PIR2bits.USBIF = 0;
	}
}

#pragma interruptlow mylow_isr	// JTR the labelling of this vector has been changed/corrected from the stack version I received.
void mylow_isr ()
{
}
#endif	// JTR end if PIC18 interrupt setup

#if defined(PIC_24F)

#pragma interrupt _USB1Interrupt
void __attribute__ ((interrupt,address(0xF00),no_auto_psv)) _USB1Interrupt(){

//USB interrupt
//IRQ enable IEC5bits.USB1IE
//IRQ flag	IFS5bits.USB1IF
//IRQ priority IPC21<10:8>
	//{
		usb_handler();
		IFS5bits.USB1IF=0;//	PIR2bits.USBIF = 0;
	//}
}
#pragma code
#endif


