
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

//The compiled firmware can be used 'as-is' with the ds30 Loader bootloader
//you may need to locate your own p33FJ128gp204.gld file.
//   It's in the C30 compiler directory:
/* \C30\support\dsPIC33F\gld\ */

#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 

#include <setjmp.h> 


#include "GenericTypeDefs.h"
#include "HardwareProfile.h"


#include "osp.h"






//it's important to keep configuration bits that are compatibale with the bootloader
//if you change it from the internall/PLL clock, the bootloader won't run correctly
_FOSCSEL(FNOSC_FRCPLL)		//INT OSC with PLL (always keep this setting)
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)	//disable external OSC (always keep this setting)
_FWDT(FWDTEN_OFF)				//watchdog timer off
_FICD(JTAGEN_OFF & ICS_PGD1);//JTAG debugging off, debugging on PG1 pins enabled

char uart1RXRdy(void);
char uart1RX(void);
void uart1TX(char c);
void uart1Print( char *);
 

char uart1RXRdy(void){
    return U1STAbits.URXDA;
}

char uart1RX(void){

    while(U1STAbits.URXDA == 0);
    return U1RXREG;
}

int uart1RXInt(void){
   char str[32];
   int i = 0;

   str[0] = '\0';
   do {
      while(U1STAbits.URXDA == 0); 
      str[i] = U1RXREG;
      uart1TX(str[i]);
   } while ( str[i++] != '\r' );
   str[--i] = '\0';
   
	return( atoi( str ));
}

void uart1TX(char c){
	static unsigned char discard=1;

	if(discard){
		discard--;
		return;
	}
	if(U1STAbits.UTXEN ==0)U1STAbits.UTXEN = 1; //enable UART TX
	while(U1STAbits.UTXBF == 1); //if buffer is full, wait
    U1TXREG = c;
}

void uart1Print( char *str ){
    int i,j;

    j = strlen( str );
    for( i = 0; i < j; i++) {
      uart1TX(str[i]);
    }
}

void initstuff(void) {
    
	AD1PCFGL = 0xFFFF; 
	CLKDIVbits.PLLPRE=0; 
	PLLFBD=41; 
	CLKDIVbits.PLLPOST=0;
    while(!OSCCONbits.LOCK);
	
	U1RXR_I = 14;
	RP15_O=U1TX_O;

    U1BRG = 85;
    U1MODE = 0; 
    U1MODEbits.BRGH = 1; 
    U1STA = 0;	
    U1MODEbits.UARTEN = 1; 
    IFS0bits.U1RXIF = 0; 

	SD_TRIS = 0; 
	IO1_TRIS = 0;
	LD1_TRIS = 0;
	SD_O = 1;	
	LD1_O = 1;
	IO1_O=1;
}


char str[100];
int i;


void task0(void);
void task1(void);
void task2(void);


void task0(void)
{
    int i;

    osSemInit( 0, 0);
    osSemInit( 1, 0);
    osSemInit( 2, 0);
	osSemInit( 3, 0);

    osTaskCreate( task1 );
    osTaskCreate( task2 );

     
     while(1) {
        uart1Print( "Task 0 P0 loop\n" );
        osSemP(0);
            
    }   
    osTaskExit();
}

void task1(void)
{
    int i;
    
    while(1) {
        uart1Print( "Task 1 P1 loop\n" );
        osSemP(1);       
       
        uart1Print( "Task 1 V2\n" );
        osSemV(2);
            
    }
    osTaskExit();
}

void task2(void)
{
    int i;
    
    while(1) {
        uart1Print( "Task 2 P2 loop\n" );
        osSemP(2);
    }
    osTaskExit();
}



void taskKeyboard(void)
{
    int i,j;

 	char c;
    
    while(1){
        osTaskPreempt();
        if( uart1RXRdy() ){
            c = uart1RX();
            switch (c){
        case 'b':
 			
            osSemV(0);
            break;        
        case 'n':
 			osSemV(1);
            break;
            
        case 'm':          
            osSemV(2);  
            osSemV(2);  
            osSemV(2);  
            osSemV(2);  
            break;
        
        case '0':
            //LATA &=(~0b11100000000);
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

int main(void){ 
	
    initstuff();

    osInit();
    osTaskCreate(taskKeyboard);
    osTaskCreate(task0);
    osBegin();

}






