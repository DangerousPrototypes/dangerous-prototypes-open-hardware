/* header */

#include <pic.h>
#include "./spi.h"

void initSPI(void)
{
   // setup SPI slave
    SSP2STAT=0x40;      // !smp, cke
    SSP2CON1=0x24;      // SSP1EN, !CKP, SSPM5 (SPI slave, cc enabled)
    SSP2CON3=0x00;      // !BOEN

    SSP2BUF=0xAA;       // intial byte te send to master

}

void SPIworker(void)
{
	unsigned char temp;

    while(1)
    {
        if(SSP2STATbits.BF)	// we received something :)
        {
            temp=SSP2BUF;
            SSP2BUF=temp;   //echo back
        }
    }
}
