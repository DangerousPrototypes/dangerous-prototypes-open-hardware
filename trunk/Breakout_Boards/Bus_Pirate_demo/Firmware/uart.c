/* header */

// includes
#include <pic.h>
#include "./hardware.h"
#include "./uart.h"
#include "./pwm.h"
#include "./dac.h"
#include "./adc.h"
#include "./eeprom.h"

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
    
	/*
    // enable uart interrupt (not untill GIE=1)
    RCIE=1;                 // interrupt on receive
    TXIE=0;                 // no interrupt on transmit
	**/
    // init global vars (ringbuf)
    /*rhead=0;
    rtail=0;
    for(i=0; i<(RINGBUFFSIZE-1); i++)
    {
        ringbuff[i]=0x00;
    }*/

	LED1ON;					// with uart we arent really addressed, but leds are cool :)
}

void UARTworker(void)
{
	unsigned char c,mode=0,addr=0,instruction=0,EEaddrF=0,EEaddr=0,adcc=0,helpC;
	initUART();
	//write start message (menu)
	UARTwriteString(msgMenu[0]);
	UARTwrite('\n');
	while(1)
	{	

		if(RCIF)						
		{	
			RCIF=0;
			LED2ON;						
			if(!(RCSTA&0b00000110))		
			{	rhead++;				
				rhead&=RINGBUFFMASK;	
				ringbuff[rhead]=RCREG;	
			}							
			LED2OFF;
			c=UARTread();
			UARTwrite(c);
			//c=UARTcharFromString(c);
			switch (mode)
			{
				case 0:
					mode=c-48;
					UARTwriteString(msgMenu[c-48]);
					if(mode==2)enablePWM();
					else if(mode==3)enableDAC();
					break;
				case 1://ADC
					switch(c)
					{
						case 'r'://single read
							UARTwriteString("\n\nADC value: ");
							helpC=getADC(adcc);
							UARTwriteDecimal(helpC);
							UARTwriteString(msgMenu[1]);
							break;
						case '1'://chanell one
							UARTwriteString("\n\nchannel 1 selected");
							adcc=0;
							UARTwriteString(msgMenu[1]);
							break;
						case '2'://chanel two
							UARTwriteString("\n\nchannel 2 selected");
							adcc=1;
							UARTwriteString(msgMenu[1]);
							break;
						case '3'://chanell three
							UARTwriteString("\n\nchannel 3 selected");
							adcc=2;
							UARTwriteString(msgMenu[1]);
							break;
						case 't'://temp
							UARTwriteString("\n\nTemp sensor selected");
							adcc=3;
							UARTwriteString(msgMenu[1]);
							break;
						case 'm'://back to start
							mode = 0;
							UARTwriteString(msgMenu[0]);	
							break;
						default:
							break;
					}
					break;
				case 2://PWM
					if(instruction)
					{
						switch(instruction)
						{	
							case 'p':
								//pwm period = c;
								setPeriod(UARTcharFromString(c));
								UARTwriteString(msgMenu[2]);
								break;
							case 'd':
								setDuty(UARTcharFromString(c));
								UARTwriteString(msgMenu[2]);
								//pwm period =c;	
								break;
							case 'm':
								mode =0;
								//pwm off
								UARTwriteString(msgMenu[0]);	
								break;
							default:
								break;
						}
						instruction = 0;						
					}
					else
					{
						instruction = c;				//loads the instruction
						if(instruction == 'p')
						{
							UARTwriteString("\n\nEnter the PWM Period: ");
							
						}
						else if(instruction == 'd')
						{
							UARTwriteString("\n\nEnter the PWM Duty Cycle: ");
						}
						else if(instruction == 'm')		//if it's m goes back to the start menu...
						{
							mode =0;						
							instruction =0;
							disablePWM();
							UARTwriteString(msgMenu[0]);
						}
					}
					break;
				case 3://DAC
					if(instruction)
					{
						switch(instruction)
						{
							case 'v':	//enter woltage
								setDAC(UARTcharFromString(c));
								UARTwriteString(msgMenu[3]);
								break;
							case 'm':
								mode = 0;
								UARTwriteString(msgMenu[0]);
								break;
							default:	
								break;
						}
						instruction =0;
					}
					else
					{
						instruction = c;				//loads the instruction
						if(instruction == 'v')
						{
							UARTwriteString(msgDACsetV);
						}
						else if(instruction == 'm')		//if it's m goes back to the start menu...
						{
							mode =0;						
							instruction =0;
							disableDAC();
							UARTwriteString(msgMenu[0]);
						}
					}
					break;
				case 4://MEM
					if(instruction)		//if instruction has been sent previusly
					{
						if(EEaddrF)			//instruction was sent previusly, check if address was sent
						{						//address was sent
							if(instruction == 'w')		//if instruction was W-writes recived character to EEProm[ADDR]
							{
								EEPROMwrite(EEaddr,UARTcharFromString(c));
								UARTwriteString(msgMenu[4]);
								//write c to eeprom
							}
							else if (instruction == 'r')	//if instruction was R-reads EEprom[addr] from eeprom
							{
								UARTwriteDecimal(EEPROMread(EEaddr));
								UARTwriteString(msgMenu[4]);
							}
							else if (instruction == 'm')	//if instruction was m --returns to start menu...
							{
								mode = 0;
								UARTwriteString(msgMenu[0]);
							}
							EEaddrF=0;							//clears the addressing flag
							instruction =0;					//clears the istruction flag
						}
						else
						{
							EEaddrF=1;						//sets the address flage
							EEaddr=UARTcharFromString(c);
							
							if(instruction=='w')UARTwriteString(msgEEw);
							else if(instruction == 'r')UARTwriteString("\n\nHit any key to read from EEPROM.\n\n"); 
						}
					}
					else 
					{
						instruction = c;				//loads the instruction
						if((instruction == 'w')||(instruction == 'r'))
						{
							UARTwriteString(msgEEaddr);
						}
						else if(instruction == 'm')		//if it's m goes back to the start menu...
						{
							mode =0;						
							instruction =0;
							UARTwriteString(msgMenu[0]);
						}
					}
					break;
				default:
					mode=0;
					UARTwriteString(msgMenu[0]);
					break;				
			}				
		}								
	}
}

// gets a byte from the ringbuffer
unsigned char UARTread(void)
{
    unsigned char temp;

    //while(rtail==rhead);         // block untill we get some data

    // temporary disable interrupts
    //GIE=0;
    rtail++;
    rtail&=RINGBUFFMASK;
    temp=ringbuff[rtail];
    //GIE=1;

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

void UARTwriteString (char str[])
{
	unsigned char i=0;
	while(str[i])
	{
		UARTwrite(str[i++]);
	}
}

unsigned char UARTcharFromString(unsigned char c)
{
	unsigned char rC,outF=0,c1=c-48;
	while(outF==0)
	{
		while(RCIF==0);
		if(!(RCSTA&0b00000110))		
		{	rhead++;				
			rhead&=RINGBUFFMASK;	
			ringbuff[rhead]=RCREG;	
		}
		RCIF=0;
		rC=UARTread();
		UARTwrite(rC);
		if(rC==13)outF=1;	//CR end of transmition
		else
		{
			c1*=10;
			c1+=(rC-48);
		}
	}
	return c1;
}

void UARTwriteDecimal(unsigned char c)
{
	unsigned char hC,d=100;
	do
	{
		hC=c/d;
		UARTwrite(hC+48);
		c-=hC*d;
		d/=10;
	}while(d);		
}