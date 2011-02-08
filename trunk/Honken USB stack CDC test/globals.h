#ifndef GLOBALS_H
#define GLOBALS_H

// i put all the

// =================== GLOBAL TYPEDEFS
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;


/*
#define putUnsignedCharArrayUsbUsart(u8Array,Num) 	putUSBUSART((char*)(u8Array),(Num))
#define getUnsignedCharArrayUsbUart(u8Array,Num)	getsUSBUSART((char*)(u8Array),(Num))
*/
#define INVALID	0xFF

#ifndef FALSE
#define FALSE 	0
#endif
#ifndef TRUE
#define TRUE	(!FALSE)
#endif
// =================== GLOBAL HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usb_config.h"

#if 1
#include "usb_stack.h"
#include "cdc.h"
#else
//USB stack
#include "./USB/usb.h"
#include "./USB/usb_function_cdc.h"
#include "./USB/usb_device.h"
#endif

#endif
