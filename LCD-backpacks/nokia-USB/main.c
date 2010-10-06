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
#define BYTE1 0
#define BYTE2 1

//ROM update struct
static struct _sm {
	unsigned char state;
	unsigned int repeat;
	unsigned char crc;
	unsigned char cmdcnt;
	unsigned char cmdbuf[4];
}sm;

static void init(void);
unsigned char spi(unsigned char c);
void usbbufservice(void);
void usbbufflush(void);
unsigned char usbbufgetbyte(unsigned char* c);


#pragma code
void main(void){  
	unsigned char inbuf; 
	unsigned int clr[]={0b111100000000,0b11110000,0b1111, 0b11111100, 0b11100011, 0b00011111};
	int i,j;
	int m, color;
	long k;

	unsigned long timer;
	#define longDelay(x) timer=x; while(timer--)

    init();			//setup the crystal, pins, hold the FPGA in reset
	usbbufflush();	//setup the USB byte buffer

	LCD_init(); //init the LCD
	fillBox(0,0);

	sm.state=BYTE1;	//start up looking for a command
	sm.cmdcnt=0;

/*
	while(1){
		//draw screen with colors from the clr pallet...
		for(j=0;j<3;j++){
			fillBox(0,0);
			for(i=0; i<ENDPAGE; i++){
				for(m=0;m<ENDCOL;m=m+2){
					//pset(clr[j],i,m);
					#define color clr[j]
					LCD_data((color>>4)&0x00FF);
					LCD_data(((color&0x0F)<<4)|(color>>8));
					LCD_data(color&0x0FF);  	// nop(EPSON)		
					#undef color
				}
			}
		    //for (k = 0; k < 300000; k++);	//delay_ms(100);
		}
	
	}
*/

    USBDeviceInit();//setup usb


    while(1){
        USBDeviceTasks(); 

    	if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) continue;
		usbbufservice();//load any USB data into byte buffer

		switch(sm.state){//switch between the upgrade mode states
			case BYTE1:
				if(!usbbufgetbyte(&inbuf)) continue; //wait for more data
				color=inbuf;
				color=color<<8;

				sm.state=BYTE2;  //wait for next instruction packet
			case BYTE2:
				if(!usbbufgetbyte(&inbuf)) continue; //wait for more data

				color|=(inbuf&0x00ff);

				LCD_data((color>>4)&0x00FF);
				LCD_data(((color&0x0F)<<4)|(color>>8));
				LCD_data(color&0x0FF);  	// nop(EPSON)		

				sm.state=BYTE1;  //wait for next instruction packet
				break;
		}//switch

    	CDCTxService();

    }//end while
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

	//B2 RP5 CS
	//B1 RP4 RESET
	//B0 RP3 BKLIT
	//C7 RP18 DATA
	//C6 RP17 CLOCK
	//CS disabled
	LAT_CS=1; //CS high
	TRIS_CS=0; //CS output

	LAT_MOSI=0; //MOSI low
	TRIS_MOSI=0; //MOSI output
	//RPOR18=9; //PPS output
	
	LAT_SCK=0; //MOSI low
	TRIS_SCK=0; //MOSI output
	//RPOR17=10; //PPS output

	SSP2CON1=0b00100000; //SSPEN/ FOSC/4 CP=0
	SSP2STAT=0b01000000; //cke=1
}

unsigned char spi(unsigned char c){
	SSP2BUF=c;
	while(SSP2STATbits.BF==0);
	c=SSP2BUF;
	return c;
}

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