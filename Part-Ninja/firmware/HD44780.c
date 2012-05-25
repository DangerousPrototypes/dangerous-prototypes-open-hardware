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
#include "globals.h" //for pin and hardware info
#include "test.h"
#include "HD44780.h"
//RS (register select) pin states
#define COMMAND 0
#define DATA 1


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

//reset LCD to 4bit mode
void HD44780_Reset(void){
	//set initial pin states
	LCD_BL_TRIS&=(~LCD_BL_PIN);//backlight pin output
	LCD_BL_LAT|=LCD_BL_PIN; //backlight on

	//all I/O should be to ground, low to start
	TRISC&=(~0b11000000);
	LATC&=(~0b11000000);

	TRISD&=(~0b11111000);
	LATD&=(~0b11111000);


	//# Wait more than 15 msecs after power is applied.
	delayMS(15);
	LCD_RS=0;//0 for a command
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

	LCD_RW=0; //write mode =0

	if(reg==DATA){	//does RS need to be set?
		LCD_RS=1; //set register select flag for text
	}else{
		LCD_RS=0;//0 for a command
	}

	HD44780_WriteNibble((dat>>4) );
	HD44780_WriteNibble((dat & 0x0F));
}

//write 4 bits dat to register reg
void HD44780_WriteNibble(unsigned char dat){
	unsigned int i;
	//ensure everything starts low elsewhere....
	//load values on pins
	LATD&=(~0b11110000);
	i=dat;
	LATD|=(i<<4);

	delayUS(5);//optional setup delay
	LCD_EN=1; //raise the EN line to clock in the values
	delayUS(16);//optional setup delay
	LCD_EN=0; //lower EN line
}

//delay in US
void delayUS(const unsigned char delay){
	volatile unsigned char i;
	
	for(i=0;i<delay;i++){//@32MHz = 16MIPS, 16I/uS
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
		Nop();
		Nop();
		Nop();

	}
}

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
	HD44780_WriteByte(COMMAND, (CMD_FUNCTIONSET + DATAWIDTH4 + FONT5X7 + DISPLAYLINES2)); //0x28, 0b101000

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

void LCD_ExitCGRAM(void){ LCD_CursorPosition(cursorPosition);}

//write a string to the LCD
//curser position is not tracked....

void LCD_WriteString(rom char *s) //for 18F
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

void LCD_WriteINT(u16 value)
{
   unsigned int temp,dvd=10000;
   char i=0,k=0;
   temp = value;
   for (i=0;i<5;i++)
   {
      temp=value/dvd;
      if(temp)k++;
      if(k)HD44780_WriteByte(DATA, temp + '0');
      value = value - (temp*dvd);
      dvd/=10;
   }

}
void LCD_WritePinout()
{
	LCD_WriteString("1:");
	LCD_WriteChar(pins[0]);
	LCD_WriteChar(' ');
	LCD_WriteString("2:");
	LCD_WriteChar(pins[1]);
	LCD_WriteChar(' ');
	LCD_WriteString("3:");
	LCD_WriteChar(pins[2]);
	LCD_WriteChar(' ');
}
//file ends with a blank line after this comment
