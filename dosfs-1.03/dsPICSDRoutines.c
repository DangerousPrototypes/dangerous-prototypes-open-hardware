#include "dsPICSDRoutines.h"

int DFS_ReadSector(uint8_t unit,uint8_t *buffer, uint32_t sector, uint32_t count)
{

}
int DFS_WriteSector(uint8_t unit,uint8_t *buffer, uint32_t sector, uint32_t count)
{

}

void SD_SPI_Init()
{
    SD_CS_TRIS  = 0; //set direction of CS pin as output (master)
    
    SD_CS_DIS(); //set CS pin high


    //MISO1 C2/RP18 (input)
    SDI2R_I = 10;                   
    //CLK1 C0/RP16 (output)
    RP11_O = SCK2OUT_O;     
    //MOSI1 C1/RP17 (output)
    RP12_O = SDO2_O;
    SPICON1bits.MSTEN = 1;
    SPICON1bits.CKP = 0;
	SPICON1bits.SSEN = 0;
    SPICON1bits.CKE = 1;
    SPICON1bits.SMP = 0;
    
    // set clock freq to 100kHz<312.50kHz<400kHz
    SPICON2 |= 1;
    SPICON2 &= 0xffe1; 
  
    SPIENABLE = 1;
    SD_CS_DIS();
}

SD_sendCMD(uint8_t cmd,uint32_t data, uint8_t crc)
{
     uint8_t i;
     SD_SPITXRX();

     SD_SPI_Send(cmd|0x40);

     for(i=0;i<4;i++)
     {
        SD_SPI_Send((data>>(8*(3-i)))&0x000F);
     }
     SD_SPI_Send(crc);
}
SD_GET_Response()
{

}
void initSD()
{
   uint8_t i;
   SD_SPI_Init();
   SD_CS_DIS();
    
   //send 80 clock pulse
   for(i=0;i<10;i++)
      SD_SPI_Send(0xff);
   SD_CS_EN();
   SD_sendCMD(0x40,0,0x95); // send CMD0 command;
   
}