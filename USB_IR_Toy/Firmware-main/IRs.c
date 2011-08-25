/*
 *
 *	USB infrared remote control receiver transmitter firmware v1.0
 *	License: creative commons - attribution, share-alike
 *	Copyright Ian Lesnet 2010
 *	http://dangerousprototypes.com
 *
 */
//
//	IR sampler
//
// This new mode counts the duration of each IR pulse/space
// the signal is returned as 16bit timer counts that each represent 21.3us
// the values are returned Pulse-h P-l Blank-h B-l P-h P-l etc.
// the last value will be 0xff 0xff, representing 1.7seconds of blank

#include "globals.h"
#include "PICUSB.h"

BYTE FAST_usb_handler(void);
void USBDeviceTasks(void);

#define IRS_TRANSMIT_HI	0
#define IRS_TRANSMIT_LO	1

extern struct _irtoy irToy;
extern BYTE cdc_In_buffer[64];
extern BYTE cdc_Out_buffer[64];
extern BYTE cdc_Out_bufferA[64];
extern BYTE cdc_Out_bufferB[64];
extern BYTE cdc_In_bufferA[64];
extern BYTE cdc_In_bufferB[64];
extern BYTE *InPtr;
extern BYTE *OutPtr;

static unsigned char h, l, tmr0_buf[3]; //JTR3 note swapped tmr0buf H/L bytes Now [0] = low [1] = high [2] = end of data byte
static unsigned char modFreq[8];
static unsigned char modFreqCnt;

void cleanup(void);

#define TRUE 1

///////////////////////// THIS IS FOR SETTING THE PORT

void IrS_SetPortEqual(BYTE HiByte, BYTE LoByte) {
    if (irToy.HardwareVersion < 2) {
        LATC = (LATC & 0x3F) | (LoByte & 0xC0);
    } else {
        LATA = (LATA & (~0x3C)) | (LoByte & 0x3C);
        LATB = (LATB & (~0x29)) | (HiByte & 0x29);
    }
}

void IrS_SetPortTrisEqual(BYTE HiByte, BYTE LoByte) {
    if (irToy.HardwareVersion < 2) {
        TRISC = (TRISC & 0x3F) | (LoByte & 0xC0);
    } else {
        TRISA = (TRISA & (~0x3C)) | (LoByte & 0x3C);
        TRISB = (TRISB & (~0x29)) | (HiByte & 0x29);
    }
}

BYTE IrS_ReadPort(void) {
    if (irToy.HardwareVersion < 2) {
        return PORTC & 0xC0;
    } else {
        return
        (
                ((PORTA >> 2)&0x0F) |
                (PORTBbits.RB0 << 4) |
                (PORTBbits.RB3 << 5) |
                (PORTBbits.RB5 << 6)
                );
    }
}

////////////////////////

static struct {
    unsigned char RXsamples;
    unsigned char TXsamples;
    unsigned char timeout;
    unsigned char TX : 1;
    unsigned char rxflag : 1;
    unsigned char txflag : 1;
    unsigned char flushflag : 1;
    unsigned char overflow : 1;
    unsigned char TXInvert : 1;
    unsigned char handshake : 1;
    unsigned char sendcount : 1;
    unsigned char sendfinish : 1;
    unsigned char RXcompleted : 1;
	unsigned char txerror : 1;
} irS;

