//Due to licensing issues, we can't redistribute the Microchip USB source. 
//You can get it from the Microchip website for free: 
//http://www.microchip.com/usb
//
//1.Download and install the USB source. These files install to c:\Microchip Soultions\ by default.
//2.Place the project folder in the Microchip source install directory (c:\Microchip Soultions\ by default)
//3.Copy usb_config.h & usb_descriptors.c from \Microchip Solutions\USB Device - CDC - Basic Demo\CDC - Basic Demo - Firmware3\ to the project folder.
//4. That's it. You've got the latest source and we're compliant with the license.
//
//Depending on the install location you may need to tweak the include paths under Project->build options.
#include "globals.h"
#include "config.h"
#include "MMA7455L2.h"
#include "descriptors.h"	// JTR Only included in main.c

extern unsigned char usb_device_state; // JTR2 corrected type
extern unsigned char cdc_trf_state;
extern BYTE cdc_In_buffer[64];
extern BDentry *Inbdp;

unsigned char d=0;

void user_configured_init(void);
void usb_start(void);
void initCDC(void);
void usb_init(ROMPTR const unsigned char*, ROMPTR const unsigned char*, ROMPTR const unsigned char*, int);
BYTE FAST_usb_handler(void);
void USBDeviceTasks(void);

//this struct buffers the USB input because the stack doesn't like 1 byte reads
#pragma udata
static struct _usbbuffer{
	unsigned char inbuf[64];
	unsigned char cnt;
	unsigned char rdptr;
} ubuf;

BYTE inByte; // JTR3 Global
typedef unsigned char uint8_t;
typedef signed int int16_t;
//USB output buffer
#define USB_OUT_BUF 64
unsigned char buf[USB_OUT_BUF];
unsigned char uartincnt=0;

static void init(void);
void usbbufservice(void);
void usbbufflush(void);
unsigned char usbbufgetbyte(unsigned char* c);
unsigned char waitforbyte(void);
unsigned char checkforbyte(void);
void sendok(void);
void send(unsigned char c);
void mma_init(void);
//unsigned char spi(unsigned char c);


unsigned char spi_rw(unsigned char c);
void mma_write( uint8_t address, uint8_t value );
uint8_t mma_read( uint8_t address );
int16_t mma_read10( uint8_t address );
void mma_calibrate_offset( int16_t x, int16_t y, int16_t z );
void mma_wait_until_ready(void);
void mma_get_average( uint8_t power_of_two, int16_t * x, int16_t * y, int16_t * z );
void mma_get_average8( uint8_t power_of_two, signed char * x8, signed char * y8, signed char * z8 );


void mma_init()
{
	//setup SPI 

	//C7 - EEPROM CS
	//A2 ACL CS
	//C0 PR11 MISO 
	//C1 PR12 MOSI
	//C2 RP13 CLK

	LATAbits.LATA2=1;
	TRISAbits.TRISA2=0;

	LATCbits.LATC7=1;
	TRISCbits.TRISC7=0;

	//CS disabled
	//PIN_FLASH_CS=1; //CS high
	//TRIS_FLASH_CS=0; //CS output

	//TRIS_FLASH_MISO=1;
	RPINR21=11;//PPS input SPI2MISO=RP11

	//TRIS_FLASH_MOSI=0;
	//PIN_FLASH_MOSI=0;
	LATCbits.LATC1=0;
	TRISCbits.TRISC1=0;
	RPOR12=9; //PPS output
	
	//TRIS_FLASH_SCK=0;
	//PIN_FLASH_SCK=0;
	LATCbits.LATC2=0;
	TRISCbits.TRISC2=0;
	RPOR13=10; //PPS output

	SSP2CON1=0b00100000; //SSPEN/ FOSC/4 CP=0
	SSP2STAT=0b01000000; //cke=1
}


