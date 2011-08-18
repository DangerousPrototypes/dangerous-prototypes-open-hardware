/*
 *
 *	USB infrared remote control receiver transmitter firmware v1.0
 *	License: creative commons - attribution, share-alike
 *	Copyright Ian Lesnet 2010
 *	http://dangerousprototypes.com
 *
 */
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

//includes config fuses


//USB stack
#include "globals.h"
#include "configwords.h"	// JTR only included in main.c
#include "descriptors.h"	// JTR Only included in main.c
//#include "cdc.h"

extern unsigned char usb_device_state; // JTR2 corrected type
extern unsigned char cdc_trf_state;
extern BYTE cdc_In_buffer[64];
extern BDentry *Inbdp;

void user_configured_init(void);
void usb_start(void);
void initCDC(void);
void usb_init(ROMPTR const unsigned char*, ROMPTR const unsigned char*, ROMPTR const unsigned char*, int);
BYTE FAST_usb_handler(void);
//BYTE putPARTARRAYUSBUSART(char* data, unsigned char length);
//BYTE WaitInReady(void);
//
//	This variable tracks the current IR Toy mode
//
#pragma udata

static enum _mode {
    IR_MAIN = 0,
    IR_DECODER, //IRMAN IR RC decoder
    IR_SUMP, //SUMP logic analyzer
    IR_IO, //IR input output mode
    IR_S, //IR Sampling mode
    IR_REFLECT, // IR Reflection mode
    USB_UART,
    IRWIDGET
    //IR_RECORDER //record IR signal to EEPROM, playback
} mode = IR_MAIN; //mode variable tracks the IR Toy mode

//enum _mode DefaultMode = IR_DECODER;

struct _irtoy irToy;
BYTE inByte; // JTR3 Global
void SetupBoard(void);
void InterruptHandlerHigh();
void InterruptHandlerLow();
void SelfTest(void);
void GetUsbIrToyVersion(void);
void USBDeviceTasks(void);
void cleanup(void);
void ProcessDefaultMainMode(void);
void SetUpDefaultMainMode(void);
void IrSumpSetup(void);
void DefaultISR(void);
BYTE irSUMPservice(void); //pass this command SUMP
void DispatchISR(void);


#pragma code

void main(void) {
	static unsigned char ledtrig;

    initCDC(); // JTR this function has been highly modified It no longer sets up CDC endpoints.
    SetupBoard(); //setup the hardware, USB
    usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS); // TODO: Remove magic with macro
    usb_start();
    usbbufflush(); //flush USB input buffer system
    SetUpDefaultMainMode();
	ledtrig=1; //only shut LED off once
    //	Never ending loop services each task in small increments
    while (1) {
        do {
            if (!TestUsbInterruptEnabled()) //JTR3 added
                USBDeviceTasks(); ////service USB tasks Guaranteed one pass in polling mode even when usb_device_state == CONFIGURED_STATE
            if ((usb_device_state < DEFAULT_STATE)) { // JTR2 no suspendControl available yet || (USBSuspendControl==1) ){
                LedOff();
            } else if (usb_device_state < CONFIGURED_STATE) {
                LedOn();
            }else if((ledtrig==1) && (usb_device_state == CONFIGURED_STATE)){
				LedOff();
				ledtrig=0;
			}
        } while (usb_device_state < CONFIGURED_STATE);

        //TRISB &= 0x7f;
        //TRISB |= 0x40;
        //LATB |= 0x40;

        //mode = IRWIDGET;
        //irWidgetservice();

        switch (mode) { //periodic service routines
            case IR_SUMP:
                //SUMPlogicCommand();
                if (irSUMPservice() != 0) SetUpDefaultMainMode();

                break;
            case IR_IO: //increment IR_IO module dump state machine
                if (irIOservice() != 0) SetUpDefaultMainMode();

                break;
            case IR_S:
                if (irsService() != 0) SetUpDefaultMainMode();

                break;
            case IR_REFLECT:
                if (IrReflectService() != 0) SetUpDefaultMainMode();

                break;
            case USB_UART:
                if (Usb2UartService() != 0) SetUpDefaultMainMode();

                break;

                //case IR_RECORDER: 				//save IR wave to EEPROM for playback
                // Not currently supported
            // case IR_DECODER:
            default:

                ProcessIR(); //increment IR decoder state machine

                usbbufservice(); //service USB buffer system
                // Kludge entry to SUMP MODE. Test for commands: 0, 1, 2
                // Do not remove from input buffer, just take a PEEK.
                // SUMPLogicCommand will remove from input buffer
                // (Standardized coding)
                if (PEEKusbbufgetbyte(&inByte) > 0) {
                    switch (inByte) {
                        case 0: //SUMP clear
                        case 1: //SUMP run
                        case 2: //SUMP ID
                            mode = IR_SUMP; //put IR Toy in IR_SUMP mode
                            IrSumpSetup();
                            if (irSUMPservice() != 0) SetUpDefaultMainMode(); //pass this command SUMP
                            break;
                    }
                }

                if (usbbufgetbyte(&inByte) == 1) { //break; //get (and remove!) a single byte from the USB buffer
                    switch (inByte) {
                        case 'r': //IRMAN decoder mode
                        case 'R':
                            SetupRC5();
                            mode = IR_DECODER;
                            if (WaitInReady()) { //it's always ready, but this could be done better
                                cdc_In_buffer[0] = 'O'; //answer OK
                                cdc_In_buffer[1] = 'K';
                                putUnsignedCharArrayUsbUsart(cdc_In_buffer, 2);
                            }
                            break;

                        case 'S': //IRIO Sampling Mode
                        case 's':
                            mode = IR_S;
                            irsSetup();
                            break;
                        case 'X': //IRIO RXTX mode
                        case 'x':
                            mode = IR_IO;
                            irIOsetup();
                            break;
                        case 'E':
                        case 'e':
                            mode = IR_REFLECT;
                            IrReflectSetup();
                            break;
                        case 'U':
                        case 'u':
                            mode = USB_UART;
                            Usb2UartSetup();
                            break;
                        case 'T':
                        case 't'://self test
                            SelfTest(); //run the self-test
                            break;
                        case 'V':
                        case 'v':// Acquire Version
                            GetUsbIrToyVersion();
                            break;

                        case 'P':
                        case 'p':// Acquire Version
                            mode = IRWIDGET;
                            GetPulseFreq();
                            SetUpDefaultMainMode();
                            //GetPulseTime();
                            break;

                        case '$'://bootloader jump
                            BootloaderJump();
                            break;
                    }//switch(c)
                }//if byte

                break;
        } //switch(mode)
    }//end while
}//end main

