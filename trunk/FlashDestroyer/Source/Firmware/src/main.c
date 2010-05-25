/* ===========================================================
*	Dangerous Prototypes Flash Destroyer v1.0 Firmware v1.0
*	License: creative commons - attribution, share-alike
* 	http://creativecommons.org/licenses/by-sa/2.0/
*	Copyright 2010
*	http://dangerousprototypes.com
====================================================
Project: 	FlashDestroyer
Author: 	Sevenstring/Ian Lesnet
Compiler: 	MPLAB C18
MCU:		PIC18F2550
Version:
	1.0 - Initial release
=========================================================== */


////////////// CONFIG FUSES ///////////////////
#pragma config PLLDIV = 1
#pragma config CPUDIV = OSC1_PLL2
#pragma config USBDIV = 1
#pragma config FOSC = HS
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRT = OFF //ON //off for debug
#pragma config BOR = ON //ON
#pragma config BORV = 2 //watch voltage levels, can dip when display starts scanning
#pragma config VREGEN = ON
#pragma config  WDT = OFF
#pragma config WDTPS = 32768
#pragma config MCLRE = ON
#pragma config LPT1OSC = OFF
#pragma config PBADEN = OFF
#pragma config CCP2MX = OFF
#pragma config STVREN = ON
#pragma config LVP = OFF
#pragma config XINST = OFF
#pragma config DEBUG = OFF
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPB = OFF
#pragma config CPD = OFF
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF
///////////////////////////////////////////////

//////////// INCLUDE //////////////////////////
#include "globals.h"
/////////////////////////////////////////////

/////////////// SWITCH ///////////////////
#define S1_PRESSED	0
#define S1_BUTTON PORTCbits.RC2
//////////////////////////////////////////

//////////// MCU Functions //////////////////
void hal_MCU_InitPorts(void);
////////////////////////////////////////////

u16 dummydelay, bigdelay;
#define MY_DELAY(x) dummydelay=(x); do{dummydelay--;}while(dummydelay!=0)
#define MY_BIG_DELAY(x) bigdelay=(x); do{MY_DELAY(0xffff); bigdelay--;}while(bigdelay!=0)

void main(void)
{
static volatile u32 EepromCtr;
static u8 KeyPressedFlag=FALSE;
static u8 boolErase;

//INIT PIC
hal_MCU_InitPorts();

//INIT I2C
hal_EEPROM_Init();

//INIT 7Segment
SevenSegment_InitPort();

#define ctr EepromCtr // just to save memory space

hal_7SegDrv_SetDispMode(DISP_MODE_FLASH); //display FLASH on start
hal_Timer_Init(); //start display timer
MY_BIG_DELAY(50); //delay

boolErase=FALSE;
hal_7SegDrv_SetDispMode(DISP_MODE_DESTROY); //display DISTROY
for(ctr=0;ctr<50;ctr++) //check for erase button press
	{
	if(S1_BUTTON==S1_PRESSED)
		{
		boolErase=TRUE;
		}
	MY_BIG_DELAY(1);
	}

if(boolErase==TRUE) //confim erase
	{
	hal_7SegDrv_SetDispMode(DISP_MODE_ERASE);
	MY_BIG_DELAY(50);
	if(S1_BUTTON==S1_PRESSED)
		{
		hal_InternalEEPROM_Erase();
		hal_7SegDrv_SetDispMode(DISP_MODE_ERASING);
		MY_BIG_DELAY(50);
		}
	}

#undef ctr

// retrieve any previous counter value from EEPROM
EepromCtr=hal_InternalEEPROM_Read();

hal_7SegDrv_ExtractNumToArray(EepromCtr);

while(1)
	{
	MY_DELAY(0x7fff);

	//Write
	if (hal_EEPROM_DestroyWrite()==ERROR_I2C)
		{
		hal_7SegDrv_SetDispMode(DISP_MODE_I2C_ERR);
		MY_BIG_DELAY(20);
		continue; //try again on the next loop
		}

	//Read
	switch(hal_EEPROM_DestroyReadAndVerify())
		{
		case TRUE: //success
			hal_7SegDrv_ExtractNumToArray(EepromCtr);
			EepromCtr++;
			break;
		case FALSE: //verify failed, read error, (try again?)
			hal_InternalEEPROM_Write(EepromCtr);
			while(1)
				{
				hal_7SegDrv_SetDispMode(DISP_MODE_DEAD);
				MY_BIG_DELAY(20); // TODO: ADJUST THIS
				hal_7SegDrv_ExtractNumToArray(EepromCtr);
				MY_BIG_DELAY(20); // TODO: ADJUST THIS
				}
			break;
		case ERROR_I2C: //I2C bus error, (try again?)
			hal_InternalEEPROM_Write(EepromCtr);
			while(1)
				{
				hal_7SegDrv_SetDispMode(DISP_MODE_I2C_ERR);
				MY_BIG_DELAY(20); // TODO: ADJUST THIS
				hal_7SegDrv_ExtractNumToArray(EepromCtr);
				MY_BIG_DELAY(20); // TODO: ADJUST THIS
				}
			break;
		}

	if(S1_BUTTON==S1_PRESSED)
		{
		// Place other code for Switch Press
		// TODO Debounce Routine: TBD

		MY_DELAY(0xFFFF); // ADJUST THIS //act as the delay
		if((S1_BUTTON==S1_PRESSED) && (KeyPressedFlag==FALSE)) // reverify
			{
			hal_7SegDrv_SetDispMode(DISP_MODE_SAVE);
			MY_BIG_DELAY(20); // TODO: ADJUST THIS
			hal_InternalEEPROM_Write(EepromCtr);
			hal_7SegDrv_ExtractNumToArray(EepromCtr);
			}
		KeyPressedFlag=TRUE;
		//while(1); // HALT!
		}
	else
		{
		KeyPressedFlag=FALSE;
		}
	}
}


void hal_MCU_InitPorts(void)
{
ADCON1=0x0F;
CMCON=0x07;

LATA=0;
LATB=0;
LATC=0;
TRISA=0;
TRISB=0x03; // i2c
TRISC=0x04; // switch
}

#define REMAPPED_RESET_VECTOR_ADDRESS         0x800
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS   0x808
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS   0x818

//We didn't use the low priority interrupts,
// but you could add your own code here
#pragma interruptlow InterruptHandlerLow
void InterruptHandlerLow(void){}

//these statements remap the vector to our function
//When the interrupt fires the PIC checks here for directions
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void){
     _asm goto hal_7SegmentISR _endasm
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
////// EOF ////////
