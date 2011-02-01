
/*
* This file is part of a project from Dangerous Prototypes (http://dangerousprototypes.com/).
*
* Written and maintained by DangerousPrototypes.com.
*
* To the extent possible under law, the project has
* waived all copyright and related or neighboring rights to this code. This
* work is published from United States.
*
* For details see: http://creativecommons.org/publicdomain/zero/1.0/.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 

#include "HardwareProfile.h"

#include "osp.h"


//it's important to keep configuration bits that are compatibale with the bootloader
//if you change it from the internall/PLL clock, the bootloader won't run correctly
_FOSCSEL(FNOSC_FRCPLL)		//INT OSC with PLL (always keep this setting)
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)	//disable external OSC (always keep this setting)
_FWDT(FWDTEN_OFF)				//watchdog timer off
_FICD(JTAGEN_OFF & ICS_PGD1);//JTAG debugging off, debugging on PG1 pins enabled


int uart1RXRdy(void);
char uart1RX(void);
void uart1TX(char c);
void uart1Print( char *);
void initstuff(void);



char str[100];
void task1(void);
void task2(void);

void task1(void)
{
    int i;

    osTaskCreate( task2 );

    for ( i = 0; i++ < 30; ) {
        sprintf( str, "Task 1  i: %d\n", i );
        uart1Print( str );
        osTaskPreempt();
    }
    osTaskExit();
}

void task2(void)
{
    int i;

    for ( i = 0; i++ < 10; ) {
        sprintf( str, "Task 2  i: %d\n", i );
        uart1Print( str );
        osTaskPreempt();
    }
    osTaskExit();
}


void taskKeyboard(void)
{
 	char c;
    
    while(1){
        osTaskPreempt();
        if( uart1RXRdy() ){
            c = uart1RX();
            switch (c){
                
        case '0':
            LD1_O = 0;
            IO1_O = 0;
            SD_O = 0;
            break;
        case '1':
            LD1_O = 1;
            break;
        case '2':
            IO1_O = 1;
            break;			
        case '3':
            SD_O = 1;
            break;

        default:
            break;
        }
         
        uart1TX(c);
         
        }

    }
}


int main(void)
{ 	
    initstuff();

    osInit();
    osTaskCreate(taskKeyboard);
    osTaskCreate(task1);
    osBegin();
}



void initstuff(void) 
{    
  
	AD1PCFGL = 0xFFFF; //digital pins

	//setup internal clock for 80MHz/40MIPS
	//7.37/2=3.685*43=158.455/2=79.2275
	CLKDIVbits.PLLPRE=0; // PLLPRE (N2) 0=/2 
	PLLFBD=41; //pll multiplier (M) = +2
	CLKDIVbits.PLLPOST=0;// PLLPOST (N1) 0=/2
    while(!OSCCONbits.LOCK);//wait for PLL ready

	//UART can be placed on any RPx pin
	//we need to configure it for RP14/RP15 to use the FTDI usb->serial converter
	//you could also output one (or both) of the two available UARTS to the I/O header
	//assign pin 14 to the UART1 RX input register
	//RX PR14 (input)
	U1RXR_I = 14;
	//assign UART1 TX function to the pin 15 output register
	//TX RP15 (output)
	RP15_O=U1TX_O;

	//setup UART
    U1BRG = 85;//86@80mhz, 85@79.xxx=115200
    U1MODE = 0; //clear mode register
    U1MODEbits.BRGH = 1; //use high percison baud generator
    U1STA = 0;	//clear status register
    U1MODEbits.UARTEN = 1; //enable the UART RX
    IFS0bits.U1RXIF = 0;  //clear the receive flag

	//setup LEDs
	SD_TRIS = 0; //set pin direction to output
	IO1_TRIS = 0;
	LD1_TRIS = 0;
	SD_O = 1;	//set all pins high (LED on)
	LD1_O = 1;
	IO1_O=1;

}


void uart1Print( char *str )
{
    int i,j;

    j = strlen( str );
    for(i = 0; i < j; i++) {
      uart1TX(str[i]);
    }
}

int uart1RXRdy(void)
{
    return U1STAbits.URXDA;
}

char uart1RX(void)
{
    while(U1STAbits.URXDA == 0);
    return U1RXREG;
}

void uart1TX(char c)
{
	static unsigned char discard=1;//discard the first TX byte before enabling UART TX
	if(discard){//discard the first few bytes to avoid back powering the FTDI chip
		discard--;
		return;
	}
	if(U1STAbits.UTXEN ==0)U1STAbits.UTXEN = 1; //enable UART TX
	while(U1STAbits.UTXBF == 1); //if buffer is full, wait
    U1TXREG = c;
}






