#include "globals.h"



u8 hal_Acl_Read(u8 r)
{
u8 c;

ACL_CS=0;
hal_spi_rw((r<<1));
c=hal_spi_rw(0xff);
ACL_CS=1;
}



void hal_Acl_Enable(void){
ACL_CS=0;
hal_spi_rw((0x16<<1)|0b10000000);//write setup
hal_spi_rw(0b0001);//low g, measurement
ACL_CS=1;
}


void hal_Acl_Config(void)
{
//TODO
}


HAL_ACL_DIRECTION hal_Acl_IsItReverseOrForward(void)
{
//TODO
return ACL_REVERSE;
//return ACL_FORWARD;
}
