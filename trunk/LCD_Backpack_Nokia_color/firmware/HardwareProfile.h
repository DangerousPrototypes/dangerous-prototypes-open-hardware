#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

//the first batch of OLS has 20mhz crystal on the PIC
//use this to compile for that hardware
#define XTAL_20MHZ

//hardware version string
#define HW_VER 0x01

//firmware version string
#define FW_VER_H 0x02
#define FW_VER_L 0x00

//pin setup
/*
A0 PR0 AN0 boost feedback

B7 RP10 PGD
B6 RP9 PGC

B2 RP5 CS
B1 RP4 RESET
B0 RP3 BKLIT
C7 RP18 DATA
C6 RP17 CLOCK
*/
#define TRIS_BKLITE	TRISBbits.TRISB0
#define LAT_BKLITE	LATBbits.LATB0

#define TRIS_SCK	TRISCbits.TRISC6
#define PIN_SCK	PORTCbits.RC6
#define LAT_SCK LATCbits.LATC6

#define TRIS_MOSI	TRISCbits.TRISC7
#define PIN_MOSI	PORTCbits.RC7
#define LAT_MOSI LATCbits.LATC7

#define TRIS_CS	TRISBbits.TRISB2
#define PIN_CS	PORTBbits.RB2
#define LAT_CS LATBbits.LATB2

#define TRIS_RESET	TRISBbits.TRISB1
#define PIN_RESET	PORTBbits.RB1
#define LAT_RESET LATBbits.LATB1

#define EnableSPIPPS() 	RPOR18=9;RPOR17=10
#define DisableSPIPPS() 	RPOR18=0;RPOR17=0

#define BootloaderJump() _asm goto 0x16 _endasm

//these are unneeded, but the stack complains if they're not defined
//#define USE_SELF_POWER_SENSE_IO
#define tris_self_power     TRISCbits.TRISC2    
#define self_power          1

//#define USE_USB_BUS_SENSE_IO
#define tris_usb_bus_sense  TRISCbits.TRISC2    
#define USB_BUS_SENSE       1 

#endif 
