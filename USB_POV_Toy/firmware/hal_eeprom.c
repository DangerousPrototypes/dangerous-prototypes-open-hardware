#include "globals.h"

void hal_eeprom_wren(void)
{
	EEPROM_CS = 0;
	hal_spi_rw(EEPROM_WREN);
	EEPROM_CS = 1;
}

void hal_eeprom_write(u16 add,u8 dat)
{
	u8 high = add >> 8;
	u8 low = add & 0x00FF;

	EEPROM_CS = 0;
	hal_spi_rw(EEPROM_WRITE);
	hal_spi_rw(high);
	hal_spi_rw(low);
	hal_spi_rw(dat);
	EEPROM_CS = 1;
}

u8 hal_eeprom_read(u16 add)
{
	u8 c;
	u8 high = add >> 8;
	u8 low = add & 0x00FF;

	EEPROM_CS = 0;
	hal_spi_rw(EEPROM_READ);
	hal_spi_rw(high);
	hal_spi_rw(low);
	c = hal_spi_rw(DUMMY);
	EEPROM_CS = 1;

	return c;
}

u8 hal_eeprom_rdsr(void)
{
	u8 c;
	
	EEPROM_CS = 0;
	hal_spi_rw(EEPROM_RDSR);
	c = hal_spi_rw(DUMMY);
	EEPROM_CS = 1;

	return c;
}

void hal_eeprom_wip_poll(void)
{	
	u8 status = 0;

	do {
        status = hal_eeprom_rdsr();  
    } while(status & 0x01); 

}