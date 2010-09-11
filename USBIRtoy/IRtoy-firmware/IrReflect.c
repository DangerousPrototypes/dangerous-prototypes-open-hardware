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

#include "globals.h"

#define RBINTERRUPTCOUNTLIMIT	10

#define IsRbCountExceeded()	(RBInterruptCount>RBINTERRUPTCOUNTLIMIT)

#define EnablePortbChangeInterrupt() IRRX_IF=0; IRRX_IE=1;
#define DisablePortbChangeInterrupt() IRRX_IE=0;

volatile u8 RBInterruptCount=0;


#define IrTxTurnOn()  			TRIS_IRTX=0;
#define IrTxTurnOff()			TRIS_IRTX=1;

typedef enum
{
	TX_LED_TURN_OFF=0,
	TX_LED_TURN_ON
}SM_TX_LED_STATE;


volatile SM_TX_LED_STATE txledstate;



static void IrReflectTxPwmSetup(void )
{
//setup for IR TX
/*
 * PWM registers configuration
 * Fosc = 48000000 Hz
 * Fpwm = 36144.58 Hz (Requested : 36000 Hz)
 * Duty Cycle = 50 %
 * Resolution is 10 bits
 * Prescaler is 4
 * Ensure that your PWM pin is configured as digital output
 * see more details on http://www.micro-examples.com/
 * this source code is provided 'as is',
 * use it at your own risks
 * http://www.micro-examples.com/public/microex-navig/doc/097-pwm-calculator
 */

//LAT_IRTX=0;//TX LED off
//TRIS_IRTX=1; // input mode
IrTxTurnOff()

CCP1CON=0;
T2CON=0;

T2IF=0;//clear the interrupt flag
T2IE=0; //disable interrupts
PR2 = 0b01010010 ; //82
T2CON = 0b00000101 ;
CCPR1L = 0b00101001 ;	//upper 8 bits of duty cycte
CCP1CON = 0b00011100 ; //we leave this on for visual inspection (5-4 two LSB of duty, 3-0 set PWM)
}



#if 0
static void IrReflectTxPwmDeactivate()
{
LAT_IRTX=0;//TX LED off
TRIS_IRTX=1; // input mode
}
#endif


void IrReflectSetup(void){


if( mUSBUSARTIsTxTrfReady() )
	{
	irToy.usbOut[0]='E';//answer OK
	irToy.usbOut[1]='0';
	irToy.usbOut[2]='1';
	putUSBUSART(irToy.usbOut,3);
	}



IrReflectTxPwmSetup();
EnablePortbChangeInterrupt()
RBInterruptCount=0;
txledstate=TX_LED_TURN_OFF;
LedOff();
}



unsigned char IrReflectService(void)
{
static u16 ctr=0;
char buff;

if(getsUSBUSART(&buff,1)!=0)
	{
	if((buff=='0')||(buff==0)) // TODO remove the 0 later hehe
		{
		IrTxTurnOff();
		DisablePortbChangeInterrupt();
		LedOff();
		return 1;
		}
	}

if(ctr>5000) //just a magic trial and error number :)
	{
	u8 isRbCountingOk;
	isRbCountingOk=FALSE;
	txledstate^=1;
	txledstate&=0x01;
	switch(txledstate)
		{
		case TX_LED_TURN_OFF:
			if(IsRbCountExceeded()) // since it is turned on previously, it must have pulses on RB
				{isRbCountingOk=TRUE;}
			IrTxTurnOff();
			break;
		case TX_LED_TURN_ON:
#if 0
			if(!IsRbCountExceeded()) // since it is turned off previously, it must have no pulses on RB
				{isRbCountingOk=TRUE;}
#endif
			isRbCountingOk=INVALID;
			IrTxTurnOn();
			break;
		}

	// I will still be putting something here :) For now Leds toggling

	if(isRbCountingOk==TRUE)
		{
		LedOn();
		if(mUSBUSARTIsTxTrfReady())
			putrsUSBUSART("DETECT!");
		}
	else if(isRbCountingOk==FALSE)
		{
		LedOff();
		}

	RBInterruptCount=0; //reset counter
	ctr=0;
	}
ctr++;
return 0;
}








//high priority interrupt routine
#pragma interrupt IrReflectionInterruptHandlerHigh
void IrReflectionInterruptHandlerHigh (void){
//irIO driver
if(IRRX_IE==1 && IRRX_IF == 1)
	{
	RBInterruptCount++;
	RBInterruptCount&=0x7F; // make sure it is below 127
	IRRX_IF=0;
	}

}


