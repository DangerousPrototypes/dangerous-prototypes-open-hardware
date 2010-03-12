#ifndef _DSPICSDROUTINES_H
#define _DSPICSDROUTINES_H
#include <stdlib.h>

#define SD_CS_EN()    SD_CS=0 
#define SD_CS_DIS()   SD_CS=1
#define SD_SPI_BUF    SPIBUF
#define SD_SPITXRX() 	while(!EEPROM_SPI_IF)
#define SD_SPI_Send(data) SD_SPI_BUF = data; SD_SPITXRX()

int DFS_ReadSector(uint8_t unit,uint8_t *buffer, uint32_t sector, uint32_t count);

int DFS_WriteSector(uint8_t unit,uint8_t *buffer, uint32_t sector, uint32_t count);

void SD_SPI_Init(void);


#endif