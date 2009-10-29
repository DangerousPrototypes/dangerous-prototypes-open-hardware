#include "Compiler.h"
#include "HardwareProfile.h"
#include "shiftbrite.h"

#define RGB_LAT LATBbits.LATB7
#define RGB_CLK LATCbits.LATC7 //rx
#define RGB_DAT LATCbits.LATC6 //tx
#define SBDELAY 255

void SetupShiftBrite(void){
	unsigned char i;

	//setup pins
	TRISBbits.TRISB7=0;
	RGB_LAT=0;
	TRISCbits.TRISC6=0;
	RGB_DAT=0;
	TRISCbits.TRISC7=0;
	RGB_CLK=0;
	LEDout();
	LEDoff();

	//give everything some time to settle
	for(i=0; i<20; i++){
		delay(255);
	}

	//setup chip
	writebyte(0x47);
	writebyte(0xf1);
	writebyte(0xfc);
	writebyte(0x7f);
	//latch high and low
	RGB_LAT=1;
	delay(SBDELAY);
	RGB_LAT=0;

	shiftBriteColor(0x0000, 0x0000, 0x0000);

}

#define STORM_COLOR() shiftBriteColor(0x03FF, 0x0000, 0x0000)
#define STORM_CLEAR() shiftBriteColor(0x0000, 0x0000, 0x0000)
//#define STORM_CLEAR() shiftBriteColor(0x03ff, 0x03ff, 0x03ff)

void storm(){
	unsigned char i;

	STORM_CLEAR();//off
	delay(255);

	for(i=0; i<20; i++){
		STORM_COLOR();
		delay(255);
		delay(255);
		STORM_CLEAR();
		delay(255);
		delay(255);
		delay(255);
		STORM_COLOR();
		delay(255);
		STORM_CLEAR();
		delay(255);
		STORM_COLOR();
		delay(255);
		delay(255);
		delay(255);
		delay(255);
		STORM_CLEAR();
		delay(255);
	}
}

void rgbtest(void){
	while(1){
		//send colors
		shiftBriteColor(0x3FF, 0x3ff, 0x3ff);
		LEDon();
		delay(255);
		LEDoff();

		shiftBriteColor(0x3FF, 0, 0);
		LEDon();
		delay(255);
		LEDoff();	

		shiftBriteColor(0, 0x3FF, 0);
		LEDon();
		delay(255);
		LEDoff();

		shiftBriteColor(0,0,0x3FF);
		LEDon();
		delay(255);
		LEDoff();
	}
}

//send 10bit color values
void shiftBriteColor(unsigned int r, unsigned int g, unsigned int b){

	//start latch low
	RGB_LAT=0;

	writeBit(0); //color set command begin 00
	writeBit(0);
	write10Bits(b);	//shift out 
	write10Bits(r);	//shift out 
	write10Bits(g);	//shift out 


	//latch high and low
	RGB_LAT=1;
	delay(SBDELAY);
	RGB_LAT=0;

}

void write10Bits(unsigned int i){
	volatile unsigned char c;

	//for each bit in the byte
	for(c=0; c<10; c++){
		
		//set data pin state
		if(i & 0b1000000000)
			RGB_DAT=1;
		else
			RGB_DAT=0;
		
		delay(SBDELAY);
		//clock tick
		RGB_CLK=1;
		delay(SBDELAY);
		RGB_CLK=0;		
	
		//shift bits
		i=i<<1;
	}

}

void writebyte(unsigned char c){
	volatile unsigned char i;

	//for each bit in the byte
	for(i=0; i<8; i++){
		
		//set data pin state
		if(c & 0b10000000)
			RGB_DAT=1;
		else
			RGB_DAT=0;
		
		delay(SBDELAY);
		//clock tick
		RGB_CLK=1;
		delay(SBDELAY);
		RGB_CLK=0;		
	
		//shift bits
		c=c<<1;
	}

}

void writeBit(unsigned char c){

	//set data pin state
	RGB_DAT=c;
	delay(SBDELAY);

	//clock tick
	RGB_CLK=1;
	delay(SBDELAY);
	RGB_CLK=0;		

}

volatile void delay(unsigned char c){
	volatile unsigned char i;
	
	for(i=0; i<c; i++){
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
		Nop();
	}
}