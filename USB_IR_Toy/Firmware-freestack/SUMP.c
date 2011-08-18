/*
 *
 *	USB infrared remote control receiver transmitter firmware v1.0
 *	License: creative commons - attribution, share-alike
 *	Copyright Ian Lesnet 2010
 *	http://dangerousprototypes.com
 *
 */
//
// SUMP LA
//#ifdef SUMP_LA

#include "globals.h"
#include "PICUSB.h"

extern BYTE cdc_In_buffer[64];
extern BYTE cdc_In_bufferA[64];
extern BYTE cdc_In_bufferB[64];
extern BYTE cdc_Out_bufferA[64];
extern BYTE cdc_Out_bufferB[64];
extern BYTE inByte;
extern BYTE *InPtr;
extern BYTE *OutPtr;
void SumpReset(void);
//commandset
//http://www.sump.org/projects/analyzer/protocol/
#define SUMP_RESET 0x00
#define SUMP_RUN	0x01
#define SUMP_ID	0x02
#define SUMP_META	0x04
#define SUMP_XON	0x11
#define SUMP_XOFF 0x13

volatile static enum _LAstate {
    LA_IDLE = 0,
    LA_ARMED,
    LA_DUMP,
    LA_RESET,
    LA_ZLP
} LAstate = LA_IDLE;

volatile static struct {
    unsigned int sample;
    unsigned int ptr;
    unsigned char btrack;
} loga;

#ifdef SUMP_8CH
#pragma udata usb_data3
#endif

#ifdef SUMPMODEIRRAW
#define SUMP_PIN IRRAW
#endif
#ifdef SUMPMODEIRRX
#define SUMP_PIN IRX
#endif

#pragma udata

void IrSumpSetup(void) {
    BYTE dummy;
    //setup IR SUMP mode
    //IRRXIE = 0; //disable RX interrupts
    // T2IE = 0; //disable any Timer 2 interrupt
    dummy = IRRX_PORT; // Init read for PORTB IOR
}

BYTE irSUMPservice(void) {
    unsigned int i, i2;

    enum _SUMP {
        C_IDLE = 0,
        C_PARAMETERS,
        C_PROCESS,
    } sumpRXstate = C_IDLE;

    static struct _sumpRX {
        unsigned char command[5];
        unsigned char parameters;
        unsigned char parCnt;
    } sumpRX;

    usbbufservice(); //service USB buffer system
    if (usbbufgetbyte(&inByte) == 1) {//process any command bytes
        WaitInReady();
        switch (sumpRXstate) { //this is a state machine that grabs the incoming commands one byte at a time
            case C_IDLE:
                switch (inByte) {//switch on the current byte
                    case SUMP_RESET://reset
                        SumpReset();
                        return 0xFF;
                        break;
                    case SUMP_ID://SLA0 or 1 backwards: 1ALS
                        cdc_In_buffer[0] = '1';
                        cdc_In_buffer[1] = 'A';
                        cdc_In_buffer[2] = 'L';
                        cdc_In_buffer[3] = 'S';
                        putUnsignedCharArrayUsbUsart(cdc_In_buffer, 4);
                        break;
                    case SUMP_RUN://arm the triger
                        IRRXIF = 0; //Reset the RB Port Change Interrupt Flag bit
                        IRRXIE = 0; //Enables the RB port change interrupt
                        WaitInReady();
                        //counter = 0;
                        LedOff(); //ARMED, turn on LED
                        //LAstate = LA_ARMED;
                        LAstate = LA_DUMP;
                        ArmCDCOutDB();
                        loga.ptr = 0;
                        loga.sample = 0;
                        *InPtr = IRRX_PORT;
                        T2IE = 0; //disable interrupts...
                        T2ON = 0; //tmr2 off
                        TRISB |= 0x10;
                        TRISB &= 0x1F;

                        for (i = 0; i < 3; i++) {
                            LedOff();
                            for (i2 = 0; i2 < 65535; i2++);
                            LedOn();
                            for (i2 = 0; i2 < 65535; i2++);
                        }

                        IRRXIF = 0; //Reset the RB Port Change Interrupt Flag bit
                        IRRXIE = 1; //Enables the RB port change interrupt

                        INTCONbits.GIEL = 1; //enable peripheral interrupts
                        INTCONbits.GIEH = 1; //enable interrupts

                        break;

                    case SUMP_META://meta data
                        cdc_In_buffer[0] = 0x40;
                        cdc_In_buffer[1] = 0x08; //JTR3 sump 2 8 channels
                        cdc_In_buffer[2] = 0x41;
                        cdc_In_buffer[3] = 0x02;
                        cdc_In_buffer[4] = 0x00;
                        putUnsignedCharArrayUsbUsart(cdc_In_buffer, 5);
                        break;
                    case SUMP_XON://resume send data
                        //	xflow=1;
                        break;
                    case SUMP_XOFF://pause send data
                        //	xflow=0;
                        break;
                    default://long command
                        sumpRX.command[0] = inByte; //store first command byte
                        sumpRX.parameters = 4; //all long commands are 5 bytes, get 4 parameters
                        sumpRX.parCnt = 0; //reset the parameter counter
                        sumpRXstate = C_PARAMETERS;
                        break;
                }
                break;
            case C_PARAMETERS:
                sumpRX.command[sumpRX.parCnt] = inByte; //store each parameter
                sumpRX.parCnt++;
                if (sumpRX.parCnt < sumpRX.parameters) break; //if not all parameters, quit
            case C_PROCESS: //ignore all long commands for now
                sumpRXstate = C_IDLE;
                break;
        }
    }


    switch (LAstate) {//dump data
            //case IDLE:
            //case ARMED:
            //case LA_START_DUMP:
        case LA_DUMP: // JTR3 does nothing now except run the back ground USB STATE machine.
            // JTR2 Does NOT send ZLP after each packet only one at the end is required.
            do {

                if (0 != FAST_usb_handler()) {
                    // JTR2 Need to pop the CDC TX (USB IN) tranfer from the USB FIFO and also give SETUP PACKETs a chance.
                    LAstate = LA_IDLE;
                    for (i = 0; i < 6; i++) {
                        LedOff();
                        for (i2 = 0; i2 < 65535; i2++);
                        LedOn();
                        for (i2 = 0; i2 < 32684; i2++);
                    }
                    return 0xff;
                }

            } while (LAstate == LA_DUMP);

            DisArmCDCOutDB();
            break;
        case LA_ZLP:
            SendZLP();
            LAstate = LA_RESET;
        case LA_RESET:
            SumpReset();
            return 0xff;
            break;
    }
    return 0;
}

