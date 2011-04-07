/*
 * This file is part of the #twatch project (dangerousprototypes.com).
 * NOTE: this code requires the Microchip TCP/IP stack, which is released under the Microchip license.
 *       Code written by the #twatch project is released into the public domain, 
 *		 The Microchip license still applies to the Microchip TCP/IP stack.
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
#define LCD_LINE1_POSITION 0x00
#define LCD_LINE2_POSITION 0x40
#define LCD_LINE3_POSITION 0x14
#define LCD_LINE4_POSITION 0x54

#define LCD_SETUP_DELAY 4 //setup delay for LCD data (us)
#define LCD_HOLD_DELAY 12 //LCD clock hold time (us)

#define LCD_BL LATCbits.LATC2
#define LCD_EN LATAbits.LATA4
#define LCD_RS LATCbits.LATC0

//setup all LCD control pins
//D0-3 RB0-3
//D4-7 RA0-3
//RS RC0
//R/W RA5 (ground)
//E RA4
//BL RC2
#define LCD_PIN_SETUP() TRISB&=(~0b1111);LATB &=(~0b1111);TRISA&=(~0b111111);LATA&=(~0b111111);TRISC&=(~0b101);LATC&=(~0b101)
void LCD_BlinkCursor(unsigned char blink);
void LCD_UnderlineCursor(unsigned char cursor);
void HD44780_Reset(void); //reset the LCD to 4 bit mode
void HD44780_Init(void); //initialize LCD to 4bit mode with typical settings and X displaylines
void LCD_WriteCGRAM(char c); //write a command to the LCD
void LCD_WriteRAM(char c); //write to RAM
void LCD_WriteChar(char c); //write a character to the LCD with line wrap
void LCD_WriteString(char *s); //write a string to the LCD
void LCD_WriteByteVal(unsigned char c);//write this byte value to LCD as ascii text
void LCD_CursorPosition(unsigned char c);//set cursor to 0-80 position, with adjustment
void LCD_Clear(void);//clear LCD and return to positon 0
void LCD_Home(void); //return to postion 0
void LCD_Backlight(unsigned char c); //0 (off) 0< (on)
void delayMS(const unsigned char delay); //delay x MS
