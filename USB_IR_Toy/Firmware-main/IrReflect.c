/*
 *
 *	USB infrared remote control receiver transmitter firmware v1.0
 *	License: creative commons - attribution, share-alike
 *	Copyright Ian Lesnet 2010
 *	http://dangerousprototypes.com
 *
 */


#include "globals.h"

extern BYTE cdc_In_buffer[64];
extern BDentry *Inbdp;

volatile BYTE RBInterruptCount = 0;
volatile SM_TX_LED_STATE txledstate;

static void IrReflectTxPwmSetup(void) {
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

    //LAT_IRTX=0;//TX LED off
    //TRIS_IRTX=1; // input mode
    IrTxTurnOff();

    CCP1CON = 0;
    T2CON = 0;

    T2IF = 0; //clear the interrupt flag
    T2IE = 0; //disable interrupts
    PR2 = 0b01010010; //82
    T2CON = 0b00000101;
    CCPR1L = 0b00101001; //upper 8 bits of duty cycte
    CCP1CON = 0b00011100; //we leave this on for visual inspection (5-4 two LSB of duty, 3-0 set PWM)
}

void IrReflectSetup(void) {
  //  if (WaitInReady()) {
     WaitInReady();
        cdc_In_buffer[0] = 'E'; //answer OK
        cdc_In_buffer[1] = '0';
        cdc_In_buffer[2] = '1';
        putUnsignedCharArrayUsbUsart(cdc_In_buffer, 3);
   // }
    IrReflectTxPwmSetup();
    EnablePortbChangeInterrupt()
    RBInterruptCount = 0;
    txledstate = TX_LED_TURN_OFF;
    LedOff();
}

unsigned char IrReflectService(void) {
    static unsigned int ctr = 0;
    BYTE inbyte = 0;

    usbbufservice(); //service USB buffer system
    if (usbbufgetbyte(&inbyte) > 0) {//process any command bytes

        if ((inbyte == '0') || (inbyte == 0)) {
            IrTxTurnOff();
            DisablePortbChangeInterrupt();
            LedOff();
            return 1;
        }
    }
    if (ctr > 5000) //just a magic trial and error number :)
    {
        BYTE isRbCountingOk;
        isRbCountingOk = FALSE;
        txledstate ^= 1;
        txledstate &= 0x01;
        switch (txledstate) {
            case TX_LED_TURN_OFF:
                if (IsRbCountExceeded()) // since it is turned on previously, it must have pulses on RB
                {
                    isRbCountingOk = TRUE;
                }
                IrTxTurnOff();
                break;
            case TX_LED_TURN_ON:
                isRbCountingOk = INVALID;
                IrTxTurnOn();
                break;
        }

        // I will still be putting something here :) For now Leds toggling

        if (isRbCountingOk == TRUE) {
            LedOn();
           // if (WaitInReady()) // bad mistake no {}
                 WaitInReady();
                cdc_In_buffer[0] = 'D';
            cdc_In_buffer[1] = 'E';
            cdc_In_buffer[2] = 'T';
            cdc_In_buffer[3] = 'E';
            cdc_In_buffer[4] = 'C';
            cdc_In_buffer[5] = 'T';
            cdc_In_buffer[6] = '!';
            putUnsignedCharArrayUsbUsart(cdc_In_buffer, 7);
        } else if (isRbCountingOk == FALSE) {
            LedOff();
        }
        RBInterruptCount = 0; //reset counter
        ctr = 0;
    }
    ctr++;
    return 0;
}

//high priority interrupt routine
//#pragma interrupt IrReflectionInterruptHandlerHigh

void IrReflectionInterruptHandlerHigh(void) {
    //irIO driver
    if (IRRXIE == 1 && IRRXIF == 1) {
        RBInterruptCount++;
        RBInterruptCount &= 0x7F; // make sure it is below 127
        IRRXIF = 0;
    }
}



