#ifndef HAL_EEPROM_H
#define HAL_EEPROM_H

#define EEPROM_CS LATCbits.LATC7
#define EEPROM_READ 0b00000011
#define EEPROM_WRITE 0b00000010
#define EEPROM_WRDI 0b00000100
#define EEPROM_WREN 0b00000110
#define EEPROM_RDSR 0b00000101
#define EEPROM_WRSR 0b00000001
#define DUMMY		0xFF

void hal_eeprom_wren(void);
void hal_eeprom_write(u16,u8);
u8 hal_eeprom_read(u16);
void hal_eeprom_wip_poll(void);

#endif