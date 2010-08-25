/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
#define HARDWARE_VERSION '1'
#define FIRMWARE_VERSION_H '0'
#define FIRMWARE_VERSION_L '6'


#define SAMPLE_ARRAY_SIZE 0x0080 //0x0010
#define SAMPLE_SIZE 0x0400 //0x0080 //(SAMPLE_ARRAY_SIZE*0x0008)
struct _irtoy{
	unsigned char s[SAMPLE_ARRAY_SIZE];
	unsigned char usbIn[30];
	unsigned char usbOut[64];
	unsigned char HardwareVersion;
};

//hardware platform?
#define USBIRTOY //Dangerous Prototypes IR Toy, RX on RB4 and RB2,TX on RC2, 2550
#define IRRX_ONRB4 //force RB4 interrupt instead of INT2 on USBIRTOY
//#define HAD_USBIRC //hackaday RX on B4 only, PIC 2455

//select the correct interrupt pin depending on hardware and settings
#if defined (HAD_USBIRC) || defined (IRRX_ONRB4)// irRX B4 (25)
	#define	IRRX_LAT  LATB
	#define IRRX_TRIS TRISB
	#define IRRX_PORT PORTB
	#define IRX PORTBbits.RB4
	#define IRRX_PIN  0b10000
	#define IRRX_IE	INTCONbits.RBIE
	#define IRRX_IF	INTCONbits.RBIF
	#define IRRX_IP INTCON2bits.RBIP
#else //use INT2 with edge trigger, schmidt buffer
	#define IRRX_ONINT2 //tells other functions we're using INT2 interrupt
	#define	IRRX_LAT  LATB
	#define IRRX_TRIS TRISB
	#define IRRX_PORT PORTB
	#define IRX PORTBbits.RB2
	#define IRRX_PIN  0b100
	#define IRRX_IE	INTCON3bits.INT2IE
	#define IRRX_IF	INTCON3bits.INT2IF
	#define IRRX_IP INTCON3bits.INT2IP
	#define IRRX_EDGE INTCON2bits.INTEDG2
#endif
#define IRRX_PULLUP INTCON2bits.RBPU //one pullup bit for all PORTB pins

#if defined (HAD_USBIRC)
	// LED C2 (13)
	#define	LED_LAT LATC
	#define LED_TRIS TRISC
	#define LED_PIN  0b100
#elif defined (USBIRTOY)
	// LED A0 (2)
	#define	LED_LAT  LATA
	#define LED_TRIS TRISA
	#define LED_PIN  0b1
	// irTX C2 (13) CCP1
	#define	IRTX_LAT  LATC
	#define IRTX_TRIS TRISC
	#define IRTX_PIN  0b100

	//
	//V2 extra hardware
	//
	//raw receiver
	//CCP pin (12/RC1)
	#define IRFREQ_CAP_LAT	LATC
	#define IRFREQ_CAP_TRIS TRISC
	#define IRFREQ_CAP_PORT PORTC
	#define IRFREQ_CAP_PIN 	0b10
	#define IRFREQ_CAP		PORTCbits.RC1
	#define IRFREQ_CAP_SETUP() PIE2bits.CCP2IE=0; T3CON=0; CCP2CON=0b00000101 //capture every rising edge (0100 = falling edge) //select timer1 for CPP2 in T3CON	
	#define IRFREQ_CAP_IE	PIE2bits.CCP2IE
	#define IRFREQ_CAP_IF	PIR2bits.CCP2IF		
	#define IRFREQ_CAP_L	CCPR2L
	#define IRFREQ_CAP_H	CCPR2H	
	#define IRFREQ_CCPxCON	CCP2CON	

	//Interrupt pin (22/RB1)
	#define IRFREQ_INT_LAT 	LATB
	#define IRFREQ_INT_TRIS TRISB
	#define IRFREQ_INT_PORT PORTB
	#define IRFREQ_INT_PIN 	0b10
	#define IRFREQ_INT 		PORTBbits.RB1

	//T1/3 external clock (11/RC0)
	#define IRFREQ_EC_LAT	LATC
	#define IRFREQ_EC_TRIS	TRISC
	#define IRFREQ_EC_PORT	PORTC
	#define IRFREQ_EC_PIN	0b1
	#define IRFREQ_EC		PORTCbits.RC0
	
	//all connected IR FREQ pin to input
	#define IRFREQ_PIN_SETUP() IRFREQ_CAP_TRIS|=IRFREQ_CAP_PIN; IRFREQ_INT_TRIS|=IRFREQ_INT_PIN; IRFREQ_EC_TRIS|=IRFREQ_EC_PIN
#endif

// RX C7 (18)
// TX C6 (17)

#define LEDoff() LED_LAT&=(~LED_PIN)
#define LEDon() LED_LAT|=LED_PIN
#define LEDout() LED_TRIS&=(~LED_PIN)
#define LEDin() LED_TRIS|=LED_PIN

#define TM0IF INTCONbits.T0IF
#define TM0IE INTCONbits.T0IE
#define TM0ON T0CONbits.TMR0ON

#define T1IF 	PIR1bits.TMR1IF
#define T1IE 	PIE1bits.TMR1IE
#define T1ON	T1CONbits.TMR1ON

#define T2IF 	PIR1bits.TMR2IF
#define T2IE 	PIE1bits.TMR2IE
#define T2ON 	T2CONbits.TMR2ON

//10us timer for TVBGONE on TIMER1 (65415)
#define T1_10usOffset() TMR1H=0xFF; TMR1L=0x9A //87

//10khz default sampling clock for IRIO on TIMER1
#define T1_OFFSET 0xFB4B //64331 preload = 10006.8kHz
#define T1_OFFSETH 0xFB //(T1_OFFSET>>8)
#define T1_OFFSETL 0x4B //(T1_OFFSET &= (~0xff00))
#define T1_10kHzOffset()  TMR1H=T1_OFFSETH; TMR1L=T1_OFFSETL

//SUMP sample period with TIMER2
#define T2_RXsampleperiod() PR2 = 150; T2CON = PRE_x4 + POST_x2 //10040.1Hz

//RC5 bit and half bit period with TIMER2
#define T2_RC5halfbitperiod() PR2=221; T2CON=PRE_x4+POST_x6 //setup to hit in the middle of next bit period
#define T2_RC5bitperiod() PR2=221; T2CON=PRE_x4+POST_x12 //full bit values from now on

//50us Timer2 settings for irS
#define T2_irS50uS() PR2=201; T2CON=POST_x3 //setup to hit in the middle of next bit period

//we don't use these, disable
#define self_power          1
#define USB_BUS_SENSE       1
    
#define BootloaderJump() _asm goto 0x16 _endasm

//TMR2 Pre- and post- scalers
#define PRE_x4 0b01
#define PRE_x16 0b11
#define POST_x2 0b1000
#define POST_x3 0b10000
#define POST_x4 0b11000
#define POST_x5 0b100000
#define POST_x6 0b101000
#define POST_x7 0b110000
#define POST_x8 0b111000
#define POST_x9 0b1000000
#define POST_x10 0b1001000
#define POST_x11 0b1010000
#define POST_x12 0b1011000
#define POST_x13 0b1100000
#define POST_x14 0b1101000
#define POST_x15 0b1110000
#define POST_x16 0b1111000
