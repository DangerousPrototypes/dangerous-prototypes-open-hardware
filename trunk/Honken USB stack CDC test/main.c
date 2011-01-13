

#include "config.h"
#include "globals.h"

#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
#include "delays.h"
#endif

void init(void);		//hardware init

#pragma udata
char test;

#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
void main( void ) 
#elif defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)
void _USB1Interrupt(void);
int main(void)
#endif	
{	unsigned char c;
	unsigned char i;

	init();
#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
	Delay10KTCYx(0);	// wait 1s to stabilize everything?
	Delay10KTCYx(0);	// wait 1s to stabilize everything?
	Delay10KTCYx(0);	// wait 1s to stabilize everything?
	Delay10KTCYx(0);	// wait 1s to stabilize everything?
#endif
	InitCDC();

	while(1)
	{	
#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
		Delay1KTCYx(1);		// 10 ms
#endif

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
#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
	#if defined(__18F14K50)//
		PORTA=0x00;
		PORTB=0x00;		// init port
	
		TRISA=0xFF;
		TRISB=0x00;		// RB6 = debug LED(tm)
	
		LATB=0xFF;
	#endif
	
	#if defined(__18F2550) //IR Toy
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

	//setup USB as interrupt service
	PIE2bits.USBIE = 1;	// Enable USB interrupts
	IPR2bits.USBIP = 0;	// USB interrupt low priority
	
   	INTCONbits.GIEL = 1;//enable peripheral interrupts
   	//INTCONbits.GIEH = 1;//enable interrupts

#elif defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)
    CLKDIV = 0x0000;    // Set PLL prescaler (1:1)
	AD1PCFG = 0xFFFF;                 // Default all pins to digital
	OSCCONbits.SOSCEN=0;	
#endif	

}


#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)

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

#elif defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)
#pragma interrupt _USB1Interrupt
void __attribute__ ((interrupt,address(0xF00),no_auto_psv)) _USB1Interrupt(){

//USB interrupt
//IRQ enable IEC5bits.USB1IE
//IRQ flag	IFS5bits.USB1IF
//IRQ priority IPC21<10:8>
	//if (PIR2bits.USBIF)
	//{	
		usb_handler();
		IFS5bits.USB1IF=0;//	PIR2bits.USBIF = 0;
	//}
	
}

#pragma code
#endif

