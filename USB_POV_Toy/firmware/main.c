/* ***************************************************************************************************************************************************
 Copyright (C) 2011 Where Labs, LLC (DangerousPrototypes.com/Ian Lesnet)

 This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the License for more details. You should have received a copy of the License along with this program. If not, see <http://creativecommons.org/licenses/by-sa/3.0/>.

 Contact: http://www.DangerousPrototypes.com

********************************************************************************************************************************************* */

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
//#include "MatrixOrbital.h"

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
void usbbufservice(void);
void usbbufflush(void);
unsigned char usbbufgetbyte(unsigned char* c);
unsigned char waitforbyte(void);
unsigned char checkforbyte(void);
void sendok(void);
void send(unsigned char c);
//unsigned char spi(unsigned char c);

void UsageMode(void);

//unsigned char hal_Acl_Read(unsigned char r);
//void hal_Acl_Enable(void);

#pragma code
void main(void){  
	u8 i,cmd, param[9],c;
	u16 temp; // TODO to be removed later on
	u16 x,y,z;
	u8 pwr = 2;
	long l;
	//unsigned char t[]={"Hello World"};

    init();			//setup the crystal, pins
	usbbufflush();	//setup the USB byte buffer

	//setup SPI 

	//C7 - EEPROM CS
	//A2 ACL CS
	//C0 PR11 MISO 
	//C1 PR12 MOSI
	//C2 RP13 CLK

	LATAbits.LATA2=1;		//ACC CS
	TRISAbits.TRISA2=0;		//ACC CS

	LATCbits.LATC7=1;		//EEPROM CS
	TRISCbits.TRISC7=0;		//EEPROM CS

	//CS disabled
	//PIN_FLASH_CS=1; //CS high
	//TRIS_FLASH_CS=0; //CS output
	//TRIS_FLASH_MISO=1;
	LATCbits.LATC0 = 1;
	TRISCbits.TRISC1=1;
	RPINR21=11;//PPS input SPI2MISO=RP11	//MISO

	//TRIS_FLASH_MOSI=0;
	//PIN_FLASH_MOSI=0;
	LATCbits.LATC1=0;		//MOSI
	TRISCbits.TRISC1=0;		//MOSI
	RPOR12=9; //PPS output
	
	//TRIS_FLASH_SCK=0;
	//PIN_FLASH_SCK=0;
	LATCbits.LATC2=0;		//SCK
	TRISCbits.TRISC2=0;		//SCK
	RPOR13=10; //PPS output

	SSP2CON1=0b00100000; //SSPEN/ FOSC/4 CP=0
	SSP2STAT=0b01000000; //cke=1

	//LEDs
	//PWM on cathode
	TRISAbits.TRISA0=0;
	LATAbits.LATA0=1; //enable cathode

	//setup LEDs
	LATB=0;
	TRISB=0;

	hal_acl_enable();

//	hal_acl_IntSetup();
//#if 1

    USBDeviceInit();//setup usb

    while(1){

		USBDeviceTasks(); 

    	if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) continue;
		usbbufservice();//load any USB data into byte buffer
		
		switch(waitforbyte()){//switch on the command
			case 0x00:
			  	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
					param[0]='B';
					param[1]='B';
					param[2]='I';
					param[3]='O';
					param[4]='1';
					putUnsignedCharArrayUsbUsart(param,5);
				}
				break;
			case 0x01: 
				ACL_CS=0;
				hal_spi_rw((0x0d<<1));
				param[0]=0x00;//spi(0xff);
				param[1]=hal_spi_rw(0xff);
				ACL_CS=1;
			  	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
					putUnsignedCharArrayUsbUsart(param,2);
				}
				break;
			case 0x02:
				param[0]=waitforbyte();
				LATB=param[0];
				break;
			case 0x06:

				while(1){
					//c=hal_acl_read(0x06);
					//mma_wait_until_ready();
					//c=hal_acl_read(OUTPUT_X_8BIT);

					//if(c&0b10000000){//negative
					//	c^=0xff;
					//}
					mma_get_x_average(pwr,&x);
					c=x;
					
					LATB=c;
					if(checkforbyte())break;
				}
				break;
			case 0x07:
				while(1){
					//mma_wait_until_ready();
					//c=hal_acl_read(OUTPUT_Y_8BIT);
	
					//if(c&0b10000000){//negative
					//	c^=0xff;
					//}
					mma_get_y_average(pwr,&y);
					c=y;
					LATB=c;
					if(checkforbyte())break;
				}
				break;
			case 0x08:
				while(1){
					//mma_wait_until_ready();
					//c=hal_acl_read(OUTPUT_Z_8BIT);

					//if(c&0b10000000){//negative
					//	c^=0xff;
					//}
					mma_get_z_average(pwr,&z);
					c=z;
					LATB=c;
					if(checkforbyte())break;
				}
				break;
			case 0x15: 
				param[0]=0x00;//spi(0xff);
				while(1){
					//ACL_CS=0;
					//hal_spi_rw((0x06<<1));
					//param[1]=hal_acl_read(OUTPUT_X_8BIT);
					//ACL_CS=1;


				//	mma_get_x_average(pwr,&x);
				//	param[1]=x;
					mma_get_y_average(pwr,&y);
					param[1]=y;
				//	mma_get_z_average(pwr,&z);
				//	param[1]=z;

					LATB = param[1];
	
				  	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
						putUnsignedCharArrayUsbUsart(param,2);
					}
					if(checkforbyte())break;
				}
				break;
			case 0x16:
				//while(1)
				{
					//ACL_CS=0;
					//hal_spi_rw((0x06<<1));
					//param[0]=hal_spi_rw(0xff);
					//hal_acl_read( OUTPUT_X_8BIT );
					//param[1]='|';
					//param[2]=hal_spi_rw(0xff);
					//param[2]=hal_acl_read( OUTPUT_Y_8BIT );
					//param[3]=':';
					//param[4]=hal_spi_rw(0xff);
					//param[4]=hal_acl_read( OUTPUT_Z_8BIT );
					//param[5]=0x13;
					//param[6]=0x10;
					//ACL_CS=1;


					mma_get_average(pwr,&x,&y,&z);
					param[0] = x;
					param[1] = '|';
					param[2] = y;
					param[3] = ':';
					param[4] = z;
					param[5]=0x13;
					param[6]=0x10;
					
				  	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
						putUnsignedCharArrayUsbUsart(param,7);
					}
					if(checkforbyte())break;
				}
				break;
			case 0x17:
