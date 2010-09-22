/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
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
//
//	Other options:
//	We also changed the default usb_descriptors.c to fit our needs. 
//	You may need to double check these settings depending on your USB stack version.
//	*configDescriptor1[] remove _SELF from the attributes
//	*manufacturer and product string descriptors
#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818


//includes config fuses
#include "config.h"

//USB stack
#include "globals.h"



//
//	This variable tracks the current IR Toy mode
//
#pragma udata
static enum _mode { 
	IR_DECODER=0, //IRMAN IR RC decoder
	IR_SUMP, //SUMP logic analyzer
	IR_IO, //IR input output mode
	IR_S, //IR Sampling mode
	IR_REFLECT, // IR Reflection mode
	USB_UART
	//IR_RECORDER //record IR signal to EEPROM, playback
} mode=IR_DECODER; //mode variable tracks the IR Toy mode

struct _irtoy irToy;

void SetupBoard(void);
void InterruptHandlerHigh();
void InterruptHandlerLow();
unsigned char SelfTest(void);
void version(void);

#pragma code
void main(void){   		
	static unsigned char inByte, usbcfg;
	volatile static unsigned int cnt;

	SetupBoard(); 	//setup the hardware, USB
	usbbufflush();	//flush USB input buffer system
	SetupRC5(); 	//start in RC decoder mode

#if 0 //startup in a mode to help with development debugging
	T2IE=0; 	//disable any Timer 2 interrupt
	IRRX_IE=0; 	//enable RX interrupts for data ACQ
	mode=IR_S;
	irssetup();
#endif



	//
	//	Never ending loop services each task in small increments
	//
 	USBDeviceInit();		//initialize USB (usb_device.c)



	while(1){


        USBDeviceTasks(); ////service USB tasks	
	    //CDCTxService(); //service the CDC stack
		//continue;
		//DETACHED_STATE 
		//ATTACHED_STATE 
		//POWERED_STATE 
		//DEFAULT_STATE 
		//ADDRESS_STATE 
		//CONFIGURED_STATE
		//LED OFF if computer is powered off or standby
		if( (USBDeviceState < ATTACHED_STATE) || (USBSuspendControl==1) ){
			LED_LAT &= (~LED_PIN);
			continue;
		//LED ON when being configured
		}else if( (USBDeviceState < CONFIGURED_STATE) ){
			LED_LAT |= LED_PIN;
			usbcfg=1;
			continue;
		}else if (usbcfg){
			//LED OFF again when connected and ready, only do it once
			LED_LAT &= (~LED_PIN);
			usbcfg=0;//clear flag
		}



		switch(mode){ //periodic service routines
			case IR_SUMP:
				//see if there's byte to be fetched
				usbbufservice(); //service USB buffer system		
				if(usbbufgetbyte(&inByte)==1){//process any command bytes
					SUMPlogicCommand(inByte);
				}
				
				if(SUMPlogicService()==0xff){//increment dump state machine
					SetupRC5();
					mode=IR_DECODER; //exit if done dumping
				}
				break;
			case IR_IO:			//increment IR_IO module dump state machine
				if(irIOservice()!=0){//IRIO exit
					SetupRC5();
					mode=IR_DECODER; //exit if done dumping
				}
				break;
			case IR_S:
				if(irsService()!=0){//IRIO exit
					SetupRC5();
					mode=IR_DECODER; //exit if done dumping
				}
				break;
			case IR_REFLECT:
				if(IrReflectService()!=0)
					{
					SetupRC5();
					mode=IR_DECODER; //exit if done dumping
					}
				break;

			case USB_UART:
				if(Usb2UartService()!=0)
					{
					SetupRC5();
					mode=IR_DECODER; //exit if done dumping
					}
				break;

			//case IR_RECORDER: 				//save IR wave to EEPROM for playback
			//case IR_DECODER:
			default:
				//LED_LAT &= (~LED_PIN); 			//disable LED once connected and in RC decoder mode
				
				ProcessIR();   					//increment IR decoder state machine

				usbbufservice(); 				//service USB buffer system
	
				if(usbbufgetbyte(&inByte)==0)break; //get a single byte from the USB buffer

				switch(inByte){
					case 0 : //SUMP clear
					case 1 : //SUMP run
					case 2 : //SUMP ID
						//setup IR SUMP mode
						IRRX_IE=0; 				//disable RX interrupts
						T2IE=0; 				//disable any Timer 2 interrupt
						mode=IR_SUMP; 			//put IR Toy in IR_SUMP mode
						SUMPlogicCommand(inByte); 	//pass this command SUMP
						break;
					case 'r': //IRMAN decoder mode
					case 'R':
						SetupRC5();
						mode=IR_DECODER;
						IRmanString(); //send OK for IRman mode
						break;
					case 'S':		//IRIO RXTX mode
					case 's':
						T2IE=0; 	//disable any Timer 2 interrupt
						IRRX_IE=0; 	//enable RX interrupts for data ACQ
						mode=IR_S;
						irsSetup();
						break;
					case 'X':		//IRIO RXTX mode
					case 'x':
						T2IE=0; 	//disable any Timer 2 interrupt
						IRRX_IE=0; 	//enable RX interrupts for data ACQ
						mode=IR_IO;
						irIOsetup();
						break;

					case 'E':
					case 'e':
						mode=IR_REFLECT;
						IrReflectSetup();
						break;

					case 'U':
					case 'u':
						mode=USB_UART;
						Usb2UartSetup();
						break;

					case 'T':
					case 't'://self test
						IRRX_IE=0; 				//disable RX interrupts
						T2IE=0; 				//disable any Timer 2 interrupt

						inByte=SelfTest(); //run the self-test

					  	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
							if(inByte>0x30){
								LED_LAT &=(~LED_PIN); //LED off
								irToy.usbOut[0]='F';//answer fail
								irToy.usbOut[1]='A';
								irToy.usbOut[2]=((inByte&0b1100)>>2)+0x30; //frequency detector error code
								irToy.usbOut[3]=(inByte&0b11)+0x30;			//receiver error code
							}else{
								version();
							}
							putUnsignedCharArrayUsbUsart(irToy.usbOut,4);
						}
		
						break;
					case 'V':
					case 'v'://self test
					  	if( mUSBUSARTIsTxTrfReady() ){ //it's always ready, but this could be done better
							version();
						}
		
						break;
					case '$'://bootloader jump
						BootloaderJump();
						break;
				}//switch(c)
				break;
		}//switch(mode)

	    CDCTxService(); //service the CDC stack
    }//end while
}//end main

