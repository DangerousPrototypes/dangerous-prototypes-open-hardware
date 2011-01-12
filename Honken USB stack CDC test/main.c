

#include "config.h"
#include "globals.h"
#include "delays.h"

void init(void);		//hardware init

#pragma udata
char test;

void main(void)
{	unsigned char c;
	unsigned char i;

	init();
	Delay10KTCYx(0);	// wait 1s to stabilize everything?
	Delay10KTCYx(0);	// wait 1s to stabilize everything?
	Delay10KTCYx(0);	// wait 1s to stabilize everything?
	Delay10KTCYx(0);	// wait 1s to stabilize everything?
	InitCDC();

	while(1)
	{	Delay1KTCYx(1);		// 10 ms

		usb_handler();	

		if(DataRdyCDC())
		{	c=getcCDC();
			putcCDC(c);
		}

		i++;
		if(i==0) LATB^=0xFF;

	}
}

// hardware init
void init(void)
{	
#if defined(__18F14K50)
	PORTA=0x00;
	PORTB=0x00;		// init port

	TRISA=0xFF;
	TRISB=0x00;		// RB6 = debug LED(tm)

	LATB=0xFF;
#endif

#if defined(__18F2550)

#endif

#if defined(__18F24J50)

#endif



	//setup USB as interrupt service
	PIE2bits.USBIE = 1;	// Enable USB interrupts
	IPR2bits.USBIP = 0;	// USB interrupt low priority
	
   	INTCONbits.GIEL = 1;//enable peripheral interrupts
   	//INTCONbits.GIEH = 1;//enable interrupts


}

#pragma code HIGH_INTERRUPT_VECTOR = 0x08
void High_ISR (void)
{	
}

#pragma code LOW_INTERRUPT_VECTOR = 0x18
void Low_ISR (void)
{	if (PIR2bits.USBIF)
	{	usb_handler();
		PIR2bits.USBIF = 0;
	}
}