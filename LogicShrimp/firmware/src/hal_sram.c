#include "globals.h"



static u8 * hal_sram_ParallelRWByte(u8 returnData);

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
	SCLK=PORT_ON;  				\
	if(IN)  				\
		res|=(1<<ctr); 		\
	SCLK=PORT_OFF;

//	DO_0=0;
//	if((c>>ctr)&0x01)
//		DO_0=1;
//	SCLK=PORT_ON;
//	if(DI_0)
//		res|=(1<<ctr);
//	SCLK=PORT_OFF;



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




static void hal_sram_spiInit(void)
{
// set Tristate Port and Logic Level

//input buffer setup
LATBbits.LATB5=1; //buffer output, high (disabled)
TRISBbits.TRISB5=0; 

// SRAM Data Out (PIC input)
TRISA|=0b1111;

// SRAM data In (PIC output)
TRISB&=(~0b1111);

// Chip Select
set_all_cs(PORT_ON);
TRISAbits.TRISA5=0;
TRISCbits.TRISC1=0;
TRISCbits.TRISC2=0;
TRISBbits.TRISB4=0;

// Clock buffer setup
TRISCbits.TRISC0=0;//clock gate output
LATCbits.LATC0=1;//disabled

//uC clock pin setup
TRISCbits.TRISC7=0; //uC clock out to output
SCLK=PORT_OFF; //low
}
////////////////////////////////////////////////////////////////////////////











#if 0
////////// ADDRESS TRACKERS /////////////
static u16 u16SramAddressTracker[4]={0,0,0,0};


void hal_sram_TrackingAddressSetAll(u16 value)
{
u16SramAddressTracker[0]=value;
u16SramAddressTracker[1]=value;
u16SramAddressTracker[2]=value;
u16SramAddressTracker[3]=value;
}



// Reset Tracking Index
void hal_sram_TrackingAddressReset(void)
{
hal_sram_TrackingAddressSetAll(0);
}



// Set Individual Tracking Index
void hal_sram_TrackingAddressSet(SRAM_INDEX index,u16 value)
{
u16SramAddressTracker[index]=value;
}


// Increment Tracking Index
void hal_sram_TrackingAddressIncrement(SRAM_INDEX index)
{
u16SramAddressTracker[index]++;
}


// Retreive Tracking Index
u16 hal_sram_TrackingAddressGet(SRAM_INDEX index)
{
return u16SramAddressTracker[index];
}
////// END OF ADDRESS TRACKERS /////////
#endif








//////////////////////////////// EXPOSED FUNCTIONS /////////////////////////
void hal_sram_parallelInit(void)
{
#define DEBUG_SRAM_INIT // uncomment this line to abort test

#ifdef DEBUG_SRAM_INIT
u8 * ptr_array;
#endif

//setup for control and IO from uC
hal_sram_spiInit();

//SPI>[0x01 0b01000001]
///CS ENABLED
//WRITE: 0x01<<<config update command
//WRITE: 0x41<<<Config register value
///CS DISABLED
//SPI>

set_all_cs(PORT_OFF);; // cs low
hal_sram_ParallelRWByte(SRAM_CMD_WRSR);
hal_sram_ParallelRWByte(0x41);
set_all_cs(PORT_ON); // cs high

//3WIRE>[5 r]
///CS ENABLED
//WRITE: 0x05
//READ: 0x41
///CS DISABLED
//3WIRE>
set_all_cs(PORT_OFF); // cs low
hal_sram_ParallelRWByte(SRAM_CMD_RDSR);
ptr_array=hal_sram_ParallelRWByte(0xFF);
set_all_cs(PORT_ON); // cs high

#ifdef DEBUG_SRAM_INIT
// FOR DEBUGGING PURPOSE ONLY!!
if((ptr_array[0]!=0x41)||(ptr_array[1]!=0x41)||(ptr_array[2]!=0x41)||(ptr_array[3]!=0x41))
	{
	while(1){HAL_LOGICSHRIMP_LED_LAT^=1;} // toggle indefinitely
	}
#endif

#undef DEBUG_SRAM_INIT
}




//setup the SRAM to caputre input from the buffer
void hal_sram_setup_capture(void)
{
//setup the SRAM to record
set_all_cs(PORT_OFF); // cs low
hal_sram_ParallelRWByte(SRAM_CMD_WRITE);
hal_sram_ParallelRWByte(0x00);
hal_sram_ParallelRWByte(0x00);

TRISB|=0b1111;//SRAM in/PIC out pins to input/hiz

//hal_logicshrimp_BufferEnable();//open up the buffer
}



