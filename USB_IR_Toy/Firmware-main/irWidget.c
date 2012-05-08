/* *****************************************************************************
 IR TOY 2012. A folked version by JTR. Please see changelog.txt for details.
 * IR Widget mode added by JTR
 *
 * JTR Version 0.1 beta
********************************************************************************/
#include "prj_globals.h"
#include "..\dp_usb\usb_stack_globals.h"    // USB stack only defines Not function related.
#include <delays.h>

#define IRS_TRANSMIT_HI	0
#define IRS_TRANSMIT_LO	1
#define RISING 1
#define FALLING 0
extern struct _cdc_ControlLineState cls;
extern BYTE *InPtr;
extern BYTE *OutPtr;
extern BYTE LineStateUpdated;

static struct {
    BYTE RXsamples;
    BYTE flushflag : 1;
    BYTE edge : 1;
    BYTE updated : 1;
    BYTE irWmode : 1;
} irW;

unsigned int time;

static volatile BYTE count;

void irWidgetservice() {
    CCP2CON = 0;
    INTCON2bits.INTEDG1 = 0;
    IRFREQ_CAPIE = 0;
    IRRAWINTIE = 0;
    IRRAWINTIF = 0;
    IRRXIE = 0;
    T0_IE = 0;
    T1CONbits.T1OSCEN = 0;
    T1IE = 0;
    T1IF = 0;
    T2IE = 0;
    T2IF = 0;
    T2ON = 0;
    TMR2 = 0;
    TRISB |= 0x14;
    TRISC |= 0x03;

    while (1) {
        LineStateUpdated = 0;
        do {
            usb_handler();
        } while (cls.DTR == 0);

        if (cls.RTS) {
            GetPulseTime();
        } else {
            GetPulseFreq();
        }
    }
}

void GetPulseTime(void) {
    // ----- Pulse time capture -----
    irW.edge = FALLING; // Start with falling edge
    time = 0; // Init current time
    irW.updated = 0;
    irW.flushflag = 0;
    irW.RXsamples = 0;
    T2CON = 0x00; //16uS period
    TMR2 = 0; //
    PR2 = 191;
    irW.irWmode = 0;
    IRRXIE = 1;
    T2IE = 1;

    while (irW.edge == FALLING) {
        usb_handler();
    }

    do {
        usb_handler(); // Required for CDC update
        if (irW.updated) {
            time &= 0x7FFF;
            if (irW.edge == RISING)
                time |= 0x8000;
            *InPtr = time & 0xFF;
            InPtr++;
            *InPtr = (time / 256) & 0xFF;
            InPtr++;
            irW.RXsamples += 2;
            irW.updated = 0;
            time = 0;
        }

        if (((irW.RXsamples == 30) || (irW.flushflag && irW.RXsamples))) { //if we have full buffer, or end of capture flush
            putda_cdc(irW.RXsamples);
            irW.RXsamples = 0;
            irW.flushflag = 0;
        }
    } while (cls.DTR);
    if (irW.RXsamples) {
        putda_cdc(irW.RXsamples);
        IRRXIE = 0;
        T2IE = 0;
        T2IF = 0;
        T1IE = 0;
        T1IF = 0;
        T1ON = 0;
    }
}

void GetPulseFreq(void) {

    T2CON = 0x03; // prescaler /16
    TMR2 = 0; //
    PR2 = 74; // ((12MHz / 16) / 75- 1) = 10KHz = 100us period
    irW.RXsamples = 0;
    count = 0; // Init current time
    irW.irWmode = 1;

    Delay10KTCYx(0); // about 200ms
    IRRAWINTIF = 0;
    IRRAWINTIE = 1;

    do {
        usb_handler(); // Required for CDC update
        if (((irW.RXsamples >= 30))) { //if we have full buffer, or end of capture flush
            INTCONbits.GIEH = 0;
            if (putda_cdc(irW.RXsamples))
                irW.RXsamples = 0;
            INTCONbits.GIEH = 1;
        }
    } while (cls.DTR);

    IRRAWINTIE = 0;
    IRRAWINTIF = 0;
    T2ON = 0;
    T2IE = 0;
    T2IF = 0;

    if (irW.RXsamples) {
        putda_cdc(irW.RXsamples);
    }
}
//high priority interrupt routine dispatched from main.c

void irWInterruptHandlerHigh(void) {
    BYTE dummy;
    if (IRRAWINTIE == 1 && IRRAWINTIF == 1) {
        IRRAWINTIF = 0;
        if (T2ON == 1) {
            count += 1;
            irW.updated = 1;
        } else {
            T2ON = 1;
            T2IF = 0;
            T2IE = 1;
        }
    } else if (T2IE == 1 && T2IF == 1) {
        if (irW.irWmode == 1) {
            *InPtr = count;
            InPtr++;
            irW.RXsamples++;
            T2IF = 0;
        } else {
            time++;
            T2IF = 0;
            T1ON = 0; //timer on
            TMR1H = 0;
            TMR1L = 0;
            T1ON = 1; //timer on
        }
    } else if (IRRXIE == 1 && IRRXIF == 1) { //if RB Port Change Interrupt
        dummy = IRRX_PORT;
        if (dummy & 0x10) {
            irW.edge = FALLING;
        } else {
            irW.edge = RISING;
        }
        irW.updated = 1;
        //reset timer1, USB packet send timeout
        T1ON = 0; //timer on
        TMR1H = 0;
        TMR1L = 0;
        T1ON = 1; //timer on
        //clear portb interrupt
        IRRXIF = 0; //Reset the RB Port Change Interrupt Flag bit
    } else if (T1IE == 1 && T1IF == 1) {
        irW.flushflag = 1;
        T1IF = 0;
    }
}



