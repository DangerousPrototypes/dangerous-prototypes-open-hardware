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
    25AAnnn SPI Serial EEPROM Driver. Tested on 25AA080.
*/

#include "types.h"
#include "SPI.h"
#include "SPIFlash.h"

//Read a byte from SPI EEPROM specified by the address
uint8_t SPIFlash_ReadByte(uint16_t address)
{
    uint8_t  buffer;
    uint16_t MB=0x0000, LB=0x0000;
    MB = address >> 8;
    LB = 0x00FF & address;
    SPIFlash_CS = 0; //Select SPI EEPROM
    SPI_WriteByte(SPIFlash_CMD_READ); //Send READ instruction
    SPI_WriteByte(MB); //Send Address MSByte
    SPI_WriteByte(LB); //Send Address LSByte
    buffer = SPI_ReadByte();
    SPIFlash_CS = 1; //Unselect chip
    return buffer;
}

//Enable Write latch
void SPIFlash_WriteEnable(void)
{
    SPIFlash_CS = 0;                         // Select SPI EEPROM
    SPI_WriteByte(SPIFlash_CMD_WREN);        // Enable Write Operation
    SPIFlash_CS = 1;                         // Unselect SPI EEPROM
}

//Disable Write latch
void SPIFlash_WriteDisable(void)
{
    SPIFlash_CS = 0;                         // Select SPI EEPROM
    SPI_WriteByte(SPIFlash_CMD_WRDI);        // Disable Write Operation
    SPIFlash_CS = 1;                         // Unselect chip
}

//Write a byte to the address specified
uint8_t SPIFlash_WriteByte(uint16_t address, uint8_t data)
{
    uint8_t  WIP=0;
    uint16_t MB=0x0000, LB=0x0000;
    MB = address >> 8;
    LB = 0x00FF & address;
    SPIFlash_WriteEnable();                  // Enable Write Latch.
    SPIFlash_CS = 0;                         // Select EEPROM
    SPI_WriteByte(SPIFlash_CMD_WRITE);       // Send Write instruction
    SPI_WriteByte(MB);                       // Send Address MSByte
    SPI_WriteByte(LB);                       // Send Address LSByte
    SPI_WriteByte(data);                     // Write data
    SPIFlash_CS = 1;                         // Deselect EEPROM. Starts the internal write cycle
    
    do {
        SPIFlash_CS = 0;
        SPI_WriteByte(SPIFlash_CMD_RDSR);
        WIP = SPI_ReadByte() & 0x01;
        SPIFlash_CS = 1;
    } while(WIP); // Wait until Write In Progress(WIP) bit of status register is reset

}

//Read a page
uint8_t SPIFlash_ReadPage(uint16_t pageaddress, uint8_t *buffer)
{
    uint8_t  WIP=0, i;
    uint16_t MB=0x0000, LB=0x0000;
    MB = pageaddress >> 8;
    LB = 0x00FF & pageaddress;
    SPIFlash_CS = 0;                         // Select EEPROM
    SPI_WriteByte(SPIFlash_CMD_READ);        // Send READ instruction
    SPI_WriteByte(MB);                       // Send Address MSByte
    SPI_WriteByte(LB);                       // Send Address LSByte
    for(i=0; i< SPIFlash_PAGE_SIZE; i++)
    {
        *buffer++ = SPI_ReadByte();;         // Read data
    }
    SPIFlash_CS = 1;                         // Deselect EEPROM. Starts the internal write cycle
}

//Write a page
uint8_t SPIFlash_WritePage(uint16_t pageaddress, uint8_t *buffer)
{
    uint8_t  WIP=0, i;
    uint16_t MB=0x0000, LB=0x0000;
    MB = pageaddress >> 8;
    LB = 0x00FF & pageaddress;
    SPIFlash_WriteEnable();                  // Enable Write Latch.
    SPIFlash_CS = 0;                         // Select EEPROM
    SPI_WriteByte(SPIFlash_CMD_WRITE);       // Send Write instruction
    SPI_WriteByte(MB);                       // Send Address MSByte
    SPI_WriteByte(LB);                       // Send Address LSByte
    for(i=0; i< SPIFlash_PAGE_SIZE; i++)
    {
        SPI_WriteByte(*buffer++);            // Write data
    }
    SPIFlash_CS = 1;                         // Deselect EEPROM and also starts the internal write cycle
    
    do {
        SPIFlash_CS = 0;
        SPI_WriteByte(SPIFlash_CMD_RDSR);
        WIP = SPI_ReadByte() & 0x01;
        SPIFlash_CS = 1;
    } while(WIP); // Wait until Write In Progress(WIP) bit of status register is reset

}

