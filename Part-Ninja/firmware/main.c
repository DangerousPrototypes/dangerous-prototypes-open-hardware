
#include "globals.h"
#include "config.h"
#include "HD44780.h"
#include "test.h"

//USB stack
#include "..\dp_usb\usb_stack_globals.h"    // USB stack only defines Not function related.
#include "descriptors.h"	// JTR Only included in main.c





#define REMAPPED_RESET_VECTOR_ADDRESS		0x800
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818

#define BootloaderJump() _asm goto 0x16 _endasm

static void init(void);
void InterruptHandlerHigh();
void InterruptHandlerLow();
void USBSuspend(void);
void USBSuspend(void){}

u8 testF=1;//0;
u8 usbCON=0;	//usb connection flag, if connected 1;
u8 cdc_switch(BYTE rB);
u8 terminalF=0;
u8 procF=0;

#pragma udata
extern BYTE usb_device_state;

#pragma code
void main(void)
{  
	u32 usbTimerPN=0;
	//BYTE RecvdByte;
	init();			//setup the crystal, pins
	
	initCDC(); // setup the CDC state machine

    usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS); // initialize USB. TODO: Remove magic with macro
    usb_start(); //start the USB peripheral

#if defined USB_INTERRUPTS // See the prj_usb_config.h file.
    EnableUsbPerifInterrupts(USB_TRN + USB_SOF + USB_UERR + USB_URST);
#if defined __18CXX //turn on interrupts for PIC18
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
#endif
    EnableUsbGlobalInterrupt(); // Only enables global USB interrupt. Chip interrupts must be enabled by the user (PIC18)
#endif

	// Wait for USB to connect
	do 
	{
		usbTimerPN++;
#ifndef USB_INTERRUPTS
        usb_handler();
#endif
		if(usbTimerPN>1000000)
		{
			usbCON=1;
			break;
		}
    } while (usb_device_state < CONFIGURED_STATE);

    if(!usbCON)usb_register_sof_handler(CDCFlushOnTimeout); // Register our CDC timeout handler after device configured


	Delay_MS(10);	

	HD44780_Reset();//setup the LCD
	HD44780_Init();
	//LCD_Backlight(1);//turn it on, we ignore the parameter

	LCD_CursorPosition(0);
	LCD_WriteString("Part Ninja r1928");
	LCD_CursorPosition(21);
	LCD_WriteString("      testing...");
 	CDC_Flush_In_Now();
	while(1)
	{
		if(testF)testPart();
		if(usbCON)
		{
			CDC_Flush_In_Now();
			if (poll_getc_cdc(&RecvdByte)) 
			{ 
        	    putc_cdc(RecvdByte); //
            	CDC_Flush_In_Now(); 
				cdc_switch(RecvdByte);
			}
		}
		
		//testing comleate...
	
	}
}//end main

static void init(void){
	unsigned int cnt = 2048;
	
	//all pins digital
	//disable some defaults
    ADCON1 |= 0b1111;   	//all pins digital
	CVRCON=0b00000000;

	//make sure everything is input (should be on startup, but just in case)
	TRISA=0xff;
	TRISB=0xff;
	TRISE=0xff;
	TRISC=0b11111111; 

	//comparator analog pins setup...
	CMCONbits.C2INV = 1;	//whne voltage on RA1 > vreff cout2=>1
	CMCONbits.C1INV = 1;	//whne voltage on RA1 > vreff cout1=>1
	CMCONbits.CIS=0; 		//the Cvin- input aer RA0 na RA1
	CMCONbits.CM2=1,CMCONbits.CM1=0,CMCONbits.CM0=0; //100 C1 and C2 V+ conencted to vref, while v+ conected to RA1 and RA2
	INTCONbits.GIE = 1;
	INTCONbits.PEIE =1;
	IPR2bits.CMIP =1;

	//on 18f24j50 we must manually enable PLL and wait at least 2ms for a lock
	//OSCTUNEbits.PLLEN = 1;  //enable PLL
	//while(cnt--); //wait for lock

}

u8 cdc_switch(BYTE rB)
{
	switch(rB)
	{
		case 's':
			testF=1;
			return 1;
		case 't':
			terminalF =1;
			procF=0;
			return 1;
		case 'p':
			testF=1;
			procF=1;
			terminalF =0;
			ProcessingDebug();
			return 1;
		case '0':
			terminalF =0;
			procF=0;
			testF=0;
			return 1;
		default:
			terminalF =0;
			procF=0;
			testF=0;
			return 0;
	}
}


//PIC18F style interrupts with remapping for bootloader
//	Interrupt remap chain
//
//This function directs the interrupt to
// the proper function depending on the mode
// set in the mode variable.
//USB stack on low priority interrupts,
#pragma interruptlow InterruptHandlerLow nosave= PROD, PCLATH, PCLATU, TBLPTR, TBLPTRU, TABLAT, section (".tmpdata"), section("MATH_DATA")
void InterruptHandlerLow(void) {
    if(PIR2bits.USBIF)	//usb interrupt
	{
		usb_handler();
	    ClearGlobalUsbInterruptFlag();
	}
	if(CMP_INTF)
	{
		CMP_INTE=0;
		CMP_INTF=0;
		testCMP=0;
	}
}

#pragma interrupt InterruptHandlerHigh nosave= PROD, PCLATH, PCLATU, TBLPTR, TBLPTRU, TABLAT, section (".tmpdata"), section("MATH_DATA")
void InterruptHandlerHigh(void) { //Also legacy mode interrupt.
	
   if(PIR2bits.USBIF)//usb interrupt
	{
	usb_handler();
    ClearGlobalUsbInterruptFlag();
	}
	if(CMP_INTF)
	{
		CMP_INTE=0;
		CMP_INTF=0;
		testCMP=0;
	}
}

//these statements remap the vector to our function
//When the interrupt fires the PIC checks here for directions
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS

void Remapped_High_ISR(void) {
    _asm goto InterruptHandlerHigh _endasm
}

#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS

void Remapped_Low_ISR(void) {
    _asm goto InterruptHandlerLow _endasm
}

//relocate the reset vector
extern void _startup(void);
#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS

void _reset(void) {
    _asm goto _startup _endasm
}
//set the initial vectors so this works without the bootloader too.
#pragma code HIGH_INTERRUPT_VECTOR = 0x08

void High_ISR(void) {
    _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
}
#pragma code LOW_INTERRUPT_VECTOR = 0x18

void Low_ISR(void) {
    _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
}
