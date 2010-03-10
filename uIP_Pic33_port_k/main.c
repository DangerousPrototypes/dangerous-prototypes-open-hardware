//The compiled firmware can be used 'as-is' with the ds30 Loader bootloader
//you may need to locate your own p33FJ128gp204.gld file.
//   It's in the C30 compiler directory:
/* \C30\support\dsPIC33F\gld\ */

#include "HardwareProfile.h"
#include "uip.h"
#include "uip_arp.h"
#include "enc28j60.h"
#include "nic.h"

//it's important to keep configuration bits that are compatibale with the bootloader
//if you change it from the internall/PLL clock, the bootloader won't run correctly
_FOSCSEL(FNOSC_FRCPLL)		//INT OSC with PLL (always keep this setting)
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)	//disable external OSC (always keep this setting)
_FWDT(FWDTEN_OFF)				//watchdog timer off
_FICD(JTAGEN_OFF & 0b11);//JTAG debugging off, debugging on PG1 pins enabled
void initTimer(void)
{
//timer init routine here.
// Set up the timer interrupt
IPC0  = IPC0 | 0x1000;  // Priority level is 1
IEC0  = IEC0 | 0x0008;  // Timer1 interrupt enabled
PR1   = 10000;
T1CON = 0x8030;
}
//I don't know how to call interrupts in DSPIC
int main(void)
{ //main function, execution starts here

	AD1PCFGL = 0xFFFF; //digital pins

	//setup internal clock for 80MHz/40MIPS
	//7.37/2=3.685*43=158.455/2=79.2275
	CLKDIVbits.PLLPRE=0; // PLLPRE (N2) 0=/2 
	PLLFBD=41; //pll multiplier (M) = +2
	CLKDIVbits.PLLPOST=0;// PLLPOST (N1) 0=/2
    
   
    while(!OSCCONbits.LOCK);//wait for PLL ready
    nic_init(); // Initialize ENC28j60. At this point uIP is not used yet

    // init uIP
    uip_init();

    // init app
    example1_init();

    // init ARP cache
    uip_arp_init();

    // init periodic timer
    initTimer();

     
    
    while(1)
    {//never ending loop
    

	}
}





