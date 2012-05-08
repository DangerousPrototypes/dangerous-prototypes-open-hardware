#include <p18cxxx.h>
//USB stack
#include "..\dp_usb\usb_stack_globals.h"    // USB stack only defines Not function related.
#include "descriptors.h"	// JTR Only included in main.c
#include "config.h"
#include "MMA7455L.h"
#include "SPI.h"
#include "SPIFlash.h"
#include "POVToy.h"
#include "types.h"

// PIC18F Move reset vectors for bootloader compatibility
	#define REMAPPED_RESET_VECTOR_ADDRESS		0x800
	#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
	#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818

void init(void);
void InterruptHandlerHigh();
void InterruptHandlerLow();
void USBSuspend(void);

#pragma udata
extern BYTE usb_device_state;

#pragma code// declare executable instructions
void main()
{
    BYTE RecvdByte;

    initCDC(); // setup the CDC state machine

    init();                   //Make all port pins digital(ADCON) and PLL Config
    POVToy_Init             //POV Toy Initialization sequence
    usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS); // initialize USB. TODO: Remove magic with macro
    usb_start(); //start the USB peripheral

    //Set up global interrupts
	#if defined USB_INTERRUPTS // See the prj_usb_config.h file.
    EnableUsbPerifInterrupts(USB_TRN + USB_SOF + USB_UERR + USB_URST);
	IPR2bits.USBIP = 1;
	#endif
    RCONbits.IPEN = 1;          // Enable priority levels on interrupts
    INTCONbits.GIEL = 1;        // Allow low priority interrupts
    INTCONbits.GIEH = 1;        // Enable interrupts
	#if defined USB_INTERRUPTS // See the prj_usb_config.h file.
    EnableUsbGlobalInterrupt(); // Only enables global USB interrupt. Chip interrupts must be enabled by the user (PIC18)
	#endif


// Wait for USB to connect
    do {
#ifndef USB_INTERRUPTS
        usb_handler();
#endif
    } while (usb_device_state < CONFIGURED_STATE);

    usb_register_sof_handler(CDCFlushOnTimeout); // Register our CDC timeout handler after device configured

// Main echo loop
    do {

// If USB_INTERRUPT is not defined each loop should have at least one additional call to the usb handler to allow for control transfers.
#ifndef USB_INTERRUPTS
        usb_handler();
#endif

// Receive and send method 1
// The CDC module will call usb_handler each time a BULK CDC packet is sent or received.
// If there is a byte ready will return with the number of bytes available and received byte in RecvdByte
        if (poll_getc_cdc(&RecvdByte)) 
            putc_cdc(RecvdByte+1); //

// Receive and send method 2
// Same as poll_getc_cdc except that byte is NOT removed from queue.
// This function will wait for a byte and return and remove it from the queue when it arrives.
        if (peek_getc_cdc(&RecvdByte)) { 
            RecvdByte = getc_cdc(); 
            putc_cdc(RecvdByte+1);
        }

// Receive and send method 3
// If there is a byte ready will return with the number of bytes available and received byte in RecvdByte
// use CDC_Flush_In_Now(); when it has to be sent immediately and not wait for a timeout condition.
        if (poll_getc_cdc(&RecvdByte)) { 
            putc_cdc(RecvdByte+1); //
            CDC_Flush_In_Now(); 
        }
    } while (1);
}

void init(void)
{
    //MCU initializtion
    unsigned long int count = 0xFFFF; // **** Fix this when integrating USB driver.
    //All pins digital
    ANCON0 = 0xFF;
    ANCON1 = 0b00011111;

    //on 18F24J50 we must manually enable PLL and wait at least 2ms for a lock
    OSCTUNEbits.PLLEN = 1;  //enable PLL
    while(count--);//wait for lock
}

//-------------------I-n-t-e-r-r-u-p-t-s----------B-e-g-i-n---------------------
// Iterrupt Service Routines

// USB suspend not yet enabled
void USBSuspend(void) {}

//interrupt routines for PIC 18 and PIC24
#if defined(USB_INTERRUPTS)
//	Interrupt remap chain
//
//This function directs the interrupt to
// the proper function depending on the mode
// set in the mode variable.
//USB stack on low priority interrupts,
#pragma interruptlow InterruptHandlerLow //nosave= PROD, PCLATH, PCLATU, TBLPTR, TBLPTRU, TABLAT, section (".tmpdata"), section("MATH_DATA")
void InterruptHandlerLow(void) {
    POVToy_LowPriorityISR();

    //usb_handler();
    //ClearGlobalUsbInterruptFlag();
}

#pragma interrupt InterruptHandlerHigh nosave= PROD, PCLATH, PCLATU, TBLPTR, TBLPTRU, TABLAT, section (".tmpdata"), section("MATH_DATA")
void InterruptHandlerHigh(void) { //Also legacy mode interrupt.
	usb_handler();
    ClearGlobalUsbInterruptFlag();
}

//these statements remap the vector to our function
//When the interrupt fires the PIC checks here for directions
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS

void Remapped_High_ISR(void) {
    _asm goto InterruptHandlerHigh _endasm
}

#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS

void Remapped_Low_ISR(void) {
    _asm goto InterruptHandlerLow _endasm
}

//relocate the reset vector
extern void _startup(void);
#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS

void _reset(void) {
    _asm goto _startup _endasm
}
//set the initial vectors so this works without the bootloader too.
#pragma code HIGH_INTERRUPT_VECTOR = 0x08

void High_ISR(void) {
    _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
}
#pragma code LOW_INTERRUPT_VECTOR = 0x18

void Low_ISR(void) {
    _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
}
#endif

#pragma code

//-------------------I-n-t-e-r-r-u-p-t-s----------E-n-d---------------------------
