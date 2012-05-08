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
// IRman compatible RC decoder for RC5, RC5x
// Sends a 6 byte packet:
// RC5 address byte (0)
// RC5 command byte (1) *bit 6 is RC5x bit
// Bytes 2-5 are 0 padding
//
// Note that the official spec inverses the RC5x bit, but we do not do that...
//
//#ifdef RC_DECODER

#include "prj_globals.h"
#include "..\dp_usb\usb_stack_globals.h"    // USB stack only defines Not function related.

static enum _RC5STATE { //struct of variable to decode RC5
    IDLE = 0,
    HALF_PERIOD,
    BIT_PERIOD_0,
    BIT_PERIOD_1,
    SEND,
} decoderState = IDLE;

static struct _RC5decoder { //bits to trach the manchester encoding bit periods
    BYTE bp0; //manchester period 0
    BYTE bp1; //manchester period 1
    BYTE bcnt; //bit count
} RC5;

extern BYTE HardwareVersion;
BYTE DecoderBuffer[8];
//disable timers, setup IR activity interrupt

void SetupRC5(void) {
    BYTE dummy;
    dummy = IRRX_PORT; // Init read for PORTB IOR
    decoderState = IDLE;
    CCP1CON = 0; //disable any PWM
    T2CON = 0;
    T2IE = 0; //disable any Timer 2 interrupt
    T2IF = 0;
    IRRXIF = 0;
    IRRXIE = 1; //enable RX interrupts for data ACQ
}

//IR signals are first captured in the interrupt loop below
//when the capture is complete, the bits are decoded into bytes and sent to USB from this function

void ProcessIR(void) {
    static BYTE i;
    BYTE temp;
    if (decoderState == SEND) {

        //process IR data (decode RC5) in DecoderBuffer[]
        //byte# | description
        //0 second start bit, use as bit 6 in command byte for RC5x protocol support
        //1 toggle bit, discard
        //2-6 5bit address
        //7-12 6bit command

        //final USB packet is:
        //byte 1 bits 7-5 (don't care)
        //byte 1 bits 4-0 (5 address bits)
        //byte 2 bit 7 (don't care)
        //byte 2 bit 6 (RC5x/start bit 2, not inversed)
        //byte 2 bits 5-0 (RC5 6 bit command)
        //byte 3-6 (unused)

        //first byte of USB data is the RC5 address (lower 5 bits of first byte)
        //loop through DecoderBuffer[] and shift the 5bit address into the USB output buffer
        //5 address bits, 5-0, MSB first

        //        cdc_In_buffer[0] = 0; //clear USB buffer byte to 0

        temp = 0;

        for (i = 2; i < 7; i++) { //loop through and assemble 5 address bits into a byte, bit 4 to bit 0, MSB first

            temp <<= 1; //shift last bit up
            temp |= DecoderBuffer[i]; //set bit 0 to value of DecoderBuffer[i]
        }
        putc_cdc(temp);

        //second byte of USB data is the RC5 command (lower 6 or 7 bits of second byte)
        //for RC5x, the second start bit is used as the MSB of the command (bit 6)
        //cdc_In_buffer[1]=(~DecoderBuffer[0]);		//technically this should be inversed, but that would ruin compatibility for exisitng remote profiles
        temp = ~(DecoderBuffer[0]); //start with the value of the RC5x bit (bit 6),

        //loop through DecoderBuffer[] and shift the 'normal' 6 command bits, bit 5 to bit 0, into the USB output buffer
        //6 command bits, 5-0, MSB first
        for (i = 7; i < 13; i++) { //loop through and assemble 6 command bits into a byte, bit 5 to bit 0, MSB first
            temp <<= 1; //shift last bit up
            temp |= DecoderBuffer[i]; //set bit 0 to value of DecoderBuffer[i]
        }
        putc_cdc(temp);

        //four extra bytes for 6 byte IRMAN format
        putc_cdc(0x00);
        putc_cdc(0x00);
        putc_cdc(0x00);
        putc_cdc(0x00);
        CDC_Flush_In_Now();

        decoderState = IDLE; //wait for more RC commands....
        IRRXIE = 1; //interrupts back on
        //LedOff(); //LED OFF!
    }
}

//high priority interrupt routine dispatched from main.c

void IRdecoderInterruptHandlerHigh(void) {
    //RC5 decoder
    if (IRRXIE == 1 && IRRXIF == 1) { //if RB Port Change Interrupt

        if (decoderState == IDLE && ((IRRX_PORT & IRRX_PIN) == 0)) {//only if idle and pin state == 0
            IRRXIE = 0; //disable port b interrupt
            LedOn(); //LED ON! (off after .5 bit period)
            T2_RC5halfbitperiod(); //setup to hit in the middle of next bit period
            T2IF = 0; //clear the interrupt flag
            T2IE = 1; //able interrupts...
            T2ON = 1;
            decoderState = HALF_PERIOD;
        }
        IRRXIF = 0; //Reset the RB Port Change Interrupt Flag bit

    } else if (T2IE == 1 && T2IF == 1) {
        switch (decoderState) {
            case HALF_PERIOD: //middle of first bit period is actually second bit of first pair (first bit is invisible)
                T2ON = 0; //timer off
                T2_RC5bitperiod(); //full bit values from now on
                RC5.bcnt = 0; //reset samples
                decoderState = BIT_PERIOD_0; //next timeis bit period 0

                T2IF = 0; //clear the interrupt flag
                T2IE = 1; //able interrupts...
                T2ON = 1;

                LedOff(); //LED OFF!
                break;
            case BIT_PERIOD_0:
                RC5.bp0 = IRX;
                decoderState = BIT_PERIOD_1;
                break;
            case BIT_PERIOD_1:
                RC5.bp1 = IRX;

                if (RC5.bp0 == 1 && RC5.bp1 == 0) {
                    DecoderBuffer[RC5.bcnt] = 1;
                } else if (RC5.bp0 == 0 && RC5.bp1 == 1) {
                    DecoderBuffer[RC5.bcnt] = 0;
                } else {//error
                    decoderState = IDLE; //reset
                    T2ON = 0; //timer off
                    IRRXIE = 1; //IR interrupts back on
                    break;
                }
                decoderState = BIT_PERIOD_0;
                RC5.bcnt++;
                if (RC5.bcnt == 13) {//done sampling
                    decoderState = SEND; //process and send in service loop
                    T2ON = 0; //turn off the timer
                }
                break;
        }//switch
        T2IF = 0; //clear the interrupt flag
    }//if
}
//#endif //RC_DECODER

