#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018

#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "RCdecoder.h" 	//RC5 decoder
#include "HardwareProfile.h"
#include "config.h" 
#include "shiftbrite.h"

#pragma udata
void SetupBoard(void);
void InterruptHandlerHigh();
void InterruptHandlerLow();

#pragma code
void main(void){   		

	SetupBoard(); 	//setup the hardware
	SetupShiftBrite();
	SetupRC5(); 	//start in RC decoder mode

	//
	//	Never ending loop services each task in small increments
	//	
	while(1){		
		ProcessIR();   					//increment IR decoder state machine
	}
}//end main

//
//
// Initial configuration
//
//
void SetupBoard(void){
	//disable some defaults
    ADCON1 |= 0b1111;   	//all pins digital
	CVRCON=0b00000000;

	//visual indicator LED config
	LED_LAT |=LED_PIN; 		//start with LED ON till USB connect 
	LED_TRIS &=(~LED_PIN); 	//direction output

	//setup the timers
	CCP1CON=0;			//reset PWM registers
	CCP2CON=0;
	T1CON=0; 			//clear timer 1 control
	IPR1bits.TMR1IP=1;	//timer 1 high priority
	T2CON=0; 			//clear timer 2 control
	IPR1bits.TMR2IP=1;	//timer 2 high priority

	//setup IR RX interrupt on RB32 or RB4 (see HardwareProfile.h)
	IRRX_PULLUP=1; 	//(dis)enable port b pullups (0=enable)
	IRRX_LAT=0;		//ground
	IRRX_TRIS=0;	//output
	IRRX_TRIS|=IRRX_PIN; //direction to input
	IRRX_IF = 0;    //Reset the RB Port Change Interrupt Flag bit   
	IRRX_IE = 0;  	//startup in IR_DECODER mode, enable IR RX interrupt
	IRRX_IP = 1; 	//high priority interrupt
	#ifdef IRRX_ONINT2 	//make sure unused pin isn't going to interfere on dual connected PCBs
		IRRX_EDGE = 0; 	//falling edge interrupt on RB2
		TRISB|=0b10000; //make RB4 input so it doesn't interfere!
	#else
		TRISB|=0b100; 	//make RB2 input so it doesn't interfere!
	#endif

   	INTCONbits.GIEL = 1;//enable peripheral interrupts
   	INTCONbits.GIEH = 1;//enable interrupts
}

//
//
//	Interrupt remap chain
// 	
//
//This function directs the interrupt to 
// the proper function 
#pragma code InterruptHandlerHigh
void InterruptHandlerHigh(void){
	_asm goto IRdecoderInterruptHandlerHigh _endasm //see IRIO.c
}

//We didn't use the low priority interrupts, 
// but you could add your own code here
#pragma interruptlow InterruptHandlerLow
void InterruptHandlerLow(void){}

//these statements remap the vector to our function
//When the interrupt fires the PIC checks here for directions
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void){
     _asm goto InterruptHandlerHigh _endasm
}

#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
void Remapped_Low_ISR (void){
     _asm goto InterruptHandlerLow _endasm
}

#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
	//relocate the reset vector
	extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
	void _reset (void){
	    _asm goto _startup _endasm
	}
	//set the initial vectors so this works without the bootloader too.
	#pragma code HIGH_INTERRUPT_VECTOR = 0x08
	void High_ISR (void){
	     _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#pragma code LOW_INTERRUPT_VECTOR = 0x18
	void Low_ISR (void){
	     _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
	}
#endif	



