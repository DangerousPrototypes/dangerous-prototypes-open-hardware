/* header */

#include <pic.h>
#include "./spi.h"
#include "./eeprom.h"
#include "./pwm.h"
#include "./dac.h"
#include "./adc.h"

void initSPI(void)
{
   // setup SPI slave
	 TRISCbits.TRISC1 = 0;
    SSP2STAT=0x40;      // !smp, cke
    SSP2CON1=0x24;      // SSP1EN, !CKP, SSPM5 (SPI slave, cc enabled)
    SSP2CON3=0x00;      // !BOEN
	
    SSP2BUF=0xAA;       // intial byte te send to master

}

void SPIworker(void)
{
	unsigned char temp;
	initSPI();
    while(1)
    {
        if(SSP2STATbits.BF)	// we received something :)
        {
            temp=SSP2BUF;
            SSP2BUF=temp;   //echo back
        }
    }
}

//25AA020A emulator 256BYTE SPI EEPROM
void SPIEEworker(void)
{
	unsigned char token, instruction, fInst=0,addr=0,addressed =0,STATUS=0,fb=0,fb2=0,bf=0;
	unsigned char i,pageIndex=0,WREN=0,WIP=0,w=0;
	initSPI();
	SSP2BUF = 0xFD;
   while (1)
	{
		while(PORTCbits.RC0 ==0)
 	  	{
  	 		if(SSP2STATbits.BF)	// we received something :)
			{
				bf=1;
      		if(fb==0)
				{
					token = SSP2BUF;
					instruction = token & SPIEEMASK;
				}
				fb=1;
				switch(instruction)
				{
					case SPI_READ:
						if(fInst)
						{
							if(addressed==0)
							{
								addr = SSP2BUF;
								addressed =1;
								SSP2BUF = eeBuf[addr++];
							}
							else
							{
								SSP2BUF = eeBuf[addr++];
							}
						}
						else
						{
							fInst=1;
							SSP2BUF = STATUS;
						}
						break;
					case SPI_WRITE:
						if(WREN)
						{
							if(fInst)
							{
								if(addressed)
								{
									if(STATUS > 11);
									else if(STATUS >7)
									{
										if(addr<0x80)
											{
												eeBuf[addr++]=SSP2BUF;
												STATUS|=1;	//write in progress
												w++;
											}
									}
									else if(STATUS > 3)
									{
										if(addr<0xC0)
										{
											eeBuf[addr++]=SSP2BUF;
											STATUS|=1;	//write in progress
											w++;
										}
									}
									else
									{
										eeBuf[addr++]=SSP2BUF;
										w++;
										STATUS|=1;	//write in progress
									}
								}
								else
								{
									addr = SSP2BUF;
									addressed =1;
								}
							}
							else
							{
								fInst=1;
							}
						}
						SSP2BUF = STATUS;
						break;
					case SPI_WRDI:
						WREN=0;
						STATUS&=~(1<<1);
						break;
					case SPI_WREN:
						WREN =1;
						STATUS|=1<<1;
						SSP2BUF = STATUS;
						break;
					case SPI_RDSR:
						SSP2BUF = STATUS;
						break;
					case SPI_WRSR:
						if(fInst)STATUS = SSP2BUF;
						fInst=1;
						break;
				}	
			}			
		}
		if(bf)
		{
			addressed=0;
			if (token == SPI_WRITE)
			{
				WREN =0;
				STATUS&=0b11111100;
			}
			if(w>0)
			{
				for(i=addr-w;i<addr;i++)EEPROMwrite(i,eeBuf[i]);
			}
			w=0;
			fb=0;
			fInst=0;
			bf=0;
		}
	}
}


void SPIPWMworker(void)
{
	unsigned char token, instruction, fInst=0,fb=0,bf=0;
	initSPI();
	SSP2BUF = 0xFD;
	enablePWM();
   while (1)
	{
		while(PORTCbits.RC0 ==0)//CS LOW
 	  	{
  	 		if(SSP2STATbits.BF)	// we received something :)
			{
				bf=1;
      		if(fb==0)
				{
					token = SSP2BUF;
					instruction = token & SPIEEMASK;
				}
				fb=1;
				switch (instruction)
				{
					case 0:
						if(fInst)
						{
							if(fInst==1)setPeriod(SSP2BUF);
							fInst++;
						}
						else
						{
							fInst=1;
						}
						SSP2BUF = PWMperiod;
						break;
					case 1:
						if(fInst)
						{
							if(fInst==1)setDuty(SSP2BUF);
							fInst++;
						}
						else
						{
							fInst=1;
						}
						SSP2BUF = PWMduty;
						break;
				}
			}
		}
		if(bf)	//CS HIGH
		{
			fb=0;
			bf=0;
			fInst = 0;
		}	
	}

}

//MCP4801 SPI DAC..
void SPIDACworker(void)
{
	unsigned char token, instruction, fInst=0,fb=0,bf=0;
	initSPI();
	SSP2BUF = 0xFD;
	enableDAC();
	//DACOE =0;
   while (1)
	{
		while(PORTCbits.RC0 ==0)//CS LOW
 	  	{
  	 		if(SSP2STATbits.BF)	// we received something :)
			{
				bf=1;
				if(fb)
					{
						setDAC(SSP2BUF);
					}
				else
				{
					fb=1;
					if(SSP2BUF&0b00010000)DACOE =1;//DAC on
					else DACOE =0;					//DACoff
				}
				SSP2BUF = DACCON1&0x1F;
			}
		}
		if(bf)	//CS HIGH
		{
			fb=0;
			bf=0;
		}
	}	

}

//MCP3004 4-chanell SPI 10bit ADC...(only 8bits used) 
void SPIADCworker(void)
{
	unsigned char token, instruction, chanel, fInst=0,fb=0,bf=0;
	initSPI();
	SSP2BUF = 0xFD;
	enableTS;
	while (1)
	{
		while(PORTCbits.RC0 ==0)//CS LOW
 	  	{
  	 		if(SSP2STATbits.BF)	// we received something :)
			{
				SSP2STATbits.BF=0;
				bf=1;
				if(fb==0)
					{
					if(SSP2BUF==1)fb=1;
					SSP2BUF=0;	
					}
				else if(fb==1)
				{
					chanel = SSP2BUF &0b00110000;
					chanel = chanel>>4;
					SSP2BUF = getADC(chanel);
				}
			
			}
		}
		if(bf)	//CS HIGH
		{
			fb=0;
			bf=0;
		}
	}	
}