/*
 * This file is part of the #twatch project (dangerousprototypes.com).
 * NOTE: this code requires the Microchip TCP/IP stack, which is released under the Microchip license.
 *       Code written by the #twatch project is released into the public domain. 
 *		 The Microchip license applies to the Microchip TCP/IP stack.
 *
 * Originally written by Ian Lesnet <ian@dangerousprototypes.com>
 *
 * To the extent possible under law, Ian Lesnet <ian@dangerousprototypes.com> has
 * waived all copyright and related or neighboring rights to this code. This
 * work is published from United States.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include "HardwareProfile.h" //for pin and hardware info
#include "HD44780.h" 

#define LCD_SETUP_DELAY 4 //setup delay for LCD data (us)
#define LCD_HOLD_DELAY 12 //LCD clock hold time (us)

//RS (register select) pin states
#define COMMAND 0
#define DATA 1

//
//HD44780 commands and related options
//
#define CMD_CLEARDISPLAY 	0b00000001 //82us-1.64ms

#define CMD_RETURNHOME 		0b00000010 //40us-1.64ms

#define CMD_ENTRYMODESET 	0b00000100 //40us
#define INCREMENT 0b10
#define DECREMENT 0b00
#define DISPLAYSHIFTON 0b1
#define DISPLAYSHIFTOFF 0

#define CMD_DISPLAYCONTROL 	0b00001000 //40us
#define DISPLAYON 0b100
#define DISPLAYOFF 0
#define CURSORON 0b10
#define CURSOROFF 0
#define BLINKON 0b1
#define BLINKOFF 0

#define CMD_CURSORDISPLAYSHIFT 0b00010000 //40us
#define DISPLAYSHIFT 0b1000
#define CURSORMOVE 0
#define SHIFTRIGHT 0b100
#define SHIFTLEFT 0

#define CMD_FUNCTIONSET 	0b00100000 //40us
#define DATAWIDTH8 0b10000
#define DATAWIDTH4 0
#define DISPLAYLINES2 0b1000
#define DISPLAYLINES1 0
#define FONT5X10 0b100
#define FONT5X7 0
#define MODULE24X4 0b1

#define CMD_SETCGRAMADDR 	0b01000000 //40us
//6bit character generator RAM address

#define CMD_SETDDRAMADDR 	0b10000000 //40us
//7bit display data RAM address

//internal functions
void HD44780_WriteByte(unsigned char reg, unsigned char dat); //write a byte to LCD to register REG
void HD44780_WriteNibble(unsigned char dat);//write 4 bits to LCD to register REG
void delayUS(const unsigned char delay); //delay x US
void delayMS(const unsigned char delay); //delay x MS

static unsigned char cursorPosition=1;//track current cursor position
static struct _LCDdisplayControl{
	unsigned char cursor:1;
	unsigned char blink:1;
} LCDdisplayControl; //track blink and cursor underline control bits

//
//
//	TWATCH v2 - 18F
//
//
#if defined(__18CXX) //twatch v2, 18F

//Define how pins connect to the LCD
#define LCD_RS PORTDbits.RD1
#define LCD_RW PORTDbits.RD0
#define LCD_EN PORTEbits.RE5
#define LCD_D0 PORTEbits.RE4
#define LCD_D1 PORTEbits.RE3
#define LCD_D2 PORTEbits.RE2
#define LCD_D3 PORTEbits.RE1
#define LCD_D4 PORTEbits.RE0
#define LCD_D5 PORTBbits.RB0
#define LCD_D6 PORTBbits.RB1
#define LCD_D7 PORTBbits.RB2
//#define LCD_BL PORTBbits.RB3

//set pin direction
#define LCD_RS_TRIS TRISDbits.TRISD1
#define LCD_RW_TRIS TRISDbits.TRISD0
#define LCD_EN_TRIS TRISEbits.TRISE5
#define LCD_D0_TRIS TRISEbits.TRISE4
#define LCD_D1_TRIS TRISEbits.TRISE3
#define LCD_D2_TRIS TRISEbits.TRISE2
#define LCD_D3_TRIS TRISEbits.TRISE1
#define LCD_D4_TRIS TRISEbits.TRISE0
#define LCD_D5_TRIS TRISBbits.TRISB0
#define LCD_D6_TRIS TRISBbits.TRISB1
#define LCD_D7_TRIS TRISBbits.TRISB2
//#define LCD_BL_TRIS TRISBbits.TRISB3

//different type of define for backlight pins
//if we use the bits approach the compiler does stupid things
#define LCD_BL_TRIS TRISB
#define LCD_BL_LAT LATB
#define LCD_BL_PIN 0b1000

//reset LCD to 8bit mode
void HD44780_Reset(void){
	//set initial pin states
	//we use open drain with pullup resistors to interface the LCD at 5volts
	//all I/O should be to ground, low to start
	//all to low for ground on TRIS clear
	PORTB &=(~0b1111); //clear B bits (B765)
	PORTD &=(~0b11); //clear D bits (RS/RW)
	PORTE &=(~0b111111); //clear the E bits (E01234)
	//all start output/low, 0 on HD44780 pins
	TRISB &=(~0b1111); //clear B bits (B765)
	TRISD &=(~0b11); //clear D bits (RS/RW)
	TRISE &=(~0b111111); //clear the E bits (E01234)

	//# Wait more than 15 msecs after power is applied.
	delayMS(15);

	//# Write 0x30 to LCD and wait 5 msecs for the instruction to complete
	HD44780_WriteByte(COMMAND, 0x30);
	delayMS(5);
	//# Write 0x30 to LCD and wait 160 usecs for instruction to complete
	HD44780_WriteByte(COMMAND, 0x30);
	delayUS(160);
	//# Write 0x30 AGAIN to LCD and wait 160 usecs (or poll the Busy Flag) 
	HD44780_WriteByte(COMMAND, 0x30);
	delayUS(160);
}

//write byte dat to register reg
void HD44780_WriteByte(unsigned char reg, unsigned char dat){
	unsigned int i;

	TRISD&=(~0b1); //LCD_RW_TRIS=0; //write mode =0 (this is always set from the beginning)

	if(reg==DATA){	//does RS need to be set?
		TRISD|=0b10; //LCD_RS_TRIS=1; //set register select flag for text
	}else{
		TRISD&=(~0b10); //LCD_RS_TRIS=0;//0 for a command
	}

	//load values on pins
	//ensure everything starts low elsewhere....
	TRISE &=(~0b11111); //clear the E bits (01234)
	TRISB &=(~0b111); //clear B bits (765)

	//put lower 5 bits on E01234
	i=0;
	if(dat & 0b1) i|=0b10000;
	if(dat & 0b10) i|=0b1000;
	if(dat & 0b100) i|=0b100;
	if(dat & 0b1000) i|=0b10;
	if(dat & 0b10000) i|=0b1;	
	TRISE|=i;
	
	//put upper 3 bits on B210
	TRISB|=(dat>>5);

	//clock in the data
	delayUS(LCD_SETUP_DELAY);//optional setup delay (5)
	TRISE|=0b100000; //LCD_EN_TRIS=1; //raise the EN line to clock in the values
	delayUS(LCD_HOLD_DELAY);//hold data delay (16)
	TRISE &=(~0b100000); //LCD_EN_TRIS=0; //lower EN line
}

//delay in US
void delayUS(const unsigned char delay){
	volatile unsigned char i;
	
	for(i=0;i<delay;i++){//@41.6MHz = ~10MIPS, 10I/uS
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
	}
}

#elif defined(__PIC24F__)
//
//
//	TWATCH v1 - 24F
//
//

#include <p24fxxxx.h>
#include "HD44780.h"

//Define how pins connect to the LCD
#define LCD_RS PORTBbits.RB5
#define LCD_RW PORTBbits.RB6
#define LCD_EN PORTBbits.RB7
#define LCD_D4 PORTBbits.RB8
#define LCD_D5 PORTBbits.RB9
#define LCD_D6 PORTBbits.RB10
#define LCD_D7 PORTBbits.RB11
//#define LCD_BL PORTBbits.RB13

//set pin direction
#define LCD_RS_TRIS TRISBbits.TRISB5
#define LCD_RW_TRIS TRISBbits.TRISB6
#define LCD_EN_TRIS TRISBbits.TRISB7
#define LCD_D4_TRIS TRISBbits.TRISB8
#define LCD_D5_TRIS TRISBbits.TRISB9
#define LCD_D6_TRIS TRISBbits.TRISB10
#define LCD_D7_TRIS TRISBbits.TRISB11
//#define LCD_BL_TRIS TRISBbits.TRISB13

#define LCD_BL_TRIS TRISB
#define LCD_BL_LAT LATB
#define LCD_BL_PIN 0b10000000000000

//reset LCD to 4bit mode
void HD44780_Reset(void){
	//set initial pin states
	//LCD_BL_TRIS=0;//backlight pin output
	//LCD_BL=0; //backlight off

	//we use open drain with pullup resistors to interface the LCD at 5volts
	//all I/O should be to ground, low to start
	PORTB &= (~0b10111111100000);
	LATB &= (~0b10111111100000);
	TRISB &= (~0b10111111100000);

	//# Wait more than 15 msecs after power is applied.
	delayMS(15);
	LCD_RS_TRIS=0;//0 for a command
	//# Write 0x03 to LCD and wait 5 msecs for the instruction to complete
	HD44780_WriteNibble(0x03);
	delayMS(5);
	//# Write 0x03 to LCD and wait 160 usecs for instruction to complete
	HD44780_WriteNibble(0x03);
	delayUS(160);
	//# Write 0x03 AGAIN to LCD and wait 160 usecs (or poll the Busy Flag) 
	HD44780_WriteNibble(0x03);
	delayUS(160);
	//Set the Operating Characteristics of the LCD
    //* Write 0x02 to the LCD to Enable Four Bit Mode 
	HD44780_WriteNibble(0x02);
	delayUS(160);
}

//write byte dat to register reg
void HD44780_WriteByte(unsigned char reg, unsigned char dat){

	LCD_RW_TRIS=0; //write mode =0

	if(reg==DATA){	//does RS need to be set?
		LCD_RS_TRIS=1; //set register select flag for text
	}else{
		LCD_RS_TRIS=0;//0 for a command
	}

	HD44780_WriteNibble((dat>>4) );
	HD44780_WriteNibble((dat & 0x0F));
}

//write 4 bits dat to register reg
void HD44780_WriteNibble(unsigned char dat){
	unsigned int i;
	//ensure everything starts low elsewhere....
	//load values on pins
	TRISB&=(~0b111100000000);
	i=dat;
	TRISB|=(i<<8);

	delayUS(5);//optional setup delay
	LCD_EN_TRIS=1; //raise the EN line to clock in the values
	delayUS(16);//optional setup delay
	LCD_EN_TRIS=0; //lower EN line
}

//delay in US
void delayUS(const unsigned char delay){
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

#endif

//
//
//	SHARED FUNCTIONS
//
//

//backlight control
//the LED draws a lot of power when it comes on 
//and it messes with the pull-up resistors on the data pins
//#define LCD_BL_TRIS TRISB
//#define LCD_BL_LAT LATB
//#define LCD_BL_PIN 0b1000
void LCD_Backlight(unsigned char c){
	unsigned char i;
	LCD_BL_TRIS &= (~LCD_BL_PIN); //backlight pin output
	if(c){
		//turn on slowly with PWM
		for(i=0; i<255; i++){
			LCD_BL_LAT |=LCD_BL_PIN; //backlight ON	
			delayUS(i);//on for increasing us
			LCD_BL_LAT &= (~LCD_BL_PIN); //backlight OFF
			delayUS((255-i));//off for decreasing us
		}	
		LCD_BL_LAT |=LCD_BL_PIN; //exit with light ON	
	}else{
		LCD_BL_LAT &= (~LCD_BL_PIN); //backlight off
	}
}

//initialize LCD with standard features
void HD44780_Init(void){
	//Function set
	#if defined(__18CXX) //8bit interface on v2
		HD44780_WriteByte(COMMAND, (CMD_FUNCTIONSET + DATAWIDTH8 + FONT5X7 + DISPLAYLINES2)); //0x28, 0b101000
	#elif defined(__PIC24F__) //4bit interface on v1
		HD44780_WriteByte(COMMAND, (CMD_FUNCTIONSET + DATAWIDTH4 + FONT5X7 + DISPLAYLINES2)); //0x28, 0b101000
	#endif
	delayMS(15);//delay 15ms
	
	//Turn display off
	HD44780_WriteByte(COMMAND, CMD_DISPLAYCONTROL + DISPLAYOFF + CURSOROFF + BLINKOFF);//0x08, 0b1000
	delayMS(15);//delay 15ms
	
	//Clear LCD and return home
	HD44780_WriteByte(COMMAND, CMD_CLEARDISPLAY);
	delayMS(15);//delay 15ms
	
	//Turn on display, turn off cursor and blink
	HD44780_WriteByte(COMMAND, CMD_DISPLAYCONTROL + DISPLAYON + CURSOROFF + BLINKOFF);   // 0x0f, 0b1111
	delayMS(15);//delay 15ms
	LCDdisplayControl.cursor=CURSOROFF;
	LCDdisplayControl.blink=BLINKOFF;
}

//write to character generator RAM
void LCD_WriteCGRAM(char c){
	c*=8;
	HD44780_WriteByte(COMMAND, CMD_SETCGRAMADDR + c);  
	delayUS(46);
}

//no cursor compensation, for CGRAM
void LCD_WriteRAM(char c){
	HD44780_WriteByte(DATA, c);
	delayUS(46);
}

//blink and underline share a command byte, 
//we need to remember them so we can keep the correct setting on one when we update the other
void LCD_BlinkCursor(unsigned char blink){
	LCDdisplayControl.blink=blink; //store the setting
	blink=CMD_DISPLAYCONTROL + DISPLAYON; //setup the command
	if(LCDdisplayControl.cursor) blink+=CURSORON; //set cursor bit
	if(LCDdisplayControl.blink) blink+=BLINKON;  //set blink bit
	HD44780_WriteByte(COMMAND, blink);   //send command
	delayUS(40);//delay
}
//same as LCD_BlinkCursor(), different bit
void LCD_UnderlineCursor(unsigned char cursor){
	LCDdisplayControl.cursor=cursor;
	cursor=CMD_DISPLAYCONTROL + DISPLAYON;
	if(LCDdisplayControl.cursor) cursor+=CURSORON;
	if(LCDdisplayControl.blink) cursor+=BLINKON;
	HD44780_WriteByte(COMMAND, cursor); 
	delayUS(40);//delay
}

//Clear LCD and return home
void LCD_Clear(void){
	HD44780_WriteByte(COMMAND, CMD_CLEARDISPLAY);
	cursorPosition=1; //cursor is positioned at home
	delayMS(15);//delay 15ms
}

//return cursor to home
void LCD_Home(void){
	HD44780_WriteByte(COMMAND,CMD_RETURNHOME);
	cursorPosition=1; //cursor is positioned at home
	delayMS(2);//delay 15ms
}

//set position, with compensation for actual LCD layout
//this is used to align character 21 with line 2 postion 1, instead of the default line 3.
void LCD_CursorPosition(unsigned char c){
	cursorPosition=c;
	//calculate actual cursor position value
	if(c>=1 && c<=20){
		c--;
	}else if (c>=21 && c<=40){
		c+=43;
	}else if (c>=41 && c<=60){
		c-=21;
	}else if (c>=61){
		c+=23;
	}
	HD44780_WriteByte(COMMAND, CMD_SETDDRAMADDR | c);
}

//this function sends text to the LCD, with compensation for non-linearity
//write a character to the LCD with wrap to the next line
void LCD_WriteChar(char c){
	HD44780_WriteByte(DATA, c);
	//wrap the cursor at the end of the line
	//1-20, line  1, 0x00-0x13
	//21-40, line 2, 0x40-0x53
	//41-60, line 3, 0x14-0x27 (20)
	//61-80, line 4, 0x54-0x67
	cursorPosition++;
	if (cursorPosition==21 || cursorPosition==41 || cursorPosition==61){
		LCD_CursorPosition(cursorPosition);
	}else if (cursorPosition==81){
		cursorPosition=0;
		LCD_CursorPosition(cursorPosition);
	}
}

//write a string to the LCD
//curser position is not tracked....
#if defined(__18CXX)
void LCD_WriteString(ROM char *s) //for 18F
#else
void LCD_WriteString(char *s) //other processors
#endif
{
	char c;
	while((c = *s++)) HD44780_WriteByte(DATA, c);
}

//write this byte value to LCD as ascii text
//output an 8bit/byte decimal value to the LCD
void LCD_WriteByteVal(unsigned char c){
    unsigned char d,j,m,k=0;

	d=100;
	for(j=0; j<2; j++){
		m=c/d;
		if(k || m){
			HD44780_WriteByte(DATA, m + '0');
		    c = c - (m*d);
			k=1;
		}
		d/=10;	
	}
    HD44780_WriteByte(DATA, c + '0');
}

//delay in MS
void delayMS(const unsigned char delay){
	volatile unsigned int i;
	volatile unsigned char c;
	
	for(c=0;c<delay;c++){
		for(i=0;i<4;i++) delayUS(250);
	}

}

//file ends with a blank line after this comment
