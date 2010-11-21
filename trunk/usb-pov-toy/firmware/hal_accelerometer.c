#include "globals.h"



u8 hal_acl_read(u8 r)
{
u8 c;

ACL_CS=0;
hal_spi_rw((r<<1));
c=hal_spi_rw(0xff);
ACL_CS=1;
}



void hal_acl_enable(void){
ACL_CS=0;
hal_spi_rw((0x16<<1)|0b10000000);//write setup
hal_spi_rw(0b0001);//low g, measurement
ACL_CS=1;
}


void hal_acl_config(void)
{
//TODO
}


HAL_ACL_DIRECTION hal_acl_IsItReverseOrForward(void)
{
//TODO
return ACL_REVERSE;
//return ACL_FORWARD;
}

void hal_acl_adjustInterruptLvl(u8 value)
{
// TODO
}