//exits with IR LED on for visual inspection with a camera

void SelfTest(void) {
    unsigned char err = 0; //error flag starts with ASCII 0
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

    if (irToy.HardwareVersion == 2) {
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
    if (WaitInReady()) { //it's always ready, but this could be done better
        if (err) {
            LedOff(); //LED off
            cdc_In_buffer[0] = 'F'; //answer fail
            cdc_In_buffer[1] = 'A';
            cdc_In_buffer[2] = ((err & 0b1100) >> 2) + 0x30; //frequency detector error code
            cdc_In_buffer[3] = (err & 0b11) + 0x30; //receiver error code
            putUnsignedCharArrayUsbUsart(cdc_In_buffer, 4); // JTR3 moved this up to stop version number being send twice.
        } else {
            GetUsbIrToyVersion();
        }
    }
}
//
// Initial configuration
//

void ProcessDefaultMainMode(void) {
    /*
     *  ADD your IR_MAIN (DEFAULT) MODE HANDLER HERE
     * Currently this is the IR MAN DECODER
     */
    ProcessIR(); //increment IR decoder state machine
}

void SetUpDefaultMainMode(void) {
    //    switch (DefaultMode) {
    //        case IR_DECODER:
    SetupRC5();
    //            break;
    //        case IR_SUMP:
    //            IrSumpSetup();
    //            break;
    //      case IR_IO: //increment IR_IO module dump state machine
    //        mode = IR_IO;
    //      break;
    //case IR_S:
    //  irsSetup();
    //break;
    //    case IR_REFLECT:
    //    IrReflectSetup();
    //    break;
    //    case USB_UART:
    //    Usb2UartSetup();
    //    break;
    //}
    mode = IR_MAIN;
}

void AbortHandler(void) {
    unsigned int i, i2;

    SetupBoard();
    usbbufflush(); //flush USB input buffer system
    cleanup();
    SetUpDefaultMainMode();
    user_configured_init();
    for (i = 0; i < 6; i++) {
        LedOff();
        for (i2 = 0; i2 < 65535; i2++);
        LedOn();
        for (i2 = 0; i2 < 32684; i2++);
    }
}

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
        irToy.HardwareVersion = 1;
    } else {
        irToy.HardwareVersion = 2;
    }

    //cleanup
    IRRX_PULLUP = 1; //disable(1) RB pullups
    TRISB = 0xff; //all inputs
    IRFREQ_PIN_SETUP(); //all inputs
#else
    irToy.HardwareVersion = 0;
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

    //INTCONbits.GIEL = 1; //enable peripheral interrupts
    INTCONbits.GIEH = 1; //enable HIGH proirity interrupts
}

void GetUsbIrToyVersion(void) {
    if (WaitInReady()) {
        cdc_In_buffer[0] = 'V'; //answer OK
        cdc_In_buffer[1] = (irToy.HardwareVersion + 0x30);
        cdc_In_buffer[2] = FIRMWARE_VERSION_H;
        cdc_In_buffer[3] = FIRMWARE_VERSION_L;
        putUnsignedCharArrayUsbUsart(cdc_In_buffer, 4);
    }
}

//	Interrupt remap chain
//
//This function directs the interrupt to
// the proper function depending on the mode
// set in the mode variable.
#pragma interrupt InterruptHandlerHigh nosave= PROD, PCLATH, PCLATU, TBLPTR, TBLPTRU, TABLAT, section (".tmpdata"), section("MATH_DATA")

void InterruptHandlerHigh(void) {
    //   DispatchISR();
    ////   }
    //#pragma code
    //    void DispatchISR(void) {
    switch (mode) {
        case IRWIDGET:
            _asm call irWInterruptHandlerHigh, 0 _endasm
            break;
        case IR_IO:
            //_asm call irIOInterruptHandlerHigh, 0 _endasm //see IRIO.c
            irIOInterruptHandlerHigh();
            break;
        case IR_S:
            _asm call irsInterruptHandlerHigh, 0 _endasm //see IRIO.c
            break;
        case IR_SUMP:
            _asm call SUMPInterruptHandlerHigh, 0 _endasm //see SUMP.c
            break;
        case IR_DECODER:
            _asm call IRdecoderInterruptHandlerHigh, 0 _endasm //see RCdecoder.c
            break;
        case IR_REFLECT:
            _asm call IrReflectionInterruptHandlerHigh, 0 _endasm //see RCdecoder.c
            break;
        case USB_UART:
            _asm call Usb2UartInterruptHandlerHigh, 0 _endasm //see RCdecoder.c
            break;
        case IR_MAIN:
            _asm call DefaultISR, 0 _endasm
            break;
        default:

            // _asm call DefaultISR _endasm
            break;
    }
}

//#pragma interrupt DefaultISR

void DefaultISR(void) {
    _asm goto IRdecoderInterruptHandlerHigh _endasm //see RCdecoder.c

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
