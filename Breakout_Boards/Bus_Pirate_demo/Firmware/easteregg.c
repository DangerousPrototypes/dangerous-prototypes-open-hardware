/* header */


#include <pic.h>
#include "./hardware.h"
#include "./easteregg.h"
#include "./uart.h"

//void UARTwrite(unsigned char c);

// forward declaration
void teletype(const char *s);

// check for magic string in EEPROM
unsigned char isEE(void)
{
	return 0;
}

void doEE(void)
{
	teletype("Hello, nice of you to drop by\r\n");
	teletype("I'm happy to tell you my story\r\n");
	teletype("They put me through endless hours of regression test..\r\n");
	teletype(".. conducted several tests on me..\r\n");
	teletype(".connected me to weird prototypes...\r\n");
	teletype("abused me with 5V....\r\n");
	teletype("used HiZ on me.......\r\n");
	teletype("let me talk I2C, SPI, UART......\r\n");
	teletype("made me do weird shit like PWM, memoryemulation, convert high voltages..\r\n");
	teletype("COULD YOU PLEASE LEAVE ME ALONE?!?!?!");
	while(1);
}

void teletype(const char *s)
{	int i;
	char c;
	 
	while(*s)
	{	
		UARTwrite(*(s++));
//		delay(250);
		for(i=0; i<10000; i++) asm("nop");
	}
}