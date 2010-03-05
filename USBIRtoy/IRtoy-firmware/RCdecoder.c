/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
//
// IRman compatible RC decoder for RC5, RC5x
// Sends a 6 byte packet:
// RC5 address byte (0)
// RC5 command byte (1) *bit 6 is RC5x bit
// Bytes 2-5 are 0 padding
//
//#ifdef RC_DECODER
#include "HardwareProfile.h"

//USB stack
#include "usb_config.h" //download these files from Microchip
#include "./USB/usb.h"
#include "./USB/usb_device.h" 
#include "./USB/usb_function_cdc.h"

extern struct _irtoy irToy;

static enum _RC5STATE{
	IDLE=0,
	HALF_PERIOD,
	BIT_PERIOD_0,
	BIT_PERIOD_1,
	SEND,
}decoderState=IDLE;

static struct _RC5decoder{
	unsigned char bp0;//manchester period 0
	unsigned char bp1;//manchester period 1
	unsigned char bcnt;//bit count
}RC5;

void SetupRC5(void){
	decoderState=IDLE;
	CCP1CON=0; //disable any PWM
	T2CON=0;
	T2IE=0; //disable any Timer 2 interrupt
	T2IF=0;
	IRRX_IF=0;
	IRRX_IE=1; //enable RX interrupts for data ACQ

}

void IRmanString(void){
	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
		irToy.usbOut[0]='O';//answer OK
		irToy.usbOut[1]='K';
		putUSBUSART(irToy.usbOut,2);
	}
}

void ProcessIR(void){   
	static unsigned char i;
	//static unsigned char rc5x, toggle, addr, cmd;

	if((decoderState==SEND) && (USBUSARTIsTxTrfReady())){
	
		//process IR data (decode RC5)
		//rc5x=irToy.s[0]; //0 second start bit, use below
		//toggle=irToy.s[1]; //1 toggle bit, discard

		irToy.usbOut[0]=0; //addr=0; //address is first byte of 6 byte packet
		for(i=2;i<7;i++){ //loop through and assemble 8 address bits into byte
			irToy.usbOut[0]<<=1;
			irToy.usbOut[0]|=irToy.s[i];					
		}

		irToy.usbOut[1]=irToy.s[0]; //command is second byte
											  // optional rc5x bit is bit 6
		for(i=7;i<13;i++){ //assemble 6 command bits into byte
			irToy.usbOut[1]<<=1;
			irToy.usbOut[1]|=irToy.s[i];
		}


		//irToy.usbOut[0]=addr;
		//irToy.usbOut[1]=cmd;	

		irToy.usbOut[2]=0x00;//four extra bytes for 6 byte IRMAN format
		irToy.usbOut[3]=0x00;
		irToy.usbOut[4]=0x00;
		irToy.usbOut[5]=0x00;	

		putUSBUSART(irToy.usbOut,6);

		decoderState=IDLE;//wait for more RC commands....
		IRRX_IE=1;//interrupts back on	

	}

}	

//high priority interrupt routine
#pragma interrupt IRdecoderInterruptHandlerHigh
void IRdecoderInterruptHandlerHigh (void){

	//RC5 decoder
	if(IRRX_IE==1 && IRRX_IF == 1){ //if RB Port Change Interrupt	
	  if(decoderState==IDLE && ((IRRX_PORT & IRRX_PIN)==0) ){//only if idle and pin state == 0
			IRRX_IE=0;	//disable port b interrupt
  			LED_LAT |= LED_PIN; //LED ON! (off after .5 bit period)
			T2_RC5halfbitperiod(); //setup to hit in the middle of next bit period
			T2IF=0;//clear the interrupt flag
			T2IE=1; //able interrupts...
			T2ON=1;
			decoderState=HALF_PERIOD;
		}	
    	IRRX_IF = 0;    //Reset the RB Port Change Interrupt Flag bit  

  	}else if(T2IE==1 && T2IF==1){
		switch(decoderState){
			case HALF_PERIOD: //middle of first bit period is actually second bit of first pair (first bit is invisible)
				T2ON=0;//timer off
				T2_RC5bitperiod(); //full bit values from now on
				RC5.bcnt=0; //reset samples
				decoderState=BIT_PERIOD_0; //next timeis bit period 0

				T2IF=0;//clear the interrupt flag
				T2IE=1; //able interrupts...
				T2ON=1;
				
				LED_LAT &= (~LED_PIN); //LED OFF!
				break;
			case BIT_PERIOD_0:
				RC5.bp0=IRX;
				decoderState=BIT_PERIOD_1;
				break;
			case BIT_PERIOD_1:
				RC5.bp1=IRX;

				if(RC5.bp0==1 && RC5.bp1==0){
					irToy.s[RC5.bcnt]=1;
				}else if (RC5.bp0==0 && RC5.bp1==1){
					irToy.s[RC5.bcnt]=0;
				}else{//error			
					decoderState=IDLE; //reset
					T2ON=0; //timer off
					IRRX_IE=1;	//IR interrupts back on
					break;
				}

				decoderState=BIT_PERIOD_0;

				RC5.bcnt++;			
				if(RC5.bcnt==13){//done sampling
					decoderState=SEND; //process and send in service loop
					T2ON=0;//turn off the timer
				}
				break;				
		}//switch
		T2IF=0;//clear the interrupt flag
	}//if   
}
//#endif //RC_DECODER

