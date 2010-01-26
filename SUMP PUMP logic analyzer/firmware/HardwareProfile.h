#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H
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
	#define PIN_DONE		PORTAbits.RA5
	#define PIN_UPDATE 		PORTCbits.RC1
	#define PIN_LED			PORTCbits.RC2

	#define TRIS_UART1_TX	TRISCbits.TRISC6
	#define PIN_UART1_TX	PORTCbits.RC6

	#define TRIS_UART2_TX	TRISBbits.TRISB1
	#define PIN_UART2_TX	PORTBbits.RB1

	#define TRIS_FLASH_SCK	TRISBbits.TRISB5
	#define PIN_FLASH_SCK	PORTBbits.RB5
	#define TRIS_FLASH_MOSI	TRISAbits.TRISA0
	#define PIN_FLASH_MOSI	PORTAbits.RA0

	#define TRIS_FLASH_CS	TRISAbits.TRISA2
	#define PIN_FLASH_CS	PORTAbits.RA2

	//these are unneeded, but the stack complains if they're not defined
    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISCbits.TRISC2    
    #define self_power          1

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISCbits.TRISC2    
    #define USB_BUS_SENSE       1 

#endif 
