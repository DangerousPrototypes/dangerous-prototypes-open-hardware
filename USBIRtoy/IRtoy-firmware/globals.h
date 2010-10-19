#ifndef GLOBALS_H
#define GLOBALS_H

// i put all the

// =================== GLOBAL TYPEDEFS
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;



#define putUnsignedCharArrayUsbUsart(u8Array,Num) 	putUSBUSART((char*)(u8Array),(Num))
#define getUnsignedCharArrayUsbUart(u8Array,Num)	getsUSBUSART((char*)(u8Array),(Num))

#define INVALID	0xFF

//#define TRUE	1
//#define FALSE 	0

// =================== GLOBAL HEADERS
#include "HardwareProfile.h"
#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "usb_config.h"

#if 1
#include "USBStack\usb.h"
#include "USBStack\usb_device.h"
#include "USBStack\usb_function_cdc.h"
#else
//USB stack
#include "./USB/usb.h"
#include "./USB/usb_function_cdc.h"
#include "./USB/usb_device.h"
#endif

//IR Toy functions
#include "SUMP.h" 		//sump functions
#include "IRIO.h" 		//IRIO functions
#include "IRs.h" 		//IRs functions
#include "RCdecoder.h" 	//RC5 decoder
#include "IrReflect.h"
#include "usb2uart.h"

#include "hal_lin_m.h"

//our USB input buffer functions
#include "USBbuf.h"

#include "main.h"

// From Microchip Library
// For portability purpose: adjusts itself accdg to the target processor
#include <capture.h>
#include <timers.h>





#endif
