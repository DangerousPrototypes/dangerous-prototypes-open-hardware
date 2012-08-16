/* header */



#include <pic.h>
#include "./hardware.h"
#include "./i2c.h"

#include "./eeprom.h"
#include "./adc.h"
#include "./dac.h"
#include "./pwm.h"

void initI2C(void)
{  
    // init I2C slave, 7bit address, 100KHz
   
    SSP2BUF=0x00;           // clear buffer
    SSP2STAT=0x80;          // 100KHZ
    SSP2MSK=I2CADDMASK;     // and mask; this will allow multiple instances
    SSP2CON1=0x36;           // SSP1EN|!clockstretching|7bit mode /w int
    SSP2CON3|=0b11000000;		//ACK on, STOP interupt on
}


// main loop + statemachine
// EEPROM
void I2CEEworker(void)
{   
	unsigned char token,i, addr=0, temp=0, addressed=0,w=0;
 
 
   SSP2ADD=I2CADDEE;      // Set slave addres
   SSP2CON1bits.SSPEN=1;
   while(1)
   {
		//i2c state machine
      if(SSP2IF)			//waiting for interrupt (MWA,MWD,MRA,MRD, stop) no Start
      {   
      	SSP2IF=0;		//clearing the interrupt
			token=SSP2STAT&I2CSTATMASK;
         if(SSP2STATbits.S)            // start condition
         {   
         	LED1ON;
            switch(token)
            {
            	case MWA:               // master write address
               	temp=SSP2BUF;      // clears te BF flag
                  break;
               case MWD:               // master write data
               	if(!addressed)			//check if first byte
                  {   
                  	addr=SSP2BUF;		//recived data is moved to the EE address pointer
                     addressed=1;		//flags that addres has been stored
                  }
                  else
                  {	//if this is the second byte writes data to buffer
                  	eeBuf[addr++]=SSP2BUF;	
							w++;	//counts the number of bytes stored in the buffer
                  }
                  break;
					case MRA:               // master read addres
                  temp=SSP2BUF;			//clears the BF flag
						SSP2BUF = eeBuf[addr++];	//sets up the first byte for transmision
                  break;
					case MRD:              // master read data
						temp=SSP2BUF;			//clears the BF flag,
						//adds new data to the buffer if ACD recived on previus transmision
						if(SSP2CON2bits.ACKSTAT==0)SSP2BUF=eeBuf[addr++];	//subsequent transmision
						break;
				}
			}
         else if(SSP2STATbits.P)         // STOP condition
         {   
				LED1OFF;
            addressed=0;	//clears the first byte write flag
				if(w>0)			//if data was writen to the buffer
				{					//moves that data to the EEPROM
					for(i=addr-w;i<addr-1;i++)
					{
						EEPROMwrite(i,eeBuf[i]);
					}
				}
				w=0;	
	         asm("NOP");
			}
         SSP2CON1bits.CKP=1;            //release SCL line
		}
	}
}

//MCP3428
//http://ww1.microchip.com/downloads/en/DeviceDoc/22226a.pdf
//general call unsuporrted
// main loop + statemachine
// ADC
void I2CADCworker(void)
{	unsigned char token, temp, adc,config=0,adcON=0,fb=0;

	adc=0x00;
	enableTS();
    SSP2ADD=0x68;//I2CADDADC;		// Set slave addres

    while(1)
    {
        //i2c state machine
        if(SSP2IF)
        {
            token=SSP2STAT&I2CSTATMASK;

            if(SSP2STATbits.S)				// start condition
            {	LED1ON;
                switch(token)
                {
                    case MWA:               // master write address
                        temp=SSP2BUF;		// temp holds I2Caddress
                        break;
                    case MWD:               // master write data
								config=SSP2BUF;
                        break;
                    case MRA:               // master read addres
                        temp=SSP2BUF;
								I2CWrite(ADRESH);
                        break;
                    case MRD:               // master read data
								temp=SSP2BUF;
								if(fb==0)
								{
									fb=1;
									I2CWrite(ADRESL);
								}
								else 
								{
									I2CWrite(config&(ADCON0bits.ADGO<<7));
								}
                        break;
                }
            }
            else if(SSP2STATbits.P)			// STOP condition
            {	
					fb=0;
					LED1OFF;
					adc=config&0b01100000;
					adc>>=5;					
					startADC16(adc);
                asm("NOP");
					//ADC setup here stuff like turn it on etccc....
            }
				
            SSP2IF=0;
				ADCON0bits.ADGO=1;
            SSP2CON1bits.SSPEN=1;
            SSP2CON1bits.CKP=1;				//release SCL line

        }
    }
}

