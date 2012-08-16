/* header */
#ifndef SPI_H
#define SPI_H
// forward declarations
void initSPI(void);
void SPIworker(void);
void SPIEEworker(void);
void SPIPWMworker(void);
void SPIDACworker(void);
void SPIADCworker(void);
// spi interrupt service routine
#define SPIisr	do { \
} while(0);

//Instruction defines for SPI EEPROM
#define SPIEEMASK 0xF7	
#define SPI_READ	0x03	//Read data from memory array beginning at selected address
#define SPI_WRITE	0x02	//Write data to memory array beginning at selected address
#define SPI_WRDI	0x04	//Reset the write enable latch (disable write operations)
#define SPI_WREN	0x06	//Set the write enable latch (enable write operations)
#define SPI_RDSR	0x05	//Read STATUS register
#define SPI_WRSR	0x01	//Write STATUS register
extern unsigned char eeBuf[256];
#endif