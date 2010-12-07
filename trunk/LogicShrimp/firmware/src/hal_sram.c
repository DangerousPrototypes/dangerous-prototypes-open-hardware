#include "globals.h"

#define CS_PIN 	LATCbits.LATC0

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


////////////// CHIP SELECT FUNCTIONS ////////////////////
#define set_all_cs(x) 	CS_0=x;CS_1=x;CS_2=x;CS_3=x;

#define SET_CS0_FUNC(x) void set_CS ## x (u8 state){CS_ ## x   =state;}

// create functions for Chip Selects
SET_CS0_FUNC(0)
SET_CS0_FUNC(1)
SET_CS0_FUNC(2)
SET_CS0_FUNC(3)

// Static! Not Exposed Outside
static void (*SetCS[])(u8 state)={set_CS0,set_CS1,set_CS2,set_CS3};
/////////////////////////////////////////////////////////





///////////////// SPI R/W Functions //////////////////////
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
int ctr;
u8 res=0;

for(ctr=0;ctr<8;ctr++)
	{
	MY_SPI_MACRO(DO_0,DI_0)
	}
}


u8 spi_rw_1(u8 c)
{
int ctr;
u8 res=0;

for(ctr=0;ctr<8;ctr++)
	{
	MY_SPI_MACRO(DO_1,DI_1)
	}
}


u8 spi_rw_2(u8 c)
{
int ctr;
u8 res=0;

for(ctr=0;ctr<8;ctr++)
	{
	MY_SPI_MACRO(DO_2,DI_2)
	}
}


u8 spi_rw_3(u8 c)
{
int ctr;
u8 res=0;

for(ctr=0;ctr<8;ctr++)
	{
	MY_SPI_MACRO(DO_3,DI_3)
	}
}


// Static! Not Exposed Outside
static u8 (*SpiRWPtr[])(u8 c)={spi_rw_0,spi_rw_1,spi_rw_2,spi_rw_3};
////////////////////////////////////////////////////////////////////////////








//////////////////////////////// EXPOSED FUNCTIONS /////////////////////////
void hal_spi_init(void)
{
// set Tristate Port and Logic Level

// Data Out
TRISA&=0xF0;

// Data In
TRISB|=0x0F;

// Chip Select
TRISAbits.TRISA5=0;
TRISCbits.TRISC1=0;
TRISCbits.TRISC2=0;
TRISBbits.TRISB4=0;

// Clock
TRISCbits.TRISC0=0;

SCLK=OFF;
set_all_cs(ON);
}




void hal_sram_init(SPI_GROUP s)
{
#define DEBUG_SRAM_INIT // uncomment this line to abort test

#ifdef DEBUG_SRAM_INIT
u8 temp;
#endif

hal_spi_init();

//SPI>[0x01 0b01000001]
///CS ENABLED
//WRITE: 0x01<<<config update command
//WRITE: 0x41<<<Config register value
///CS DISABLED
//SPI>
SetCS[s](OFF); // cs low
SpiRWPtr[s](0x01);
SpiRWPtr[s](0x41);
SetCS[s](ON); // cs high


//3WIRE>[5 r]
///CS ENABLED
//WRITE: 0x05
//READ: 0x41
///CS DISABLED
//3WIRE>
SetCS[s](OFF); // cs low
SpiRWPtr[s](0x05);
temp=SpiRWPtr[s](0xFF);
SetCS[s](ON); // cs high

#ifdef DEBUG_SRAM_INIT
// FOR DEBUGGING PURPOSE ONLY!!
if(temp!=0x41)
	{
	while(1){CS_PIN^=1;} // toggle indefinitely
	}
#endif

#undef DEBUG_SRAM_INIT
}




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
void hal_sram_read(SPI_GROUP s,u8 AddrHi,u8 AddrLo,int DataCount, u8 *DataArray)
{
static int ctr;
SetCS[s](OFF); // cs low
SpiRWPtr[s](0x03);
SpiRWPtr[s](AddrHi);
SpiRWPtr[s](AddrLo);
for(ctr=0;ctr<DataCount;ctr++)
	{
	DataArray[ctr]=SpiRWPtr[s](0xFF);
	}
SetCS[s](ON); // cs high
}





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
void hal_sram_write(SPI_GROUP s,u8 AddrHi,u8 AddrLo,int DataCount, u8 *DataArray)
{
static int ctr;
SetCS[s](OFF); // cs low
SpiRWPtr[s](0x02);
SpiRWPtr[s](AddrHi);
SpiRWPtr[s](AddrLo);
for(ctr=0;ctr<DataCount;ctr++)
	{
	SpiRWPtr[s](DataArray[ctr]);
	}
SetCS[s](ON); // cs high
}


////////////////////////


