/*
 *
 *	USB infrared remote control receiver transmitter firmware v1.0
 *	License: creative commons - attribution, share-alike
 *	Copyright Ian Lesnet 2010
 *	http://dangerousprototypes.com
 *
 */

/* *****************************************************************************
 IR TOY 2012. A folked version by JTR. Please see changelog.txt for details.

 * JTR Version 0.1 beta
********************************************************************************/

//
//Depending on the install location you may need to tweak the include paths under Project->build options.
//
//	Other options:
//	We also changed the default usb_descriptors.c to fit our needs.
//	You may need to double check these settings depending on your USB stack version.
//	*configDescriptor1[] remove _SELF from the attributes
//	*manufacturer and product string descriptors
#define REMAPPED_RESET_VECTOR_ADDRESS		0x800
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818

#define IRTOY

//USB stack
#include "prj_globals.h"
#include "..\dp_usb\usb_stack_globals.h"    // USB stack only defines Not function related.
#include "configwords.h"	// JTR only included in main.c
#include "descriptors.h"	// JTR Only included in main.c



extern BYTE usb_device_state; // JTR2 corrected type
extern BYTE cdc_In_len;
//extern BYTE IsSuspended;

#pragma udata

static enum _mode {
    IR_DECODER = 0, //IRMAN IR RC decoder
    IR_SUMP, //SUMP logic analyzer
    IR_S, //IR Sampling mode
    USB_UART,
    IRWIDGET
    //IR_RECORDER //record IR signal to EEPROM, playback
} mode = IR_DECODER; //mode variable tracks the IR Toy mode

BYTE HardwareVersion;

#pragma code

void main(void) {
    static BYTE ledtrig;
    BYTE OutByte;

    SetupBoard(); //setup the hardware, USB
    SetupRC5();
    usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS); // TODO: Remove magic with macro
    initCDC(); // JTR this function has been highly modified It no longer sets up CDC endpoints.
    usb_start();
    //usbbufflush(); //flush USB input buffer system

    ledtrig = 1; //only shut LED off once
    //	Never ending loop services each task in small increments
    while (1) {
        do {
           // if (!TestGlobalUsbInterruptEnabled()) //JTR3 added
                usb_handler(); ////service USB tasks Guaranteed one pass in polling mode even when usb_device_state == CONFIGURED_STATE
            if ((usb_device_state < DEFAULT_STATE)) { // JTR2 no suspendControl available yet || (USBSuspendControl==1) ){
                LedOff();
            } else if (usb_device_state < CONFIGURED_STATE) {
                LedOff();
            } else if ((ledtrig == 1) && (usb_device_state == CONFIGURED_STATE)) {
               // LedOn();
                ledtrig = 0;
            }
        } while(usb_device_state < CONFIGURED_STATE);

        //TRISB &= 0x7f;
        //TRISB |= 0x40;
        //LATB |= 0x40;

        //mode = IRWIDGET;
        //irWidgetservice();

#ifdef UARTONLY
        //mode = USB_UART;
        Usb2UartService(); // Never returns
#endif

        // Test for commands: 0, 1, 2 (Entry to SUMP MODE.)
        // Do not remove from input buffer, just take a PEEK.
        // SUMPLogicCommand will remove from input buffer
        // (Standardized coding)

        if (peek_getc_cdc(&OutByte)) {
            switch (OutByte) {
                case 0: //SUMP clear
                case 1: //SUMP run
                case 2: //SUMP ID
                    mode = IR_SUMP; //put IR Toy in IR_SUMP mode
                    irSUMPservice(); // Fully self contained, does not return until exited via 0x00 command.
                    cdc_In_len = 0;
                    mode = IR_DECODER;
                    SetupRC5();
                    break;

                case 'r': //IRMAN decoder mode
                case 'R':
                    OutByte = getc_cdc(); // now ok to remove byte from the USB buffer
                    SetupRC5();
                    mode = IR_DECODER;
                    putc_cdc('O');
                    putc_cdc('K');
                    CDC_Flush_In_Now();
                    break;
                case 'S': //IRs Sampling Mode
                case 's':
                    OutByte = getc_cdc(); // now ok to remove byte from the USB buffer
                    mode = IR_S;
                    irsService(); // Fully self contained, does not return until exited via 0x00 command.
                    cdc_In_len = 0;
                    mode = IR_DECODER;
                    SetupRC5();
                    break;
                case 'U':
                case 'u':
                    OutByte = getc_cdc(); // now ok to remove byte from the USB buffer
                    mode = USB_UART;
                    Usb2UartService();
                    break;
                case 'P':
                case 'p':// IR Widget mode
                    OutByte = getc_cdc(); // now ok to remove byte from the USB buffer
                    mode = IRWIDGET;
                    GetPulseFreq(); // Never returns
                    //GetPulseTime();
                    break;

                case 'T':
                case 't'://self test
                    OutByte = getc_cdc(); // now ok to remove byte from the USB buffer
                    SelfTest(); //run the self-test
                    break;
                case 'V':
                case 'v':// Acquire Version
                    OutByte = getc_cdc(); // now ok to remove byte from the USB buffer
                    GetUsbIrToyVersion();
                    break;
                case '$'://bootloader jump
                    OutByte = getc_cdc(); // now ok to remove byte from the USB buffer
                    BootloaderJump();
                    break;

                default:
                    OutByte = getc_cdc();

            }//switch(OutByte
        } // if peek OutByte == 1
        ProcessIR(); //increment IR decoder state machine
    }//end while(1)
}//end main

