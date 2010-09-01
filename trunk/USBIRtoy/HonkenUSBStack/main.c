/*
This work is licensed under the Creative Commons Attribution 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/
or send a letter to
	Creative Commons,
	171 Second Street,
	Suite 300,
	San Francisco,
	California,
	94105,
	USA.
*/

#pragma config PLLDIV = 5
#pragma config CPUDIV = OSC1_PLL2
#pragma config USBDIV = 2
#pragma config FOSC = HSPLL_HS
#pragma config IESO = OFF
#pragma config PWRT = OFF
#pragma config BOR = ON
#pragma config VREGEN = ON
#pragma config WDT = OFF
#pragma config WDTPS = 32768
#pragma config MCLRE = ON
#pragma config LPT1OSC = OFF
#pragma config PBADEN = OFF
#pragma config CCP2MX = ON
#pragma config STVREN = ON
#pragma config LVP = OFF
//#pragma config ICPRT = OFF
#pragma config XINST = OFF
#pragma config DEBUG = OFF
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPB = OFF
#pragma config CPD = OFF
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF

#include <p18cxxx.h>
#include "usb_stack.h"
#include "cdc.h"

#ifdef __DEBUG
#include <usart.h>
#include <stdio.h>
#endif

void main( void ) {
#ifdef __DEBUG
	OpenUSART(	USART_TX_INT_OFF &
				USART_RX_INT_OFF &
				USART_ASYNCH_MODE &
				USART_EIGHT_BIT &
				USART_CONT_RX &
				USART_BRGH_HIGH,
				25);								// 115200:8-n-1 @ 20MHz XTAL
	stderr = _H_USART;
	fprintf(stderr, (const far rom char *) "\n\nHonken USB Stack Debug\n");
#endif
	usb_init();

	// Infinity local echo
	while(1) {
		usb_handler();
		if (DataRdyCDC())
			putcCDC(getcCDC());
	}
}


#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
//relocate the reset vector
extern void _startup (void);  
#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
void _reset (void){
    _asm goto _startup _endasm
}
