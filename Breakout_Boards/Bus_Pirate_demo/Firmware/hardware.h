/* header */
#ifndef HARDWARE_H
#define HARDWARE_H
#define OSCCONVALUE	0xEA		// 4Mhz, PLL enable, intosc, UART 

#define MODESPI		0x01 //0b10
#define MODEI2C		0x03 //0b11
#define MODEUART		0x02 //0b01
#define MODEUNK		0x00 //0b00 (both jumpers

#define MODEADC		0x03 //0b11
#define MODEDAC		0x01 //0b10
#define MODEMEM		0x02 //0b01
#define MODEPWM		0x00 //0b00 (both jumpers

// leds
#define LED1ON		RC5=1;
#define LED1OFF		RC5=0;
#define LED2ON		RC3=1;
#define LED2OFF		RC3=0;

// jumpers
#define X1			RA2
#define X2			RC2
#define Y1			RB4
#define Y2			RB6
#endif
