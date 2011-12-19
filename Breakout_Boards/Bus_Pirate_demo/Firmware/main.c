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
__CONFIG(PLLEN_OFF&STVREN_ON&LVP_OFF);

// forward declarations
void init(void);
void interrupt isr(void);
void nullfunc1(void);

typedef struct _proto {
	void (*ADCworker)(void);
	void (*DACworker)(void);
	void (*EEPROMworker)(void);
	void (*PWMworker)(void);
} proto;

proto protos[4] = { //first is UNK
	{	nullfunc1,				// ADC
		nullfunc1,				// DAC
		nullfunc1,				// EEPROM
		nullfunc1,				// PWM
	}
	,							//UART
	{	UARTworker,				// ADC
		UARTworker,				// DAC
		UARTworker,				// EEPROM
		UARTworker,				// PWM
	}
	,							//I2C
	{	I2CADCworker,				// ADC
		I2CDACworker,				// DAC
		I2CEEworker,				// EEPROM
		nullfunc1,				// PWM
	}
	,							//SPI
	{	SPIworker,				// ADC
		SPIworker,				// DAC
		SPIworker,				// EEPROM
		SPIworker,				// PWM
	}

};

// globals
unsigned char mode,mode_device,mode_protocol;

void nullfunc1(void){	}

int main(void)
{	
	mode=MODEI2C;

	init();

	while(1){

		if(isEE()) doEE();
	
		// main loop
		switch(mode_device)
		{		case MODEADC:	protos[mode_protocol].ADCworker();
								break;
				case MODEMEM:	protos[mode_protocol].EEPROMworker();
								break;
				case MODEDAC:	protos[mode_protocol].DACworker();
								break;
				case MODEPWM:	protos[mode_protocol].PWMworker();
				default:		break;		
		}
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
	
	LED1ON;
	LED2ON;

	//X is device
	//Y is protocol

	// check jumpers
	mode_device=0x00;
	mode_protocol=0x00;
	mode_device|=(X2<<1);
	mode_device|=(X1);
	mode_protocol|=(Y2<<1);
	mode_protocol|=(Y1);


	// protocol specific initialisation
	switch(mode_protocol)
	{		case MODESPI:	initSPI();
							break;
			case MODEI2C:	initI2C();
							break;
			case MODEUART:	initUART();
							break;
			case MODEUNK:	break;
			default:		break;		
	}

	LED1OFF;

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
