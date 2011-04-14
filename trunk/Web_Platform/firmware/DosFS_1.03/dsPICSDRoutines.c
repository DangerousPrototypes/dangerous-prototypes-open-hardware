#include "dsPICSDRoutines.h"
#include "HardwareProfile.h"
/*Function required by DosFS to read from sector# = sector with 
count number of sectors into buffer.
*/
uint32_t DFS_ReadSector(uint8_t unit, uint8_t *buffer, uint32_t sector, uint32_t count)
{
    uint8_t response;
    uint16_t i;
    uint32_t offset;
    offset =  sector * 512;
    
  	SD_CS_EN();
    //send read command
	SD_sendCMD(0x51,offset,0xff);
    
	if(SD_GET_Response()==0)
 	{
    	do
    	{
      		SD_SPI_Send(0xFF);
      		response = SD_SPI_BUF; 
    	}while(response==0xff);//wait
    	if (response == 0xFE)
    	//start of sector data
		{
 			for( i=0; i<512; count++)
 			{
 			    SD_SPI_Send(0xFF);      
           		*buffer++ = SD_SPI_BUF;
    		}       	
        	SD_SPI_Send(0xFF);
			SD_SPI_Send(0xFF);
			SD_CS_DIS();
			return 0;
		}
	}
    SD_CS_DIS();
    return 1;
    	
}

/*Function required by DosFS to write the data contained by buffer
 into sector# = sector with count number of sectors.
*/
uint32_t DFS_WriteSector(uint8_t unit,uint8_t *buffer, uint32_t sector, uint32_t count)
{
	uint8_t response;
    uint16_t i;
    uint32_t offset;
    offset =  sector * 512;
    
  	SD_CS_EN();
    //send write command
	SD_sendCMD(0x58,offset,0xff);
	if(SD_GET_Response()==0)//command accepted
 	{
	 	SD_SPI_Send(0xFF);//one byte gap
	 	SD_SPI_Send(0xFE);//send start data token
	 	for(i=0;i<512;i++)//send 512 bytes
	 		SD_SPI_Send(buffer[i]);
	 	SD_SPI_Send(0xFF);//crc lo
	 	SD_SPI_Send(0xFF);//crc hi
	 	SD_SPI_Send(0xFF);
	 	response = SD_SPI_BUF;
	 	if (response &0x0F == 0x05)
	 	{
		 	do
	 		{
	 			SD_SPI_Send(0xFF);
	 			response = SD_SPI_BUF;
	 		}while(response !=0xFF); // wait till not busy
	 		SD_CS_DIS();
	 		return 0; //success
	 	}
	 	SD_CS_DIS();
		return 1; //error writing
	}
	SD_CS_DIS();
	return 1; //error writing
}

/*
initialize SPI for SD.
*/
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

/*
Function for sending a command to the SD card.
cmd is the command, data is the 4-byte parameter in 
Big Endian and crc is the Checksum.
*/
void SD_sendCMD(uint8_t cmd,uint32_t data, uint8_t crc)
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

/*
FUnction to get the response from SD
*/
unsigned char SD_GET_Response()
{
 //Response comes 1-8bytes after command
  //the first bit will be a 0
  //followed by an error code
  //data will be 0xff until response
  int i=0;

  char response;

  while(i<=64)
  {
    SD_SPI_Send(0xff);
    response = SD_SPI_BUF;
    if(response==0x00)break;
    if(response==0x01)break;
    i++;
  }
  return response;
}


/*
initialize SD card
*/
unsigned char initSD()
{
   uint8_t i, response;
   SD_SPI_Init();
   SD_CS_DIS();
    
   //send 80 clock pulse
   for(i=0;i<10;i++)
      SD_SPI_Send(0xff);
   SD_CS_EN();
   SD_sendCMD(0x40,0,0x95); // send CMD0 command;
   while ((response = SD_GET_Response())== 0x01)
   { 
      SD_CS_DIS();
      SD_SPI_Send(0xff);    
      SD_CS_EN();
      SD_sendCMD(0x41,0,0x95); //send CMD1
      
   }
   SD_CS_DIS();
   return 0;  
}
