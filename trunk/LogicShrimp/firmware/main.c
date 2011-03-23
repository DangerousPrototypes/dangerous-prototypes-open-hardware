//Due to licensing issues, we can't redistribute the Microchip USB source. 
//You can get it from the Microchip website for free: 
//http://www.microchip.com/usb
//
//1.Download and install the USB source. These files install to c:\Microchip Soultions\ by default.
//2.Place the project folder in the Microchip source install directory (c:\Microchip Soultions\ by default)
//3.Copy usb_descriptors.c from \Microchip Solutions\USB Device - CDC - Basic Demo\CDC - Basic Demo - Firmware3\ to the project folder.
//4. That's it. You've got the latest source and we're compliant with the license.
//
//Depending on the install location you may need to tweak the include paths under Project->build options.
// This work is licensed CC-BY-SA
// Copyright Ian Lesnet 2011
// DangerousPrototypes.com
#include "globals.h"
#include "config.h"

//commandset
//http://www.sump.org/projects/analyzer/protocol/
#define SUMP_RESET 	0x00
#define SUMP_RUN	0x01
#define SUMP_ID		0x02
#define SUMP_TEST	0x03
#define SUMP_META	0x04

#define SUMP_XON	0x11
#define SUMP_XOFF 	0x13
#define SUMP_DIV 	0x80
#define SUMP_CNT	0x81
#define SUMP_FLAGS	0x82
#define SUMP_TRIG	0xc0
#define SUMP_TRIG_VALS 0xc1

#define LA_SAMPLE_SIZE  0XFFFF

#define EXT_OSC 0
#define INT_PWM 1
#define TRUE 1
#define FALE 0

//this struct buffers the USB input because the stack doesn't like 1 byte reads
#pragma udata

static struct _usbbuffer{
	unsigned char inbuf[64];
	unsigned char cnt;
	unsigned char rdptr;
} ubuf;

static void init(void);
void usbbufservice(void);
void usbbufflush(void);
unsigned char usbbufgetbyte(unsigned char* c);
unsigned char waitforbyte(void);
unsigned char checkforbyte(void);
void sendok(void);
void send(unsigned char c);
void usbservice(void);
void InterruptHandlerHigh(void);
void InterruptHandlerLow(void);

u8 UsbFifoBufferArray[66];
static unsigned long samples_read, samples_delay, divider;
u8 command[5], clock=EXT_OSC, trigger=FALSE;
u8 inByte, addl, addh;
unsigned int add16, j;

