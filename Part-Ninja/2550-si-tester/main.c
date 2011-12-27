#include "globals.h"
#include "config.h"
static void init(void);
#define LOW 0
#define HIGH 1
void R_680 (u8 Pin, u8 State);
void R_470K (u8 Pin, u8 State);
void R_0 (u8 Pin, u8 State);
void Delay_MS(u8 s);
u16 ReadADC(u8 Pin);
void checkpins(u8 HighPin, u8 LowPin, u8 TristatePin);
void DischargePin(u8 Pin, u8 State);
void HiZ(u8 Pin);
#define PART_NONE 0
#define PART_TRANSISTOR 1
#define PART_FET 2
#define PART_MODE_NONE 0
#define PART_MODE_NPN 1
#define PART_MODE_PNP 2
u8 PartType, PartMode, RepeatDetect;
u16 hfe[2], vBE[2];
u8 c,b,e;
#pragma code
void main(void){  
	unsigned char i,cmd, param[9], tmp; 
	unsigned long lhfe;
	//unsigned char t[]={"Hello World"};

    init();			//setup the crystal, pins

	while(1){
		PartType=0;
		PartMode=0;
		RepeatDetect=0;
		checkpins(0, 1, 2); //CBE npn --
		checkpins(0, 2, 1); //CBE npn
		checkpins(1, 0, 2); //CBE npn --
		checkpins(1, 2, 0); //CBE npn
		checkpins(2, 0, 1); //CBE npn
		checkpins(2, 1, 0); //CBE npn
		if(PartType==PART_TRANSISTOR){
			if(RepeatDetect==0){
				hfe[1] = hfe[0];
				vBE[1] = vBE[0];
			}

			if(hfe[0]>hfe[1]){
				hfe[1] = hfe[0];
				vBE[1] = vBE[0];
				tmp = c;
				c = e;
				e = tmp;
			}
			if(PartMode == PART_MODE_NPN) {
				tmp=tmp;
			} else {
				tmp=tmp;
			}

			lhfe = hfe[1];

			lhfe *= (((unsigned long)4700 * 100) / (unsigned long)680);	//Verhältnis von High- zu Low-Widerstand

			if(vBE[1]<11) vBE[1] = 11;
			lhfe /= vBE[1];
			hfe[1] = (unsigned int) lhfe;
		}
	}


}//end main

u16 ReadADC(u8 Pin){
	u16 i;
	//setup ADC
	ADCON2=0b10101110; //R justified result, 12TAD time 101, FOSC/64 110 
	//Analog inputs
	//A0-2 are analog monitors
	ADCON1=0b1100; //internal Vrefs, A0-2 analog
	//set channel
	ADCON0=0;
	ADCON0|=((Pin)<<2);//enable the channel
	ADCON0|=0b1;//ADON=1
	//take reading
	Delay_MS(1);
	ADCON0|=0b10; //GO/!DONE=1
	while(ADCON0&0b10);
	//return reading
	//i=ADRESH;
	//i=i<<8;
	//i|=ADRESL;
	return ADRES;
}

void Delay_MS(u8 ms){
	static u16 timer;
	u8 i;

	for(i=0; i<ms; i++){
		timer=6000;
		while(timer--);
	}

}




