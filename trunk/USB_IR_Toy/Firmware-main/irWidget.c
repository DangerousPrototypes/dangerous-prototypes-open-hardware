#include "globals.h"
//#include "HardwareProfile.h"
//#include "cdc_config.h"
#include "PICUSB.h"
//#include "cdc.h"
#include <delays.h>

// #define FCY   12000000L  //define your instruction frequency, FCY = FOSC/2

//#define CYCLES_PER_MS ((unsigned long)(FCY * 0.001))        //instruction cycles per millisecond
// #define CYCLES_PER_US ((unsigned long)(FCY * 0.000001))   //instruction cycles per microsecond
// #define DELAY_MS(ms)  __delay32(CYCLES_PER_MS * ((unsigned long) ms));   //__delay32 is provided by the compiler, delay some # of milliseconds

//#define DELAY_US(us)  __delay32(CYCLES_PER_US * ((unsigned long) us));    //delay some number of microseconds


//extern unsigned char cdc_trf_state;
//unsigned char USBUSARTIsTxTrfReady( void );
//void putUSBUSART ( char *data, unsigned char length );

BYTE FAST_usb_handler(void);
void USBDeviceTasks(void);


#define IRS_TRANSMIT_HI	0
#define IRS_TRANSMIT_LO	1
#define RISING 1
#define FALLING 0
extern struct _cdc_ControlLineState cls;
extern struct _irtoy irToy;
extern BYTE cdc_In_buffer[64];
extern BYTE cdc_Out_buffer[64];
extern BYTE cdc_Out_bufferA[64];
extern BYTE cdc_Out_bufferB[64];
extern BYTE cdc_In_bufferA[64];
extern BYTE cdc_In_bufferB[64];
extern BYTE *InPtr;
extern BYTE *OutPtr;
extern BYTE LineStateUpdated;
extern BYTE l;
extern BYTE h;

static struct {
    unsigned char RXsamples;
    //unsigned char TXsamples;
    //unsigned char timeout;
    //unsigned char TX : 1;
    //unsigned char rxflag : 1;
    //unsigned char txflag : 1;
    unsigned char flushflag : 1;
    //unsigned char overflow : 1;
    unsigned char edge : 1;
    unsigned char updated : 1;
    unsigned char irWmode : 1;
} irW;

unsigned int time;


static BYTE* aptr;
static volatile BYTE count;
//extern struct cls;
//

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
            USBDeviceTasks();
        } while (cls.DTR == 0);
        // } while ((!LineStateUpdated) || (cls.DTR == 0));

        // do {
        //USBDeviceTasks();
        if (cls.RTS) {
            //GetPulseTime();
        } else {
            GetPulseFreq();

        }
        //} while (cls.DTR == 1);
        // cls.DTR = 0;
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
    PR2 = 192;
    irW.irWmode = 0;
    //aptr = cdc_In_buffer;
    ArmCDCInDB();
    IRRXIE = 1;
    T2IE = 1;

        while (irW.edge == FALLING) {
            FAST_usb_handler();
        }

    do {
        USBDeviceTasks(); // Required for CDC update
        if (irW.updated) {
            time &= 0x7FFF;
            if (irW.edge == RISING)
                time |= 0x8000;
            *InPtr = time & 0xFF;
            InPtr++;
            *InPtr = (time / 256) & 0xFF;
            InPtr++;
            //irW.edge = ~irW.edge;
            irW.RXsamples += 2;
            irW.updated = 0;
            time = 0;
        }

        if (((irW.RXsamples == 30) || (irW.flushflag && irW.RXsamples))) { // && (WaitInReady())) { //if we have full buffer, or end of capture flush
            SendCDC_In_ArmNext(irW.RXsamples);
            irW.RXsamples = 0;
            irW.flushflag = 0;
        }
    } while (cls.DTR);
    if (irW.RXsamples) {
        SendCDC_In_ArmNext(irW.RXsamples);
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
        PR2 = 75; // ((12MHz / 16) / 75) = 10KHz = 100us period 
        irW.RXsamples = 0;
        //irW.flushflag = 0;
        count = 0; // Init current time
        irW.irWmode = 1;

        Delay10KTCYx(0); // about 200ms
        ArmCDCInDB();
        IRRAWINTIF = 0;
        IRRAWINTIE = 1;

        /*
            for (i = 0; i < 20; i++) {
         */
        //do

        do {
            USBDeviceTasks(); // Required for CDC update
            //  } while ((!irW.updated) && (cls.DTR));
            // do {

            /*
                        if (!IRFREQ_INT) {
                            if (irW.edge == 0) {
                                count++;
                                irW.edge = 1;
                            }
                        } else {
                            irW.edge = 0;
                        }
             */

            // } while (T2IF == 0);

            // if (T2IF == 1) {
            //T2IF = 0;
            //*InPtr = count;
            //InPtr++;
            //irW.RXsamples++;
            //dbLedToggle();
            //irW.updated = 0;


            if (((irW.RXsamples >= 30))) { // || (irW.flushflag && irW.RXsamples))) { // && (WaitInReady())) { //if we have full buffer, or end of capture flush
                INTCONbits.GIEH = 0;
                if (SendCDC_In_ArmNext(irW.RXsamples))
                irW.RXsamples = 0;
                INTCONbits.GIEH = 1;
                //irW.flushflag = 0;
            }
            //}
        } while (cls.DTR);

        IRRAWINTIE = 0;
        IRRAWINTIF = 0;
        T2ON = 0;
        T2IE = 0;
        T2IF = 0;

        if (irW.RXsamples) {
            SendCDC_In_ArmNext(irW.RXsamples);
            //putUnsignedCharArrayUsbUsart(cdc_In_buffer, (irW.RXsamples));
        }
    }

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