void irsSetup(void) {
    BYTE dummy;
    T2IE = 0; //disable any Timer 2 interrupt
    IRRXIE = 0; //enable RX interrupts for data ACQ
    
	//send version string
	WaitInReady();
	cdc_In_buffer[0] = 'S'; //answer OK
	cdc_In_buffer[1] = '0';
	cdc_In_buffer[2] = '1';
	putUnsignedCharArrayUsbUsart(cdc_In_buffer, 3);

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

    /*
     * PWM registers configuration
     * Fosc = 48000000 Hz
     * Fpwm = 37974.68 Hz (Requested : 38000 Hz)
     * Duty Cycle = 50 %
     * Resolution is 10 bits
     * Prescaler is 4
     * Ensure that your PWM pin is configured as digital output
     * see more details on http://www.micro-examples.com/
     * this source code is provided 'as is',
     * use it at your own risks
     */
    IRTX_TRIS &= (~IRTX_PIN); //digital output
    IRTX_LAT &= (~IRTX_PIN); //low (hold PWM transistor base off)
    T2IF = 0; //clear the interrupt flag
    T2IE = 0; //disable interrupts
    //PR2 = 0b01010010 ; //36KHz
    PR2 = 0b01001110; //38KHz
    T2CON = 0b00000101;
    //CCPR1L = 0b00101001 ;	//upper 8 bits of duty cycte
    CCPR1L = 0b00100111; //50%
    CCP1CON = 0b00010000; //should be cleared on exit! (5-4 two LSB of duty, 3-0 set PWM)

    IRFREQ_PIN_SETUP();

    //setup for IR RX
    irS.rxflag = 0;
    irS.txflag = 0;
    irS.flushflag = 0;
    irS.timeout = 0;
    irS.RXsamples = 0;
    irS.TXsamples = 0;
    irS.TX = 0;
    irS.overflow = 0;
    irS.sendcount = 0;
    irS.sendfinish = 0;
    irS.handshake = 0;
    irS.RXcompleted = 0;


    //setup timer 0
    T0CON = 0;
    //configure prescaler
    //bit 2-0 T0PS2:T0PS0: Timer0 Prescaler Select bits
    //111 = 1:256 Prescale value
    //110 = 1:128 Prescale value
    //101 = 1:64 Prescale value
    //100 = 1:32 Prescale value
    //011 = 1:16 Prescale value
    //010 = 1:8 Prescale value
    //001 = 1:4 Prescale value
    //000 = 1:2 Prescale value
    T0CON = 0b111;
    //T0CONbits.T08BIT=1; //16bit mode
    //internal clock
    //low to high
    T0CONbits.PSA = 0; //1=not assigned

    //timer 1 as USB packet send timeout
    T1CON = 0;
    T2IE = 0; //disable interrupts...
    T2ON = 0; //tmr2 off

    dummy = IRRX_PORT; // Init read for PORTB IOR
    IRRXIF = 0; //Reset the RB Port Change Interrupt Flag bit
    IRRXIE = 1; //Enables the RB port change interrupt

}

typedef enum { //in out data state machine
    I_IDLE = 0,
    I_PARAMETERS,
    I_PROCESS,
    I_DATA_L,
    I_DATA_H,
    I_TX_STATE,
    I_LAST_PACKET //JTR3 New! For 0x07 command
} _smio;

typedef struct _smCommand {
    unsigned char command[5];
    unsigned char parameters;
    unsigned char parCnt;
} _smCommand;

//
// COMMANDS
//
#define IRIO_RESET 		0x00
//1 and 2 reserved for SUMP RUN and ID
//#define IRIO_TRANSMIT           0x03
#define IRIO_FREQ 		0x04
#define IRIO_SETUP_SAMPLETIMER  0x05
#define IRIO_SETUP_PWM          0x06
//#define IRIO_TRANSMIT_2 	0x07
#define IRIO_LEDMUTEON          0x10
#define IRIO_LEDMUTEOFF         0x11
#define IRIO_LEDON 		0x12
#define IRIO_LEDOFF             0x13

#define IRIO_DESCRIPTOR         0x23
#define IRIO_RETURNTXCNT        0x24
#define IRIO_NOTIFYONCOMPLETE   0X25
#define IRIO_HANDSHAKE          0x26

#define IRIO_TRANSMIT_unit      0x3

#define IRIO_IO_WRITE           0x30
#define IRIO_IO_DIR		0x31
#define IRIO_IO_READ            0x32
#define IRIO_GETCNT             0x33
#define IRIO_UART_SETUP 	0x40
#define IRIO_UART_CLOSE		0x41
#define IRIO_UART_WRITE		0x42
#define IRIO_IRW_FREQ           0x43
//

static unsigned char TxBuffCtr; //this is a total hack, needed for updated getUSBbyte function

// irIO periodic service routine
// moves bytes in and out
//

