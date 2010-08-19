//Due to licensing issues, we can't redistribute the Microchip SD file system source. 
//You can get them from the Microchip website for free: 
//http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=2680&dDocName=en537999
//
//1.Download and install the "File System for PIC18 PIC24 dsPIC PIC32" (SD file system). These files install to c:\Microchip Soultions\ by default.
//2.Place the Hack a Day project folder in the Microchip source install directory (c:\Microchip Soultions\ by default)
//3.That's it. You've got the latest source and we're compliant with the license.
//4.Depending on the install location you may need to tweak the include paths under Project->build options->project.
//
#include "Compiler.h" //this is included in Microchip's library
#include "LCD_driver.h"
#include "FSIO.h" //include the file system IO liraries (you must download and install these from Microchip)
#include "dpf.h"

void initBoard(void);

//HACKADAY: set custom configuration for PIC 24F
_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE)		// Internal FRC OSC with 4x PLL = 32MHz
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1) //turn off junk we don't need

int main(void){

//setup hardware
	initBoard();

	LCD_init(); //init the LCD

	while(1) dpfTasks();
}

void initBoard(void){
	CLKDIVbits.RCDIV0=0; //clock divider to 0
	AD1PCFG = 0xFFFF;				//All digital inputs 
	OSCCONbits.SOSCEN=0;
	
	LATBbits.LATB13=0;//LED
	TRISBbits.TRISB13=0;
	
	//HACKADAY:setup the pin assignment using peripheral pin select
	//SPI2 -> SD card
	//inputs
	RPINR22bits.SDI2R = 11;			//SDI2	

	//outputs
	#define PPSOB1 RPOR0bits.RP1R
	#define PPSOB2 RPOR1bits.RP2R
	#define PPSOB10 RPOR5bits.RP10R
	#define PPSOB9 RPOR4bits.RP9R
	PPSOB9 = SDO2_IO;		//SDO2
	PPSOB10 = SCK2OUT_IO; 	//SCK2
	
	// Lock the PPS
	asm volatile (	"mov #OSCCON,w1 \n"
					"mov #0x46, w2 \n"
					"mov #0x57, w3 \n"
					"mov.b w2,[w1] \n"
					"mov.b w3,[w1] \n"
					"bset OSCCON, #6");

}
