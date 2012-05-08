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

#include "SPI.h"

//Init SPI specific port and registers

void SPI_Init(void)
{
    //Setup SPI related port pins

    //RC7 - 25AA080 Serial EEPROM CS
    //RA2 - MMA7455L Acclerometer CS
    //RC0 PR11 MISO
    //RC1 PR12 MOSI
    //RC2 RP13 CLK

    //Config MMA7455L CS pin
    TRISAbits.TRISA2=0;
    LATAbits.LATA2=1;

    //Config 25AA080 CS pin
    TRISCbits.TRISC7=0;
    LATCbits.LATC7=1;

    //config RP11 as MISO
    RPINR21=11; //PPS input SPI2MISO=RP11
    TRISCbits.TRISC0=1; 

    //config MOSI
    TRISCbits.TRISC1=0;
    LATCbits.LATC1=0;
    RPOR12=9; //PPS output

    //Config SCK
    TRISCbits.TRISC2=0;
    LATCbits.LATC2=0;
    RPOR13=10; //PPS output

    SSP2CON1=0b00100010; //SSPEN = 1 FOSC/16 CKP=0. SPI Clock works @ 1 Mhz.
    SSP2STAT=0b01000000; //CKE=1
}

//Read after a write
uint8_t SPI_ReadWrite(uint8_t buffer) 
{
    SSP2BUF=buffer;
    while(SSP2STATbits.BF==0);
    buffer=SSP2BUF;
    return buffer;
}

//Get a byte from SPI slave device
uint8_t SPI_ReadByte(void)
{
    PIR3bits.SSP2IF = 0;     //Clear SSP2IF flag before any read or write operation.
    SSP2BUF = 0x00;          //Send dummy data to receive a byte.
    while(!PIR3bits.SSP2IF); //Wait for operation to complete.
    return SSP2BUF;          //return the received byte.
}

//Send a byte to SPI slave device
void SPI_WriteByte(uint8_t buffer)
{
    PIR3bits.SSP2IF = 0;     //Clear SSP2IF flag before any read or write operation.
    SSP2BUF = buffer;        //Send buffer(this can be a SPI Command or SPI data).
    while(!PIR3bits.SSP2IF); //Wait for operation to complete.
}




