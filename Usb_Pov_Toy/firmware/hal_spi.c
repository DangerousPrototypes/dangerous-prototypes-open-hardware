#include "globals.h"

void hal_spi_init(void)
{
//TODO
}

//read-write
u8 hal_spi_rw(u8 c)
{
SSP2BUF=c;
while(SSP2STATbits.BF==0);
c=SSP2BUF;
return c;
}
