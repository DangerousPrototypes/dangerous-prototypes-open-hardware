/*
*
*	Dangerous Prototypes Flash Destroyer firmware
*	License: creative commons - attribution, share-alike
* 	http://creativecommons.org/licenses/by-sa/2.0/
*	Copyright 2010
*	http://dangerousprototypes.com
*/

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <p18cxxx.h>
#include <i2c.h>
#include <eep.h>

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

#define TRUE	1
#define FALSE	0

#include "lld_Interrupts.h"

#include "hal_EEPROM.h"
#include "hal_InternalEEPROM.h"
#include "hal_Timer.h"
#include "hal_7SegDrv.h"

#endif /* GLOBALS_H_ */


///////////////////
