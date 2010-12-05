#include "globals.h"

#define CS_PIN LATCbits.LATC0

#define DO_0	LATAbits.LATA0
#define DO_1	LATAbits.LATA1
#define DO_2	LATAbits.LATA2
#define DO_3	LATAbits.LATA3

#define DI_0	PORTBbits.RB0
#define DI_1	PORTBbits.RB1
#define DI_2	PORTBbits.RB2
#define DI_3	PORTBbits.RB3

#define CS_0	LATAbits.LATA5
#define CS_1	LATCbits.LATC1
#define CS_2	LATCbits.LATC2
#define CS_3	LATBbits.LATB4

#define SCLK	LATCbits.LATC7



#define set_CS0(x) CS_0=x;
#define set_CS1(x) CS_1=x;
#define set_CS2(x) CS_2=x;
#define set_CS3(x) CS_3=x;

#define set_all_cs(x) 	CS_0=x;CS_1=x;CS_2=x;CS_3=x;


#define MY_SPI_MACRO(OUT,IN)   	OUT=0; \
	if((c>>ctr)&0x01)  		\
		OUT=1;  			\
	SCLK=ON;  				\
	if(IN)  				\
		res|=(1<<ctr); 		\
	SCLK=OFF;

//	DO_0=0;
//	if((c>>ctr)&0x01)
//		DO_0=1;
//	SCLK=ON;
//	if(DI_0)
//		res|=(1<<ctr);
//	SCLK=OFF;

u8 spi_rw_0(u8 c)
{
static int ctr;
static u8 res=0;

for(ctr=0;ctr<8;ctr++)
	{
	MY_SPI_MACRO(DO_0,DI_0)
	}
}


u8 spi_rw_1(u8 c)
{
static int ctr;
static u8 res=0;

for(ctr=0;ctr<8;ctr++)
	{
	MY_SPI_MACRO(DO_1,DI_1)
	}
}


u8 spi_rw_2(u8 c)
{
static int ctr;
static u8 res=0;

for(ctr=0;ctr<8;ctr++)
	{
	MY_SPI_MACRO(DO_2,DI_2)
	}
}

u8 spi_rw_3(u8 c)
{
static int ctr;
static u8 res=0;

for(ctr=0;ctr<8;ctr++)
	{
	MY_SPI_MACRO(DO_3,DI_3)
	}
}



void spi_init(void)
{
set_all_cs(ON);
//OpenSPI(SPI_FOSC_4,MODE_01,SMPMID);
//SSPCON1 |= SPI_FOSC_64;
}

////read-write
//u8 spi_rw(u8 c)
//{
//SSP2BUF=c;
//while(SSP2STATbits.BF==0);
//c=SSP2BUF;
//return c;
//}

//typedef enum
//{
//SPI_0=0,
//SPI_1,
//SPI_2,
//SPI_3,
//}SPI_GROUP;


void hal_sram_init(SPI_GROUP s)
{
switch(s)
	{
	case SPI_0:
		break;
	case SPI_1:
		break;
	case SPI_2:
		break;
	case SPI_3:
		break;
	default:
		break;
	}
}


#if 0
void hal_sram_init()
{

u8 temp;

spi_init();

//SPI>[0x01 0b01000001]
///CS ENABLED
//WRITE: 0x01<<<config update command
//WRITE: 0x41<<<Config register value
///CS DISABLED
//SPI>

cs_low();
spi_rw(0x01);
spi_rw(0x41);
cs_high();

//3WIRE>[5 r]
///CS ENABLED
//WRITE: 0x05
//READ: 0x41
///CS DISABLED
//3WIRE>

cs_low();
spi_rw(0x05);
temp=spi_rw(0xFF);
cs_high();

// FOR DEBUGGING PURPOSE ONLY!!
if(temp!=0x41)
	{
	while(1){CS_PIN^=1;} // toggle indefinitely
	}

}
#endif

//Read data
//
//3WIRE>[0x03 0 0 r:9]
///CS ENABLED
//WRITE: 0x03<<<read command
//WRITE: 0x00<<<address H
//WRITE: 0x00<<<address L
//READ: 0x05 0x06 0x07 0x08 0x09 0x0A 0x0B 0x0C 0x0D <<<data
///CS DISABLED
//3WIRE>
#if 0
void hal_sram_read(u8 AddrHi,u8 AddrLo,int DataCount, u8 *DataArray)
{

static int ctr;
cs_low();
spi_rw(0x03);
spi_rw(AddrHi);
spi_rw(AddrLo);
for(ctr=0;ctr<DataCount;ctr++)
	{
	DataArray[ctr]=spi_rw(0xFF);
	}
cs_high();

}
#endif


//Write data
//3WIRE>[0x02 0 0 5 6 7 8 9 10 11 12 13]
///CS ENABLED
//WRITE: 0x02<<<write command
//WRITE: 0x00<<<address H
//WRITE: 0x00<<<address L
//WRITE: 0x05<<<data to write
//WRITE: 0x06
//WRITE: 0x07
//WRITE: 0x08
//WRITE: 0x09
//WRITE: 0x0A
//WRITE: 0x0B
//WRITE: 0x0C
//WRITE: 0x0D
///CS DISABLED
//3WIRE>
#if 0
void hal_sram_write(u8 AddrHi,u8 AddrLo,int DataCount, u8 *DataArray)
{

static int ctr;
cs_low();
spi_rw(0x02);
spi_rw(AddrHi);
spi_rw(AddrLo);
for(ctr=0;ctr<DataCount;ctr++)
	{
	spi_rw(DataArray[ctr]);
	}
cs_high();

}
#endif


////////////////////////


