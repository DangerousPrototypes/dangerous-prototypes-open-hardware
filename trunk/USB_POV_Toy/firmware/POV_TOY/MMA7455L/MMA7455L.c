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


#include "MMA7455L.h"

extern uint8_t temp1;

uint8_t MMA7455L_ReadRegister(uint8_t address)
{
    uint8_t value;
    MMA7455L_CS=0;
    SPI_WriteByte(address << 1);
    value = SPI_ReadByte();
    MMA7455L_CS=1;
    return value;
}

void MMA7455L_WriteRegister(uint8_t address, uint8_t value)
{
    MMA7455L_CS=0;
    SPI_WriteByte((address<<1)|0b10000000);
    SPI_WriteByte(value);
    MMA7455L_CS=1;
}

void MMA7455L_Init(void)
{
    uint8_t regValue; //Temporary varible to hold read register value

    regValue = MMA7455L_ReadRegister(MMA7455L_I2CAD); //Read I2C Address register
    MMA7455L_WriteRegister(MMA7455L_I2CAD, (regValue | 0b10000000)); //Disable I2C by setting I2CDIS bit

    regValue = MMA7455L_ReadRegister( MMA7455L_CTL1 );
    MMA7455L_WriteRegister(MMA7455L_CTL1, regValue | 0b10000000); //Set DFBW bit. This sets 125Hz Bandwidth for Data Measurement. ( 250Hz sample rate )

    MMA7455L_WriteRegister(MMA7455L_MCTL, 0b00000101 ); // Set Mode control register to 2G range, config Measurement Mode and set DRPD=0 ( Data ready status is output to INT1/DRDY PIN)

    MMA7455L_WriteRegister(MMA7455L_XOFFL, MMA7455L_X_OFFSET);  //Calibrate X offset.
    LATB = regValue;
}


sint8_t MMA7455L_ReadAcceleration(sint8_t address)
{
    MMA7455L_ReadRegister(address);  //Read 8bit Accel.
}
