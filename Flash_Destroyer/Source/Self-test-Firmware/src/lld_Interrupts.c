/*
lld_Interrupts - Lower Layer Driver for Interrupt

*/

#include "globals.h"





#pragma udata
static enum _mode {
        FLASH_DESTROYER
} mode=FLASH_DESTROYER; //mode variable tracks the IR Toy mode


//
//
//      Interrupt remap chain
//
//
//This function directs the interrupt to
// the proper function depending on the mode
// set in the mode variable.



#pragma code InterruptHandlerHigh
void InterruptHandlerHigh(void){
        switch(mode){
#if 0
                case IR_IO:
                        _asm goto irIOInterruptHandlerHigh _endasm //see IRIO.c
                        break;
                case IR_SUMP:
                        _asm goto SUMPInterruptHandlerHigh _endasm //see SUMP.c
                        break;
                case IR_DECODER:
                        _asm goto IRdecoderInterruptHandlerHigh _endasm //see RCdecoder.c
                        break;
#endif
                case FLASH_DESTROYER:
						_asm goto hal_7SegmentISR _endasm //see RCdecoder.c
						break;
        }
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

//relocate the reset vector
extern void _startup (void);
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

/////////////////////////