#if 0
//
// irIO periodic service routine
// moves bytes in and out
//
unsigned char irIOservice(void){
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
				if( (irIO.btrackreset==0b10000000) || ((irToy.s[c] & 0b10000000)!=0) ){//if 8bit mode or 7bit + data packet bit
					if(irIO.TX==0){//not transmitting, disable RX, setup TX
						LED_LAT |=LED_PIN; //LED on
						irIO.TX=1;
						IRRX_IE = 0; //disable RX interrupt
						T1CON=0;
			
						irIO.flushflag=1; //force flush of remaining bytes
			
						irIO.txbuf=irToy.s[c];
			
						irIO.txflag=1; //set tx flag
						irIO.TXsamples--;
						c++;
						
						//T1_10kHzOffset();
						TMR1H=irIO.T1offsetH;
						TMR1L=irIO.T1offsetL;
						T1IF=0;		//clear the interrupt flag
						T1IE=1; 	//able interrupts...
						T1ON=1;		//timer on
		
					}else if(irIO.txflag==0){ //already on, but need to load new byte
						irIO.txbuf=irToy.s[c];
						c++;
						irIO.txflag=1; //set tx flag
						irIO.TXsamples--;
					} //both are false, we just try again on the next loop
				}else{ //process as command
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
							LedOff();
							LedOut();
							return 1; //need to flag exit!
							break;
						case IRIO_SETUP_SAMPLETIMER: //setup the values for the 10khz default sampleing timer
						case IRIO_SETUP_PWM: //setup PWM frequency
							irIOcommand.command[0]=irToy.s[c];
							irIOcommand.parameters=2;
							irIOstate=I_PARAMETERS;
							break;
						case IRIO_RAW:
							irIO.btrackreset=0b10000000; //load 8 bit bit tracker into variable
							break;
						//case IRIO_REPLAY: //not implemented yet
						//	break;
						default:
							break;
					}
					irIO.TXsamples--;
					c++;
				}
				break;
			case I_PARAMETERS://get optional parameters
				irIOcommand.command[irIOcommand.parCnt]=irToy.s[c];//store each parameter
				irIO.TXsamples--;
				c++;
				irIOcommand.parCnt++;
				if(irIOcommand.parCnt<irIOcommand.parameters) break; //if not all parameters, quit
			case I_PROCESS:	//process long commands
				switch(irIOcommand.command[0]){
					case IRIO_SETUP_SAMPLETIMER: //set user values for the 10khz default sampling timer
						irIO.T1offsetH=irIOcommand.command[1];
						irIO.T1offsetL=irIOcommand.command[2];
						break;
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
	if(irIO.rxflag==1){ //a RX byte is in the buffer
		if(irIO.RXsamples<64){ //if we have room in the USB send buffer
			irToy.usbOut[irIO.RXsamples]=irIO.rxbuf; //add to USB send buffer
			irIO.RXsamples++;
			irIO.rxflag=0;				//reset the flag
		}else{//underrun error, no more room!
			LED_TRIS |= LED_PIN; //error, LED off by making it input 
		}
	}
	//if the buffer is full, send it to USB
	if( ( (irIO.RXsamples==64) || (irIO.flushflag==1) ) && (mUSBUSARTIsTxTrfReady()) ){ //if we have full buffer, or end of capture flush
		putUSBUSART(irToy.usbOut,irIO.RXsamples);//send current buffer to USB
		irIO.RXsamples=0;
		irIO.flushflag=0;
	}
	
	return 0;//CONTINUE
}

