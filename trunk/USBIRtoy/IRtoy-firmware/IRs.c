/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
//
//	IR IO
//
//#ifdef IR_IO
//#define RXtest

#include "HardwareProfile.h"

//USB stack
#include "usb_config.h" //download these files from Microchip
#include "./USB/usb.h"
#include "./USB/usb_device.h" 
#include "./USB/usb_function_cdc.h"

extern struct _irtoy irToy;


static struct{
	unsigned char T1offsetH;
	unsigned char T1offsetL;
	unsigned char RXsamples;
	unsigned char TXsamples;
	unsigned char timeout;
	unsigned char btrack; //bit tracker
	unsigned char btrackreset; //reset value for bit tracker
	unsigned char work;
	unsigned char rxbuf;
	unsigned char txbuf;
	unsigned char TX:1;
	unsigned char rxflag:1;
	unsigned char txflag:1;
	unsigned char flushflag:1;
} irIO;

//static unsigned char USBbuf[2];

void irssetup(void){

	//send version string
  	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
		irToy.usbOut[0]='S';//answer OK
		irToy.usbOut[1]='0';
		irToy.usbOut[2]='0';
		putUSBUSART(irToy.usbOut,3);
	}

	//setup for IR RX
	irIO.rxflag=0;
	irIO.txflag=0;
	irIO.flushflag=0;
	irIO.timeout=0;
	irIO.RXsamples=0;
	irIO.TXsamples=0;
	irIO.TX=0;



	//uisng timer2 as a 50us timer
	//T2_irS50uS();


	//setup timer 0
	T0CON=0;
	//configure prescaler
	//bit 2-0 T0PS2:T0PS0: Timer0 Prescaler Select bits
	//111 = 1:256 Prescale value
	//110 = 1:128 Prescale value
	//101 = 1:64 Prescale value
	//100 = 1:32 Prescale value
	//011 = 1:16 Prescale value
	//010 = 1:8 Prescale value
	//001 = 1:4 Prescale value
	//000 = 1:2 Prescale value
	T0CON=0b111;
	//T0CONbits.T08BIT=1; //16bit mode
	//internal clock
	//low to high
	T0CONbits.PSA=0; //1=not assigned

	//timer 1 as USB packet send timeout
	T1CON=0;

	IRRX_IE = 1;  //IR RX interrupt on
	IRRX_IF = 0;  //IR RX interrupt on
}


//
// irIO periodic service routine
// moves bytes in and out
//
unsigned char irsservice(void){
	static unsigned char c;

	static enum _smio { //in out data state machine
		I_IDLE = 0,
		I_PARAMETERS,
		I_PROCESS,
	} irIOstate = I_IDLE;

	static struct _smCommand {
		unsigned char command[5];
		unsigned char parameters;
		unsigned char parCnt;
	} irIOcommand;

	//TO DO:
	//variable names, centralize variables
	//playback last recording
	//PWM, timer setup
	//0xxxxxxx - command
	//00000000 - reset, return to RC5 (same as SUMP) LED output/off, CPP1CON=0; T2ON=0; T1ON=0; T1IE=0;
	//1xxxxxxx - data
	if(irIO.TXsamples==0){
		irIO.TXsamples=getsUSBUSART(irToy.s,64);
		c=0;
	}

	if(irIO.TXsamples>0){
		switch (irIOstate){
			case I_IDLE:
					#define IRIO_RESET 0x00
					#define IRIO_SETUP_SAMPLETIMER 0x01
					#define IRIO_SETUP_PWM 0x02
					#define IRIO_RAW 0x03
					#define IRIO_REPLAY 0x04			
					switch(irToy.s[c]){
						case IRIO_RESET: //reset, return to RC5 (same as SUMP) 
							CCP1CON=0; 
							T2ON=0; 
							T1ON=0; 
							T1IE=0;
							IRRX_IE = 0;
							IRTX_TRIS|=IRTX_PIN;//digital INPUT (no PWM until active)
							IRTX_LAT&=(~IRTX_PIN);//direction 0
							LEDoff();
							LEDout();
							return 1; //need to flag exit!
							break;
						case IRIO_SETUP_PWM: //setup PWM frequency
							irIOcommand.command[0]=irToy.s[c];
							irIOcommand.parameters=2;
							irIOstate=I_PARAMETERS;
							break;
						default:
							break;
					}
					irIO.TXsamples--;
					c++;
				break;
			case I_PARAMETERS://get optional parameters
				irIOcommand.command[irIOcommand.parCnt]=irToy.s[c];//store each parameter
				irIO.TXsamples--;
				c++;
				irIOcommand.parCnt++;
				if(irIOcommand.parCnt<irIOcommand.parameters) break; //if not all parameters, quit
			case I_PROCESS:	//process long commands
				switch(irIOcommand.command[0]){
					case IRIO_SETUP_PWM: //setup user defined PWM frequency
						T2CON = 0;
						PR2 = irIOcommand.command[1];//user period
						CCPR1L =(irIOcommand.command[1]>>1);//upper 8 bits of duty cycle, 50% of period by binary division
						if((irIOcommand.command[1]& 0b1)!=0)//if LSB is set, set bit 1 in CCP1CON
							CCP1CON = 0b00101100 ; //5-4 two LSB of duty, 3-0 set PWM
						else
							CCP1CON = 0b00001100 ; //5-4 two LSB of duty, 3-0 set PWM

						T2CON = 0b00000101; //enable timer again, 4x prescaler				
						break;
				}
				irIOstate=I_IDLE;//return to idle state
				break;	

		}//switch 
	}


	//service the inbound samples here
	//keep in 64 byte buffer then send to USB for max sample rate
/*	if(irIO.rxflag==1){ //a RX byte is in the buffer
		if(irIO.RXsamples<64){ //if we have room in the USB send buffer
			irToy.usbOut[irIO.RXsamples]=irIO.rxbuf; //add to USB send buffer
			irIO.RXsamples++;
			irIO.rxflag=0;				//reset the flag
		}else{//underrun error, no more room!
			LED_TRIS |= LED_PIN; //error, LED off by making it input 
		}
	}
*/
	//if the buffer is full, send it to USB
	if( ( (irIO.RXsamples==64) || (irIO.flushflag==1) ) && (mUSBUSARTIsTxTrfReady()) ){ //if we have full buffer, or end of capture flush
		putUSBUSART(irToy.usbOut,irIO.RXsamples);//send current buffer to USB
		irIO.RXsamples=0;
		irIO.flushflag=0;
	}
	
	return 0;//CONTINUE
}

