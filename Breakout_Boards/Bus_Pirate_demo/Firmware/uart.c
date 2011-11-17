/* header */

// includes
#include <pic.h>
#include "./hardware.h"
#include "./uart.h"

// global vars
unsigned ringbuff[RINGBUFFSIZE];
volatile char rhead, rtail;

void initUART(void)
{	unsigned char i;

	APFCON0|=0x04;	// move txd to rc4
	TRISB5=1;		// rxd
	TRISC4=0;		// txd

    //setup EUSART
    // baudrate needs setup first
    BRGH=1;
    SPBRGH=0x00;
    SPBRGL=BRGVAL;

    // setup for async mode and enable the uart
    SYNC=0;
    SPEN=1;
    TXEN=1;
    CREN=1;
    
    // enable uart interrupt (not untill GIE=1)
    RCIE=1;                 // interrupt on receive
    TXIE=0;                 // no interrupt on transmit

    // init global vars (ringbuf)
    rhead=0;
    rtail=0;
    for(i=0; i<(RINGBUFFSIZE-1); i++)
    {
        ringbuff[i]=0x00;
    }

	LED1ON;					// with uart we arent really addressed, but leds are cool :)
}

void UARTworker(void)
{
	unsigned char c;

	c=UARTread();
	UARTwrite(c);
}

// gets a byte from the ringbuffer
unsigned char UARTread(void)
{
    unsigned char temp;

    while(rtail==rhead);         // block untill we get some data

    // temporary disable interrupts
    GIE=0;
    rtail++;
    rtail&=RINGBUFFMASK;
    temp=ringbuff[rtail];
    GIE=1;

    return temp;
}

// transmit a byte over the uart
void UARTwrite(unsigned char c)
{
	LED2ON;

    while(!TRMT);               // block untill data is sent

    TXREG=c;

	LED2OFF;
}

