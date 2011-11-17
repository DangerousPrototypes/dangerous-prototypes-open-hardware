/* header */

#define OSCCONVALUE	0xEA		// 4Mhz, PLL enable, intosc, UART 

#define PROTOCOLMASK 0x03
#define MODESPI		0x00
#define MODEUART	0x01
#define MODEI2C		0x02
#define MODEUNK		0x03

#define TYPEMASK	0x30
#define MODEADC		0x00
#define MODEMEM		0x10
#define MODEDAC		0x20
#define MODEPWM		0x30

// leds
#define LED1ON		RC5=1;
#define LED1OFF		RC5=0;
#define LED2ON		RC3=1;
#define LED2OFF		RC3=0;

// jumpers
#define X1			RC0
#define X2			RC2
#define Y1			RB4
#define Y2			RB6