start_mode:
//#endif
	hal_acl_config();
	//i=ACL_INT1;
	hal_pov_setupInt(); //set the interrupts
	hal_pov_setupTmr1(); //setup timer 1
T1ON=1;
hal_pov_StartCycle();

//while(1);

	while(1){

#if 0
		////////// LOADING BITMAP ///////////////
		if(hal_pov_LoadBitmapCheck()==TRUE)
			{
			hal_pov_loadBitmapFromEeToRam();
			}
		hal_pov_displayBitmap(); // call this to update the display
		/////// END OF LOADING BITMAP ////////////
#endif

		//if pin ready
		//|********ooooooooo|


		//wait for the first half of the forward stroke
		while(1)
			{
			while(ACL_INT1==0); //wait here until the pin changes
			if(hal_acl_IsItReverseOrForward()==ACL_FORWARD)
				{
				hal_pov_setupTmr0();
				//hal_pov_SetState(ACL_FORWARD);
				break;
			}
		}	

		//wait for the middle of the back stroke
		while(1){
			while(ACL_INT1==0); //wait here until the pin changes
			if(hal_acl_IsItReverseOrForward()==ACL_REVERSE){
				//stop timer 0
				//TMR0H=0;//first set the high byte
				//TMR0L=0;//set low byte copies high byte too
				//TM0ON=0;//enable the timer
				//hal_pov_SetState(ACL_REVERSE);
				hal_pov_disableTmr0();
				break;
			}

		}

		//divide that value into the new period value.
	   //2^0=1
	   //2^1=2
	   //2^2=4
	   //2^3=8
	   //2^4=16
	   //2^5=32
	   //2^6=64
	   //2^7=128
/*
		//wait half the new period
		l=(TMR0H<<8);
		l|=TMR0L;
		l=l>>1;//divide by two
		l=0x10000-l;
		TMR0H=((l&0xff00)>>8);
		TMR0L=l;
		TM0IF=0;
		TM0ON=1;
		while(TM0IF==0);
*/
		//to do: sanity checks, averaging 
		T1ON=0;
		l=(TMR0H<<8);
		l|=TMR0L;
		l=0x10000-l;
		TMR1H=((l&0xff00)>>8);
		TMR1L=l;
		hal_pov_setupTmr1();
		T1ON=1;//enable the timer
		hal_pov_StartCycle();
				//setup change interrupt
			//clear interrupt (write 0b11 to 0x17)
			//enable interrupt (write 0x00 to 0x17)
			//hal_acl_write(INT_LATCH_RST, 0b11);
			//hal_acl_write(INT_LATCH_RST, 0x00);

//////////////////////
	}
	hal_acl_enable();

//#if 0
break;
			default: //error
				break;
		}
	    CDCTxService();

	}
//#endif

}//end main




// TODO
void UsageMode(void)
{
// Initialization Here

while(1)
	{


	}
}

//unsigned char hal_Acl_Read(unsigned char r){
//	unsigned char c;
//
//	ACL_CS=0;
//	hal_spi_rw((r<<1));
//	c=hal_spi_rw(0xff);
//	ACL_CS=1;
//}
//
//void hal_Acl_Enable(void){
//	ACL_CS=0;
//	hal_spi_rw((0x16<<1)|0b10000000);//write setup
//	hal_spi_rw(0b0001);//low g, measurement
//	ACL_CS=1;
//}



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

	//make sure everything is input (should be on startup, but just in case)
	TRISA=0xff;
	TRISB=0xff;
	TRISC=0b11111111; 

	//on 18f24j50 we must manually enable PLL and wait at least 2ms for a lock
	OSCTUNEbits.PLLEN = 1;  //enable PLL
	while(cnt--); //wait for lock

}

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
     _asm goto POVInterrupt _endasm
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