//MCP47DA1
//http://ww1.microchip.com/downloads/en/DeviceDoc/25118C.pdf
// mainloop+statemachine
// dac
void I2CDACworker(void)
{	unsigned char token, temp, dac,command=0,fb=0;

	dac=0x00;
	enableDAC();
	//mode_device=MODEADC;
	
    SSP2ADD=0x5C;//I2CADDDAC;		// Set slave addres

    while(1)
    {
        //i2c state machine
        if(SSP2IF)
        {
            token=SSP2STAT&I2CSTATMASK;

            if(SSP2STATbits.S)				// start condition
            {	LED1ON;
                switch(token)
                {
                    case MWA:               // master write address
                        temp=SSP2BUF;		// temp holds I2Caddress
                        break;
                    case MWD:               // master write data
							if(fb=0)
							{	
								command = SSP2BUF;
								fb=1;
							}
							else
							{
								if(command ==0)
								{
									dac=SSP2BUF;
									dac>>=1;			// we only got 5 bits of precission
									setDAC(dac);
								}
								else temp=SSP2BUF;
							}
                        break;
                    case MRA:               // master read addres
                        temp=SSP2BUF;
								if(command==0)I2CWrite(dac<<1);
								else I2CWrite(0);
                        break;
                    case MRD:               // master read data
                        temp=SSP2BUF;
								if(command==0)I2CWrite(dac<<1);
								else I2CWrite(0);
                        break;
                }
            }
            else if(SSP2STATbits.P)			// STOP condition
            {	
					fb=0;
					LED1OFF;
                asm("NOP");
            }
            SSP2IF=0;
            SSP2CON1bits.SSPEN=1;
            SSP2CON1bits.CKP=1;				//release SCL line
        }
    }
}


// main I2C processing loop PWM
void I2CPWMworker(void)
{
	unsigned char token, tempP,tempD,temp, rDuty,rFreq,fD=0,fP=0,addr=0,addressed=0;
	enablePWM();
	SSP2ADD=I2CADDPWM;      // Set slave addres
   SSP2CON1bits.SSPEN=1;
	while(1)
   {
		//i2c state machine
      if(SSP2IF)			//waiting for interrupt (MWA,MWD,MRA,MRD, stop) no Start
      {   
      	SSP2IF=0;		//clearing the interrupt
			token=SSP2STAT&I2CSTATMASK;
         if(SSP2STATbits.S)            // start condition
         {   
         	LED1ON;
            switch(token)
            {
            	case MWA:               // master write address
               	temp=SSP2BUF;      // clears te BF flag
                  break;
               case MWD:               // master write data
               	if(!addressed)			//check if first byte
                  {   
                  	addr=SSP2BUF;		//recived data is moved to the EE address pointer
                     addressed=1;		//flags that addres has been stored
                  }
                  else
                  {
							if(addr==0)
							{
								tempP=SSP2BUF;
								addr=1;
								fP=1;
							}
							else
							{
								tempD=SSP2BUF;
								addr=0;
								fD=1;
							}
                  }
                  break;
					case MRA:               // master read addres
                  temp=SSP2BUF;			//clears the BF flag
						SSP2BUF = PWMperiod;
                  break;
					case MRD:              // master read data
						temp=SSP2BUF;			//clears the BF flag,
						//adds new data to the buffer if ACD recived on previus transmision
						SSP2BUF = PWMduty;
						break;
				}
			}
         else if(SSP2STATbits.P)         // STOP condition
         {   
				LED1OFF;
            addressed=0;	//clears the first byte write flag
	         asm("NOP");
				if(fP)setPeriod(tempP);
				if(fD)setDuty(tempD);
				fD=fP=0;

			}
         SSP2CON1bits.CKP=1;            //release SCL line
		}
	}
}

		

// outputs a byte on the bus and releases the clk line
void I2CWrite(unsigned char c)
{   
    do
    {
        SSP2CON1bits.WCOL=0;
        SSP2BUF=c;
    } while(SSP2CON1bits.WCOL);
    SSP2CON1bits.CKP=1;                  // release SCL line
}
