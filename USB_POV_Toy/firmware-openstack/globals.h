#ifndef GLOBALS_H
#define GLOBALS_H

// i put all the

// =================== GLOBAL TYPEDEFS
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;



//#define putUnsignedCharArrayUsbUsart(u8Array,Num) 	putUSBUSART((char*)(u8Array),(Num))
//#define getUnsignedCharArrayUsbUart(u8Array,Num)	getsUSBUSART((char*)(u8Array),(Num))

#define INVALID	0xFF

// =================== GLOBAL HEADERS
#include "HardwareProfile.h"
#include "GenericTypeDefs.h"
//#include "Compiler.h"
//#include "usb_config.h"
//#include "HD44780.h" 

//USB stack
#include "cdc_config.h"
#include "usb_stack.h"
#include "cdc.h"


//our USB input buffer functions
//#include "USBbuf.h"

//#include "main.h"
//#include "LCD_driver.h"

// From Microchip Library
// For portability purpose: adjusts itself accdg to the target processor
#include <capture.h>
#include <timers.h>

//register definitions
#define T1IF 	PIR1bits.TMR1IF
#define T1IE 	PIE1bits.TMR1IE
#define T1ON	T1CONbits.TMR1ON

#define TM0IF INTCONbits.T0IF
#define TM0IE INTCONbits.T0IE
#define TM0ON T0CONbits.TMR0ON

#endif