void SelfTest(void) {
    BYTE err = 0; //error flag starts with ASCII 0
    unsigned int cnt;

#ifndef USBIRTOY
    return err;
#endif

#define ERROR_RXPULLUP 		0b1
#define ERROR_RXACT 		0b10
#define ERROR_FREQPULLUP	0b100
#define ERROR_FREQACT		0b1000

    IRRXIE = 0; //disable RX interrupts
    T2IE = 0; //disable any Timer 2 interrupt
    IRRX_TRIS |= IRRX_PIN; //ir to input
    IRTX_LAT &= (~IRTX_PIN); //TX LED off
    IRTX_TRIS &= (~IRTX_PIN);
    CCP1CON = 0;
    T2CON = 0;
    cnt = 10000;
    while (cnt--);
    if (!(IRRX_PORT & IRRX_PIN)) err |= ERROR_RXPULLUP; //test IR RX pullup, should be high

    if (HardwareVersion == 2) {
        if (IRFREQ_CAP == 0) err |= ERROR_FREQPULLUP; //test IR Frequency detector pullup, should be high

        //turn IR LED solid on to test frequency detector
        IRTX_TRIS &= (~IRTX_PIN); //output
        IRTX_LAT |= IRTX_PIN; //LED on

        //give a little delay
        cnt = 1000;
        while (cnt--);

        //test IR Frequency detector, should now be off
        if (IRFREQ_CAP == 1) err |= ERROR_FREQACT;

        //LED back off
        IRTX_LAT &= (~IRTX_PIN);
    }

    //setup for IR TX
    /*
     * PWM registers configuration
     * Fosc = 48000000 Hz
     * Fpwm = 36144.58 Hz (Requested : 36000 Hz)
     * Duty Cycle = 50 %
     * Resolution is 10 bits
     * Prescaler is 4
     * Ensure that your PWM pin is configured as digital output
     * see more details on http://www.micro-examples.com/
     * this source code is provided 'as is',
     * use it at your own risks
     * http://www.micro-examples.com/public/microex-navig/doc/097-pwm-calculator
     */
    //IRTX_TRIS &=(~IRTX_PIN); //output
    //IRTX_LAT&=(~IRTX_PIN); //start low
    T2IF = 0; //clear the interrupt flag
    T2IE = 0; //disable interrupts
    PR2 = 0b01010010; //82
    T2CON = 0b00000101;
    CCPR1L = 0b00101001; //upper 8 bits of duty cycte
    CCP1CON = 0b00011100; //we leave this on for visual inspection (5-4 two LSB of duty, 3-0 set PWM)

    cnt = 40000;
    while (cnt--);

    if (IRRX_PORT & IRRX_PIN)
        err |= ERROR_RXACT; //IR LED should activate RX

    if (err) {
        LedOff(); //LED off
        putc_cdc('F'); //answer fail
        putc_cdc('A');
        putc_cdc(((err & 0b1100) >> 2) + 0x30); //frequency detector error code
        putc_cdc((err & 0b11) + 0x30); //receiver error code
        CDC_Flush_In_Now();
    } else {
        GetUsbIrToyVersion();
    }
}
//
// Initial configuration
//

