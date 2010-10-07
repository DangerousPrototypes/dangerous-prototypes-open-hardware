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

//#include "GenericTypeDefs.h"
//#include "Compiler.h"
//#include "HardwareProfile.h"
//USB stack
#include "globals.h"

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

static void init(void);
unsigned char spi(unsigned char c);
void usbbufservice(void);
void usbbufflush(void);
unsigned char usbbufgetbyte(unsigned char* c);
unsigned char waitforbyte(void);
unsigned char checkforbyte(void);
void fillLCD12bitColor(unsigned int color);
void sendok(void);
void send(unsigned char c);
void waitforpixels(unsigned int pixels);

#pragma code
void main(void){  
	unsigned char inbuf, b[9], cmd; 
	unsigned int k, color, clr[]={0b111100000000,0b11110000,0b1111, 0b11111100, 0b11100011, 0b00011111};
	unsigned char i,j,m;
	static unsigned char xs=0,ys=0,xe=ENDPAGE-1,ye=ENDCOL;
	#define fillbox_whole() fillBox(0,0, ENDPAGE-1,ENDCOL)
	#define fillbox_current() fillBox(xs,ys,xe,ye)
	
    init();			//setup the crystal, pins, hold the FPGA in reset
	usbbufflush();	//setup the USB byte buffer

	LCD_init(); //init the LCD
	fillbox_whole();
	fillLCD12bitColor(0xffff);

    USBDeviceInit();//setup usb

    while(1){

        USBDeviceTasks(); 

    	if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) continue;
		usbbufservice();//load any USB data into byte buffer
		
		cmd=waitforbyte();

		switch(cmd){//switch between the upgrade mode states
			case 0:
				//reset LCD
				break;
			case 'i'://INIT
				LCD_init(); //init the LCD
				sendok();
				break;
			case 'v': //VERSION:
			  	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
					b[0]='H';//answer OK
					b[1]='1';
					b[2]='F';
					b[3]='0';//FIRMWARE_VERSION_L;
					b[4]='0';//FIRMWARE_VERSION_L;
					b[5]='B';//FIRMWARE_VERSION_L;
					b[6]='F';//FIRMWARE_VERSION_L;
					b[7]='F';//FIRMWARE_VERSION_L;
					b[8]=0x00;//FIRMWARE_VERSION_L;
					putUnsignedCharArrayUsbUsart(b,9);
				}				
				break;
			case 'c'://CONTRAST:
				b[0]=waitforbyte();
				b[1]=waitforbyte();
				b[2]=waitforbyte();
			    LCD_command(VOLCTR);  	// electronic volume, this is the contrast/brightness(EPSON)
			    LCD_data(b[0]);   	// volume (contrast) setting - fine tuning, original
			    LCD_data(b[1]);   	// internal resistor ratio - coarse adjustment
				LCD_command(SETCON);	//Set Contrast(PHILLIPS)
				LCD_data(b[2]);	
				sendok();
				break;
			case 'b'://SET BOX:
				xs=waitforbyte();
				ys=waitforbyte();
				xe=waitforbyte();
				ye=waitforbyte();
				fillbox_current();
				sendok();
				break;
			case 'P'://DATA:
				//calculate the number of pixels in the current box
				//loop and push the pixels
				fillbox_whole();
				for(k=0; k<(ENDPAGE*(ENDCOL/2)); k++){
					LCD_data(waitforbyte());
					LCD_data(waitforbyte());
					LCD_data(waitforbyte()); 
				}
				sendok();
				break;	
			case 'p'://DATA BOX:
				//calculate the number of pixels in the current box
				//loop and push the pixels
				fillbox_current();
				for(i=xs; i<xe; i++){
					for(m=ys;m<ye;m=m+2){
						LCD_data(waitforbyte());
						LCD_data(waitforbyte());
						LCD_data(waitforbyte()); 
					}	
				}
				sendok();
				break;	
			case 'T'://TEST
				while(1){
					//draw screen with colors from the clr pallet...
					for(j=0;j<3;j++){
						if(checkforbyte()) goto test_end;//exit on any char
						fillbox_whole();
						fillLCD12bitColor(clr[j]);
					}
				
				}	
test_end:			
				//this test measures the feedback from the 7volt power supply on AN0
				ANCON0&=(~0b0001); //clear AN0 to make analog
				ADCON0=0b00000000; //setup ADC to no reference, AN0, off (pg 341)
				ADCON1=0b10111110; //setup ADC for max time, max divider (pg 342)
				ADCON0|=0b1;		//turn on ADC
				ADCON0|=0b10;		//start conversion
				while(ADCON0 & 0b10); //wait for conversion to finish
			
				ANCON0=0xff; //all pins back to digital
				ADCON0=0x00; //disable ADC
			
				if((ADRES<0x00) || (ADRES>0xffff)){
					send('0');
				}else{
					send('1');
				}
				break;	

			case 't'://TEST BOX
				while(1){
					//draw screen with colors from the clr pallet...
					for(j=0;j<3;j++){
						if(checkforbyte()) goto test_end;//exit on any char
						fillbox_current();
						for(i=xs; i<xe; i++){
							for(m=ys;m<ye;m=m+2){
								//pset(clr[j],i,m);
								#define color clr[j]
								LCD_data((color>>4)&0x00FF);
								LCD_data(((color&0x0F)<<4)|(color>>8));
								LCD_data(color&0x0FF);  	// nop(EPSON)		
								#undef color
							}
						}
					}
				
				}	
				break;	

			case 'F'://fill
				color=waitforbyte();
				color=color<<8;
				color|=(waitforbyte()&0x00ff);

				fillLCD12bitColor(color);

				sendok();

				break;	

			case 'f'://fill partial
				color=waitforbyte();
				color=color<<8;
				color|=(waitforbyte()&0x00ff);

				fillbox_current();
				for(i=xs; i<xe; i++){
					for(m=ys;m<ye;m=m+2){
						LCD_data((color>>4)&0x00FF);
						LCD_data(((color&0x0F)<<4)|(color>>8));
						LCD_data(color&0x0FF);  	// nop(EPSON)		
					}
				}
				sendok();
				break;	
			case 'a'://read ADC
				//this test measures the feedback from the 7volt power supply on AN0
				ANCON0&=(~0b0001); //clear AN0 to make analog
				ADCON0=0b00000000; //setup ADC to no reference, AN0, off (pg 341)
				ADCON1=0b10111110; //setup ADC for max time, max divider (pg 342)
				ADCON0|=0b1;		//turn on ADC
				ADCON0|=0b10;		//start conversion
				while(ADCON0 & 0b10); //wait for conversion to finish
				ANCON0=0xff; //all pins back to digital
				ADCON0=0x00; //disable ADC
			
				b[0]=(ADRES >>8);
				b[1]=(ADRES& 0x00ff);
			  	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
					putUnsignedCharArrayUsbUsart(b,2);
				}
				break;
	
		}//switch

    	CDCTxService();

    }//end while
}//end main