#pragma code
void main(void){  
	u8 i,cmd, param[9],c;
	u16 temp; // TODO to be removed later on
	long l;
	signed int x, y, z;
	signed char x8, y8, z8;
	static unsigned char ledtrig;

    initCDC(); // JTR this function has been highly modified It no longer sets up CDC endpoints.

    init();			//setup the crystal, pins
    mma_init();

    usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS); // TODO: Remove magic with macro
    usb_start();
    usbbufflush(); //flush USB input buffer system



    i = mma_read( MMA_I2CAD );
	//if((i&~0b10000000)!=0x1d)while(1);
    mma_write( MMA_I2CAD, 0x1d | MMA_I2CDIS_bit ); // disable I2C

    i = mma_read( MMA_CTL1 );
    mma_write( MMA_CTL1, i |= MMA_DFBW_bit ); // high output data rate

    mma_write( MMA_MCTL, 0b00000101 ); // 2g range; measurement mode

    //mma_calibrate_offset( 0, 0, 0 );


	//LEDs
	//PWM on cathode
	TRISAbits.TRISA0=0;
	LATAbits.LATA0=1; //enable cathode

	//setup LEDs
	LATB=0;
	TRISB=0;


	ledtrig=1; //only shut LED off once
    //	Never ending loop services each task in small increments
    while (1) {
        do {
            if (!TestUsbInterruptEnabled()) //JTR3 added
                USBDeviceTasks(); ////service USB tasks Guaranteed one pass in polling mode even when usb_device_state == CONFIGURED_STATE
            if ((usb_device_state < DEFAULT_STATE)) { // JTR2 no suspendControl available yet || (USBSuspendControl==1) ){
                //LedOff();
            } else if (usb_device_state < CONFIGURED_STATE) {
                //LedOn();
            }else if((ledtrig==1) && (usb_device_state == CONFIGURED_STATE)){
				//LedOff();
				ledtrig=0;
			}
        } while (usb_device_state < CONFIGURED_STATE);

		usbbufservice();//load any USB data into byte buffer

		if(usbbufgetbyte(&inByte) == 1){

			switch(inByte){//switch on the command
				case 0x00:
					WaitInReady();  //it's always ready, but this could be done better
					param[0]='B';
					param[1]='B';
					param[2]='I';
					param[3]='O';
					param[4]='1';
					putUnsignedCharArrayUsbUsart(param,5);
					break;
				case 0x01:
			    	mma_get_average8( 4, &x8, &y8, &z8 );
					param[0]=x8;
					param[1]=y8;
					param[2]=z8;
					WaitInReady();  //it's always ready, but this could be done better
					putUnsignedCharArrayUsbUsart(param,3);
					break;
				default: //error
					break;
			}
	
		}//if data
	}//while
//#endif

}//end main

//-------------------------------------------------------------------------------------


unsigned char spi_rw(unsigned char c){
	SSP2BUF=c;
	while(SSP2STATbits.BF==0);
	c=SSP2BUF;
	return c;
}

void mma_write( uint8_t address, uint8_t value )
{
	ACL_CS=0;
	spi_rw((address<<1)|0b10000000);
	spi_rw(value);
	ACL_CS=1;
}

uint8_t mma_read( uint8_t address )
{
    uint8_t value;
    ACL_CS=0;
    spi_rw( address << 1 );
    value = spi_rw(0x00 );
	ACL_CS=1;
    return value;
}
/*
int16_t mma_read10( uint8_t address )
{
    int16_t value=0xc000;
	uint8_t l,h;

    value = spi_rw(0x00); //<<6;//low byte
	value=value<<6;
	h=spi_rw(0x00 );
    value|= (h<<14);//high byte
    return value>>6;
}
*/

int16_t mma_read10( uint8_t address )
{
    int16_t value=0xc000;
	uint8_t l,h;

    ACL_CS=0;
    spi_rw( address << 1 );
    value = spi_rw(0x00); //<<6;//low byte
    ACL_CS=1;
	value=value<<6;
    ACL_CS=0;
    spi_rw( (address+1) << 1 );
	h=spi_rw(0x00 );
    value|= (h<<14);//high byte
	ACL_CS=1;
	//value=h;
	//value=value<<8;
	//value|=l;
    return value>>6;
}





void mma_calibrate_offset( int16_t x, int16_t y, int16_t z )
{
    int16_t offset_x = ( 0 - x ) << 1;
    int16_t offset_y = ( 0 - y ) << 1;
    int16_t offset_z = ( 64 - z ) << 1;
    mma_write( MMA_XOFFL, offset_x & 0x00ff );
    mma_write( MMA_XOFFL + 1, ( offset_x & 0xff00 ) >> 8 );
    mma_write( MMA_YOFFL, offset_y & 0x00ff );
    mma_write( MMA_YOFFL + 1, ( offset_y & 0xff00 ) >> 8 );
    mma_write( MMA_ZOFFL, offset_z & 0x00ff );
    mma_write( MMA_ZOFFL + 1, ( offset_z & 0xff00 ) >> 8 );
}

void mma_wait_until_ready()
{
	unsigned char c;
	while(1){
		c=mma_read( MMA_STATUS );
		c=c&0b1;
		if(c ) break;
	}
}

// 1 <= power_of_two <= 6
void mma_get_average( uint8_t power_of_two, int16_t * x, int16_t * y, int16_t * z )
{
    int16_t accu_x = 0;
    int16_t accu_y = 0;
    int16_t accu_z = 0;
    uint8_t i;
    for ( i = 0; i < ( 1 << power_of_two ); ++i ) {
        mma_wait_until_ready();
    	ACL_CS=0;
    	spi_rw( 0x00 );//setup read
        accu_x += mma_read10( MMA_XOUT10 );
        accu_y += mma_read10( MMA_YOUT10 );
        accu_z += mma_read10( MMA_ZOUT10 );
		ACL_CS=1;
    }
    *x = ( accu_x + ( 1 << ( power_of_two - 1 ) ) ) >> power_of_two;
    *y = ( accu_y + ( 1 << ( power_of_two - 1 ) ) ) >> power_of_two;
    *z = ( accu_z + ( 1 << ( power_of_two - 1 ) ) ) >> power_of_two;
}