void SumpReset(void) {
    T2IE = 0; //disable interrupts...
    T2ON = 0; //tmr2 off
    IRRXIE = 0; //DISABLE RB port change interrupt
    LAstate = LA_IDLE;
    DisArmCDCInDB();
}

//high priority interrupt routine
// #pragma interrupt SUMPInterruptHandlerHigh

void SUMPInterruptHandlerHigh(void) {
    if (T2IE == 1 && T2IF == 1) { //is this timer 2 interrupt?  //JTR2 swapped positions
#ifndef SUMP_8CH
        SampleBufferx5[loga.ptr] = 0x30;
        if ((IRRX_PORT & IRRX_PIN) != 0)
            SampleBufferx5[loga.ptr] = 0x31;
#endif
#ifdef SUMP_8CH
        *(InPtr) = IRRX_PORT; //set current buffer bit if RX high
        *(InPtr) ^= 0x54; // Invert demodulator output.
#endif
        loga.ptr += 1;
        InPtr++;
        loga.sample += 1;

        if ((loga.ptr == CDC_BUFFER_SIZE - 2) || ((unsigned int) loga.sample == (unsigned int) SUMP_SAMPLE_SIZExx)) {

            SendCDC_In_ArmNext(loga.ptr);
            loga.ptr = 0;
            FAST_usb_handler();
        }
        if ((unsigned int) loga.sample == (unsigned int) SUMP_SAMPLE_SIZExx) {//done sampling
            if ((loga.sample % (CDC_BUFFER_SIZE) != 0)) {
                LAstate = LA_RESET;
            } else { // Last sample packet was modulo CDC_BUFFER_SIZE so flag requirement for a ZLP
                LAstate = LA_ZLP;
            }
            T2ON = 0; //disable the sampling timer
            T2IE = 0;
            LedOn(); //LED off
            T2IF = 0; //clear the interrupt flag

        }

    } else if (IRRXIE == 1 && IRRXIF == 1) { //if RB Port Change Interrupt
        if ((IRRX_PORT & IRRX_PIN) == 0) {
            IRRXIE = 0; //disable port b interrupt
            IRRXIF = 0; //Reset the RB Port Change Interrupt Flag bit
            //TIMER2 sample rate,
            //need to adjust speed for 2x frequency, nyquist rate
            //T2CON=PRE_x4+POST_x3;
            //PR2=221;
            T2_RXsampleperiod();
            T2IF = 0; //clear the interrupt flag
            T2IE = 1; //able interrupts...
            T2ON = 1; //timer on

#ifndef SUMP_8CH
            if ((IRRX_PORT & SUMP_PIN) == 0) {//only if 0, must read PORTB to clear RBIF
                *InPtr = 0x31; //;0b10000000; //preload value for pretty LA output
                InPtr++;
                *InPtr = 0x30; //;0b10000000; //preload value for pretty LA output
                InPtr++;
                loga.sample = 2; //start with 2 existing samples
                //loga.ptr = 2; //start with byte 1
            }
#endif
#ifdef SUMP_8CH
            *InPtr = IRRX_PORT; //set current buffer bit if RX high
            *(InPtr) ^= 0x54; // Invert demodulator output.
            loga.sample = 1; //start with 2 existing samples
            loga.ptr = 1; //start with byte 1
            //counter = 1;
            InPtr++;
#endif
            //LedOff(); //LED OFF
            LAstate = LA_DUMP;
            //LedToggle();
        }
        IRRXIF = 0; //Reset the RB Port Change Interrupt Flag bit
    }

}
