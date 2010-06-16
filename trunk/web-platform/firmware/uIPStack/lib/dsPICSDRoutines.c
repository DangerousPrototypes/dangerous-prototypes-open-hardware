#include "dsPICSDRoutines.h"

//some VERY basic caching strategy to stop the dosfs library repeated reading the same sector
static uint8_t* lastbuffer = 0;
static uint32_t lastsector = 0;
/*
Set PPS pins to point SPI peripheral to SD card pins
*/
void SD_PPSSetup(){

    //MISO1 C2/RP18 (input)
    SDI2R_I = 10;                   
    //CLK1 C0/RP16 (output)
    RP11_O = SCK2OUT_O;     
    //MOSI1 C1/RP17 (output)
    RP12_O = SDO2_O;

}




/*Function required by DosFS to read from sector# = sector with 
count number of sectors into buffer.
*/
uint8_t DFS_ReadSector(uint8_t unit, uint8_t *buffer, uint32_t sector, uint32_t count)
{
	//caching!
	if(lastbuffer == buffer && lastsector == sector ) return 0;


    uint8_t response;
    uint16_t i;
    uint32_t offset;
    offset =  sector << 9; // multiply by 512
    
  	SD_CS_EN();

	SD_PPSSetup();
    //send read command
	SD_sendCMD(0x11,offset,0xff);

	response = SD_GET_Response();     
	if(response==0)
 	{
    	do
    	{
      		SD_SPI_Send(0xFF);
      		response = SD_SPIBUF; 
    	}while(response==0xff);//wait
    	if (response == 0xFE)
    	//start of sector data
		{
			lastbuffer =buffer;
			lastsector = sector; 
 			for( i=0; i<512; i++)
 			{
 			    SD_SPI_Send(0xFF);      
           		*buffer = SD_SPIBUF;
				buffer++;
    		}       	
			//get checksum byte 1
        	SD_SPI_Send(0xFF);
		 	response = SD_SPIBUF;
			//and checksum byte 2
			SD_SPI_Send(0xFF);
		 	response = SD_SPIBUF;
			SD_CS_DIS();
			return 0;
		}
	}
    SD_CS_DIS();
    return response;
    	
}

/*Function required by DosFS to write the data contained by buffer
 into sector# = sector with count number of sectors.
*/
uint8_t DFS_WriteSector(uint8_t unit,uint8_t *buffer, uint32_t sector, uint32_t count)
{
	uint8_t response;
    uint16_t i;
    uint32_t offset;
    offset =  sector * 512;
    
  	SD_CS_EN();
    SD_PPSSetup();

	//send write command
	SD_sendCMD(0x18,offset,0xff);

	if(SD_GET_Response()==0)//command accepted
 	{
	 	SD_SPI_Send(0xFF);//one byte gap
	 	response = SD_SPIBUF;
	 	SD_SPI_Send(0xFE);//send start data token
	 	response = SD_SPIBUF;
	 	for(i=0;i<512;i++)
		{	//send 512 bytes
	 		SD_SPI_Send(buffer[i]);
		 	response = SD_SPIBUF;
		}
	 	SD_SPI_Send(0xFF);//crc lo
	 	response = SD_SPIBUF;
	 	SD_SPI_Send(0xFF);//crc hi
	 	response = SD_SPIBUF;
	 	SD_SPI_Send(0xFF);
	 	response = SD_SPIBUF;
	 	if ((response & 0x0F) == 0x05)
	 	{
		 	do
	 		{
	 			SD_SPI_Send(0xFF);
	 			response = SD_SPIBUF;
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

	SD_PPSSetup();

    SPICON1bits.MSTEN = 1;
    SPICON1bits.CKP = 0;
	SPICON1bits.SSEN = 0;
    SPICON1bits.CKE = 1;
    SPICON1bits.SMP = 0;
    
    // set clock freq to 100kHz<312.50kHz<400kHz
    SPICON2 |= 1;
    SPICON2 &= 0xffe1; 
  
    SPISTATbits.SPIEN = 1;
    SD_CS_DIS();
}

/*
Function for sending a command to the SD card.
cmd is the command, data is the 4-byte parameter in 
Big Endian and crc is the Checksum.
*/
void SD_sendCMD(uint8_t cmd,uint32_t data, uint8_t crc)
{
	volatile uint8_t dummy;
	register uint8_t i;
	
	SD_SPI_Send(0xff);
	dummy = SD_SPIBUF;
	SD_SPI_Send(cmd|0x40);
	dummy=SD_SPIBUF;
	for(i=0;i<4;i++)
	{
		SD_SPI_Send((uint8_t)(data>>(8*(3-i))));
		dummy=SD_SPIBUF;
     }
     SD_SPI_Send(crc);
	 dummy=SD_SPIBUF;
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
		response = SD_SPIBUF;
		if((response & 0x80) == 0 ) break;
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
	volatile uint8_t dummy; 
	//send 80 clock pulse
	for(i=0;i<10;i++)
	{
		SD_SPI_Send(0xff);
		dummy = SD_SPIBUF;
	}
	SD_CS_EN();
	SD_sendCMD(0x00,0,0x95); // send CMD0 command == reset and enter idle state
	while ((response = SD_GET_Response())== 0x01)
	{ 
		SD_CS_DIS();
		SD_SPI_Send(0xff);
		dummy = SD_SPIBUF;    
		SD_CS_EN();
		SD_sendCMD(0x01,0,0x95); //send CMD1 == initialise card
	}
	SD_CS_DIS();
	return 0;  
}
