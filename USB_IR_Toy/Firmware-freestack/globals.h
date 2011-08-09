#ifndef GLOBALS_H
#define GLOBALS_H

// =================== GLOBAL TYPEDEFS
#define INVALID 0xFF
// =================== GLOBAL HEADERS
#include "HardwareProfile.h"
#include "GenericTypeDefs.h"
#include "cdc_config.h"
#include "usb_stack.h"
#include "cdc.h"

//IR Toy functions
#include "main.h"
#include "SUMP.h"               //sump functions
#include "IRIO.h"               //IRIO functions
#include "IRs.h"                //IRs functions
#include "RCdecoder.h"  //RC5 decoder
#include "IrReflect.h"
#include "usb2uart.h"
#include "hal_lin_m.h"
#include "irWidget.h"

// From Microchip Library
// For portability purpose: adjusts itself accdg to the target processor
#include <capture.h>
#include <timers.h>





#endif
