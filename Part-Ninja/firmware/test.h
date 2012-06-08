#ifndef TEST_H
#define TEST_H

#include "globals.h"


#define LOW 0
#define HIGH 1

//////TESTING CONSTANTS/////////////////
///for easier tunning purpses//////////
//if the voltage drops by 100 high side read will be 923,low side will be 100
#define CP_HIGH 	900	//V drop for HIGH side conductivity test
#define CP_LOW  	123	//V drop for LOW side conductivity test

#define CAP_DIFF 	10	//by how much will a CAP charge over noise...
#define RES_DD 		170	//by how much will zener Vdrop change with diff resistors
#define ZENER_DD 	100	//by how much will 2 anti paraller diodes VDs differ 
#define FET_HIGH    923
#define FET_LOW     100
#define TST_DEL    	200
#define DARL_BJT    50

//Enum with the different part type names...
//CC is a common cathode double diode
//CA is a common anode -||-
typedef enum type
{ERROR=0,NFET,PFET,NMOS,PMOS,NPN,CA,PNP,CC,
	DIODE,TRIAC,SCR,CAP,RES,ZENER,DD,NPN_D,PNP_D,NOID=20,
		ERROR1,ERROR2,ERROR3,ERROR4,ERROR5,ERROR6}type;

void compInit(u8 Pin);

void initT();

//Test function...does the testing..encapsulates the whole testing process for main...
u8 testPart();
//Checks conductivity through form [A]->[B] while keeping the 3rd pin at the test state birefly before the test.
//5V--[680]-Vt-[A]-->[B]---GND, if Vt < 93% VCC it is conducting
u16 checkConduct(u8 A, u8 B,u8 test);
//runs twice through all 6 posile conductive paths between 3pins
//once while keeping the 3rd pin LOW briefly befor the test
//second while HIGH, the pin is at HiZ during the test 
u8 testConduct(u8*diff);


//called only if nC =0, so no CP were found in the r680 test...
u8 testCAP_RES();
//get Part SubSection other then Res/Cap/DD/Zener
type getPartSS(u8 diff);
//get Part SubSection if Res/Cap/DD/Zener
type getPartSS2();
//main called for further annalysis based on part subsection
u8 switchPart(type SS);

//These functions test the mosfet parts
//they return the Ron value in ohms,
//or 0 if the part is not a mosfet
u16 testNFET();
u16 testPFET();
u16 testNMOS();
u16 testPMOS();
u16 testNPN();
u16 testCA();
u16 testPNP();
u16 testCC();
u16 testDIODE();
u16 testTRIAC();
u16 testSCR();
u16 testCAP();
u16 testRES();
u16 testZENER();
u16 testDD();
u16 testNPN_D();
u16 testPNP_D();


void puts_cdc(rom char *s);
void putINT_cdc(u16 value);
void tListPrint();

//stes up the ADC module and takes a reading of the Pin
u16 ReadADC(u8 Pin);
//only sets up the ADC, for future fast acquisitions
void quickADCsetup(u8 Pin);

void Delay_MS(u8 s);

//conects the pin to state(HIGH/LOW) through a 0,680,or 470k resistor
void R_680 (u8 Pin, u8 State);
void R_470K (u8 Pin, u8 State);
void R_0 (u8 Pin, u8 State);
//Brings the Pin into high impedance mode(input)
void HiZ(u8 Pin);
//Brings pins A,B, and C into HiZ
void HiZ3(u8 A,u8 B, u8 C);

//same as above functions, only it initialises the quick ADC
//and uses the delay once the pin is set before teh ADC is read..

u16 R_680adc (u8 Pin, u8 State,u16 delay);
u16 R_470Kadc (u8 Pin, u8 State,u16 delay);
//reads the ADCpin when the Pin is brought to HiZ, if delay=0--no delay..
u16 HiZadc(u8 Pin,u8 ADCpin, u16 delay);

void ProcessingDebug();


////////////////////////////////////////////////////
//Global Variables//////////////////////////////////

//The list where all the conductive paths are kept.
//[0]->[1] pins for direction, [3] is the read value r680
//5v--[680]--[0]-->[1]---GND
extern u16 tList[12][3];
extern u8 nC;
extern char pins[3];
extern u8 tIN[3];
extern u8 tOUT[3];
extern u8 tC[3];
extern u8 tN[8];
extern u8 node; 
extern u8 testCMP;
extern u8 diff;
extern char unit;
extern BYTE RecvdByte;
extern u8 terminalF;
extern u8 procF;
extern u16 temp;
extern type pPartSS,PartSS;
extern u16 ptList[12][3];
#endif