#if 1
#pragma code
void main(void)
{
u8 i;


init();			//setup the crystal, pins
if(hal_sram_parallelInit()==1){
	LATCbits.LATC6=1; //hal_logicshrimp_setLed(PORT_ON); //setup the SRAM, error if one doesn't reply
//while(1);
}
usbbufflush();	//setup the USB byte buffer

USBDeviceInit();//setup usb

while(1)
	{

	USBDeviceTasks();

	if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) continue;
	usbbufservice();//load any USB data into byte buffer
//goto test;
	inByte=waitforbyte();
	switch(inByte)
		{//switch on the command
		case SUMP_RESET://reset
			break;
		case SUMP_XON://resume send data
			//	xflow=1;
			break;
		case SUMP_XOFF://pause send data
			//	xflow=0;
			break;
		case SUMP_ID://SLA0 or 1 backwards: 1ALS
			if( mUSBUSARTIsTxTrfReady() )
				{
				//putsUSBUSART("1ALS"); //doesn't work b/c of 0x00
				UsbFifoBufferArray[0]='1';
				UsbFifoBufferArray[1]='A';
				UsbFifoBufferArray[2]='L';
				UsbFifoBufferArray[3]='S';
				putUnsignedCharArrayUsbUsart(UsbFifoBufferArray,4);
				}
			break;
		case SUMP_META:
			if( mUSBUSARTIsTxTrfReady() )
				{
				//putsUSBUSART("1ALS"); //doesn't work b/c of 0x00
				UsbFifoBufferArray[0]=0x01;
				UsbFifoBufferArray[1]='S';
				UsbFifoBufferArray[2]='h';
				UsbFifoBufferArray[3]='r';
				UsbFifoBufferArray[4]='i';
				UsbFifoBufferArray[5]='m';
				UsbFifoBufferArray[6]='p';
				UsbFifoBufferArray[7]='1';
				UsbFifoBufferArray[8]='.';
				UsbFifoBufferArray[9]='0';
				UsbFifoBufferArray[10]=0x00;
				UsbFifoBufferArray[11]=0x02;
				UsbFifoBufferArray[12]='1';
				UsbFifoBufferArray[13]='.';
				UsbFifoBufferArray[14]='3';
				UsbFifoBufferArray[15]=0x00;
				UsbFifoBufferArray[16]=0x00;
				putUnsignedCharArrayUsbUsart(UsbFifoBufferArray,17);
				}			
			break;
		case SUMP_TEST:
			LATCbits.LATC6=1; //hal_logicshrimp_setLed(PORT_ON); //setup the SRAM, error if one doesn't reply
			
			/*
			*	Test SRAMs
			*
			*/
			UsbFifoBufferArray[0]=hal_sram_parallelInit();

			/*
			*	Test buffer
			*
			*/
			//setup counter
			//SRAM ADDRESS TRACKING: follows the address in the SRAM, always on
			//TMR3 with async external input//
			//Need to know where in the SRAM we are//
			//setup a external counter on C0 to track the SRAM address (/4 prescaler)
			RPINR6=11; // RP11   Timer3 External Clock Input T3CKI RPINR6 T3CKR<4:0>
			//setup T3
			//16bit timer
			// /4 prescaler
			T3CON=0b10100100; //0b10 16 bit 4xprescaler
			//clear to sync to SRAM internal address
			TMR3H=0;
			TMR3L=0;
			T3CON|=0b1;//enable the counter		


			//open buffer
			TRISC|=(0b1);//disable PIC->SRAM clock pin
			LATC&=(~0b10000000); //lower OSC buffer OE, connect OSC to the SRAM clock pins

			//waste time
			j=100;
			while(j--);
			
			//close buffer
			//disable external clock
			LATCbits.LATC7=1; 	//disable EXT_OSC buffer
			TRISC&=(~0b1);//enable PIC->SRAM clock pin

			//is counter >0?
			//get the current SRAM address
			addl=TMR3L;
			addh=TMR3H;

			//move to a 16bit variable
			add16=addh;
			add16=(add16<<8);
			add16|=addl;

			if(add16<100)UsbFifoBufferArray[0]|=0b10; //add error bit

			//Loopback test
			//all SRAM CS high (off)
			CS_0=1; //LATAbits.LATA5
			CS_1=1;	//LATCbits.LATC1
			CS_2=1;	//LATCbits.LATC2
			CS_3=1;	//LATBbits.LATB4

//swap from normal config, pic outputs through CH output pins, inputs through buffer
			// SRAM Data Out (PIC input)
			TRISA&=(~0b1111);
			// SRAM data In (PIC output)
			TRISB|=0b1111;
			
			//74LVC573 buffer open to see input
			hal_logicshrimp_BufferEnable();//enable the input buffer
			
			//alternate pattern on data output pins
			LATA&=(~0b1111);
			LATA|=0b1010;
			//waste time
			j=4;
			while(j--);
			if((PORTB&0xF)!=0b1010) UsbFifoBufferArray[0]|=0b100; //add error bit
			
			LATA&=(~0b1111);
			LATA|=0b0101;
			//waste time
			j=4;
			while(j--);
			if((PORTB&0xF)!=0b0101) UsbFifoBufferArray[0]|=0b100; //add error bit

//cleanup
			LATA&=(~0b1111);
			
			//close sample buffer
			hal_logicshrimp_BufferDisable();//disable the input buffer

			if( mUSBUSARTIsTxTrfReady() )
				{
				putUnsignedCharArrayUsbUsart(UsbFifoBufferArray,1);
				}

			// SRAM Data Out (PIC input)
			TRISA|=0b1111;
			// SRAM data In (PIC output)
			TRISB&=(~0b1111);

			break;
		case SUMP_RUN://arm the triger
//
//
//	CAPTURE SETUP
//
//
			//ARMED, turn on LED
			LATCbits.LATC6=1; //hal_logicshrimp_setLed(PORT_ON);

			//SRAM SETUP: setup the SRAM for record
			hal_sram_parallelInit(); //unlocks, verifies settings
			hal_sram_setup_capture();//setup write,
			TRISB|=0b1111;//SRAM in/PIC out pins to input/hiz

			//ENABLE INPUT BUFFER: let the buffer drive the SRAM input pins
			hal_logicshrimp_BufferEnable();//enable the input buffer

			//SRAM ADDRESS TRACKING: follows the address in the SRAM, always on
			//TMR3 with async external input//
			//Need to know where in the SRAM we are//
			//setup a external counter on C0 to track the SRAM address (/4 prescaler)
			RPINR6=11; // RP11   Timer3 External Clock Input T3CKI RPINR6 T3CKR<4:0>
			//setup T3
			//16bit timer
			// /4 prescaler
			T3CON=0b10100100; //0b10 16 bit 4xprescaler
			//clear to sync to SRAM internal address
			TMR3H=0;
			TMR3L=0;
			T3CON|=0b1;//enable the counter		

			//SAMPLE COUNTER: counts samples after trigger, off until trigger
			//TMR1 with async external input//	
			//timer 1 is fixed on RP11/C0
			T1CON=0b10100100; //4x prescaler
			//preload timer1 to interrupts after samples_delay
			samples_delay=0x10000-samples_delay;
			TMR1H=((samples_delay>>8)&0xff);
			TMR1L=(samples_delay&0xff);
			//use CCP2 to compare to desired count and interrupt??

			//CLOCK SOURCE: PWM or 20MHz oscillator//
			//start the clock source
			//this is the 20MHz external clock
			//OR PWM from PIC pin RC0/RP11
			if(clock==EXT_OSC){//use 20MHz OSC
				TRISC|=(0b1);//disable PIC->SRAM clock pin
				LATC&=(~0b10000000); //lower OSC buffer OE, connect OSC to the SRAM clock pins
			}else{//use PIC PWM (setup during configuration)
				TRISC&=(~0b1); //PWM to output
				LATC&=(~0b1); //PWM to ground
				RPOR11= 14; // PWM A to RP11
				T2CON|=0x04;//start PWM with settings
			}

//
//
//	TRIGGER 
//
//
			//service USB during trigger pause on timer 4 low priority interrupt
			//IPR3bits.TMR4IP=0; //low priority
			//PIE3bits.TMR4IE=1; //enable
			//PIR3bits.TMR4IF=0; //clear the flag
			//T4CON=0b00000110; //on with 16 prescaler

			if(trigger==TRUE){
				//clear pin interrupts and enable
				//interrupt will start the sample counter
	             INTCONbits.INT0IF=0;
	             INTCON3bits.INT1IF=0;
	             INTCON3bits.INT2IF=0;
	             INTCON3bits.INT3IF=0;
				INTCONbits.GIEL = 1;
				INTCONbits.GIEH = 1;
			}else{
				//jump straight to starting the sample counter
				trigger=TRUE;
				INTCONbits.GIEL = 1;
				INTCONbits.GIEH = 1;
				//start sample counter
				PIR1bits.TMR1IF=0;
				PIE1bits.TMR1IE=1;
				T1CON|=0b1;
			}
		
//
//
//	CAPTURE
//
//
			//wait for capture to finish
			while(trigger){usbservice();}

			//MOVED TO INTERRUPT
			//disable address tracking counter
			//T3CON&=(~0b1);
			//raise CS to end write to SRAM
			//hal_sram_end_capture(); 

//
//
//	CLEANUP
//
//

			//end USB service interrupts
			//T4CON=0b00000010; //turn off USB service timer4
			//PIE3bits.TMR4IE=0;

			//disable all interrupts
			INTCONbits.GIEL = 0;
			INTCONbits.GIEH = 0;

			//disable external clock
			LATCbits.LATC7=1; 	//disable EXT_OSC buffer

			//disable PWM
			T2CON&=(~0x04);		//disable PWM clock
			RPOR11= 0; 			// RP11 to 0
			
			//buffer inputs disabled so the PIC an take charge		
			LATBbits.LATB5=1; //hal_logicshrimp_BufferDisable();

			//restore uC clock to output
			LATCbits.LATC0=0; //clock start low
			TRISCbits.TRISC0=0; //uC clock out to output

			//ARM LED off
			LATCbits.LATC6=0; //hal_logicshrimp_setLed(PORT_OFF);

//
//
//			DUMP
//
//
//			
			//get the current SRAM address
			addl=TMR3L;
			addh=TMR3H;

			//move to a 16bit variable
			add16=addh;
			add16=(add16<<8);
			add16|=addl;

			//find the start location to read back the desired number of samples
			add16=add16-((samples_read));//samples_read is 4bit count, so is add16 (each bit is 4 samples)
										//this preserves the rollover in counters and variables

			//adjust the 4samples/bit of the timer to 8samples/byte address of the SRAM
			add16=add16>>1;//divide by 2

			//write the SRAM command to read from the beginning
			hal_sram_setup_dump((add16>>8), (add16&0xff));

			//adjust sample size to actual bits (the value given by SUMP is /4)
			samples_read=(samples_read*4);//multiply by 4 to find actual number of samples to dump

			//loop untill all is read
			while(1){
				usbservice();
				if(USBUSARTIsTxTrfReady()){

					static u8 USBWriteCount;
					USBWriteCount=0;

					//each loop reads one sample from the four channels and places it in one byte
					for(i=0; i<32; i++){

						SCLK=PORT_ON; //clock up
						Nop(); //delay

						UsbFifoBufferArray[USBWriteCount]= PORTA & 0b1111; //get the lower 4 bits of PORTA

						SCLK=PORT_OFF; //clock down
	
						USBWriteCount++;//increment byte counter

						samples_read--;//decrement samples remaining
						if(samples_read==0) break;//send 64/128/512/1024 samples exactly! break at the end of samples
					}
					
					putUnsignedCharArrayUsbUsart(UsbFifoBufferArray,USBWriteCount);//send this load to USB
				}
				if(samples_read==0)break; //send 64/128/512/1024 samples exactly! break at the end of samples
			}

			//set_all_cs(PORT_ON); // cs low
			LATBbits.LATB4=1;//raise CS to end read
			LATCbits.LATC2=1;//CS
			LATCbits.LATC1=1;//CS
			LATAbits.LATA5=1;//CS
//
//
// CLEAR SRAM
//
//
//this step is to help with debugging. It clears the contents of the SRAMs after a capture
			//SRAM SETUP: setup the SRAM for record
			hal_sram_parallelInit(); //unlocks, verifies settings
			hal_sram_setup_capture();//setup write,

			LATB|=0b0000;//fill SRAM with 0x00

			TRISC|=(0b1);//disable PIC->SRAM clock pin
			LATC&=(~0b10000000); //lower OSC buffer OE, connect OSC to the SRAM clock pins

			for(add16=0; add16<16000; add16++){usbservice();} //pause
			
			//disable external clock
			LATCbits.LATC7=1; 	//disable EXT_OSC buffer

			//restore uC clock to output
			LATCbits.LATC0=0; //clock start low
			TRISCbits.TRISC0=0; //uC clock out to output
			break;
		default://long command
			command[0]=inByte;//store first command byte
			command[1]=waitforbyte();
			command[2]=waitforbyte();
			command[3]=waitforbyte();
			command[4]=waitforbyte();
			switch(command[0]){
		
				case SUMP_TRIG: //setup edge interrupt for triggers
                // INT0  - PPS Config not required
                RPINR1=4; // INT1
                RPINR2=5; // INT2
                RPINR3=6; // INT3

                INTCONbits.INT0IE=0;
                INTCON3bits.INT1IE=0;
                INTCON3bits.INT2IE=0;
                INTCON3bits.INT3IE=0;
				
				if(command[1] & 0b1000) INTCON3bits.INT3IE=1;
				if(command[1] & 0b100)  INTCON3bits.INT2IE=1;
				if(command[1] & 0b10)  	INTCON3bits.INT1IE=1;
				if(command[1] & 0b1) 	INTCONbits.INT0IE=1;

	           INTCONbits.INT0IF=0;
	           INTCON3bits.INT1IF=0;
	           INTCON3bits.INT2IF=0;
	           INTCON3bits.INT3IF=0;

				command[1]&=(~0b11110000);
				if(command[1]==0){
					trigger=FALSE;
				}else{
					trigger=TRUE;
				}
				
				break;
				case SUMP_TRIG_VALS:
                
                //select the edge
                INTCON2bits.INTEDG0=0;
                INTCON2bits.INTEDG1=0;
                INTCON2bits.INTEDG2=0;
                INTCON2bits.INTEDG3=0;

                if(command[1] & 0b1)INTCON2bits.INTEDG0=1;
                if(command[1] & 0b10)INTCON2bits.INTEDG1=1;
                if(command[1] & 0b100)INTCON2bits.INTEDG2=1;
                if(command[1] & 0b1000)INTCON2bits.INTEDG3=1;
				break;
				case SUMP_FLAGS:
				/*
				sumpPadBytes=0;//if user forgot to uncheck chan groups 2,3,4, we can send padding bytes
				if(sumpRX.command[1] & 0b100000) sumpPadBytes++;
				if(sumpRX.command[1] & 0b10000) sumpPadBytes++;
				if(sumpRX.command[1] & 0b1000) sumpPadBytes++;
				break;
				*/
				break;
				case SUMP_CNT:
				samples_read=command[2];
				samples_read<<=8;
				samples_read|=command[1];
				samples_read=(samples_read+1);
				//constrain to 256K
				//if(samples_read>LA_SAMPLE_SIZE) samples_read=LA_SAMPLE_SIZE;

				samples_delay=command[4];
				samples_delay<<=8;
				samples_delay|=command[3];
				samples_delay=(samples_delay+1);
				//constrain to 256K
				//if(samples_delay>LA_SAMPLE_SIZE) samples_delay=LA_SAMPLE_SIZE;
				break;
				case SUMP_DIV:
				divider=command[3];
				divider<<=8;
				divider|=command[2];
				divider<<=8;
				divider|=command[1];
				divider++;
		
				//setup clock source -
				//20mhz direct from OSC
				//0-Xmhz with PIC PWM
				clock=INT_PWM;
				if(divider<=5){
					clock=EXT_OSC;
				}else if(divider<=(100/12)){ //8.333=12mhz
					PR2=0b00000000;
					T2CON=0b00000100;
					CCPR1L=0b00000000;
					CCP1CON=0b00011100;
				}else if(divider<=(100/6)){//16.66=6mhz
					PR2=0b00000001;
					T2CON=0b00000100;
					CCPR1L=0b00000000;
					CCP1CON=0b00111100;
				}else if(divider<=(100/4)){
					PR2=0b00000010;
					T2CON=0b00000100;
					CCPR1L=0b00000001;
					CCP1CON=0b00011100;
				}else if(divider<=(100/3)){
					PR2=0b00000011;
					T2CON=0b00000100;
					CCPR1L=0b00000001;
					CCP1CON=0b00111100;
				}else if(divider<=(100/2)){
					PR2=0b00000101;
					T2CON=	0b00000100;
					CCPR1L=0b00000010;
					CCP1CON=0b00111100;
				}else if(divider<=(100/1)){
					PR2=0b00001011;
					T2CON=0b00000100;
					CCPR1L=0b00000101;
					CCP1CON=0b00111100;
				}else if(divider<=(200)){//500khz
					PR2=0b00010111;
					T2CON=0b00000100;
					CCPR1L=0b00001011;
					CCP1CON=0b00111100;
				}else if(divider<=(500)){//200khz
					PR2=0b00111011;
					T2CON=0b00000100;
					CCPR1L=0b00011101;
					CCP1CON=0b00111100;
				}else if(divider<=(1000)){//100khz
					PR2=0b01110111;
					T2CON=0b00000100;
					CCPR1L=0b00111011;
					CCP1CON=0b00111100;
				}



		
				//convert from SUMP 100MHz clock to our 12MIPs
				//l=((l+1)*16)/100;
				//l=((l+1)*4)/25;
		
				//adjust downwards a bit
				//if(l>0x10)
				//	l-=0x10;
				//else //fast as possible
				//	l=1;
		
				//setup PR register
				//PR5=(l>>16);//most significant word
				//PR4=l;//least significant word
		
				break;
			}
		}
	}
	CDCTxService();
}

