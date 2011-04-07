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
#include "Compiler.h"
#include "config.h" //includes config fuses
#include "HardwareProfile.h" //hardware definitions
#include "TVBGONE.h" 	//tvbgone functions

#pragma code
void main(void){   		
    ADCON1 |= 0b1111;   	//all pins digital
	CVRCON=0b00000000;
   	//disable all interrupts so it doesn't exit sleep on a pin change, etc.
	INTCONbits.GIEL = 0;//peripheral interrupts
   	INTCONbits.GIEH = 0;//interrupts

	tvbgonePlayer();//do TVBGONE	

	Sleep(); 	//got to zero power sleep, wake on MCLR reset or power cycle
				//should sleep forever because no interrupts are set
}//end main

//relocate the reset vector to work with the bootloader
extern void _startup (void);  
#pragma code REMAPPED_RESET_VECTOR = 0x800
void _reset (void){
    _asm goto _startup _endasm
}