//exits with IR LED on for visual inspection with a camera 
unsigned char SelfTest(void){
	unsigned char err=0x30; //error flag starts with ASCII 0
	unsigned int cnt;

	#define ERROR_RXPULLUP 		0b1
	#define ERROR_RXACT 		0b10
	#define ERROR_FREQPULLUP	0b100
	#define ERROR_FREQACT		0b1000

	IRRX_TRIS |=IRRX_PIN; //ir to input
	IRTX_LAT  &=(~IRTX_PIN);//TX LED off
	IRTX_TRIS &=(~IRTX_PIN);						
	CCP1CON=0;
	T2CON=0;
	cnt=10000;
	while(cnt--);
	if(!(IRRX_PORT & IRRX_PIN)) err|=ERROR_RXPULLUP; //test IR RX pullup, should be high

	if(irToy.HardwareVersion==2){
		if(IRFREQ_CAP==0) err|=ERROR_FREQPULLUP; //test IR Frequency detector pullup, should be high

		//turn IR LED solid on to test frequency detector
		IRTX_TRIS &=(~IRTX_PIN); //output
		IRTX_LAT|=IRTX_PIN; //LED on
		
		//give a little delay
		cnt=1000;
		while(cnt--);
		
		//test IR Frequency detector, should now be off
		if(IRFREQ_CAP==1) err|=ERROR_FREQACT; 
		
		//LED back off
		IRTX_LAT&=(~IRTX_PIN); 
	}

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
	//IRTX_TRIS &=(~IRTX_PIN); //output
	//IRTX_LAT&=(~IRTX_PIN); //start low
	T2IF=0;//clear the interrupt flag
	T2IE=0; //disable interrupts
	PR2 = 0b01010010 ; //82
	T2CON = 0b00000101 ;
	CCPR1L = 0b00101001 ;	//upper 8 bits of duty cycte
	CCP1CON = 0b00011100 ; //we leave this on for visual inspection (5-4 two LSB of duty, 3-0 set PWM)

	cnt=40000;
	while(cnt--);

	if(IRRX_PORT & IRRX_PIN) err|=ERROR_RXACT;//IR LED should activate RX

	return err;
}