//}//end main

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
void usbservice(){
	USBDeviceTasks(); 
	CDCTxService();
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

	hal_logicshrimp_pinsetup();

	RCONbits.IPEN=1; //enable interrupt priority
	INTCONbits.GIEL = 0;
	INTCONbits.GIEH = 0;

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


#endif

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
void InterruptHandlerLow(void){
	if(PIR3bits.TMR4IF && PIE3bits.TMR4IE){
		usbservice();
		PIR3bits.TMR4IF=0;	
	}
	INTCONbits.GIEL = 1;
}

//We didn't use the low priority interrupts, 
// but you could add your own code here
#pragma interrupt InterruptHandlerHigh
void InterruptHandlerHigh(void){

	if(PIR1bits.TMR1IF && PIE1bits.TMR1IE){
		//disable address tracking counter
		T3CON&=(~0b1);
		
		//clean up pins from capture settings
		//hal_sram_end_capture(); 
		LATBbits.LATB4=1;//raise CS to end write to SRAM
		LATCbits.LATC2=1;//CS
		LATCbits.LATC1=1;//CS
		LATAbits.LATA5=1;//CS

		//turn off timer1
		PIE1bits.TMR1IE=0;
		PIR1bits.TMR1IF=0;
		T1CON&=(~0b1);
		
		//clear trigger flag so main loop continues
		trigger=FALSE;
	}else {
		//start sample counter
		PIE1bits.TMR1IE=1;
		PIR1bits.TMR1IF=0;
		T1CON|=0b1;

		//disable any change interrupts (combine 1-3...)
        INTCONbits.INT0IE=0;
        INTCON3bits.INT1IE=0;
        INTCON3bits.INT2IE=0;
        INTCON3bits.INT3IE=0;

		//clear any change interrupt flags
        INTCONbits.INT0IF=0;
        INTCON3bits.INT1IF=0;
        INTCON3bits.INT2IF=0;
        INTCON3bits.INT3IF=0;
	}

	INTCONbits.GIEH = 1;

}

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


