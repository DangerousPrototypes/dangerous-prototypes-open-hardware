/* header  */
#ifndef EEPROM_H
#define EEPROM_H


void EEPROMwrite (unsigned char addr, unsigned char data);
unsigned char EEPROMread(unsigned char addr);

#endif
