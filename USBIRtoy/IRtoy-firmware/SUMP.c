/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
//
// SUMP LA
//
//#ifdef SUMP_LA

#include "globals.h"

//extern struct _irtoy irToy;

//commandset
//http://www.sump.org/projects/analyzer/protocol/
#define SUMP_RESET 0x00
#define SUMP_RUN	0x01
#define SUMP_ID	0x02
#define SUMP_XON	0x11
#define SUMP_XOFF 0x13

static enum _LAstate {
	LA_IDLE = 0,
	LA_ARMED,
	LA_DUMP,
	LA_RESET,
} LAstate = LA_IDLE;

volatile static struct {
	unsigned int sample;
	unsigned int ptr;
	unsigned char btrack;
}loga;

void SUMPlogicCommand(unsigned char inByte){

	static enum _SUMP {
		C_IDLE = 0,
		C_PARAMETERS,
		C_PROCESS,
	} sumpRXstate = C_IDLE;

	static struct _sumpRX {
		unsigned char command[5];
		unsigned char parameters;
		unsigned char parCnt;
	} sumpRX;

	switch(sumpRXstate){ //this is a state machine that grabs the incoming commands one byte at a time

		case C_IDLE:

			switch(inByte){//switch on the current byte
				case SUMP_RESET://reset
	    			T2IE=0; //disable interrupts...
					T2ON=0;//tmr2 off
					IRRX_IE = 0;  //DISABLE RB port change interrupt
					LAstate=LA_RESET;
					break;
				case SUMP_ID://SLA0 or 1 backwards: 1ALS
		    		if( mUSBUSARTIsTxTrfReady() ){
						//putsUSBUSART("1ALS"); //doesn't work b/c of 0x00
						irToy.usbOut[0]='1';
						irToy.usbOut[1]='A';
						irToy.usbOut[2]='L';
						irToy.usbOut[3]='S';
						putUnsignedCharArrayUsbUsart(irToy.usbOut,4);
					}
					break;
				case SUMP_RUN://arm the triger
					LED_LAT |= LED_PIN;//ARMED, turn on LED
					LAstate=LA_ARMED;
   					IRRX_IF = 0;    //Reset the RB Port Change Interrupt Flag bit   
   					IRRX_IE = 1;  //Enables the RB port change interrupt
					break;
				case SUMP_XON://resume send data
				//	xflow=1;
					break;
				case SUMP_XOFF://pause send data
				//	xflow=0;
					break;
				default://long command
					sumpRX.command[0]=inByte;//store first command byte
					sumpRX.parameters=4; //all long commands are 5 bytes, get 4 parameters
					sumpRX.parCnt=0;//reset the parameter counter
					sumpRXstate=C_PARAMETERS;
					break;
			}
			break;
		case C_PARAMETERS: 
			sumpRX.command[sumpRX.parCnt]=inByte;//store each parameter
			sumpRX.parCnt++;
			if(sumpRX.parCnt<sumpRX.parameters) break; //if not all parameters, quit
		case C_PROCESS: //ignore all long commands for now
			sumpRXstate=C_IDLE;
			break;					
		}
}

unsigned char SUMPlogicService(void){
	static unsigned char i, USBWriteCount;

	switch(LAstate){//dump data
		//case IDLE:
		//case ARMED:
		//case LA_START_DUMP: 
		case LA_DUMP:
		    if(USBUSARTIsTxTrfReady()){
				USBWriteCount=0;
				for(i=0; i<8; i++){

					loga.btrack<<=1; //shift bit at begin to reset from last loop
					if((loga.btrack==0) && (loga.ptr>0) ){//no bits left
						loga.btrack=0b00000001;//start at bit 0
						loga.ptr--;
					}
		
					if( (irToy.s[loga.ptr] & loga.btrack)!=0)
						irToy.usbOut[USBWriteCount]=0; 
					else
						irToy.usbOut[USBWriteCount]=1;

					USBWriteCount++;

					loga.sample--;
					if(loga.sample==0){//send 64/128/512/1024 samples exactly!
						LAstate=LA_RESET;
						break;
					}

				}
				putUnsignedCharArrayUsbUsart(irToy.usbOut,USBWriteCount);

			}
			break;
		case LA_RESET:
			LAstate = LA_IDLE;
			return 0xff;	
			break;
	}
	return 0;
}


//high priority interrupt routine
#pragma interrupt SUMPInterruptHandlerHigh
void SUMPInterruptHandlerHigh (void){

	//SUMP logic analyzer
	if(IRRX_IE==1 && IRRX_IF == 1){ //if RB Port Change Interrupt	
		if((IRRX_PORT & IRRX_PIN)==0){//only if 0, must read PORTB to clear RBIF
			IRRX_IE=0; //disable port b interrupt
			LED_LAT |= (LED_PIN);//LED OFF
			//LED_LAT ^= (LED_PIN);//LED toggle (the dim feature caused data glitches)

			//TIMER2 sample rate, 
			//need to adjust speed for 2x frequency, nyquist rate
			//T2CON=PRE_x4+POST_x3;
			//PR2=221;
			T2_RXsampleperiod();
			T2IF=0;//clear the interrupt flag
			T2IE=1; //able interrupts...
			T2ON=1;//timer on

			//setup the sample storage buffer
			irToy.s[0]=0b10000000; //preload value for pretty LA output	
			loga.sample=2; //start with 2 existing samples
			loga.ptr=0; //start with byte 1
			loga.btrack=0b00100000;//start on bit 3
		}
    	IRRX_IF=0;    //Reset the RB Port Change Interrupt Flag bit  

	}else if(T2IE==1 && T2IF==1){ //is this timer 2 interrupt?
		//LED_LAT ^= (LED_PIN);//LED toggle	(dimming caused data glitches)
		if( ((IRRX_PORT & IRRX_PIN)!=0) && (loga.ptr< SAMPLE_ARRAY_SIZE) ){ //stay within the array
			//((IRRX_PORT & IRRX_PIN)!=0)
			irToy.s[loga.ptr]|=loga.btrack; //set current buffer bit if RX high
		}

		loga.btrack>>=1; //shift bit tracker for next time
		if((loga.btrack==0)){//no bits left
			loga.btrack=0b10000000;//start at bit 7
		 	loga.ptr++;//increment the array pointer
			//if(loga.ptr>=125){ //for debugging
			//	Nop();
			//}
			if(loga.ptr<SAMPLE_ARRAY_SIZE) irToy.s[loga.ptr]=0; //clear new byte
		}

		loga.sample++; //increment the sample count
		if((unsigned int)loga.sample==(unsigned int)SAMPLE_SIZE){//done sampling
			LAstate=LA_DUMP;//dump the samples
			T2ON=0; //disable the sampling timer
			T2IE=0;
			LED_LAT &= (~LED_PIN);//LED off
		}

		T2IF=0;//clear the interrupt flag
	}   
}
//#endif