unsigned char irsService(void) {
    static unsigned char i;
    static unsigned int txcnt;
    static _smio irIOstate = I_IDLE;
    static _smCommand irIOcommand;
    unsigned char j;

    if (irS.TXsamples == 0) {
        irS.TXsamples = getUnsignedCharArrayUsbUart(irToy.s, CDC_BUFFER_SIZE);
        TxBuffCtr = 0;
    }

    WaitInReady();

    if (irS.TXsamples > 0) {

        switch (irIOstate) {
            case I_IDLE:

                switch (irToy.s[TxBuffCtr]) {

                    case IRIO_TRANSMIT_unit: //start transmitting

                        //setup for transmit mode:
                        //disable timer 0, 1, 2, etc
                        ArmCDCOutDB();
                        txcnt = 0; //reset transmit byte counter, used for diagnostic
                        T0_IE = 0;
                        T1IE = 0;
                        IRRXIE = 0;
                        irS.TX = 0;
                        //setup the PWM pin, frequency etc.
                        //setup timer 0
                        irS.txflag = 0; //transmit flag =0 reset the transmit flag
                        irIOstate = I_TX_STATE; //change to transmit data processing state
						tmr0_buf[2]=0x00; //last data packet flag
						irS.txerror=0; //reset error message

                        LedOff();

                        if (irS.handshake) {
                            WaitInReady();
                            cdc_In_buffer[0] = (CDC_BUFFER_SIZE - 2);
                            putUnsignedCharArrayUsbUsart(cdc_In_buffer, 1); //Ask for first packet
                            FAST_usb_handler();
                            FAST_usb_handler(); //probably overkill.
                        }

                        do {
                            irS.TXsamples = getCDC_Out_ArmNext();
                            if (irS.TXsamples) { // host may have sent a ZLP skip transmit if so.

                                if (irS.handshake) {
                                    WaitInReady();
                                    cdc_In_buffer[0] = CDC_BUFFER_SIZE - 2;
                                    putUnsignedCharArrayUsbUsart(cdc_In_buffer, 1); //Ask for first packet
                                    FAST_usb_handler();
                                }

                                for (i = 0; i < irS.TXsamples; i += 2, OutPtr += 2) {

                                    // JTR 3 The idea here is to preprocess the "OVERHEAD"
                                    // In what is otherwise dead time. I.E. waiting for the
                                    // IR Tx Timer to timeout.
                                    //check here for 0xff 0xff and return to IDLE state

                                    if (((*(OutPtr) == 0xFF) && (*(OutPtr + 1)) == 0xff)) {
										tmr0_buf[2]=0xff; //flag end of data
                                        irIOstate = I_LAST_PACKET;
                                        i = irS.TXsamples;
                                        *(OutPtr + 1) = 0; // JTR3 replace 0xFFFF with 0020 (Ian's value)
                                        *(OutPtr) = 20;

                                    }

                                    // This cute code calculates the two's compliment (subtract from zero)
                                    // The quick way to do this in invert and add 1.
                                    *OutPtr = ~*OutPtr;
                                    *(OutPtr + 1) = ~*(OutPtr + 1);

                                    *(OutPtr + 1) += 1;
                                    if (*(OutPtr + 1) == 0) // did we get rollover in LSB?
                                        *(OutPtr) += 1; // then must add the carry to MSB

                                    while (irS.txflag == 1) {
                                        FAST_usb_handler();
                                        //dbLedToggle();
                                    }

                                    tmr0_buf[1] = *(OutPtr); //put the second byte in the buffer
                                    tmr0_buf[0] = *(OutPtr + 1); //put the first byte in the buffer
                                    
                                    txcnt += 2; //total bytes transmitted
                                    irS.txflag = 1; //reset the interrupt buffer full flag

                                    if (irS.TX == 0) {//enable interrupt if this is the first time
                                        if (!TestUsbInterruptEnabled()) {
                                            FAST_usb_handler();
                                        }

                                        irS.TX = 1;
                                        TMR0H = tmr0_buf[1]; //first set the high byte
                                        TMR0L = tmr0_buf[0]; //set low byte copies high byte too
                                        T0_IF = 0;
                                        T0_IE = 1;
                                        T0ON = 1; //enable the timer
                                        //enable the PWM
                                        TMR2 = 0;
                                        CCP1CON |= 0b1100;
                                        irS.TXInvert = IRS_TRANSMIT_LO;
                                        LedOn();
                                    }

                                    if (irIOstate == I_LAST_PACKET)
                                        break;
                                }//for
                            } // if ZLP
                        } while (irIOstate != I_LAST_PACKET);

                        // JTR3 all done! 

                        irIOstate = I_IDLE;
                        DisArmCDCOutDB();
                            FAST_usb_handler();
                            FAST_usb_handler();

                        if (irS.sendcount) { //return the total number of bytes transmitted if required
                            WaitInReady();
                            cdc_In_buffer[0] = 't';
                            cdc_In_buffer[1] = (txcnt >> 8)&0xff;
                            cdc_In_buffer[2] = (txcnt & 0xff);
                            putUnsignedCharArrayUsbUsart(cdc_In_buffer, 3); //send current buffer to USB
                        }
                        while (irS.txflag == 1);
                        LedOff();
                        if (irS.sendfinish) { // Really redundant giving we can send a count above.
                            WaitInReady();
                            cdc_In_buffer[0] = 'C';
							if(irS.txerror) cdc_In_buffer[0] = 'F';
                            putUnsignedCharArrayUsbUsart(cdc_In_buffer, 1); //send current buffer to USB
                        }
                        irS.TXsamples = 1; //will be zeroed at end, super hack yuck!  //JTR3 super yuck!
                        break;



                    case IRIO_RESET: //reset, return to RC5 (same as SUMP)
                        cleanup();
                        LedOff();
                        LedOut();
                        return 1; //need to flag exit!
                        break;

                    case IRIO_FREQ:
                        if ((irToy.HardwareVersion > 1)) { // end of capture flush
                            WaitInReady();

                            for (j = 0; j < 5; j++) {
                                cdc_In_buffer[j] = modFreq[j];
                            }
                            cdc_In_buffer[7] = TMR3L;
                            cdc_In_buffer[6] = TMR3H;
                            putUnsignedCharArrayUsbUsart(cdc_In_buffer, 8); //send current buffer to USB
                        }
                        break;
                    case IRIO_LEDMUTEON:
                        LedIn();
                        break;
                    case IRIO_LEDMUTEOFF:
                        LedOut();
                        break;
                    case IRIO_LEDON:
                        LedOn();
                        break;
                    case IRIO_LEDOFF:
                        LedOff();
                        break;

                        // JTR3 New commands for unified transmit protocol.
                    case IRIO_HANDSHAKE:
                        irS.handshake = 1;
                        break;
                    case IRIO_NOTIFYONCOMPLETE:
                        irS.sendfinish = 1;
                        break;
                    case IRIO_GETCNT:
                        WaitInReady();
                        cdc_In_buffer[0] = 't';
                        cdc_In_buffer[1] = (txcnt >> 8)&0xff;
                        cdc_In_buffer[2] = (txcnt & 0xff);
                        putUnsignedCharArrayUsbUsart(cdc_In_buffer, 3); //send current buffer to USB
                        break;
                    case IRIO_RETURNTXCNT:
                        irS.sendcount = 1;
                        break;
                        // JTR3 End of new commands

                    case IRIO_DESCRIPTOR:
                        WaitInReady();
                        cdc_In_buffer[0] = PR2; //PWM
                        cdc_In_buffer[1] = CCPR1L; //duty cycle
                        cdc_In_buffer[2] = T2CON; //PWM prescaler, 2 extra bits of duty cycle
                        cdc_In_buffer[3] = T0CON; //transmit timer prescaler
                        cdc_In_buffer[4] = 0x2; //48000000Hz (4 bytes)
                        cdc_In_buffer[5] = 0xdc; //add to USB send buffer
                        cdc_In_buffer[6] = 0x6c; //add to USB send buffer
                        cdc_In_buffer[7] = 0x00; //add to USB send buffer
                        putUnsignedCharArrayUsbUsart(cdc_In_buffer, 8); //send current buffer to USB
                        break;

                    case IRIO_SETUP_PWM: //setup PWM frequency
                        irIOcommand.command[0] = irToy.s[TxBuffCtr];
                        irIOcommand.parameters = 2;
                        irIOstate = I_PARAMETERS;
                        break;
                    case IRIO_SETUP_SAMPLETIMER: //setup sample timer prescaler
                        irIOcommand.command[0] = irToy.s[TxBuffCtr];
                        irIOcommand.parameters = 1;
                        irIOstate = I_PARAMETERS;
                        break;

                    case IRIO_IO_WRITE: //Write this to pins
                    case IRIO_IO_DIR: //Setup direction IO
                        irIOcommand.command[0] = irToy.s[TxBuffCtr];
                        irIOcommand.parameters = 2; //1;
                        //irIOcommand.parCnt=1;
                        irIOstate = I_PARAMETERS;
                        break;
                    case IRIO_IO_READ: //return the port read
                        WaitInReady();
                        //cdc_In_buffer[0]=PORTB; //not just portB, but the IO pins in the correct order....
                        cdc_In_buffer[0] = IrS_ReadPort(); //not just portB, but the IO pins in the correct order....
                        putUnsignedCharArrayUsbUsart(cdc_In_buffer, 1); //send current buffer to USB
                        break;

                    case IRIO_UART_SETUP: //setup UART using CDC settings
                        Usb2Uart_InitUart(FALSE);
                        break;
                    case IRIO_UART_CLOSE: //close UART
                        Usb2Uart_CloseUart();
                        break;
                    case IRIO_UART_WRITE: //write to the UART, get byte to write
                        irIOcommand.command[0] = irToy.s[TxBuffCtr];
                        irIOcommand.parameters = 1;
                        //irIOcommand.parCnt=1;
                        irIOstate = I_PARAMETERS;
                        break;

                    case IRIO_IRW_FREQ:
                        IRRAWINTIF = 0;
                        IRRAWINTIE = 1;
                        break;

                    default:
                        break;
                }
                irS.TXsamples--;
                TxBuffCtr++;
                irIOcommand.parCnt = 0;
                break;

            case I_PARAMETERS://get optional parameters
                irIOcommand.parCnt++;
                irIOcommand.command[irIOcommand.parCnt] = irToy.s[TxBuffCtr]; //store each parameter
                irS.TXsamples--;
                TxBuffCtr++;
                if (irIOcommand.parCnt < (irIOcommand.parameters)) break; //if not all parameters, quit
            case I_PROCESS: //process long commands
                switch (irIOcommand.command[0]) {
                    case IRIO_SETUP_PWM: //setup user defined PWM frequency
                        //stop timer
                        T2CON = 0;

                        //setup the user defined period
                        PR2 = irIOcommand.command[1]; //user period
#define DUTY irIOcommand.command[1]
                        //setup the duty cycle
                        if (irIOcommand.command[2] > 0) {
                            ; //user duty?
                            DUTY = irIOcommand.command[2]; //move to variable
                        }

                        CCPR1L = (DUTY >> 1); //upper 8 bits of duty cycle, 50% of period by binary division
                        if ((DUTY & 0b1) != 0)//if LSB is set, set bit 1 in CCP1CON
                            CCP1CON |= 0b00100000; //5-4 two LSB of duty, 3-0 set PWM
                        else
                            CCP1CON &= (~0b00100000); //5-4 two LSB of duty, 3-0 set PWM

                        T2CON = 0b00000101; //enable timer again, 4x prescaler
                        break;
#undef DUTY
                    case IRIO_SETUP_SAMPLETIMER:
                        T0CON = 0; //setup timer 0
                        IRRXIE = 0; //IR RX interrupt off
                        //configure prescaler
                        //bit 2-0 T0PS2:T0PS0: Timer0 Prescaler Select bits
                        T0CON |= (irIOcommand.command[1]&0b111); //set new prescaler bits
                        IRRXIF = 0; //IR RX interrupt on
                        IRRXIE = 1; //IR RX interrupt on
                        IRRXIF = 0; //IR RX interrupt on
                        break;

#define  IRIO_COMMAND_PARAM irIOcommand.command[1],irIOcommand.command[2] // so it will be easy to adjust who is MSB and who is LSB hehe
#if 0
                    case IRIO_IO_SET: //set these IO bits
                        //PORTB|=irIOcommand.command[1];
                        IrS_SetPortOr(IRIO_COMMAND_PARAM);
                        break;
                    case IRIO_IO_CLR: //clear these IO bits
                        //PORTB&=(~irIOcommand.command[1]);
                        IrS_SetPortAnd(IRIO_COMMAND_PARAM); //
                        break;
#endif
                    case IRIO_IO_WRITE: //clear these IO bits
                        //PORTB=(irIOcommand.command[1]);
                        IrS_SetPortEqual(IRIO_COMMAND_PARAM);
                        break;
                    case IRIO_IO_DIR: //Setup direction IO
                        //TRISB=irIOcommand.command[1];
                        IrS_SetPortTrisEqual(IRIO_COMMAND_PARAM);
                        break;
#undef IRIO_COMMAND_PARAM
                    case IRIO_UART_WRITE:
                        if (TxIf) // If Uart is not full and no data to be sent
                        {
                            TXREG = irIOcommand.command[1];
                        }
                        break;
                }
                irIOstate = I_IDLE; //return to idle state

                irS.TXsamples--;
                TxBuffCtr++;
                break;
        }
    }//switch


    if (irS.overflow == 0) {
        //service the inbound samples here
        //keep in 64 byte buffer then send to USB for max sample rate
        if (irS.rxflag == 1) { //a RX byte is in the buffer
            *InPtr = h; //add to USB send buffer
            irS.RXsamples++;
            InPtr++;
            *InPtr = l; //add to USB send buffer

            irS.RXsamples++;
            InPtr++;
            irS.rxflag = 0; //reset the flag
        }

        //if the buffer is full, send it to USB
        if (((irS.RXsamples == CDC_BUFFER_SIZE) || (irS.flushflag == 1))) { // && (WaitInReady())) { //if we have full buffer, or end of capture flush

            SendCDC_In_ArmNext(irS.RXsamples);

            if ( irS.RXcompleted == 1) {
                irIOstate = I_IDLE;
                DisArmCDCInDB();

                if (irS.RXsamples == CDC_BUFFER_SIZE)
                    putUnsignedCharArrayUsbUsart(cdc_In_buffer, 0); // JTR ZLP at end of last packet was CDC_BUFFER_SIZE

            }
            irS.RXsamples = 0;
            irS.flushflag = 0;
        }

    } else {//overflow error
        //on overflow we loop until we can send 6 0xff then reset everything

        WaitInReady();
        cdc_In_buffer[0] = 0xff; //add to USB send buffer
        cdc_In_buffer[1] = 0xff; //add to USB send buffer
        cdc_In_buffer[2] = 0xff; //add to USB send buffer
        cdc_In_buffer[3] = 0xff; //add to USB send buffer
        cdc_In_buffer[4] = 0xff; //add to USB send buffer
        cdc_In_buffer[5] = 0xff; //add to USB send buffer
        irS.RXsamples = 6;
        putUnsignedCharArrayUsbUsart(cdc_In_buffer, irS.RXsamples); //send current buffer to USB

        T1ON = 0; //t1 is the usb packet timeout, disable it
        T0ON = 0; //timer0 off
        T0_IF = 0;
 
       //reset the pin interrupt, just in case
        IRRXIF = 0;

        irS.RXsamples = 0;
        irS.flushflag = 0;
        irS.overflow = 0;

        LedOff();
    }
    return 0; //CONTINUE
}

