/*
This work is licensed under the Creative Commons Attribution 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/
or send a letter to
	Creative Commons,
	171 Second Street,
	Suite 300,
	San Francisco,
	California,
	94105,
	USA.
*/
#define IRTOY_BOOTLOADER
#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
#pragma config PLLDIV = 5
#pragma config CPUDIV = OSC1_PLL2
#pragma config USBDIV = 2
#pragma config FOSC = HSPLL_HS
#pragma config IESO = OFF
#pragma config PWRT = OFF
#pragma config BOR = ON
#pragma config VREGEN = ON
#pragma config WDT = OFF
#pragma config WDTPS = 32768
#pragma config MCLRE = ON
#pragma config LPT1OSC = OFF
#pragma config PBADEN = OFF
#pragma config CCP2MX = ON
#pragma config STVREN = ON
#pragma config LVP = OFF
//#pragma config ICPRT = OFF
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

#define	LED_LAT  LATA
#define LED_TRIS TRISA
#define LED_PIN  0b1
#define LedOff() LED_LAT&=(~LED_PIN)
#define LedOn() LED_LAT|=LED_PIN
#define LedOut() LED_TRIS&=(~LED_PIN)
#define LedIn() LED_TRIS|=LED_PIN

#include <p18cxxx.h>

#elif defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)

#include <p24fxxxx.h>

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2) 
_CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV3 & IOL1WAY_ON & PLL_96MHZ_ON)

#endif

#include "usb_stack.h"
#include "cdc.h"
void InterruptHandlerHigh();
void InterruptHandlerLow();

#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)

//#pragma interrupt arbiter
#pragma interruptlow arbiter
void arbiter( void ) {
	if (PIR2bits.USBIF)
		usb_handler();
		PIR2bits.USBIF = 0;
}

#pragma code

#elif defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)
/*
void __attribute__((__interrupt__(?))) arbiter( void ) {
	usb_handler();
}
*/
#endif
	
#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
void main( void ) 
#elif defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)
int main(void)
#endif
{

	DINIT();
	DPRINTF("\n\nHonken USB Stack Debug\n");

#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
	/* Setup and enable interrupts */
	RCONbits.IPEN = 1;		// Enable interrupt priorities
	PIR1 = PIR2 = 0;		// Clear all pending interrupts
	PIE2bits.USBIE = 1;		// Enable USB interrupts
	IPR2bits.USBIP = 1;		// USB interrupt high priority
	INTCONbits.PEIE = 1;	// Enable peripherial interrupts
	INTCONbits.GIE = 1;		// Enable all interrupts
	LedOut();
	LedOff();
#elif defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)
//#error "Interrupt driven stack not implemented on pic24fj256GB110 family"
#endif

	cdc_init();

	// Infinity local echo
	while(1) {

#if defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)
		/* No interrupt driven p24 just yet. */
		usb_handler();
#endif

		if (DataRdyCDC()){
#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
			LedOn();
#endif
			putcCDC(getcCDC());
#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
			LedOff();
#endif
		}
	}
}
#if defined(IRTOY_BOOTLOADER)
#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818

//these statements remap the vector to our function
//When the interrupt fires the PIC checks here for directions
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void){
     _asm GOTO arbiter _endasm
}

#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
void Remapped_Low_ISR (void){
     _asm GOTO arbiter _endasm
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
#endif