void mma_get_average8( uint8_t power_of_two, signed char * x8, signed char * y8, signed char * z8 )
{
    int16_t accu_x = 0;
    int16_t accu_y = 0;
    int16_t accu_z = 0;
    uint8_t i;
    for ( i = 0; i < ( 1 << power_of_two ); ++i ) {
        mma_wait_until_ready();
        accu_x += mma_read( 0x06 );
        accu_y += mma_read( 0x07 );
        accu_z += mma_read( 0x08 );
    }
    *x8 = ( accu_x + ( 1 << ( power_of_two - 1 ) ) ) >> power_of_two;
    *y8 = ( accu_y + ( 1 << ( power_of_two - 1 ) ) ) >> power_of_two;
    *z8 = ( accu_z + ( 1 << ( power_of_two - 1 ) ) ) >> power_of_two;
}



#if defined(USE_INTERRUPT)
#define POWER_OF_TWO 5
static volatile int16_t x_array[ 1 << POWER_OF_TWO ];
static volatile int16_t y_array[ 1 << POWER_OF_TWO ];
static volatile int16_t z_array[ 1 << POWER_OF_TWO ];
static volatile int16_t x_moving_average;
static volatile int16_t y_moving_average;
static volatile int16_t z_moving_average;
static volatile uint8_t i;

ISR( INT0_vect )
{
    int16_t x = mma_read10( MMA_XOUT10 );
    int16_t y = mma_read10( MMA_YOUT10 );
    int16_t z = mma_read10( MMA_ZOUT10 );
    x_moving_average -= x_array[ i ];
    y_moving_average -= y_array[ i ];
    z_moving_average -= z_array[ i ];
    x_array[ i ] = x;
    y_array[ i ] = y;
    z_array[ i ] = z;
    x_moving_average += x;
    y_moving_average += y;
    z_moving_average += z;
    ++i;
    if ( i >= ( 1 << POWER_OF_TWO ) ) {
        i = 0;
    }
}

void mma_get_moving_average( int16_t * x, int16_t * y, int16_t * z )
{
    *x = ( ( x_moving_average + ( 1 << ( POWER_OF_TWO - 1 ) ) ) ) >> POWER_OF_TWO;
    *y = ( ( y_moving_average + ( 1 << ( POWER_OF_TWO - 1 ) ) ) ) >> POWER_OF_TWO;
    *z = ( ( z_moving_average + ( 1 << ( POWER_OF_TWO - 1 ) ) ) ) >> POWER_OF_TWO;
}
#endif
















//---------------------------------------------------------------------------------


static void init(void){
	unsigned int cnt = 2048;
	
	//all pins digital
    ANCON0 = 0xFF;                  
    ANCON1 = 0b00011111;// updated for lower power consumption. See datasheet page 343                  

	//make sure everything is input (should be on startup, but just in case)
	TRISA=0xff;
	TRISB=0xff;
	TRISC=0b11111111; 

	//on 18f24j50 we must manually enable PLL and wait at least 2ms for a lock
	OSCTUNEbits.PLLEN = 1;  //enable PLL
	while(cnt--); //wait for lock

}
/*
void usbbufservice(void){
	if(ubuf.cnt==0){//if the buffer is empty, get more data
		ubuf.cnt = getUnsignedCharArrayUsbUart(ubuf.inbuf,64);
		ubuf.rdptr=0;
	}
}

//puts a byte from the buffer in the byte, returns 1 if byte
unsigned char usbbufgetbyte(unsigned char* c){
	if(ubuf.cnt>0){
		*c=ubuf.inbuf[ubuf.rdptr];
		ubuf.cnt--;
		ubuf.rdptr++;
		return 1;
	}
	return 0;
}

void usbbufflush(void){
	ubuf.cnt = 0;
	ubuf.rdptr=0;
}
*/

//
//
//the stack calls these, if they aren't here we get errors. 
//
//


#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818

//We didn't use the low priority interrupts, 
// but you could add your own code here
#pragma interruptlow InterruptHandlerLow
void InterruptHandlerLow(void){}
/*
//We didn't use the low priority interrupts, 
// but you could add your own code here
#pragma interrupthigh InterruptHandlerHigh
void InterruptHandlerHigh(void){}
*/
//these statements remap the vector to our function
//When the interrupt fires the PIC checks here for directions
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void){
     //_asm goto POVInterrupt _endasm
}

#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
void Remapped_Low_ISR (void){
     _asm goto InterruptHandlerLow _endasm
}

//relocate the reset vector
extern void _startup (void);  
#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
void _reset (void){
    _asm goto _startup _endasm
}
//set the initial vectors so this works without the bootloader too.
#pragma code HIGH_INTERRUPT_VECTOR = 0x08
void High_ISR (void){
     _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
}
#pragma code LOW_INTERRUPT_VECTOR = 0x18
void Low_ISR (void){
     _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
}


