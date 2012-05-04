

//USB stack
#include "..\dp_usb\usb_stack_globals.h"    // USB stack only defines Not function related.
#include "descriptors.h"	// JTR Only included in main.c
#include "configwords.h"	// JTR only included in main.c


#ifdef __18CXX
#define REMAPPED_RESET_VECTOR_ADDRESS		0x800
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818
#endif

void SetupBoard(void);
void InterruptHandlerHigh();
void InterruptHandlerLow();
void USBSuspend(void);

extern BYTE usb_device_state;


#pragma udata


#pragma code
#ifdef PIC_18F
void main(void)
#else

int main(void)
#endif
{
    BYTE RecvdByte;

    initCDC(); // JTR this function has been highly modified It no longer sets up CDC endpoints.
    SetupBoard(); //setup the hardware, USB
    usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS); // TODO: Remove magic with macro
    usb_start();

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

#if defined USB_INTERRUPTS // See the prj_usb_config.h file.
    EnableUsbPerifInterrupts(USB_TRN + USB_SOF + USB_UERR + USB_URST);
#if defined __18CXX
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
#endif
    EnableUsbGlobalInterrupt(); // Only enables global USB interrupt. Chip interrupts must be enabled by the user (PIC18)
#endif


    do {
#ifndef USB_INTERRUPTS
        usb_handler();
#endif
    } while (usb_device_state < CONFIGURED_STATE);

    usb_register_sof_handler(CDCFlushOnTimeout); // Register our CDC timeout handler after device configured


    do {
        //If USB_INTERRUPT is not defined each loop should have at least one additional call to the usb handler to allow for control transfers.

#ifndef USB_INTERRUPTS
        usb_handler();
#endif
        // The CDC module will call usb_handler each time a BULK CDC packet is sent or received.

        if (poll_getc_cdc(&RecvdByte)) // If there is a byte ready will return with the number of bytes available and received byte in RecvdByte
            putc_cdc(RecvdByte); //

        if (peek_getc_cdc(&RecvdByte)) { // Same as poll_getc_cdc except that byte is NOT removed from queue.
            RecvdByte = getc_cdc(); // This function will wait for a byte and return and remove it from the queue when it arrives.
            putc_cdc(RecvdByte);
        }
        if (poll_getc_cdc(&RecvdByte)) { // If there is a byte ready will return with the number of bytes available and received byte in RecvdByte
            putc_cdc(RecvdByte); //
            CDC_Flush_In_Now(); // when it has to be sent immediately and not wait for a timeout condition.
        }
    } while (1);
} //end main

void SetupBoard(void) {
#if defined (BUSPIRATEV4)
    INTCON1bits.NSTDIS = 1;
    volatile unsigned long delay = 0xffff;
    CLKDIV = 0x0000; // Set PLL prescaler (1:1)
    //	BP_LEDUSB_DIR=0;	// output
    CORCONbits.PSV = 1; // JTR PIC24 fixup ?? PSV not being initialized. May have been done by c_init though.
    PSVPAG = 0; //
    OSCCONbits.SOSCEN = 0;
    AD1PCFGL = 0x7FD8; //BUSPIRATEV4 has five analog pins b0, b1, b2, b5, b15
    AD1PCFGH = 0x2;
    TRISBbits.TRISB10 = 0; // Let there be LEDS
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    while (delay--);
#endif

#if defined (IRTOY)
    //disable some defaults
    ADCON1 |= 0b1111; //all pins digital
    CVRCON = 0b00000000;
#endif
    //visual indicator LED config
    //LedOn(); //start with LED ON till USB connect
    //LedTris()
}

void USBSuspend(void) {}

#if defined(USB_INTERRUPTS)
#if defined(BUSPIRATEV4)
#pragma interrupt _USB1Interrupt

void __attribute__((interrupt, auto_psv)) _USB1Interrupt() {
    //USB interrupt
    //IRQ enable IEC5bits.USB1IE
    //IRQ flag	IFS5bits.USB1IF
    //IRQ priority IPC21<10:8>
    usb_handler();
    ClearGlobalUsbInterruptFlag();
}
#endif

#if defined(__18CXX)
//	Interrupt remap chain
//
//This function directs the interrupt to
// the proper function depending on the mode
// set in the mode variable.
#pragma interrupt InterruptHandlerHigh nosave= PROD, PCLATH, PCLATU, TBLPTR, TBLPTRU, TABLAT, section (".tmpdata"), section("MATH_DATA")

void InterruptHandlerHigh(void) { //Also legacy mode interrupt.
	usb_handler();
    ClearGlobalUsbInterruptFlag();
}

//USB stack on low priority interrupts,
#pragma interruptlow InterruptHandlerLow nosave= PROD, PCLATH, PCLATU, TBLPTR, TBLPTRU, TABLAT, section (".tmpdata"), section("MATH_DATA")

void InterruptHandlerLow(void) {
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
#endif

#pragma code