//the first falling edge starts a timer
//the next interrupt copies the timer value to a buffer and resets the timer
//if the timer interrupts, then timeout and end.
//high priority interrupt routine
#pragma interrupt irsInterruptHandlerHigh
void irsInterruptHandlerHigh (void){
	unsigned char h,l;

	if(IRRX_IE==1 && IRRX_IF == 1){ //if RB Port Change Interrupt	
	
		if( ((IRRX_PORT & IRRX_PIN)==0)){};//only if 0, must read PORTB to clear RBIF
		l=IRRX_PORT;
		if(TM0ON==0){ //timer not running, setup and start
			LED_LAT |= LED_PIN;//LED ON
			TMR0H=0;//first set the high byte
			TMR0L=0;//set low byte copies high byte too
			TM0IE=1;
			TM0IF=0;
			TM0ON=1;//enable the timer
			
			TMR1H=0;
			TMR1L=0;
			T1IF=0;		//clear the interrupt flag
			T1IE=1; 	//able interrupts...
			T1ON=1;		//timer on


		}else{//timer running, save value and reset
			//the goal is to reset the timer as quickly as possible
			//later we can fine tune the start value to compensate for the lost cycles
			TM0ON=0;//disable the timer
			l=TMR0L;//read low byte, puts high byte in H
			h=TMR0H; //read high byte
			TMR0H=0;//first set the high byte
			TMR0L=0;//set low byte copies high byte too
			TM0IF=0;
			TM0ON=1;//enable the timer

			//reset timer1, USB packet send timeout
			T1ON=0;		//timer on
			TMR1H=0;
			TMR1L=0;
			T1ON=1;		//timer on

			irToy.usbOut[irIO.RXsamples]=h; //add to USB send buffer
			irIO.RXsamples++;
			irToy.usbOut[irIO.RXsamples]=l; //add to USB send buffer
			irIO.RXsamples++;
		}
		//clear portb interrupt		
    	IRRX_IF=0;    //Reset the RB Port Change Interrupt Flag bit  

	}else if(TM0IE==1 && TM0IF==1){ //is this timer 0 interrupt?
		//the idea is that if we got here
		//it has been so long without a pin change that 
		//there is not more signal
		//it would be more robust to check the pin state for 0
		//need to examine the limits of typical protocols closer
		T1ON=0;		//timer off

		TM0ON=0; //timer off
		TM0IF=0;
/*
			TMR0H=0;//first set the high byte
			TMR0L=0;//set low byte copies high byte too
			TM0IF=0;
			TM0ON=1;//enable the timer
*/

		//maybe we need to send a long pause to the PC at the end...
		irToy.usbOut[irIO.RXsamples]=0xff; //add to USB send buffer
		irIO.RXsamples++;
		irToy.usbOut[irIO.RXsamples]=0xff; //add to USB send buffer
		irIO.RXsamples++;
		irIO.flushflag=1;

		//reset the interrupt, just in case
		IRRX_IE=1;
		IRRX_IF=0;

		LED_LAT &=(~LED_PIN); //LED off
	}else if(T1IE==1 && T1IF==1){ //is this timer 0 interrupt?
		irIO.flushflag=1;	
		T1IF=0;		//clear the interrupt flag
	}  
}

//#endif //IR_IO
