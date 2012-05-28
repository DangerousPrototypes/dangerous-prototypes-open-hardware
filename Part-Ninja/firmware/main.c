#include "globals.h"
#include "config.h"
#include "HD44780.h"
#include "test.h"

static void init(void);




#pragma code
void main(void)
{  
    init();			//setup the crystal, pins

	Delay_MS(10);	

	HD44780_Reset();//setup the LCD
	HD44780_Init();
	//LCD_Backlight(1);//turn it on, we ignore the parameter

	LCD_CursorPosition(0);
	LCD_WriteString("Part Ninja v0.0a");
	LCD_CursorPosition(21);
	LCD_WriteString("      testing...");
 
	while(1) testPart();
}//end main

static void init(void){
	unsigned int cnt = 2048;
	
	//all pins digital
	//disable some defaults
    ADCON1 |= 0b1111;   	//all pins digital
	CVRCON=0b00000000;

	//make sure everything is input (should be on startup, but just in case)
	TRISA=0xff;
	TRISB=0xff;
	TRISC=0b11111111; 

	//comparator analog pins setup...
	CMCONbits.C2INV = 1;	//whne voltage on RA1 > vreff cout2=>1
	CMCONbits.C1INV = 1;	//whne voltage on RA1 > vreff cout1=>1
	CMCONbits.CIS=0; 		//the Cvin- input aer RA0 na RA1
	CMCONbits.CM2=1,CMCONbits.CM1=0,CMCONbits.CM0=0; //100 C1 and C2 V+ conencted to vref, while v+ conected to RA1 and RA2
	INTCONbits.GIE = 1;
	INTCONbits.PEIE =1;
	IPR2bits.CMIP =1;

	/*//Timer 1 contorl setup
	T1CONbits.RD16=1;
	T1CONbits.T1RUN=0;
	T1CONbits.T1CKPS=3;//8prescaler
	T1CONbits.TMR1CS=0;*/
		//on 18f24j50 we must manually enable PLL and wait at least 2ms for a lock
	//OSCTUNEbits.PLLEN = 1;  //enable PLL
	//while(cnt--); //wait for lock

}

#pragma interrupt high_isr

void    high_isr(void)
{
   /* high priority interrupt handling code here */
	CMP_INTE=0;
	CMP_INTF=0;
	testCMP=1;
}

#pragma interruptlow low_isr

void    low_isr(void)
{
   /* low priority interrupt handling code here */

}

#pragma code high_vector=0x08

void    high_vector(void)
{
   _asm GOTO high_isr _endasm
}

#pragma code low_vector=0x18

void    low_vector(void)
{
   _asm GOTO low_isr _endasm
}

