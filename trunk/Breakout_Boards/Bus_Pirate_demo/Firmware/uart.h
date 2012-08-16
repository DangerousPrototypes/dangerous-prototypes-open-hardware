/* header */

#define BRGVAL          207      // should be 9600 baud@4mhz (BRGH=1)
#define RINGBUFFSIZE    8       // ringbuffer size (should be power of 2!)
#define RINGBUFFMASK    (RINGBUFFSIZE-1)


// forward declarations
void initUART(void);
void UARTworker(void);
void UARTwrite(unsigned char c);
void UARTwriteDecimal(unsigned char c);
unsigned char UARTread(void);
void UARTwriteString (char* str);

extern unsigned ringbuff[RINGBUFFSIZE];
extern volatile char rhead, rtail;

// spi interrupt service routine
#define UARTisr	do {				\
	if(RCIF)						\
	{	LED2ON;						\
		if(!(RCSTA&0b00000110))		\
		{	rhead++;				\
			rhead&=RINGBUFFMASK;	\
			ringbuff[rhead]=RCREG;	\
		}							\
		RCIF=0;						\
		LED2OFF;					\
	}								\
	if(TXIF)						\
	{	TXIF=0;						\
	}								\
} while(0);

unsigned char UARTcharFromString(unsigned char c);

const char msgMenu0[]="\n\nBus Pirate Demo Board v5\nFW verison v0.95\n\n  Main Menu\n-------------\n\n1)ADC\n2)PWM\n3)DAC\n4)EEPROM\n\nChoose(1-4):\0";
const char msgMenu1[]="\n\nADC Menu\n-----------\n\nr)Read ADC\n1)Channel l\n2)Channel 2\n3)Channel 3\nt)Temperature sensor\nm)Back to main menu\n\nChoose: \0";
const char msgMenu2[]="\n\nPWM Menu\n-----------\n\np)Set PWM Period\nd)Set PWM Duty Cycle\nm)Back to main menu\n\nChoose: \0";
const char msgMenu3[]="\n\nDAC Menu\n-----------\n\nv)Set DAC level 0-31\nm)Back to main menu\n\nChoose: \0";
const char msgMenu4[]="\n\nEEPROM Menu\n--------------\n\nw)Write a character to EEPROM\nr)Read a character from EEPROM\nm)Back to main menu\n\nChoose: \0";

const char msgDACsetV[]="\n\nEnter desired DAC level from 0 to 31: ";

const char msgEEw[]="\n\nEnter the variable (0-255) to be entered into EEPROM: ";
const char msgEEaddr[]="\n\nEnter the address 0-255: ";

const char *msgMenu[] ={msgMenu0,msgMenu1,msgMenu2,msgMenu3,msgMenu4};