/*
*
*	Dangerous Prototypes Flash Destroyer firmware
*	License: creative commons - attribution, share-alike
* 	http://creativecommons.org/licenses/by-sa/2.0/
*	Copyright 2010
*	http://dangerousprototypes.com
*/
//Note: Hardware Abstaction Layer For I2C EEPROM

#include "globals.h"

static u8 EepDataToWrite;
u8 i2c_write(u8 data);
u8 i2c_read(u8 nack);
void i2c_start(void);
void i2c_stop(void);

//setup the hardware I2C module and pins
void hal_EEPROM_Init(void)
{
	u8 delay, i;

	TRISB|=0b11; //set SDA SCL pins to 1 (input)
	LATBbits.LATB1=0; //set clock to ground so we can manipulate it

	//clear out any bad stuff on the I2C bus
	for(i=0; i<20; i++){
		//send 20 clock ticks with data high, NACKs any hanging chips
		TRISBbits.TRISB1=0;
		delay=0xff;
		do{delay--;}while(delay!=0);//delay
		TRISBbits.TRISB1=1;
		delay=0xff;
		do{delay--;}while(delay!=0);//delay
	}

	SSPADD=EEP_I2C_SSPADD_VAL;
	SSPSTAT &= 0x3F; 
	SSPCON1 = 0x00;                
	SSPCON2 = 0x00;                
	SSPCON1 |= 0b1000;    	//1000 = I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))(2)
	SSPSTAT |= 0b10000000;// slew 
	SSPCON1 |= 0b100000; //enable

	//now send I2C STOP bit with hardware to finish clearing the bus
	i2c_stop();

	//load the initial value to write to the EEPROM
	EepDataToWrite=EEP_DESTROYER_DATA;
}

//send I2C start bit
void i2c_start(void)
{
	#define SEN 0b1
	SSPCON2|=SEN;
	while(SSPCON2&SEN);
}

//send I2C stop bit
void i2c_stop(void)
{
	#define PEN 0b100
	SSPCON2|=PEN;//stop
	while(SSPCON2&PEN);
}

//send 1 byte by I2C
//returns ACK (TRUE) or NACK (FALSE)
u8 i2c_write(u8 data)
{
PIR1bits.SSPIF=0;
SSPBUF=data;
while(PIR1bits.SSPIF==0);
if(SSPCON2bits.ACKSTAT==1)
	{
	return FALSE;
	}
return TRUE;
}

//read one byte from I2C
// send 0/1 for ack
u8 i2c_read(u8 nack){
PIR1bits.SSPIF=0;

SSPCON2bits.RCEN=1;
while(PIR1bits.SSPIF==0);

if(nack)
	{
	SSPCON2bits.ACKDT=0;
	}
else
	{
	SSPCON2bits.ACKDT=1;
	}
SSPCON2bits.ACKEN=1;
while(SSPCON2bits.ACKEN==1);

return SSPBUF;
}

//writes data to the entire EEPROM
//returns TRUE on success, ERROR_I2C on bus errors such as timeout or no ACK
u8 hal_EEPROM_DestroyWrite(void )
{
u8 ctr, pages, a;
u16 u16timeout;

EepDataToWrite=~EepDataToWrite; // Alternating every run 0xAA,0x55,0xAA,0x55.. so on so forth
	
for(pages=0; pages<EEP_PAGES_TO_WRITE; pages++)//for X pages
	{
	i2c_start();
	if(i2c_write(EEP_DEV_ADD)==FALSE)goto I2C_BUS_ERROR;//while(1);//address
	if(i2c_write(pages*8)==FALSE)goto I2C_BUS_ERROR;//while(1);//write location

	for(ctr=0;ctr<EEP_BYTES_PER_PAGE;ctr++)//for page bytes
		{
		if(i2c_write(EepDataToWrite)==FALSE)goto I2C_BUS_ERROR;//while(1);//I2C send data
		}
	i2c_stop();

	u16timeout=0xFFF; // TODO : adjust this
	while(u16timeout!=0)
		{
		i2c_start();
		a=i2c_write(EEP_DEV_ADD);
		i2c_stop();
		if(a==TRUE)	break;//poll for ACK
		}
	if(u16timeout==0) goto I2C_BUS_ERROR;
	}

return TRUE;

I2C_BUS_ERROR:
i2c_stop();
return ERROR_I2C;
}

//Read the EEPROM and verify that the values match what we wrote
//returns TRUE if values match, FALSE if values differ, ERROR_I2C on bus errors
u8 hal_EEPROM_DestroyReadAndVerify(void )
{
u8 pages, ctr;

//first setup the address pointer to 0x00
i2c_start();
if(i2c_write(EEP_DEV_ADD)==FALSE) goto I2C_BUS_ERROR; //while(1);//address
if(i2c_write(0x00)==FALSE) goto I2C_BUS_ERROR; //while(1);//write location
i2c_stop();

//now start reading from the read address
i2c_start();
if(i2c_write(EEP_DEV_ADD|0x01)==FALSE)goto I2C_BUS_ERROR;//while(1);//address

for(pages=0; pages<EEP_PAGES_TO_WRITE; pages++)//for X pages
	{
	for(ctr=0;ctr<EEP_BYTES_PER_PAGE;ctr++)//for page bytes
		{
		if(i2c_read(TRUE)!=EepDataToWrite) //read and ack it
			{
			i2c_read(FALSE); //NACK it so we don't leave the chip hanging
			i2c_stop();
			return FALSE;
			}
		}
	}

	i2c_read(FALSE); //send a NACK to clear up the chip
	i2c_stop();
	return TRUE;

I2C_BUS_ERROR:
	i2c_read(FALSE); //send a NACK to clear up the chip
	i2c_stop();
	return ERROR_I2C;
}
/////////

