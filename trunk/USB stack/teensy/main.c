/* Simple example for Teensy USB Development Board
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2008 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
//use these defines to switch between compiles for OLS and IR Toy
#define OLS
//#define IRTOY

#include "usb_serial.h"

#ifdef OLS
	#include "config-18f24j50.h"
#endif

#ifdef IRTOY
	#include "config-18f2550.h"
#endif

static void init(void);

// Very simple character echo test
int main(void)
{
	init();

	usb_init();

	while (1) {
		int n = usb_serial_getchar();
		if (n >= 0) usb_serial_putchar(n);
	}
}


#ifdef OLS
	static void init(void){
		unsigned int cnt = 2048;
		
		//all pins digital
	    ANCON0 = 0xFF;                  
	    ANCON1 = 0b00011111;// updated for lower power consumption. See datasheet page 343                  
	
		//there are some sensative FPGA pins, 
		//make sure everything is input (should be on startup, but just in case)
		TRISA=0xff;
		TRISB=0xff;
		TRISC=0b11111011; //LED out
		PIN_LED=0;
	
		//start by holding the FPGA in reset
		PROG_B_LOW();
	
		//on 18f24j50 we must manually enable PLL and wait at least 2ms for a lock
		OSCTUNEbits.PLLEN = 1;  //enable PLL
		while(cnt--); //wait for lock
	
	}
#endif

#ifdef IRTOY
	static void init(void){
		//disable some defaults
	    ADCON1 |= 0b1111;   	//all pins digital
		CVRCON=0b00000000;
	
		//setup IR LED for IR TX
		IRTX_TRIS&=(~IRTX_PIN);	//digital OUTPUT (must ground transistor)
		IRTX_LAT&=(~IRTX_PIN); 	//output to ground
	
		//visual indicator LED config
		LED_LAT |=LED_PIN; 		//start with LED ON till USB connect 
		LED_TRIS &=(~LED_PIN); 	//direction output
	
		//setup IR RX interrupt on RB32 or RB4 (see HardwareProfile.h)
		IRRX_PULLUP=1; 	//disable port b pullups (0=enable)
		TRISB|=0b10000; //make RB4 input so it doesn't interfere!
		TRISB|=0b100; 	//make RB2 input so it doesn't interfere!
	}
#endif


