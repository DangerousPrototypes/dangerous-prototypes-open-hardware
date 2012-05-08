/*

Copyright (c) 2012 dangerousprototypes.com.

The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#ifndef POVTOY_H
#define POVTOY_H

#include "types.h"

#define POVTOY_ACCELERATION_THRESHOLD	110
#define POVTOY_DIRECTION_RIGHT			0
#define POVTOY_DIRECTION_LEFT			1
#define POVTOY_DISPLAY_TOTAL_COLUMNS	48   
#define POVTOY_DISPLAY_BRIGHTNESS		128  /* Any number between 0 to 255. 0 - 0% Duty and 255 - 100% duty */

// Uncomment / comment below line to use unidirectional display or bidirectional display
#define POVTOY_DISABLE_BIDIRECTIONAL 

// Uncomment below line to use Fixed Frequency display Refresh
#define POVTOY_FIXED_FREQ_REFESH

#define POVTOY_FIXED_FREQ_RELOAD_VALUE			178  /*200 Hz*/

/* Reload values for Timer0 with 1:256 Prescale and CPUDIV = OSC1

33 -- 70.07 Hz
61 -- 80.13 Hz
82 -- 89.80 Hz
100 -- 100.16 Hz
114 -- 110.04 Hz
126 -- 120.19 Hz
136 -- 130.21 Hz
144 -- 139.51 Hz
152 -- 150.24 Hz
158 -- 158.44 Hz
164 -- 169.84 Hz
169 -- 179.60 Hz
174 -- 190.55 Hz
178 -- 200.32 Hz
204 -- 300.48 Hz
217 -- 400.64 Hz

*/

//Function prototypes
void POVToy_LEDPortInit(void);
void POVToy_PortsInit(void);
void POVToy_Int1Init(void);
void POVToy_Timer0Init(void);
void POVToy_IncrementIndex(void);
void POVToy_DecrementIndex(void);
void POVToy_SetBrightness(uint8_t brightness);
void POVToy_LowPriorityISR(void);
void POVToy_LoadBitmap(uint8_t BitmapAddress);
uint8_t POVToy_ReadSwitch(void);


//Initialization sequence for POV Toy
#define POVToy_Init       SPI_Init();               /*Init port pins related to SPI and SPI registers */ \
                          POVToy_LEDPortInit();     /*Init LED port pins */ \
                          POVToy_PortsInit();       /*Init other port pins */ \
                          POVToy_Timer0Init();      /*configure timer1 for display refresh */ \
                          POVToy_Int1Init();        /*Configure INT external interrupt. */ \
                          POVToy_LoadBitmap(0);     /*Load Bitmap to RAM from SPI Flash */ \
                          MMA7455L_Init();          /*Init Accelerometer */



#endif
