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

#include "prj_globals.h"
#include "..\dp_usb\usb_stack_globals.h"    // USB stack only defines Not function related.


extern void CDCFlushOnTimeout(void);
extern struct _cdc_ControlLineState cls;

#define USE_HNDSHK_POL_INV

BYTE Hold_pol;

//setup for USB2UART
void Usb2UartSetup(void) {
    BYTE temp;

    DisableEachInterrupt(); // PIE1 = {SPPI EADIE RCIE TXIE SSPIE CCP1IE TMR2IE TMR1IE}, IRFREQ_CAPIE, T0_IE, IRRXIE, IRRAWINTIE

    RcIf = 0;
    temp = 0x8; // baud16

#ifdef USE_HNDSHK_POL_INV
    INTCON2bits.RBPU = 0;
    HNDSHK_INV_TRISpin = 1;
    TXRX_INV_TRISpin = 1;
    RTSTRISpin = 0;
    DTRTRISpin = 0;
    if (HNDSHK_INV_PORTpin) {
        Hold_pol = 0;
    } else {
        Hold_pol = 1;
    }
    if (!TXRX_INV_PORTpin)
        temp |= 0x30;
#endif

    /* Signon not used in stand alone USB-UART mode*/
#ifndef UARTONLY
    putc_cdc('U');
    putc_cdc('0');
    putc_cdc('1');
    CDC_Flush_In_Now();
#endif

    TRISC |= 0xC0;
    TXSTA = 0x24; //baudrate high
    RCSTA = 0x90;

    BAUDCON = temp;
    PIE1 = 0x20;
    IPR1bits.RCIP = 1;
    usb_register_sof_handler(CDCFlushOnTimeout); // For timeout value see: cdc_config.h -> IRTOY -> CDC_FLUSH_MS
}
// to go back to the other default, user must unplug USB IR Toy

void Usb2UartService(void) {
    BYTE tempout;

    Usb2UartSetup();

    do {
        usb_handler();
#ifdef USE_HNDSHK_POL_INV
        if (Hold_pol) {
            RTSpin = cls.RTS;
            DTRpin = cls.DTR;
        } else {
            RTSpin = ~cls.RTS;
            DTRpin = ~cls.DTR;
        }
#endif
        if (TxIf) {
            if (poll_getc_cdc(&tempout)) {
                TXREG = tempout;
            }
        }
        if (RCSTA & 0x06) // error handling
        {
            RCSTAbits.CREN = 0;
            RCSTAbits.CREN = 1;
        }
    } while (1);
}

//high priority interrupt routine
void Usb2UartInterruptHandlerHigh(void) {
    if (RcIf) {
        putc_cdc(RCREG); // will handle timouts and ZLP for us.
        LedToggle(); // toggle led every sending
    }
}