void cleanup(void) {

    CCP1CON = 0;
    T0ON = 0;
    T0_IE = 0;
    T0CON = 0;
    T2ON = 0;
    T3CON = 0;
    IRFREQ_CCPxCON = 0;
    T1ON = 0;
    T1IE = 0;
    IRRXIE = 0;
    IRTX_TRIS |= IRTX_PIN; //digital INPUT (no PWM until active)
    IRTX_LAT &= (~IRTX_PIN); //direction 0
}

//the first falling edge starts timer0
//the next pin interrupt copies the timer0 value to a buffer and resets timer0
//if timer0 interrupts, then timeout and end.
//high priority interrupt routine
//#pragma interrupt irsInterruptHandlerHigh

void irsInterruptHandlerHigh(void) {

    if (IRRXIE == 1 && IRRXIF == 1) { //if RB Port Change Interrupt

        l = IRRX_PORT;
        if (T0ON == 0) { //timer not running, setup and start
            if (((l & IRRX_PIN) == 0)) {
                //only if 0, must read PORTB to clear RBIF

                ArmCDCInDB();

                //LedOn();
                TMR0H = 0; //first set the high byte
                TMR0L = 0; //set low byte copies high byte too
                T0_IE = 1;
                T0_IF = 0;
                T0ON = 1; //enable the timer

                TMR1H = 0;
                TMR1L = 0;
                T1IF = 0; //clear the interrupt flag
                T1IE = 1; //able interrupts...
                T1ON = 1; //timer on

                //setup the period capture module to measure the raw IR waveform period
                if (irToy.HardwareVersion > 1) {
                    //capture module measures raw IR frequency
                    IRFREQ_CAP_SETUP();
                    IRFREQ_CAPIF = 0;
                    IRFREQ_CAPIE = 1;

                    //frequency detector is also connected to TMR3 external clock
                    //here we setup the 16bit counter to count the total number of clocks in the signal
                    T3CON = 0b00000110;
                    TMR3H = 0;
                    TMR3L = 1; //first tick is rising edge after next falling edge
                    T3CON |= 0b1; //turn it on

                    modFreqCnt = 0; //used to ignore the first measurement and get the more accurate second measurement
                }
            }

        } else {//timer running, save value and reset
            //the goal is to reset the timer as quickly as possible
            //later we can fine tune the start value to compensate for the lost cycles
            T0ON = 0; //disable the timer
            l = TMR0L; //read low byte, puts high byte in H
            h = TMR0H; //read high byte
            TMR0H = 0; //first set the high byte
            TMR0L = 0; //set low byte copies high byte too
            T0_IF = 0;
            T0ON = 1; //enable the timer

            //reset timer1, USB packet send timeout
            T1ON = 0; //timer on
            TMR1H = 0;
            TMR1L = 0;
            T1ON = 1; //timer on

            if (irS.rxflag == 0) {//check if data is pending
                irS.rxflag = 1;
            } else {//error, overflow
                irS.overflow = 1;
            }
        }
        //clear portb interrupt
        IRRXIF = 0; //Reset the RB Port Change Interrupt Flag bit

    } else if (IRFREQ_CAPIF == 1 && IRFREQ_CAPIE == 1) {//capture of raw IR frequency
        if (modFreqCnt < 6) {
            //we capture on rising edge,
            //this will return 3 samples
            //subtract 2nd from 1st, 3rd from 2nd to get actual time
            modFreq[modFreqCnt] = IRFREQ_CAP_H;
            modFreqCnt++;
            modFreq[modFreqCnt] = IRFREQ_CAP_L;
            modFreqCnt++;

            IRFREQ_CAPIF = 0;

            if (modFreqCnt == 6) {
                IRFREQ_CAPIE = 0;
                IRFREQ_CCPxCON = 0;
            }
        }
    } else if (T0_IE == 1 && T0_IF == 1) { //is this timer 0 interrupt?
        //the idea is that if we got here
        //it has been so long without a pin change that
        //there is not more signal
        //it would be more robust to check the pin state for 0
        //need to examine the limits of typical protocols closer

        T1ON = 0; //t1 is the usb packet timeout, disable it
        T3CON &= (~0b1); //turn it off
        T0ON = 0; //timer0 off
        T0_IF = 0; //clear interrupt flag


        if (irS.TX == 1) {//timer0 interrupt means the IR transmit period is over
            T0_IE = 0;

			//in transmit mode, but no new data is available
            if (irS.txflag == 0) { 

				if(tmr0_buf[2]==0x00) irS.txerror=1; //if not end flag, raise buffer underrun error

                //disable the PWM, output ground
                PWMoff();
                LedOff();
                irS.TX = 0;
                //reset receive interrupt
                IRRXIF = 0;
                IRRXIE = 1; // JTR debug note, Watch the effect of this
                IRRXIF = 0;
                return;
            }

            if (irS.TXInvert == IRS_TRANSMIT_HI) {
                //enable the PWM
                PWMon();
                irS.TXInvert = IRS_TRANSMIT_LO;
            } else {
                //disable the PWM, output ground
                PWMoff();
                irS.TXInvert = IRS_TRANSMIT_HI;
            }

            //setup timer
            TMR0H = tmr0_buf[1]; //first set the high byte
            TMR0L = tmr0_buf[0]; //set low byte copies high byte too
            T0_IF = 0;
            T0_IE = 1;
            T0ON = 1; //enable the timer
            irS.txflag = 0; //buffer ready for new byte

        } else {//receive mode

            if (irS.rxflag == 0) {//check if data is pending
                //packet terminator, 1.7S with no signal
                h = 0xff; //add to USB send buffer
                l = 0xff; //add to USB send buffer
                irS.rxflag = 1; //only send 0xff oxff if you're not liyin
                //set the flush flag to send the packet from the main loop
                irS.flushflag = 1;
            } else {//error, overflow
                irS.overflow = 1;
            }

            //reset the pin interrupt, just in case
            IRRXIE = 1;
            IRRXIF = 0;

            //LedOff();
        }
    } else if (T1IE == 1 && T1IF == 1) { //is this timer 1 interrupt?
        //this is another timer
        //it tells the main loop to send any pending USB bytes
        // after a few MS
        //the idea is that the 1.7s delay for the terminaor byte is really long
        //we want to send the accumulated data sooner than that, or response will appear sluggish
        //time1 (adjust as needed) sets teh flush flag and sends any pending data on it's way
        irS.flushflag = 1;
        irS.RXcompleted = 1;
        T1IF = 0; //clear the interrupt flag
    }
}
//#endif //IRS.c