//
//
// Initial configuration
//
//
void SetupBoard(void){
	unsigned char i;
	unsigned int cnt;

	//disable some defaults
    ADCON1 |= 0b1111;   	//all pins digital
	CVRCON=0b00000000;

    USBDeviceInit();		//initialize USB (usb_device.c)

	//
	// VERSION DETECT
	//
	//test IR_FREQ pin to see if this is v1 or v2
	//CAP and EC to ground (C0 C1)
	IRFREQ_CAP_LAT&=(~IRFREQ_CAP_PIN);//ground
	IRFREQ_EC_LAT&=(~IRFREQ_EC_PIN);//ground
	IRFREQ_CAP_TRIS&=(~IRFREQ_CAP_PIN);//output
	IRFREQ_EC_TRIS&=(~IRFREQ_EC_PIN);//output

	PORTB=0; //all ground
	TRISB=0b11101011;		//RB2 and RB4 to output/ground to prevent dualing pullups
	IRRX_PULLUP=0;//enable(0) RB pullups

	cnt=10;
	while(cnt--);

	//on v1 the pullups just hold RB1 high (INT==1)
	//on v2 RB1 and C0/C1 are connected INT will be 0
	if(IRFREQ_INT==1){
		irToy.HardwareVersion=1;
	}else{
		irToy.HardwareVersion=2;
	}

	//cleanup
	IRRX_PULLUP=1;//disable(1) RB pullups
	TRISB=0xff;	//all inputs
	IRFREQ_PIN_SETUP(); //all inputs

	//
	// SETUP
	//
	//setup IR LED for IR TX
	IRTX_TRIS&=(~IRTX_PIN);	//digital OUTPUT (must ground transistor)
	IRTX_LAT&=(~IRTX_PIN); 	//output to ground

	//visual indicator LED config
	LED_LAT |=LED_PIN; 		//start with LED ON till USB connect 
	LED_TRIS &=(~LED_PIN); 	//direction output

	//setup the timers
	CCP1CON=0;			//reset PWM registers
	CCP2CON=0;
	T1CON=0; 			//clear timer 1 control
	IPR1bits.TMR1IP=1;	//timer 1 high priority
	T2CON=0; 			//clear timer 2 control
	IPR1bits.TMR2IP=1;	//timer 2 high priority

	//setup IR RX interrupt on RB32 or RB4 (see HardwareProfile.h)
	IRRX_PULLUP=1; 	//disable port b pullups (0=enable)
	IRRX_LAT=0;		//ground
	IRRX_TRIS=0;	//output
	IRRX_TRIS|=IRRX_PIN; //direction to input
	IRRX_IF = 0;    //Reset the RB Port Change Interrupt Flag bit   
	IRRX_IE = 0;  	//startup in IR_DECODER mode, enable IR RX interrupt
	IRRX_IP = 1; 	//high priority interrupt
	#ifdef IRRX_ONINT2 	//make sure unused pin isn't going to interfere on dual connected PCBs
		IRRX_EDGE = 0; 	//falling edge interrupt on RB2
		TRISB|=0b10000; //make RB4 input so it doesn't interfere!
	#else
		TRISB|=0b100; 	//make RB2 input so it doesn't interfere!
	#endif

   	INTCONbits.GIEL = 1;//enable peripheral interrupts
   	INTCONbits.GIEH = 1;//enable interrupts
}

//
//
// Give the version number
//
//
void version(void){
	irToy.usbOut[0]='V';//answer OK
	irToy.usbOut[1]=(irToy.HardwareVersion+0x30);
	irToy.usbOut[2]=FIRMWARE_VERSION_H;
	irToy.usbOut[3]=FIRMWARE_VERSION_L;
	putUnsignedCharArrayUsbUsart(irToy.usbOut,4);
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




//
//
//	Interrupt remap chain
// 	
//
//This function directs the interrupt to 
// the proper function depending on the mode 
// set in the mode variable.
#pragma code InterruptHandlerHigh
void InterruptHandlerHigh(void){
	switch(mode){
		case IR_IO: 
			_asm goto irIOInterruptHandlerHigh _endasm //see IRIO.c
			break;
		case IR_S:
			_asm goto irsInterruptHandlerHigh _endasm //see IRIO.c
			break;			
		case IR_SUMP:
			_asm goto SUMPInterruptHandlerHigh _endasm //see SUMP.c
			break;
		case IR_DECODER:
			_asm goto IRdecoderInterruptHandlerHigh _endasm //see RCdecoder.c
			break;
		case IR_REFLECT:
			_asm goto IrReflectionInterruptHandlerHigh _endasm //see RCdecoder.c
			break;
		case USB_UART:
			_asm goto Usb2UartInterruptHandlerHigh _endasm //see RCdecoder.c
			break;
	}
}

//We didn't use the low priority interrupts, 
// but you could add your own code here
#pragma interruptlow InterruptHandlerLow
void InterruptHandlerLow(void){}

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
