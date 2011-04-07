/*
This is a simple player for TVBGONE power codes.
Our player is simple because PIC C18 has easy 
reads from program memory. 

This code was written based on the description 
of the data packing method published on the Adafruit 
website. It should be a clean, black-box rewrite, but 
we'll release it as CC 2.5 Attrib & Share Alike 
out of respect for the original authors.

PIC C18 Player (c) Ian Lesnet 2009
for use with IR Toy v1.0 hardware.
http://dangerousprototypes.com

With credits to:

TV-B-Gone Firmware version 1.2
for use with ATtiny85v and v1.2 hardware
(c) Mitch Altman + Limor Fried 2009
Last edits, August 16 2009

With some code from:
Kevin Timmerman & Damien Good 7-Dec-07

Distributed under Creative Commons 2.5 -- Attib & Share Alike

Ported to PIC (18F2550) by Ian Lesnet 2009
*/
#include "HardwareProfile.h"
#include "Compiler.h"

#include "WORLDcodes.h" //include TVBGone code data

const rom unsigned char num_NAcodes = NUM_NA_CODES; //NUM_ELEM(NApowerCodes);

//These are all the variables we need to 
// slurp down the TVBGONE POWER codes and get 
// the actuall delay values.
static struct _tvbgoneparser{
	unsigned char codecnt;
	unsigned char paircnt;
	unsigned char samplebitcnt;
	unsigned char samplebytecnt;
	unsigned char bittracker;
	unsigned char timetableindex;	
	unsigned int onTime;
	unsigned int offTime;
	unsigned char numpairs;
}tvbg;

volatile void delayint10US(unsigned int delay);

//
//
// This player uses blocking delays to get the timing just right.
// The PIC18F2550 USB driver requires cooperative multi-tasking, so this won't work with an active USB connection. 
// Actually, the USB connection will stop working if you were to run this code.
//
//
void tvbgonePlayer(void){
	T1IE=0; //interrupts off
	T1IF=0;

	for(tvbg.codecnt=0; tvbg.codecnt<num_NAcodes; tvbg.codecnt++){
		//setup indicator LED
		LEDout();
		LEDoff();

		//setup IR LED pin
		IRTX_TRIS|=IRTX_PIN;//digital INPUT (no PWM until active)
		IRTX_LAT&=(~IRTX_PIN);//direction 0

		//get and set PWM frequency
		if(NApowerCodes[tvbg.codecnt]->timer_val>0){ //setup PWM with this value
			PR2=NApowerCodes[tvbg.codecnt]->timer_val; //period
			CCPR1L=(NApowerCodes[tvbg.codecnt]->timer_val>>1); //50% duty cycle
			CCP1CON = 0b00001100 ; //(5-4 two LSB of duty, 3-0 set PWM)
			T2CON = 0b00000101 ;//timer and prescalers (pre:x4)
		}else{//some don't use PWM, setup for direct on/off
			T2CON=0;
			CCP1CON=0;
			IRTX_LAT|=IRTX_PIN;//high, but off because direction = input
		}

		//setup the bit tracker and sample counter offset
		tvbg.bittracker=0b10000000;	
		tvbg.samplebytecnt=0;

		//there are numpairs pairs of bitcompression length in *samples that refer to value pairs in *times
		for(tvbg.paircnt=0; tvbg.paircnt<NApowerCodes[tvbg.codecnt]->numpairs; tvbg.paircnt++){
			
			//get the next index to the the times table values
			tvbg.timetableindex=0;	
			for(tvbg.samplebitcnt=0; tvbg.samplebitcnt<NApowerCodes[tvbg.codecnt]->bitcompression; tvbg.samplebitcnt++){
				tvbg.timetableindex=(tvbg.timetableindex<<1);
				if((NApowerCodes[tvbg.codecnt]->samples[tvbg.samplebytecnt] & tvbg.bittracker)!=0) 
					tvbg.timetableindex|=0b1; //set first bit
				tvbg.bittracker=(tvbg.bittracker>>1);
				if(tvbg.bittracker==0){
					tvbg.bittracker=0b10000000;
					tvbg.samplebytecnt++;
				}				
			}
		
			//adjust the index, there are two variables for each entry
			tvbg.timetableindex*=2; //multiply by two, the compiler knows each is an int (2 bytes)

			//PWM for ON time
			IRTX_TRIS&=(~IRTX_PIN);//IR LED output
			delayint10US(NApowerCodes[tvbg.codecnt]->times[tvbg.timetableindex]);//on time is first table entry

			//pause PWM for OFF time
			IRTX_TRIS|=IRTX_PIN;//IR LED input (no PWM)
			delayint10US(NApowerCodes[tvbg.codecnt]->times[(tvbg.timetableindex+1)]);//off time is next entry

		}//for pairs loop
		
		LEDon();//blink LED
		delayint10US(25000);//delay 250ms between codes
		LEDoff();

	}//for codes loop

	CCP1CON = 0; //(5-4 two LSB of duty, 3-0 set PWM)
	T2CON = 0;//timer and prescalers (pre:x4)

}

//
//
//	Simple blocking delay using Timer1
//	Polls interrupt to see when 10us have passed, repeats.
//	Hand tune T1_10usOffset in HardwareProfile.h
//
//
//volatile void delayint10US(unsigned int delay);
volatile void delayint10US(unsigned int delay){
	while(delay){
		T1ON=0; //timer off
		T1_10usOffset();//preload timer values
		T1ON=1;//timer back on
		while(!T1IF);//wait for T1flag
		T1IF=0;
		delay--;
	}
}

//the hardest part of this project is keeping the pointers straight
//this is a test that shows how to get the actual values from each element
//volatile static unsigned char timer, pairs, bits, sample;
//volatile static unsigned int times;
//timer=NApowerCodes[i]->timer_val;
//pairs=NApowerCodes[i]->numpairs;
//bits=NApowerCodes[i]->bitcompression;
//sample=NApowerCodes[i]->samples[0];
//times=NApowerCodes[i]->times[0];