void SetupBoard(void) {
    unsigned int cnt;

    //disable some defaults
    ADCON1 |= 0b1111; //all pins digital
    CVRCON = 0b00000000;

    //
    // VERSION DETECT
    //
    //test IR_FREQ pin to see if this is v1 or v2
    //CAP and EC to ground (C0 C1)
#if defined (USBIRTOY)
    IRFREQ_CAP_LAT &= (~IRFREQ_CAP_PIN); //ground
    IRFREQ_EC_LAT &= (~IRFREQ_EC_PIN); //ground
    IRFREQ_CAP_TRIS &= (~IRFREQ_CAP_PIN); //output
    IRFREQ_EC_TRIS &= (~IRFREQ_EC_PIN); //output

    PORTB = 0; //all ground
    TRISB = 0b11101011; //RB2 and RB4 to output/ground to prevent dualing pullups
    IRRX_PULLUP = 0; //enable(0) RB pullups

    cnt = 10;
    while (cnt--);

    //on v1 the pullups just hold RB1 high (INT==1)
    //on v2 RB1 and C0/C1 are connected INT will be 0
    if (IRFREQ_INT == 1) {
        HardwareVersion = 1;
    } else {
        HardwareVersion = 2;
    }

    //cleanup
    IRRX_PULLUP = 1; //disable(1) RB pullups
    TRISB = 0xff; //all inputs
    IRFREQ_PIN_SETUP(); //all inputs
#else
    HardwareVersion = 0;
#endif
    //
    // SETUP
    //
    //setup IR LED for IR TX
    IRTX_TRIS &= (~IRTX_PIN); //digital OUTPUT (must ground transistor)
    IRTX_LAT &= (~IRTX_PIN); //output to ground

    //visual indicator LED config
    LedOn(); //start with LED ON till USB connect
    LED_TRIS &= (~LED_PIN); //direction output

    //setup the timers
    CCP1CON = 0; //reset PWM registers
    CCP2CON = 0;
    T1CON = 0; //clear timer 1 control
    T2CON = 0; //clear timer 2 control

    //setup IR RX interrupt on RB32 or RB4 (see HardwareProfile.h)
    IRRX_PULLUP = 1; //disable port b pullups (0=enable)
    IRRX_LAT &= (~0b11101001); //ground unused port B pins
    IRRX_TRIS &= (~0b11101001); //output unused port B pins
    IRRX_TRIS |= IRRX_PIN; //direction to input
    IRRXIF = 0; //Reset the RB Port Change Interrupt Flag bit
    IRRXIE = 0; //startup in IR_DECODER mode, enable IR RX interrupt
#ifdef IRRX_ONINT2 	//make sure unused pin isn't going to interfere on dual connected PCBs
    IRRX_EDGE = 0; //falling edge interrupt on RB2
    TRISB |= 0b10000; //make RB4 input so it doesn't interfere!
#else
    TRISB |= 0b100; //make RB2 input so it doesn't interfere!
#endif
    T0_IP = 1; //timer 0 high priority
    T1_IP = 1; //timer 1 high priority
    T2_IP = 1; //timer 2 high priority
    T3_IP = 1; //timer 3 high priority
    IRRX_IP = 1; // IR DeMod high priority interrupt, either PORTB change or INT2 depending on hardware.
    IRRAWINT1_IP = 1;
    CCP1_IP = 1;
    EnableIRTOY_HI_IP();

    INTCONbits.GIEH = 1; //enable HIGH proirity interrupts
}

void GetUsbIrToyVersion(void) {
    putc_cdc('V');
    putc_cdc((HardwareVersion + 0x30));
    putc_cdc(FIRMWARE_VERSION_H);
    putc_cdc(FIRMWARE_VERSION_L);
    CDC_Flush_In_Now();
}

void USBSuspend(void) {

}

void USBWakeFromSuspend(void) {


}//end USBWakeFromSuspend

//	Interrupt remap chain
//
//This function directs the interrupt to
// the proper function depending on the mode
// set in the mode variable.
#pragma interrupt InterruptHandlerHigh nosave= PROD, PCLATH, PCLATU, TBLPTR, TBLPTRU, TABLAT, section("MATH_DATA"), section (".tmpdata")

void InterruptHandlerHigh(void) {

#ifndef UARTONLY
    switch (mode) {
        case IRWIDGET:
            _asm call irWInterruptHandlerHigh, 0 _endasm
            break;
        case IR_S:
            _asm call irsInterruptHandlerHigh, 0 _endasm //see IRs.c
            break;
        case IR_DECODER:
            _asm call IRdecoderInterruptHandlerHigh, 0 _endasm //see RCdecoder.c
            break;
        case USB_UART:
            _asm call Usb2UartInterruptHandlerHigh, 0 _endasm //see RCdecoder.c
            break;
        default:
            break;
    }
#else
            _asm call Usb2UartInterruptHandlerHigh, 0 _endasm //see RCdecoder.c
#endif

}

//We didn't use the low priority interrupts,
// but you could add your own code here
#pragma interruptlow InterruptHandlerLow

void InterruptHandlerLow(void) {
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
