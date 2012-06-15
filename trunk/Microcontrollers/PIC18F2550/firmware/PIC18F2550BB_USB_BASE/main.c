// Open source PIC USB stack echo demo
// USB stack by JTR and Honken
// CC-BY
//
// USB driver files should be in '..\dp_usb\'
// Enter a USB VID and PID in prj_usb_config.h

//USB stack
#include "..\dp_usb\usb_stack_globals.h"    // USB stack only defines Not function related.
#include "descriptors.h"	// JTR Only included in main.c
#include "configwords.h"	// JTR only included in main.c

// PIC18F Move reset vectors for bootloader compatibility
#define REMAPPED_RESET_VECTOR_ADDRESS		0x800
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818

void SetupBoard(void);
void InterruptHandlerHigh();
void InterruptHandlerLow();
void USBSuspend(void);

unsigned char PA, PB, clkF=0, DATA4=0,RS,RW;

#pragma udata
extern BYTE usb_device_state;

#pragma code
void main(void)
{
    BYTE RecvdByte;

    initCDC(); // setup the CDC state machine
    SetupBoard(); //setup the hardware, customize for your hardware
    usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS); // initialize USB. TODO: Remove magic with macro
    usb_start(); //start the USB peripheral

// PIC18 INTERRUPTS
// It is the users resposibility to set up high, low or legacy mode
// interrupt operation. The following macros for high and low interrupt
// setup have been removed:

//#define EnableUsbHighPriInterrupt()             do { RCONbits.IPEN = 1; IPR2bits.USBIP = 1; INTCONbits.GIEH = 1;} while(0) // JTR new
//#define EnableUsbLowPriInterrupt()              do { RCONbits.IPEN = 1; IPR2bits.USBIP = 0; INTCONbits.GIEL = 1;} while(0)  // JTR new

// By default, the interrupt mode will be LEGACY (ISR Vector 0x08)
// (Same as high priority vector wise but the operation (latency) is
// not the same. Consult the data sheet for details.)

// If a priority mode is enabled then this affects ALL other interrupt
// sources therefore it does not belong to the usb stack to be
// doing this. It is a global, user application choice.

    EnableUsbPerifInterrupts(USB_TRN + USB_SOF + USB_UERR + USB_URST);
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    EnableUsbGlobalInterrupt(); // Only enables global USB interrupt. Chip interrupts must be enabled by the user (PIC18)


// Wait for USB to connect
    do {
    } while (usb_device_state < CONFIGURED_STATE);

    usb_register_sof_handler(CDCFlushOnTimeout); // Register our CDC timeout handler after device configured

// Main echo loop
    do 
	{
		//Enter code here
		// Receive and send method 2
		// Same as poll_getc_cdc except that byte is NOT removed from queue.
		//This function will wait for a byte and return and remove it from the queue when it arrives.
        if (peek_getc_cdc(&RecvdByte)) { 
            RecvdByte = getc_cdc(); 
            putc_cdc(RecvdByte+1);
        }
    } while (1);

} //end main



/////////////////////////////////////////////////////////////////////////////
//board hardware setup
//add your hardware here
void SetupBoard(void) {
    //disable some defaults
    ADCON1 |= 0b1111; //all pins digital
    CVRCON = 0b00000000;
}

// USB suspend not yet enabled
void USBSuspend(void) {}

//interrupt routines for PIC 18 and PIC24
//	Interrupt remap chain
//
//This function directs the interrupt to
// the proper function depending on the mode
// set in the mode variable.
//USB stack on low priority interrupts,
#pragma interruptlow InterruptHandlerLow nosave= PROD, PCLATH, PCLATU, TBLPTR, TBLPTRU, TABLAT, section (".tmpdata"), section("MATH_DATA")
void InterruptHandlerLow(void) {
   if(PIR2bits.USBIF)//usb interrupt
	{
		usb_handler();
   		ClearGlobalUsbInterruptFlag();
	}
}

#pragma interrupt InterruptHandlerHigh nosave= PROD, PCLATH, PCLATU, TBLPTR, TBLPTRU, TABLAT, section (".tmpdata"), section("MATH_DATA")
void InterruptHandlerHigh(void) { //Also legacy mode interrupt.
   if(PIR2bits.USBIF)//usb interrupt
	{
	usb_handler();
    ClearGlobalUsbInterruptFlag();
	}
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

#pragma code


