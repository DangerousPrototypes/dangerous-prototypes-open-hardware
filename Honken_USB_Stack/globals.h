#ifndef GLOBALS_H
#define GLOBALS_H

// i put all the

// JTR compiler globals.
// I made this header safe so that it does not
// conflict with the same named header used with
// the IRTOY and BPv4.

// =================== GLOBAL TYPEDEFS
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

/*
#define putUnsignedCharArrayUsbUsart(u8Array,Num)       putUSBUSART((char*)(u8Array),(Num))
#define getUnsignedCharArrayUsbUart(u8Array,Num)        getsUSBUSART((char*)(u8Array),(Num))
*/
#define INVALID 0xFF

#define FALSE   0
#define TRUE    (!FALSE)

// =================== GLOBAL HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif
