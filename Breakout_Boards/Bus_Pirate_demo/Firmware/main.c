/* Header goes here */

// includes
#include <pic.h>
#include "./hardware.h"

// input includes
#include "./spi.h"
#include "./uart.h"
#include "./i2c.h"
#include "./easteregg.h"

// output includes
#include "./eeprom.h"
//#include "./adc.h"
//#include "./dac.h"
//#include "./pwm.h"


// config bits
__CONFIG(FOSC_INTOSC&WDTE_OFF&PWRTE_OFF&MCLRE_OFF&CP_OFF&CPD_OFF&BOREN_ON&CLKOUTEN_OFF&IESO_OFF&FCMEN_ON);
__CONFIG(WRT_BOOT&PLLEN_OFF&STVREN_ON&LVP_OFF);

// forward declarations
void init(void);
void interrupt isr(void);

// globals
unsigned char mode;

int main(void)
{	
	mode=MODEI2C;

	init();

	if(isEE()) doEE();

	// main loop
	switch(mode&PROTOCOLMASK)
	{		case MODESPI:	SPIworker();
							break;
			case MODEI2C:	I2Cworker();
							break;
			case MODEUART:	UARTworker();
							break;
			case MODEUNK:	break;
			default:		break;		
	}
}

// hardware init 
void init(void)
{	// setup oscillator
	OSCCON=OSCCONVALUE;

	// setup i/o pins
    // setup porta
    PORTA=0x00;
    LATA=0x00;
    ANSELA=0x00;
    TRISA=0xFF;
	WPUA=0x00;					// disable weakpullups

    // setup portb
    PORTB=0x00;
    LATB=0x00;
    ANSELB=0x00;
    TRISB=0xFF;
	WPUB=0x50;					// enable pullups on Y1 and Y2

    // setup portb
    PORTC=0x00;
    LATC=0x00;
    ANSELC=0x00;
    TRISC=0xD7;					// everything is input, except leds
	WPUC=0x05;					// enable pullups on X1 and X2

	nWPUEN=0;					// enable weakpullups on jumpers

	// setup PPS (sorta :))
	APFCON0=0x00;
	APFCON1=0x00;

/*
	// check jumpers
	mode=0x00;
	mode|=(Y2<<5);
	mode|=(Y1<<4);
	mode|=(X2<<1);
	mode|=(X1);
*/
	// protocol specific initialisation
	switch(mode&PROTOCOLMASK)
	{		case MODESPI:	initSPI();
							break;
			case MODEI2C:	initI2C();
							break;
			case MODEUART:	initUART();
							break;
			case MODEUNK:	break;
			default:		break;		
	}

    // enable interrupts
//    PEIE=1;
//    GIE=1;

}

// interrupt service routine
// uses specific hw functions (preferable macros?)
void interrupt isr(void)
{
	UARTisr;
	I2Cisr;
//	SPIisr();

}
