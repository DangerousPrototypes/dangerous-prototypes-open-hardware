#ifndef HAL_SRAM_H
#define HAL_SRAM_H

#define CS_PIN 	LATCbits.LATC0

#define DO_0	LATAbits.LATA0
#define DO_1	LATAbits.LATA1
#define DO_2	LATAbits.LATA2
#define DO_3	LATAbits.LATA3

#define DI_0	PORTBbits.RB0
#define DI_1	PORTBbits.RB1
#define DI_2	PORTBbits.RB2
#define DI_3	PORTBbits.RB3

#define CS_0	LATAbits.LATA5
#define CS_1	LATCbits.LATC1
#define CS_2	LATCbits.LATC2
#define CS_3	LATBbits.LATB4

#define SCLK	LATCbits.LATC7

typedef enum
{
SRAM_CMD_READ=0x03,
SRAM_CMD_WRITE=0x02,
SRAM_CMD_RDSR=0x05,
SRAM_CMD_WRSR=0x01
}SRAM_COMMANDS;


typedef enum
{
SPI_0=0,
SPI_1,
SPI_2,
SPI_3
}SPI_GROUP;


void hal_sram_parallelInit(void);
void hal_sram_parallelRead(u8 AddrHi,u8 AddrLo,u8 DataCount,u8 returnData[][4]);
void hal_sram_parallelWrite(u8 AddrHi,u8 AddrLo,int DataCount, u8 *DataArray);

#endif
