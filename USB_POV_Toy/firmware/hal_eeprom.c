#include "globals.h"

void hal_eeprom_wren(void)
{
	EEPROM_CS = 0;

	SSP2BUF=EEPROM_WREN;
	while(SSP2STATbits.BF==0);

	EEPROM_CS = 1;
}

void hal_eeprom_write(u16 add,u8 dat)
{
	u8 high = add >> 8;
	u8 low = add & 0x00FF;

	EEPROM_CS = 0;

	SSP2BUF=EEPROM_WRITE;
	while(SSP2STATbits.BF==0);

	SSP2BUF=high;
	while(SSP2STATbits.BF==0);

	SSP2BUF=low;
	while(SSP2STATbits.BF==0);
	
	SSP2BUF=dat;
	while(SSP2STATbits.BF==0);

	EEPROM_CS = 1;
}

u8 hal_eeprom_read(u16 add)
{
	u8 high = add >> 8;
	u8 low = add & 0x00FF;

	EEPROM_CS = 0;

	SSP2BUF=EEPROM_READ;
	while(SSP2STATbits.BF==0);

	SSP2BUF=high;
	while(SSP2STATbits.BF==0);

	SSP2BUF=low;
	while(SSP2STATbits.BF==0);
	
	SSP2BUF=DUMMY;
	while(SSP2STATbits.BF==0);

	EEPROM_CS = 1;

	return SSP2BUF;
}

u8 hal_eeprom_rdsr(void)
{
	EEPROM_CS = 0;

	SSP2BUF=EEPROM_RDSR;
	while(SSP2STATbits.BF==0);
	
	SSP2BUF=DUMMY;
	while(SSP2STATbits.BF==0);

	EEPROM_CS = 1;

	return SSP2BUF;
}

void hal_eeprom_wip_poll(void)
{	
	u8 status = 0;

	do {
        status = hal_eeprom_rdsr();  
    } while(status & 0x01); 

}