void fillLCD12bitColor(unsigned int color){
	unsigned int j;
	unsigned char c[3];

	//precalculate the color variables
	c[0]=((color>>4)&0x00FF);
	c[1]=(((color&0x0F)<<4)|(color>>8));
	c[2]=(color&0x0FF);

	fillbox_whole();

	for(j=0; j<(ENDPAGE*(ENDCOL/2)); j++){
		LCD_data(c[0]);
		LCD_data(c[1]);
		LCD_data(c[2]);  	// nop(EPSON)		
	}

}

void waitforpixels(unsigned int pixels){
	unsigned int j;
	for(j=0; j<pixels; j++){
		LCD_data(waitforbyte());
		LCD_data(waitforbyte());
		LCD_data(waitforbyte()); 
	}

}

void send(unsigned char c){
	unsigned char b[2];

  	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
		b[0]=c;
		putUnsignedCharArrayUsbUsart(b,1);
	}	

}

void sendok(void){
	unsigned char b[2];

  	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
		b[0]='1';//answer OK
		putUnsignedCharArrayUsbUsart(b,1);
	}	

}

unsigned char waitforbyte(void){
	unsigned char inbuf;

	if(usbbufgetbyte(&inbuf)) return inbuf; //return data
	//wait for more USB data
	//services USB peripheral
	while(1){
		USBDeviceTasks(); 
	   	if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)){
			return 0; //goto USB_loop_jump; //USB gone, fail out to main loop
		}
		usbbufservice();//load any USB data into byte buffer
		if(usbbufgetbyte(&inbuf)) return inbuf; //wait for more data
	    CDCTxService();
	}

} 

unsigned char checkforbyte(void){
	unsigned char inbuf;

	if(usbbufgetbyte(&inbuf)) return 1; //return data
	//wait for more USB data
	//services USB peripheral
	USBDeviceTasks(); 
   	if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)){
		return 1; //goto USB_loop_jump; //USB gone, fail out to main loop
	}
	usbbufservice();//load any USB data into byte buffer
	if(usbbufgetbyte(&inbuf)) return 1; //wait for more data
    CDCTxService();
	return 0;
} 

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