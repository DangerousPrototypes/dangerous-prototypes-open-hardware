/*
 * This file is part of the Bus Pirate project (http://code.google.com/p/the-bus-pirate/).
 *
 * Written and maintained by the Bus Pirate project.
 *
 * To the extent possible under law, the project has
 * waived all copyright and related or neighboring rights to Bus Pirate. 
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

// CvD: buspirate subs copied from the bus pirate svn
// CvD: Did I already mention it is highly alpha?? use with caution and only if you have a programmer to undo this!!
 

#include "hardware.h"
#include "basic.h"

// functions
void BpInit(void);
int main(void);
void bpWstring(char *s);
void bpWinthex(unsigned int c);
void bpWhex(unsigned int c);
void bpWstring(char *s);
void bpWline(char *s);
void UART1TX(char c);
void bpDelayUS(const unsigned char delay);
void bpDelayMS(const unsigned char delay);
unsigned char UART1RXRdy(void);
unsigned char UART1RX(void);

// cvD: needed??
//_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE & I2C1SEL_PRI)		// Internal FRC OSC = 8MHz
//CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1) //turn off junk we don't need

// it all happens from here

#define BELL	0x07
#define bpBR	bpWline("");
#define bpSP	UART1TX(' ');

//void basic(void);
//void list(void);
int getnumber(int def, int max, int x);


int main(void)
{	
	BpInit();
	BP_LEDMODE=0;

	while(!UART1RXRdy());
	UART1RX();
	while(!UART1RXRdy());
	UART1RX();

	bpWline("Buspirate basic version :D");
	bpWline("(C)hris 2010");
	bpWline("released under creative commons null license");
	bpWline("Press any key to continue");

	while(!UART1RXRdy());
	UART1RX();
	while(!UART1RXRdy());
	UART1RX();

	list();

	interpreter();

	while(1);

	return 0;
}


// basic starts here






// gets number from input
// -1 = abort (x)
// -2 = input to much
// 0-max return
// x=1 exit is enabled (we don't want that in the mode changes ;)

int getnumber(int def, int max, int x)	
{	char c;
	char buf[6];									// max 4 digits;
	int i, j, stop, temp, neg;

again:											// need to do it proper with whiles and ifs..

	i=0;
	stop=0;
	temp=0;
	neg=0;

	bpWstring("\r\n(");
//	bpWdec(def);
bpWinthex(def);

	bpWstring(")> ");

	while(!stop)
	{	c=UART1RX();
		switch(c)
		{	case 0x08:	if(i)
						{	i--;
							bpWstring("\x08 \x08");
						}
						else
						{	if(neg)
							{	neg=0;
								bpWstring("\x08 \x08");
							}
						}
						break;
			case '-':	if(!i)							// enable negative numbers
						{	UART1TX('-');
							neg=1;
						}
						else
						{	UART1TX(BELL);
						}
						break;
			case 0x0A:
			case 0x0D:	stop=1;
						break;
			case 'x':	if(x) return -1;					// user wants to quit :( only if we enable it :D
			default:	if((c>=0x30)&&(c<=0x39))	// we got a digit 
						{	if(i>5)					// 0-9999 should be enough??
							{	UART1TX(BELL);
								i=5;
							}
							else
							{	UART1TX(c);
								buf[i]=c;			// store user input
								i++;
							}
						}
						else						// ignore input :)
						{	UART1TX(BELL);
						}

		}
	}
	bpBR;

	if(i==0)
	{	return def;							// no user input so return default option
	}
	else
	{	temp=0;
		i--;
		j=i;

		for( ; i>=0; i--)
		{	temp*=10;
			temp+=(buf[j-i]-0x30);
		}

		if((temp>=0)&&(temp<=max))
		{	if(neg)
			{	return -temp;
			}
			else
			{	return temp;
			}
		}
		else
		{	bpWline("\r\nInvalid choice, try again\r\n");
			goto again;
		}
	}
	return temp;								// we dont get here, but keep compiler happy
}

// mostly copied from base.c, baseIO.c and baseUI.h
// CvD: how to keep synchronized with changes in the buspirate trunk??

void BpInit(void)
{
	CLKDIVbits.RCDIV0=0; //clock divider to 0
	AD1PCFG = 0xFFFF;                 // Default all pins to digital
	OSCCONbits.SOSCEN=0;	

	BP_TERM_RX=BP_TERM_RX_RP;		//Inputs UART1 RX RPINR18bits.U1RXR=4;
	BP_TERM_TX_RP=BP_TERM_TX;		// Outputs UART1 TX RPOR1bits.RP3R=U1TX_IO;

	BP_MOSI_DIR=1;
	BP_CLK_DIR=1; 
	BP_MISO_DIR=1;
	BP_CS_DIR=1; 
	BP_AUX_DIR=1; 
	BP_LEDMODE=0; //mode LED OFF
	BP_LEDMODE_DIR=0;
	#ifdef BUSPIRATEV1A
		BP_PIN6_DIR=1; //AUX2... unused
		BP_LEDPWR=1; //light power led
		BP_LEDPWR_DIR=0;
	#endif

	#if defined( BUSPIRATEV0A) || defined( BUSPIRATEV2)
		BP_PULLUP_OFF();
	#endif

	#if defined( BUSPIRATEV1A) || defined( BUSPIRATEV2)
		
		BP_VREG_OFF();//disable the VREG

		//setup voltage monitoring on ADC. Should be moved to hardwarevx.h!
		//AD1PCFGbits.PCFG9=0; //B15/AN9/ADC4/50V
		//AD1PCFGbits.PCFG10=0;//B14/AN10/ADC3/33V
		//AD1PCFGbits.PCFG11=0;//B13/AN11/ADC2/Vextpullup
		//AD1PCFGbits.PCFG12=0;//B12/AN12/ADC1/EXT
		//AD1PCFG&=(~0b11110);//analog pins
	
		//configure the ADC
		//AD1CON1bits.SSRC  = 0b111;// SSRC<3:0> = 111 implies internal
									// counter ends sampling and starts
									// converting.
		//AD1CSSL = 0;
		//AD1CON3 = 0x1F02; // Sample time = 31Tad,
							// Tad = 2 Tcy
		//AD1CON2 = 0;
	#endif

    U1BRG = 34;					//13332=300, 1666=2400, 416=9600, 34@32mhz=115200....
    U1MODE = 0;
    U1MODEbits.BRGH = 1;
    U1STA = 0;
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;
    IFS0bits.U1RXIF = 0;

}

//Write a string to the user terminal
void bpWstring(char *s){
    char c;
    while((c = *s++)) UART1TX(c);
}

//write a string to the user terminal, finish with a line break
void bpWline(char *s){
    char c;
    while((c = *s++)) UART1TX(c);
	UART1TX(0x0d);
	UART1TX(0x0a);

}

//output an 8bit/byte hex value to the user terminal
const unsigned char HEXASCII[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
void bpWhex(unsigned int c){
    unsigned int b;

	bpWstring("0x");
    b = (c>>4) & 0x0F;
    UART1TX(HEXASCII[b]);
    b = c & 0x0F;
    UART1TX(HEXASCII[b]);
    return;
}

// output a 16bit hex value to the user terminal
void bpWinthex(unsigned int c) {
    unsigned int b;
    
    bpWstring("0x");
    b = (c>>12) & 0x0F;
    UART1TX(HEXASCII[b]);
    b = (c>>8) & 0x0F;
    UART1TX(HEXASCII[b]);
    b = (c>>4) & 0x0F;
    UART1TX(HEXASCII[b]);
    b = c & 0x0F;
    UART1TX(HEXASCII[b]);
    return;
}

//add byte to buffer, pause if full
//uses PIC 4 byte UART FIFO buffer
void UART1TX(char c)
{	//if(basquiet) return;
	while(U1STAbits.UTXBF == 1); //if buffer is full, wait
    U1TXREG = c;
}

//delay in MS
void bpDelayMS(const unsigned char delay){
	volatile unsigned int i;
	volatile unsigned char c;
	
	for(c=0;c<delay;c++){
		for(i=0;i<4;i++) bpDelayUS(250);
	}

}

//delay in US
void bpDelayUS(const unsigned char delay)
{
	volatile unsigned char i;
	
	for(i=0;i<delay;i++){//@32MHz = 16MIPS, 16I/uS
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
	}
}

unsigned char UART1RXRdy(void){
    return U1STAbits.URXDA;
}

//get a byte from UART
unsigned char UART1RX(void){

    while(U1STAbits.URXDA == 0);
	return U1RXREG;
}