//end the SRAM to caputre
void hal_sram_end_capture(void)
{
//CS high to disable the SRAM write
set_all_cs(PORT_ON); // cs high
hal_logicshrimp_BufferDisable();//open up the buffer
}




//setup the SRAM to dump data from the SRAM
void hal_sram_setup_dump(void)
{
//setup the SRAM to record
hal_logicshrimp_BufferDisable();//open up the buffer
TRISB&=(~0b1111);//SRAM in/PIC out pins to output

set_all_cs(PORT_OFF); // cs low
hal_sram_ParallelRWByte(SRAM_CMD_READ);
hal_sram_ParallelRWByte(0x00); //address should be adjustable probably...
hal_sram_ParallelRWByte(0x00);

SRAM_DI_LAT|=0b1111; //output pins low
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
//TODO not yet done
//pass by reference on returnData... all the read will be put into returnData
//TODO: currently two dimensional array was used... once this is working, this should
//be transformed back into to single dimensional array for efficiency.
void hal_sram_parallelRead(u8 AddrHi,u8 AddrLo,u8 DataCount,u8 returnData[][4])
{
static int ctr;
static u8 *dataptr;
set_all_cs(PORT_OFF); // cs low
hal_sram_ParallelRWByte(SRAM_CMD_READ);
hal_sram_ParallelRWByte(AddrHi);
hal_sram_ParallelRWByte(AddrLo);
for(ctr=0;ctr<DataCount;ctr++)
	{
	dataptr=hal_sram_ParallelRWByte(0xFF);
	returnData[ctr][0]=dataptr[0];
	returnData[ctr][1]=dataptr[1];
	returnData[ctr][2]=dataptr[2];
	returnData[ctr][3]=dataptr[3];


	}
set_all_cs(PORT_ON); // cs high
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
void hal_sram_parallelWrite(u8 AddrHi,u8 AddrLo,int DataCount, u8 *DataArray)
{
static u16 ctr;
set_all_cs(PORT_OFF); // cs low
hal_sram_ParallelRWByte(SRAM_CMD_WRITE);
hal_sram_ParallelRWByte(AddrHi);
hal_sram_ParallelRWByte(AddrLo);

//ctr=AddrHi;
//ctr=(ctr<<8)|AddrLo;
//hal_sram_TrackingAddressSetAll(ctr);

for(ctr=0;ctr<DataCount;ctr++)
	{
	hal_sram_ParallelRWByte(DataArray[ctr]);

	// will be optimized later on...  TODO
//	hal_sram_TrackingAddressIncrement(SRAM_0);
//	hal_sram_TrackingAddressIncrement(SRAM_1);
//	hal_sram_TrackingAddressIncrement(SRAM_2);
//	hal_sram_TrackingAddressIncrement(SRAM_3);
	}
set_all_cs(PORT_ON); // cs high
}

// Return a pointer to an array of 4 bytes
static u8 * hal_sram_ParallelRWByte(u8 returnData)
{
static u8 array_byte[4];
static u8 ctr,temp;

array_byte[0]=0;
array_byte[1]=0;
array_byte[2]=0;
array_byte[3]=0;

ctr=7;
while(ctr!=0xFF)
	{
	if((returnData>>ctr)&0x01)
		{
		//DI_0=1;
		//DI_1=1;
		//DI_2=1;
		//DI_3=1;
		SRAM_DI_LAT|=0b1111;
		}
	else
		{
	//	DI_0=0;
		//DI_1=0;
		//DI_2=0;
		//DI_3=0;
		SRAM_DI_LAT&=(~0b1111);
		}

	SCLK=PORT_ON;
	temp=1<<ctr; // one-time computation for faster executions

	if(SRAM_DO_0)
		{
		array_byte[0]|=temp;
		}
	if(SRAM_DO_1)
		{
		array_byte[1]|=temp;
		}
	if(SRAM_DO_2)
		{
		array_byte[2]|=temp;
		}
	if(SRAM_DO_3)
		{
		array_byte[3]|=temp;
		}
	SCLK=PORT_OFF;

	ctr--;
	}


return array_byte;
}
////////////////////////


