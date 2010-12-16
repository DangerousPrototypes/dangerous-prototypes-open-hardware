#ifndef GLOBALS_H
#define GLOBALS_H


typedef unsigned char u8;
typedef unsigned int u16;

// built in headers
#include <p18cxxx.h>
//#include <spi.h>

// =================== GLOBAL HEADERS
#include "HardwareProfile.h"
#include "GenericTypeDefs.h"
#include "Compiler.h"

#include "usb_config.h"
//USB stack
#include "./USB/usb.h"
#include "./USB/usb_function_cdc.h"
#include "./USB/usb_device.h"


#define putUnsignedCharArrayUsbUsart(u8Array,Num) 	putUSBUSART((char*)(u8Array),(Num))
#define getUnsignedCharArrayUsbUart(u8Array,Num)	getsUSBUSART((char*)(u8Array),(Num))

// user definer headers
#include "hal_sram.h"
#include "hal_logicshrimp.h"

#define PORT_ON 1
#define PORT_OFF 0


//select the correct interrupt pin depending on hardware and settings
#if defined (HAD_USBIRC) || defined (IRRX_ONRB4)// irRX B4 (25)
	#define	IRRX_LAT  LATB
	#define IRRX_TRIS TRISB
	#define IRRX_PORT PORTB
	#define IRX PORTBbits.RB4
	#define IRRX_PIN  0b10000
	#define IRRX_IE	INTCONbits.RBIE
	#define IRRX_IF	INTCONbits.RBIF
	#define IRRX_IP INTCON2bits.RBIP
#else //use INT2 with edge trigger, schmidt buffer
	#define IRRX_ONINT2 //tells other functions we're using INT2 interrupt
	#define	IRRX_LAT  LATB
	#define IRRX_TRIS TRISB
	#define IRRX_PORT PORTB
	#define IRX PORTBbits.RB2
	#define IRRX_PIN  0b100
	#define IRRX_IE	INTCON3bits.INT2IE
	#define IRRX_IF	INTCON3bits.INT2IF
	#define IRRX_IP INTCON3bits.INT2IP
	#define IRRX_EDGE INTCON2bits.INTEDG2
#endif


#define TM0IF INTCONbits.T0IF
#define TM0IE INTCONbits.T0IE
#define TM0ON T0CONbits.TMR0ON

#define T1IF 	PIR1bits.TMR1IF
#define T1IE 	PIE1bits.TMR1IE
#define T1ON	T1CONbits.TMR1ON

#define T2IF 	PIR1bits.TMR2IF
#define T2IE 	PIE1bits.TMR2IE
#define T2ON 	T2CONbits.TMR2ON

#endif
