/*
*
*	Dangerous Prototypes Flash Destroyer firmware
*	License: creative commons - attribution, share-alike
* 	http://creativecommons.org/licenses/by-sa/2.0/
*	Copyright 2010
*	http://dangerousprototypes.com
*
*/
#ifndef HAL_INTERNALEEPROM_H_
#define HAL_INTERNALEEPROM_H_

#define INT_EEP_MSB	0
#define INT_EEP_LSB INT_EEP_MSB+3

#define INT_EEP_CRC	INT_EEP_MSB+4

void hal_InternalEEPROM_Write(u32 Number);
u32 hal_InternalEEPROM_Read(void);
void hal_InternalEEPROM_Erase(void);

#endif /* HAL_INTERNALEEPROM_H_ */
///////////////////////
