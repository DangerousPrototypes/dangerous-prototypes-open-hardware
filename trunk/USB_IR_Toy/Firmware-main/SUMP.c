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

extern BYTE *InPtr;
extern BYTE *OutPtr;
extern BYTE cdc_In_len;
extern BDentry *CDC_Outbdp, *CDC_Inbdp;

//commandset http://www.sump.org/projects/analyzer/protocol/
#define SUMP_RESET      0x00
#define SUMP_RUN	0x01
#define SUMP_ID         0x02
#define SUMP_META	0x04
#define SUMP_XON	0x11
#define SUMP_XOFF       0x13

volatile static enum _LAstate {
    LA_IDLE = 0,
    LA_DUMP,
} LAstate = LA_IDLE;

#pragma udata 

BYTE irSUMPservice(void) {

    BYTE a, OutByte, sump_mode;
    unsigned int totalSampleCountx64;

    struct _sumpRX {
        BYTE command[5];
        BYTE parameters;
        BYTE parCnt;
    } sumpRX;

    DisableEachInterrupt(); // PIE1 = {SPPI EADIE RCIE TXIE SSPIE CCP1IE TMR2IE TMR1IE}, IRFREQ_CAPIE, T0_IE, IRRXIE, IRRAWINTIE

    T2ON = 0; //tmr2 off


    sump_mode = 1;

    do {
        usb_handler();
        if (poll_getc_cdc(&OutByte) == 1) {//process any command bytes
            switch (OutByte) {//switch on the current byte
                case SUMP_RESET://reset
                    //                    SumpReset();
                    T2IE = 0; //disable interrupts...
                    T2ON = 0; //tmr2 off
                    IRRXIE = 0; //DISABLE RB port change interrupt
                    sump_mode = 0;
                    return 0xFF;
                    break;
                case SUMP_ID://SLA0 or 1 backwards: 1ALS
                    putc_cdc('1');
                    putc_cdc('A');
                    putc_cdc('L');
                    putc_cdc('S');
                    CDC_Flush_In_Now();

                    break;
                case SUMP_RUN://arm the triger
                    IRRXIF = 0; //Reset the RB Port Change Interrupt Flag bit
                    IRRXIE = 0; //disable the RB port change interrupt
                    WaitInReady();

                    cdc_In_len = 0;
                    CDC_Flush_In_Now(); // Start with a clean slate. Reset InPtr and count etc.
                    CDC_Flush_In_Now();
                    usb_handler();


                    LedOff(); //ARMED, turn on LED
                    LAstate = LA_IDLE;
                    //                    loga.ptr = 0;
                    totalSampleCountx64 = 0;
                    *InPtr = IRRX_PORT;
                    T2IE = 0; //disable interrupts...
                    T2ON = 0; //tmr2 off
                    TRISB = 0xFF;

                    IRRXIF = 0; //Reset the RB Port Change Interrupt Flag bit
                    IRRXIE = 0; //disable port b interrupt
                    LedOn();

                    do {
                        usb_handler();
                    } while (IRRX_PORT & IRRX_PIN);
                    T2_RXsampleperiod(); //sample speed
                    T2IF = 0; //clear the interrupt flag
                    T2ON = 1; //timer on

                    //pack first change data into USB buffer
                    //add some blank bytes so the LA display is pretty
                    *InPtr = 0x00; //set current buffer bit if RX high
                    InPtr++;
                    *InPtr = 0x00; //set current buffer bit if RX high
                    InPtr++;
                    *InPtr = 0x00; //set current buffer bit if RX high
                    InPtr++;
                    *InPtr = 0x00; //set current buffer bit if RX high
                    InPtr++;
                    *InPtr = IRRX_PORT; //set current buffer bit if RX high
                    *(InPtr) ^= 0b10110; //0x54; // Invert demodulator output.
                    InPtr++;
                    cdc_In_len += 5; //start with byte 1
                    totalSampleCountx64 = SUMP_SAMPLE_PKT_CNT;

                    LedOff(); //LED off
                    //
                    INTCON2bits.RBPU = 0;
                    LAstate = LA_DUMP;

                    do { // Critical timed loop, inversely proportional to our acheivable bandwidth
                        if (T2IF)
                            LedOn(); // debug only to show any skewing
                        do {
                            ClearUsbInterruptFlag(USB_TRN); // Not sociable but gives higher bandwidth.
                        } while (!T2IF);

                        a = IRRX_PORT;
                        a ^= 0b00010110;
                        *InPtr++ = a;
                        cdc_In_len += 1;
                        T2IF = 0;

                        if (cdc_In_len == CDC_BUFFER_SIZE) {
                            putda_cdc(CDC_BUFFER_SIZE);
                            cdc_In_len = 0;
                            totalSampleCountx64--; // += 1;
                        }
                    } while (!totalSampleCountx64);
                    LedOff(); //LED off

                    T2ON = 0; //disable the sampling timer
                    usb_handler();
                    SendZLP();
                    LAstate = LA_IDLE;
                    break;

                case SUMP_META://meta data
                    putc_cdc(0x40);
                    putc_cdc(0x08);
                    putc_cdc(0x41);
                    putc_cdc(0x02);
                    putc_cdc(0x00);
                    CDC_Flush_In_Now();
                    break;
                case SUMP_XON://resume send data
                    //	xflow=1;
                    break;
                case SUMP_XOFF://pause send data
                    //	xflow=0;
                    break;
                default://long command
                    sumpRX.command[0] = OutByte; //store first command byte
                    sumpRX.parameters = 4; //all long commands are 5 bytes, get 4 parameters
                    sumpRX.parCnt = 0; //reset the parameter counter
                    sumpRX.command[sumpRX.parCnt] = OutByte;
                    while (sumpRX.parCnt < sumpRX.parameters) {
                        sumpRX.parCnt++;
                        sumpRX.command[sumpRX.parCnt] = getc_cdc();
                        // Process sump parameters here. For now do nothing.
                    }
                    break;
            }
        }
    } while (1 == sump_mode);
    return 0xFF;
}
