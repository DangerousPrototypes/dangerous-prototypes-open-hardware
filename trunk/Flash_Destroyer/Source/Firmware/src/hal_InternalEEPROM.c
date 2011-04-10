/*
*
*	Dangerous Prototypes Flash Destroyer firmware
*	License: creative commons - attribution, share-alike
* 	http://creativecommons.org/licenses/by-sa/2.0/
*	Copyright 2010
*	http://dangerousprototypes.com
*/
#include "globals.h"

void hal_InternalEEPROM_Erase(void)
{
u8 ctr;
for(ctr=0;ctr<10;ctr++)
	{
	Write_b_eep (ctr, 0xFF); //Erase Value
	Busy_eep (); //wait for the write to finish
	}
}


//write a 32bit number to PIC internal EEPROM
//saves a simple XOR of each byte to determine if the EEPROM is blank or valid
void hal_InternalEEPROM_Write(u32 Number)
{
u8 val, crc=0;

//write each byte of the four byte long variable that stores the eeprom write count
val=Number>>24; //high 8 first
crc^=val; //calculate the checksum (crc)
Write_b_eep (INT_EEP_MSB, val); //write the byte
Busy_eep (); //wait for the write to finish

val=Number>>16;
crc^=val;
Write_b_eep (INT_EEP_MSB+1, val);
Busy_eep ();

val=Number>>8;
crc^=val;
Write_b_eep (INT_EEP_MSB+2, val);
Busy_eep ();

val=Number;
crc^=val;
Write_b_eep (INT_EEP_MSB+3, val);
Busy_eep ();

Write_b_eep (INT_EEP_CRC, crc);//save the crc to MSB+4
Busy_eep ();
}

//reads a 32bit number from PIC internal EEPROM
//keeps a running CRC and compares to stored value
//returns 0 if CRC is incorrect (usually a blank chip)
u32 hal_InternalEEPROM_Read(void)
{
u32 RetData=0;
u32 BitShiftData;
u8 val, crc=0;

val=Read_b_eep(INT_EEP_MSB+0);//get first byte to store
crc^=val; //calculate XOR crc for this byte
RetData|=val; //add current byte to 32bit value
RetData=RetData<<8; //shift up 8 bits

val=Read_b_eep(INT_EEP_MSB+1);
crc^=val;
RetData|=val;
RetData=RetData<<8;

val=Read_b_eep(INT_EEP_MSB+2);
crc^=val;
RetData|=val;
RetData=RetData<<8;

val=Read_b_eep(INT_EEP_MSB+3);
crc^=val;
RetData|=val;

val=Read_b_eep(INT_EEP_CRC); //read the CRC
if(val!=crc) //if it doesn't match (blank chip)
	{
	RetData=0; //return 0 instead of the value
	}

return RetData;
}
///////////////////////////
