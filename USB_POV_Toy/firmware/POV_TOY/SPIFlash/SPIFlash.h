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
25CXYZ SPI Serial EEPROM Driver. At the moment configured and tested for 25AA080

*/

#ifndef SPIFLASH_H
#define SPIFLASH_H

#include "types.h"
#include "SPI.h"

#define SPIFlash_CMD_READ		0b00000011	// Read data
#define SPIFlash_CMD_WRITE		0b00000010	// Write data
#define SPIFlash_CMD_WRDI		0b00000100	// Disable write operations
#define SPIFlash_CMD_WREN		0b00000110	// Enable write operations
#define SPIFlash_CMD_RDSR		0b00000101	// Read Status register
#define SPIFlash_CMD_WRSR		0b00000001	// Write Status register

#define SPIFlash_PAGE_SIZE		16			// Page size in bytes. (change this for different size chip)
#define SPIFlash_TOTAL_PAGES 	64			// Total number of pages in this chip. (change this for differnet size chip)
#define SPIFlash_TOTAL_SIZE		1024		// Total size of EEPROM in bytes

#define SPIFlash_CS				LATCbits.LATC7

uint8_t SPIFlash_ReadByte(uint16_t address);
void SPIFlash_WriteEnable(void);
void SPIFlash_WriteDisable(void);
uint8_t SPIFlash_WriteByte(uint16_t address, uint8_t data);
uint8_t SPIFlash_ReadPage(uint16_t pageaddress, uint8_t *buffer);
uint8_t SPIFlash_WritePage(uint16_t pageaddress, uint8_t *buffer);



#endif
