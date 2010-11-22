/*****************************************************************************
 * Project wide definitions, constants, prototypes, etc.
 *****************************************************************************
 * FileName:        project.h
 * Processor:       dsPIC33
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Eric Walker			20101120	Initial File Creation
 *****************************************************************************/
#ifndef _project_h
#define _project_h

//#include <limits.h>
//#include "proc.h"

#define WEB_PLATFORM_HARDWARE_VERS		"1.X"
#define WEB_PLATFORM_FIRMWARE_VERS		"0.0.0"
#define WEB_PLATFORM_FIRMWARE_TIME		__TIME__" on "__DATE__

#define UNKNOWN		0
#define STACK_ERROR	1
#define ADDRS_ERROR	2
#define RTOS_STACK	3
#define RTOS_MALLOC	4	
#define ClearResetCode()	g_resetcode = UNKNOWN;

extern unsigned char g_resetcode __attribute__((persistent));

#define SetErrorLED()		LATAbits.LATA9 = 1; /* LED 2 for right now */



#endif /* _project_h */

/*EOF*/
