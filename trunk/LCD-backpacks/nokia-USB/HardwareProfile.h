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
A0 PR0 flash_si
A1 PR1 flash_so
A2 flash_cs
A3 PROG_B (pull-down only) test high
A5 RP2 DONE (input only) test high, eventually
C1 RP12 update button (input/interrupt) test high
C2 RP13 ACT LED

B7 RP10 PGD
B6 RP9 PGC
B5 RP8 flash_sck
B4 RP7 FPGA_AUX0
B3 RP6 fpga_cs
B2 RP5 fpga_aux1
B1 RP4 FPGA_AUX2
B0 RP3 FPGA_AUX3
C7 RP18 RX1
C6 RP17 TX1
*/
#define PIN_PROG_B 		PORTAbits.RA3
#define TRIS_PROG_B 	TRISAbits.TRISA3
#define PROG_B_LOW()	PIN_PROG_B=0; TRIS_PROG_B=0 //ground,output
#define PROG_B_HIGH()	PIN_PROG_B=0; TRIS_PROG_B=1	

#define PIN_DONE		PORTAbits.RA5
#define PIN_UPDATE 		PORTCbits.RC1
#define PIN_LED			PORTCbits.RC2

#define TRIS_UART1_TX	TRISCbits.TRISC6
#define PIN_UART1_TX	LATCbits.LATC6
#define TRIS_UART1_RX	TRISCbits.TRISC7
#define PIN_UART1_RX	PORTCbits.RC7
//	#define TRIS_UART1		TRISC
//	#define TXPIN_UART1		0b01000000
//	#define RXPIN_UART1		0b10000000

#define TRIS_UART2_TX	TRISBbits.TRISB1
#define PIN_UART2_TX	PORTBbits.RB1

#define TRIS_FLASH_SCK	TRISBbits.TRISB5
#define PIN_FLASH_SCK	PORTBbits.RB5
#define TRIS_FLASH_MOSI	TRISAbits.TRISA0
#define PIN_FLASH_MOSI	PORTAbits.RA0

#define TRIS_FLASH_CS	TRISAbits.TRISA2
#define PIN_FLASH_CS	PORTAbits.RA2
#define FPGA_CS_LOW()	PIN_FLASH_CS=0; TRIS_FLASH_CS=0
#define FPGA_CS_HIGH() 	PIN_FLASH_CS=1; TRIS_FLASH_CS=0

#define TRIS_FPGA_SCK	TRISBbits.TRISB4
#define PIN_FPGA_SCK	PORTBbits.RB4
#define TRIS_FPGA_MISO	TRISBbits.TRISB2
#define PIN_FPGA_MISO	PORTBbits.RB2
#define TRIS_FPGA_MOSI	TRISBbits.TRISB3
#define PIN_FPGA_MOSI	PORTBbits.RB3
#define TRIS_FPGA_DATAREADY	TRISBbits.TRISB1
#define PIN_FPGA_DATAREADY	PORTBbits.RB1

#define TRIS_FPGA_CS	TRISAbits.TRISA1
#define PIN_FPGA_CS		PORTAbits.RA1

#define BootloaderJump() _asm goto 0x16 _endasm

//these are unneeded, but the stack complains if they're not defined
//#define USE_SELF_POWER_SENSE_IO
#define tris_self_power     TRISCbits.TRISC2    
#define self_power          1

//#define USE_USB_BUS_SENSE_IO
#define tris_usb_bus_sense  TRISCbits.TRISC2    
#define USB_BUS_SENSE       1 

#endif 
