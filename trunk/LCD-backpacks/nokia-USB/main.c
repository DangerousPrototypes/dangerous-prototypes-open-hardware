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

#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "HardwareProfile.h"
#include "config.h"
#include "./USB/usb.h"
#include "./USB/usb_function_cdc.h"
#include "usb_config.h"
#include "USB\usb_device.h"
#include "USB\usb.h"
#include "LCD_driver.h"

//this struct buffers the USB input because the stack doesn't like 1 byte reads
#pragma udata
static struct _usbbuffer{
	unsigned char inbuf[64];
	unsigned char cnt;
	unsigned char rdptr;
} ubuf;

//USB output buffer
#define USB_OUT_BUF 64
unsigned char buf[USB_OUT_BUF];
unsigned char uartincnt=0;

//ROM update mode commands
#define COMMAND 0
#define ID 1
#define WRITE 2
#define READ 3
#define SUCCESS 4
#define ERASE 5
#define ERROR 6
#define STATUS 7
#define VERSION 8

//ROM update struct
static struct _sm {
	unsigned char state;
	unsigned int repeat;
	unsigned char crc;
	unsigned char cmdcnt;
	unsigned char cmdbuf[4];
}sm;

static void init(void);
void setupROMSPI(void);
void teardownROMSPI(void);
unsigned char spi(unsigned char c);
void usbbufservice(void);
void usbbufflush(void);
unsigned char usbbufgetbyte(unsigned char* c);
static void setupUART(void);
void setupFPGASPImaster(void);
void setupFPGASPIslave(void);

#pragma code
void main(void){   
	unsigned char clr[]={0b11100000,0b00011100,0b00000011, 0b11111100, 0b11100011, 0b00011111};
	int i,j;
	int m;
	long k;

	unsigned long timer;
	#define longDelay(x) timer=x; while(timer--)

    init();			//setup the crystal, pins, hold the FPGA in reset
	usbbufflush();	//setup the USB byte buffer
	
	//setupROMSPI();	//setup SPI to program ROM
	//sm.state=COMMAND;	//start up looking for a command
	//sm.cmdcnt=0;

	LCD_init(); //init the LCD

	while(1){
		//draw screen with colors from the clr pallet...
		for(j=0;j<sizeof(clr);j++){
			for(i=0; i<ENDPAGE; i++){
				for(m=0;m<ENDCOL;m++){
					pset(clr[j],i,m);
				}
			}
		    //for (k = 0; k < 300000; k++);	//delay_ms(100);
		}
	
	}
/*
    USBDeviceInit();//setup usb

    while(1){
        USBDeviceTasks(); 

    	if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) continue;
		usbbufservice();//load any USB data into byte buffer

			//send data from the FPGA receive buffer to USB
			if((mUSBUSARTIsTxTrfReady()) && (uartincnt > 0)){
				putUSBUSART(&buf[0], uartincnt);
			}

		}

    	CDCTxService();

    }//end while

*/
}//end main

static void init(void){
	unsigned int cnt = 2048;
	
	//all pins digital
    ANCON0 = 0xFF;                  
    ANCON1 = 0b00011111;// updated for lower power consumption. See datasheet page 343                  

	//there are some sensative FPGA pins, 
	//make sure everything is input (should be on startup, but just in case)
	TRISA=0xff;
	TRISB=0xff;
	TRISC=0b11111111; //LED out

	//on 18f24j50 we must manually enable PLL and wait at least 2ms for a lock
	OSCTUNEbits.PLLEN = 1;  //enable PLL
	while(cnt--); //wait for lock
}

unsigned char spi(unsigned char c){
	SSP2BUF=c;
	while(SSP2STATbits.BF==0);
	c=SSP2BUF;
	return c;
}
/*
void setupROMSPI(void){
	//setup SPI for ROM
	//!!!leave unconfigured (input) except when PROG_B is held low!!!
	PIN_PROG_B=0; //ground
	TRIS_PROG_B=0; //output
	//A0 PR0 flash_si
	//A1 PR1 flash_so
	//B5 RP8 flash_sck
	//A2 flash_cs

	//CS disabled
	PIN_FLASH_CS=1; //CS high
	TRIS_FLASH_CS=0; //CS output

	//TRIS_FLASH_MISO=1;
	RPINR21=1;//PPS input

	TRIS_FLASH_MOSI=0;
	PIN_FLASH_MOSI=0;
	RPOR0=9; //PPS output
	
	TRIS_FLASH_SCK=0;
	PIN_FLASH_SCK=0;
	RPOR8=10; //PPS output

	SSP2CON1=0b00100000; //SSPEN/ FOSC/4 CP=0
	SSP2STAT=0b01000000; //cke=1
}

void teardownROMSPI(void){

	SSP2CON1=0; //disable SPI
	//A0 PR0 flash_si
	//A1 PR1 flash_so
	//B5 RP8 flash_sck
	//A2 flash_cs
	//TRIS_FLASH_MISO=1;
	RPINR21=0b11111; //move PPS to nothing

	TRIS_FLASH_MOSI=1;
	RPOR0=0;
	
	TRIS_FLASH_SCK=1;
	RPOR8=0;
	
	//CS disabled
	TRIS_FLASH_CS=1; //CS input
	PIN_FLASH_CS=0; //CS low

	TRIS_PROG_B=1; //input, release PROG_B
}
*/
void usbbufservice(void){
	if(ubuf.cnt==0){//if the buffer is empty, get more data
		ubuf.cnt = getsUSBUSART(ubuf.inbuf,64);
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

//
//
//the stack calls these, if they aren't here we get errors. 
//
//
void USBCBSuspend(void){}
void USBCBWakeFromSuspend(void){}
void USBCB_SOF_Handler(void){}
void USBCBErrorHandler(void){}
void USBCBCheckOtherReq(void){USBCheckCDCRequest();}//end
void USBCBStdSetDscHandler(void){}//end
void USBCBInitEP(void){CDCInitEP();}
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size){
    switch(event){
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER:
            Nop();
            break;
        default:
            break;
    }      
    return TRUE; 
}
/*
#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818

//We didn't use the low priority interrupts, 
// but you could add your own code here
#pragma interruptlow InterruptHandlerLow
void InterruptHandlerLow(void){}

//We didn't use the low priority interrupts, 
// but you could add your own code here
#pragma interrupthigh InterruptHandlerHigh
void InterruptHandlerHigh(void){}

//these statements remap the vector to our function
//When the interrupt fires the PIC checks here for directions
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void){
     _asm goto InterruptHandlerHigh _endasm
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

*/