//high priority interrupt routine
#pragma interrupt irIOInterruptHandlerHigh
void irIOInterruptHandlerHigh (void){
	//irIO driver
	if(IRRX_IE==1 && IRRX_IF == 1){ //if RB Port Change Interrupt	

		if( ((IRRX_PORT & IRRX_PIN)==0)){//only if 0, must read PORTB to clear RBIF
			IRRX_IE=0;	//disable port b interrupt
			LED_LAT |= LED_PIN;//LED ON

			//TIMER sample rate, 
			T1CON=0;
			//T1_10kHzOffset();
			TMR1H=irIO.T1offsetH;
			TMR1L=irIO.T1offsetL;
			T1IF=0;		//clear the interrupt flag
			T1IE=1; 	//able interrupts...
			T1ON=1;		//timer on

			//setup the sample storage buffer
			irIO.work=0b01000000;//preload a pretty value
			irIO.btrack=0b00100000;
			irIO.rxflag=0;
			irIO.timeout=0;//reset timeout
		}

    	IRRX_IF=0;    //Reset the RB Port Change Interrupt Flag bit  

	}else if(T1IE==1 && T1IF==1){ //is this timer 1 interrupt?
		T1ON=0; //timer off
		//T1_10kHzOffset();//preload timer values
		TMR1H=irIO.T1offsetH;
		TMR1L=irIO.T1offsetL;
		T1ON=1;//timer back on

		if(irIO.TX==1){
			if(irIO.btrack==0 && irIO.txflag==1){
				irIO.work=irIO.txbuf;//get next byte
				irIO.txflag=0; //buffer ready for new byte
				irIO.btrack=irIO.btrackreset;
			}
			
			if(irIO.btrack!=0){
				if((irIO.work & irIO.btrack)==0){
					TRISCbits.TRISC2=1;//~(irIO.work & irIO.btrack);//put 1 or 0 on the pin
				}else{
					TRISCbits.TRISC2=0;//~(irIO.work & irIO.btrack);//put 1 or 0 on the pin				
				}
				irIO.btrack>>=1; //shift one bit
			}else{//no bits left //shut down PWM, resume RX
				IRTX_TRIS|=IRTX_PIN;//digital INPUT (PWM off)
				LED_LAT &=(~LED_PIN); //LED off
				irIO.TX=0; //go back to RX mode
				T1IE=0;		//disable timer2 interrupt
				T1ON=0;
				IRRX_IE=1;//start portB interrupt again to get new data next time
			}
		}else{
		
			if((IRRX_PORT & IRRX_PIN)==0){ //inverse current pin reading
				irIO.work|=irIO.btrack;
			}	
	
			irIO.btrack>>=1; //shift one bit
			if(irIO.btrack==0){//no bits left
	
				if(irIO.work==0){ //track how many samples since last IR signal
					irIO.timeout++;
				}else{
					irIO.timeout=0;//reset timeout
				}
	
				if(irIO.timeout==5){//50 bytes without change (make define)
					T1ON=0;//disable timer
					LED_LAT &=(~LED_PIN); //LED off
					irIO.flushflag=1; //flush any remaining bytes in the sampling buffer
					IRRX_IE=1;//start portB interrupt again to get new data next time
				}
	
				if(irIO.rxflag==0){//only if cleared
					irIO.rxbuf=irIO.work;
					irIO.rxflag=1;
				}else{
					LED_TRIS |= LED_PIN; //error, LED off by making it input
				}
				irIO.work=0;
				irIO.btrack=0b10000000;
	
			}
		}
		T1IF=0;
	}  
}



//
//
//	8bit only IRTX test code
//
//
/*
#ifdef RXtest
static unsigned char p[]={0x7F,0xC0,0x1F,0xFF,0xF0,0x00,0x07,0xF8,0x03,0xFE,0x01,0xFF,0x00,0xFF,0xFF,0x80,0x3F,0xE0,0x00,0x1F,0xFF,0xF8,0x07,0xFC,0x03,0xFE,0x01,0xFE,0x00,0x00,0x00,0x00,0x00,};
static unsigned char pcnt=0;
#endif

	//1. Big buffer to hold all incomming bytes
	if(irIO.TXsamples==0){
		//test playback
		#ifdef RXtest
			irIO.TXsamples=sizeof(p);
		#else
			irIO.TXsamples=getsUSBUSART(irToy.s,64);
		#endif
		c=0;
		if((irIO.TXsamples>0)&&(irIO.TX==0)){
			//disable RX and do this when new data comes from USB
			LED_LAT |=LED_PIN; //LED off
			irIO.TX=1;
			IRRX_IE = 0; //disable RX interrupt
			T1CON=0;

			irIO.flushflag=1; //force flush of remaining bytes

			#ifdef RXtest
				irIO.txbuf=p[c];		
			#else
				irIO.txbuf=irToy.s[c];
			#endif

			irIO.txflag=1; //set tx flag
			irIO.TXsamples--;
			c++;
			
			T1_10kHzOffset();
			T1IF=0;		//clear the interrupt flag
			T1IE=1; 	//able interrupts...
			T1ON=1;		//timer on
		}
	}

	if((irIO.txflag==0) && (irIO.TXsamples>0)){//IRtx buffer free byte
		#ifdef RXtest
			irIO.txbuf=p[c];		
		#else
			irIO.txbuf=irToy.s[c];
		#endif
		c++;
		irIO.txflag=1; //set tx flag
		irIO.TXsamples--;
	}
*/
#endif


