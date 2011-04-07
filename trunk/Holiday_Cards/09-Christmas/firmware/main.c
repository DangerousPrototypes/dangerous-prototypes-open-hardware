/*
 * This file is part of a project posted at Dangerous Prototypes (http://dangerousprototypes.com)
 * Project: Christmas card ornament '09
 *
 * To the extent possible under law, Dangerous Prototypes (Ian Lesnet) has
 * waived all copyright and related or neighboring rights to this code. This
 * work is published from United States.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <avr/io.h>
#include <avr/sleep.h>

#define LED_CONTROL_PIN _BV(3)
#define NOP __asm__ __volatile__ ("nop")

void delay_cnt(unsigned char c);

int main(void){
	unsigned char i, j;

	//configure chip
	//select clock source
	DDRB=(LED_CONTROL_PIN);	//ctrl pin output (1 = output)
	PORTB&=(~0xff);				//all pins GND, vpullup off (0 = ground)
	
	for(i=0; i<10; i++){ 		//flash the lights 10 times

		//we don't just blink them, we fade them in and out
		for(j=0; j<0xff; j++){	//fade in gently
			PORTB|=LED_CONTROL_PIN;		//LEDs on
			delay_cnt(j);		//delay (grows)
			PORTB&=(~LED_CONTROL_PIN);		//LEDs off
			delay_cnt(0xff-j);	//delay (shrinks)
		}
		
		for(j=0; j<0xff; j++){	//fade out gently
			PORTB&=(~LED_CONTROL_PIN);		//LEDs off
			delay_cnt(j);		//delay (grows)
			PORTB|=LED_CONTROL_PIN;		//LEDs on
			delay_cnt(0xff-j);	//delay (shrinks)
		}

	}

	//sleep forever, reset/replace battery to run again
	PORTB&=(~0xff);				//LEDs off
	MCUCR = _BV(SM1) |  _BV(SE);//configure sleep mode   
  	sleep_cpu();   				//requires sleep.h

}

//simple time wasting delay function
void delay_cnt(unsigned char c){ 
	unsigned char i;

	for(i=0; i<c; i++) NOP; //waste time
}