void checkpins(u8 HighPin, u8 LowPin, u8 TristatePin){
	u16 InitialADC, HighPinADC,TristatePinADC, LowPinADC;

	//LowPin 680ohm R to ground
	R_680(LowPin, LOW);
	//HighPin to output/high
	R_0(HighPin, HIGH);

	Delay_MS(5);

	DischargePin(TristatePin, LOW); //for MOSFETs	

	//Read ADC on LowPin
	InitialADC=ReadADC(LowPin);

	//if ADC >= 200{ //discharge other way for P MOSFETs
		//discharge; 
		//read ADC again;
	//}

	//if(ADC>19) {
	// N-JFET, N-MOSFET
	//P-JFET P-MOSFET
	//}

	//reset pins
	//LowPin 680ohm R to ground
	R_680(LowPin, LOW);
	//HighPin to output/high
	R_0(HighPin, HIGH);

	if(InitialADC<200){
		/****************************************/
		//
		//	PNP tests
		//	If this PNP:
		// 	then collector should be high when base ground and emitter at +5
		//
		/*****************************************/
		//C, B low through 680R, E high
		R_680(TristatePin, LOW); //base to ground through 680R
		Delay_MS(2);
		
		//read LowPin ADC
		//PNP allows current from Emitter to Collector and should be high
		LowPinADC=ReadADC(LowPin);

		if(LowPinADC>700){//PHP active, current flowing to Emitter
			HiZ(TristatePin);//Base HiZ
			R_470K(TristatePin, LOW); //Base to 470K low
			
			Delay_MS(10);

			//read LowPin ADC for hfe
			LowPinADC=ReadADC(LowPin);
			
			//read TristatePin ADC, see if base is transistor (>2volts) or FET (<2volts)
			//save value for uBE too
			TristatePinADC=ReadADC(TristatePin);
			if((PartType==PART_TRANSISTOR) || (PartType==PART_FET))RepeatDetect=1;
			hfe[RepeatDetect]=LowPinADC;
			vBE[RepeatDetect]=TristatePinADC;

			//if(PartFound != PART_THYRISTOR) {
			if(TristatePinADC>200){ //high base voltage is transistor
				//PNP transistor found
				PartType=PART_TRANSISTOR;
				PartMode=PART_MODE_PNP;
			}else{ //low base voltage is MOSFET
				//MOSFET and tests
				PartType=PART_FET;
				PartMode=PART_MODE_PNP;
			}
			c=LowPin;
			e=HighPin;
			b=TristatePin;

		}

		/****************************************/
		//
		//	NPN tests
		//	If this NPN:
		// 	then collector should hold pullup low when base high and emitter to ground
		//
		/*****************************************/
		//B,C high through pullup, E low
		//LowPin ground
		R_0(LowPin, LOW);
		//HighPin and TristatePin 680R high
		R_680(HighPin, HIGH);
		R_680(TristatePin, HIGH);
		
		//read HighPin ADC to see if NPN holds the 680R pullup low...
		HighPinADC=ReadADC(HighPin);

		if(HighPinADC<500){//NPN grounds the weak pullup
			//THYRISTOR test

			/***************************************/
			//	Transistor or MOSFET test
			//	Transistor is current controlled, the base voltage after the resistor will be ~0.6-1volts
			//	MOSFET is voltage controlled, the base voltage after the resistor will be close to the supply (5volts)
			/***************************************/
			//TristatePin 470K high
			R_470K(TristatePin, HIGH);				
			//read HighPin ADC for hfe
			HighPinADC=ReadADC(HighPin);
			
			//read TristatePin ADC, see if base is transistor (<2volts) or FET (>2volts)
			//save value for uBE too
			TristatePinADC=ReadADC(TristatePin);
			if((PartType==PART_TRANSISTOR) || (PartType==PART_FET))RepeatDetect=1;
			hfe[RepeatDetect]=1023-HighPinADC;
			vBE[RepeatDetect]=1023-TristatePinADC;

			if(TristatePinADC<500){ //low base voltage is transistor
				//NPN transistor found
				PartType=PART_TRANSISTOR;
				PartMode=PART_MODE_NPN;
			}else{ //high base voltage is MOSFET
				//MOSFET and tests
				PartType=PART_FET;
				PartMode=PART_MODE_NPN;
			}
			c=HighPin;
			e=LowPin;
			b=TristatePin;
		}//adc<500
	}//adc < 200	
	//NON transistor tests
		//Diode and internal part diodes
		
		//Resistors
	
	HiZ(HighPin);
	HiZ(LowPin);
	HiZ(TristatePin);

}

void R_680 (u8 Pin, u8 State){
	u8 R0p, R680p, R470Kp;

	R0p=((1<<Pin)<<3);
	R680p=((1<<Pin)<<3);
	R470Kp=(1<<Pin);
	
	//R0 to input
	R0_DIR|=R0p;
	//470K to input
	R470K_DIR|=R470Kp;
	//680R to direction
	if(State==LOW){
		R680_OUT&=(~(R680p));
	}else{
		R680_OUT|=((R680p));
	}
	//680R to output
	R680_DIR&=(~(R680p));

}
void R_470K (u8 Pin, u8 State){
	u8 R0p, R680p, R470Kp;

	R0p=((1<<Pin)<<3);
	R680p=((1<<Pin)<<3);
	R470Kp=(1<<Pin);

	//R0 to input
	R0_DIR|=R0p;
	//R680 to input
	R680_DIR|=(R680p);
	//470K to direction
	if(State==LOW){
		R470K_OUT&=(~(R470Kp));
	}else{
		R470K_OUT|=(R470Kp);
	}
	//470K to output
	R470K_DIR&=(~(R470Kp));
}
void R_0 (u8 Pin, u8 State){
	u8 R0p, R680p, R470Kp;

	R0p=((1<<Pin)<<3);
	R680p=((1<<Pin)<<3);
	R470Kp=(1<<Pin);

	//680R to input
	R680_DIR|=(R680p);
	//470K to input
	R470K_DIR|=(R470Kp);
	//0R to direction
	if(State==LOW){
		R0_OUT&=(~(R0p));
	}else{
		R0_OUT|=(R0p);
	}
	//0R to output
	R0_DIR&=(~(R0p));
}

void HiZ(u8 Pin){
	u8 R0p, R680p, R470Kp;

	R0p=((1<<Pin)<<3);
	R680p=((1<<Pin)<<3);
	R470Kp=(1<<Pin);

	//R0 to input
	R0_DIR|=R0p;
	//680R to input
	R680_DIR|=(R680p);
	//470K to input
	R470K_DIR|=(R470Kp);

}

	//discharge the gate of a MOSFET gate, doide detection
	//0 = ground (N chanel FET), 1= Vcc (P-Channel FET)
void DischargePin(u8 Pin, u8 State) {

	R_680 (Pin, State); //R680 to ground
	Delay_MS(10); //wait for discharge
	HiZ(Pin); //return to input/HiZ
}

static void init(void){
	unsigned int cnt = 2048;
	
	//all pins digital
	//disable some defaults
    ADCON1 |= 0b1111;   	//all pins digital
	CVRCON=0b00000000;

	//make sure everything is input (should be on startup, but just in case)
	TRISA=0xff;
	TRISB=0xff;
	TRISC=0b11111111; 

	//on 18f24j50 we must manually enable PLL and wait at least 2ms for a lock
	//OSCTUNEbits.PLLEN = 1;  //enable PLL
	//while(cnt--); //wait for lock

}