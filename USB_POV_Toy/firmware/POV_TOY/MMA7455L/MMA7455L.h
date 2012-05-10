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


/*
MMA7455L Three Axis - Digital Output Accelerometer

*/

#ifndef MMA7455L_H
#define MMA7455L_H

#include "types.h"
#include "SPI.h"

//Register definition. Not all registers are used in this driver.

#define MMA7455L_XOUTL                 0x00       // 10 bits output value X LSB
#define MMA7455L_XOUTH                 0x01       // 10 bits output value X MSB
#define MMA7455L_YOUTL                 0x02       // 10 bits output value Y LSB
#define MMA7455L_YOUTH                 0x03       // 10 bits output value Y MSB
#define MMA7455L_ZOUTL                 0x04       // 10 bits output value Z LSB
#define MMA7455L_ZOUTH                 0x05       // 10 bits output value Z MSB
#define MMA7455L_XOUT8                 0x06       // 8 bits output value X
#define MMA7455L_YOUT8                 0x07       // 8 bits output value Y
#define MMA7455L_ZOUT8                 0x08       // 8 bits output value Z   
#define MMA7455L_STATUS                0x09       // Status registers               
#define MMA7455L_DETSRC                0x0A       // Detection source registers     
#define MMA7455L_TOUT                  0x0B       // Temperature output value (Optio
#define MMA7455L_RESERVED              0x0C       // (Reserved)                    
#define MMA7455L_I2CAD                 0x0D       // I2C device address    
#define MMA7455L_USRINF                0x0E       //  User information (Optional)    
#define MMA7455L_WHOAMI                0x0F       //  Who am I value (Optional)    
#define MMA7455L_XOFFL                 0x10       // Offset drift X value (LSB)     
#define MMA7455L_XOFFH                 0x11       // Offset drift X value (MSB)     
#define MMA7455L_YOFFL                 0x12       // Offset drift Y value (LSB)     
#define MMA7455L_YOFFH                 0x13       // Offset drift Y value (MSB)     
#define MMA7455L_ZOFFL                 0x14       // Offset drift Z value (LSB)     
#define MMA7455L_ZOFFH                 0x15       // Offset drift Z value (MSB)     
#define MMA7455L_MCTL                  0x16       // Mode control    
#define MMA7455L_INTRST                0x17       // Interrupt latch reset   
#define MMA7455L_CTL1                  0x18       // Control 1
#define MMA7455L_CTL2                  0x19       // Control 2   
#define MMA7455L_LDTH                  0x1A       // Level detection threshold limit
#define MMA7455L_PDTH                  0x1B       // Pulse detection threshold limit
#define MMA7455L_PW                    0x1C       // Pulse duration value 
#define MMA7455L_LT                    0x1D       // Latency time value  
#define MMA7455L_TW                    0x1E       // Time window for 2nd pulse value


#define MMA7455L_CS LATAbits.LATA2                //Chip Select Pin of MMA7455L mapped to RA2 in this hardware. Change this for a different hardware.

void MMA7455L_Init(void);    // Initialize and configure the accelerometer in I2C Mode 
uint8_t MMA7455L_ReadRegister(uint8_t address);
void MMA7455L_WriteRegister(uint8_t address, uint8_t value);
sint8_t MMA7455L_ReadAcceleration(sint8_t address);

#endif
