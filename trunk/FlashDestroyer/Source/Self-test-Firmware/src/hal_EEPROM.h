/*
*
*	Dangerous Prototypes Flash Destroyer firmware
*	License: creative commons - attribution, share-alike
* 	http://creativecommons.org/licenses/by-sa/2.0/
*	Copyright 2010
*	http://dangerousprototypes.com
*/
#ifndef HAL_EEPROM_H_
#define HAL_EEPROM_H_

#define EEP_DEV_ADD				0xA0
#define EEP_DESTROYER_DATA		0xAA
#define EEP_PAGES_TO_WRITE		16  // if 1, 0x00 to 0x07... if 2 0x08 to 0x0F.....
#define EEP_PAGES_TO_READ		EEP_PAGES_TO_WRITE
#define EEP_BYTES_PER_PAGE		8

#if EEP_PAGES_TO_WRITE>32
	#error Must not be greater than 32!
#endif

#define EEP_I2C_SSPADD_VAL	55 // 54.5555555556 = 90khz

#define ERROR_I2C		10

void hal_EEPROM_Init(void);
u8 hal_EEPROM_DestroyWrite(void);
u8 hal_EEPROM_DestroyReadAndVerify(void);

#endif /* HAL_EEPROM_H_ */


//////////////////
