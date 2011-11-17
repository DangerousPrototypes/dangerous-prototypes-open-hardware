/* header */



#include <pic.h>
#include "./hardware.h"
#include "./i2c.h"

#include "./eeprom.h"
#include "./adc.h"
#include "./dac.h"

// init the i2c hardware 
void initI2C(void)
{
	
    // init I2C slave, 7bit address, 100KHz
    SSP2BUF=0x00;           // clear buffer
    SSP2STAT=0x80;          // 100KHZ
    SSP2MSK=I2CADDMASK;     // and mask; this will allow multiple instances
    SSP2CON1=0x36;           // SSP1EN|!clockstretching|7bit mode /w int
    SSP2CON3|=0b11000000;
}


// main loop + statemachine
// EEPROM
void I2CEEworker(void)
{	unsigned char token, addr, temp, addressed;

	addr=0x00;
	addressed=0;

    SSP2ADD=I2CADDEE;		// Set slave addres

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
                        if(!addressed) 
						{	addr=SSP2BUF;
							addressed=1;
						}
						else
						{
							EEPROMwrite(addr, SSP2BUF);
							addr++;
						}

                        break;
                    case MRA:               // master read addres
                        temp=SSP2BUF;
						I2CWrite(EEPROMread(addr++));
                        break;
                    case MRD:               // master read data
                        temp=SSP2BUF;
						I2CWrite(EEPROMread(addr++));
                        break;
                }
            }
            else if(SSP2STATbits.P)			// STOP condition
            {	LED1OFF;
				addressed=0;
                asm("NOP");
            }
            SSP2IF=0;
            SSP2CON1bits.SSPEN=1;
            SSP2CON1bits.CKP=1;				//release SCL line
        }
    }
}

// main loop + statemachine
// ADC
void I2CADCworker(void)
{	unsigned char token, temp, adc;

	adc=0x00;
	enableTS();
    SSP2ADD=I2CADDADC;		// Set slave addres

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
						adc=SSP2BUF;
                        break;
                    case MRA:               // master read addres
                        temp=SSP2BUF;
						I2CWrite(getADC(adc));
                        break;
                    case MRD:               // master read data
                        temp=SSP2BUF;
						I2CWrite(getADC(adc));
                        break;
                }
            }
            else if(SSP2STATbits.P)			// STOP condition
            {	LED1OFF;
                asm("NOP");
            }
            SSP2IF=0;
            SSP2CON1bits.SSPEN=1;
            SSP2CON1bits.CKP=1;				//release SCL line
        }
    }
}

// mainloop+statemachine
// dac
void I2CDACworker(void)
{	unsigned char token, temp, dac;

	dac=0x00;
	enableDAC();
    SSP2ADD=I2CADDDAC;		// Set slave addres

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
						dac=SSP2BUF;
						dac>>=3;			// we only got 5 bits of precission
						setDAC(dac);
                        break;
                    case MRA:               // master read addres
                        temp=SSP2BUF;
						I2CWrite(getADC(dac));
                        break;
                    case MRD:               // master read data
                        temp=SSP2BUF;
						I2CWrite(getADC(dac));
                        break;
                }
            }
            else if(SSP2STATbits.P)			// STOP condition
            {	LED1OFF;
                asm("NOP");
            }
            SSP2IF=0;
            SSP2CON1bits.SSPEN=1;
            SSP2CON1bits.CKP=1;				//release SCL line
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
    SSP2CON1bits.CKP=1;						// release SCL line
}
