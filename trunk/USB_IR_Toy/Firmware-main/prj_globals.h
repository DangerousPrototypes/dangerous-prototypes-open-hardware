#ifndef PRJ_GLOBALS_H
#define PRJ_GLOBALS_H

// =================== GLOBAL TYPEDEFS
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
typedef unsigned char BYTE;


//#define putUnsignedCharArrayUsbUsart(u8Array,Num)       putUSBUSART((char*)(u8Array),(Num))
//#define getUnsignedCharArrayUsbUart(u8Array,Num)        getsUSBUSART((char*)(u8Array),(Num))

#define INVALID 0xFF

// =================== GLOBAL HEADERS
#include "HardwareProfile.h"
#include "main.h"
#include "SUMP.h"               //sump functions
#include "IRs.h"                //IRs functions
#include "RCdecoder.h"  //RC5 decoder
#include "usb2uart.h"
#include "irWidget.h"


// From Microchip Library
// For portability purpose: adjusts itself accdg to the target processor
#include <capture.h>
#include <timers.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WAIT 1
#define NOWAIT 0



#endif
