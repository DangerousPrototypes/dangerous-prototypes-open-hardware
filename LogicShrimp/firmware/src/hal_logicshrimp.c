#include "globals.h"




void hal_logicshrimp_init(void)
{
hal_logicshrimp_pinsetup();
hal_logicshrimp_ClockGateDisable();
hal_logicshrimp_BufferDisable();
}

//pins for configure mode: clock/buffer output, high (disabled); uC clock pin to output, low
void hal_logicshrimp_configmode(void){
	LATCbits.LATC0=1; //clock gate output, high (disabled)
	TRISCbits.TRISC0=0; 
	LATBbits.LATB5=1; //buffer output, high (disabled)
	TRISBbits.TRISB5=0; 
	TRISCbits.TRISC6=0; //uC clock pin output, low (to drive SRAMS)
	LATCbits.LATC6=0;

}
//pins for data capture: 
void hal_logicshrimp_capturemode(void){
	LATCbits.LATC0=1; 
	TRISCbits.TRISC0=0; 
	LATBbits.LATB5=1; 
	TRISBbits.TRISB5=0; 
	TRISCbits.TRISC6=1; 
	LATCbits.LATC6=0;
}


void hal_logicshrimp_configPPS(void)
{
// Do the unlocking procedure
INTCONbits.GIE=0;
EECON2=0x55;
EECON2=0xAA;
PPSCONbits.IOLOCK=0;

// TODO: Setup Ports here
RPINR6=11; // RP11   Timer3 External Clock Input T3CKI RPINR6 T3CKR<4:0>




// Do the locking procedure
INTCONbits.GIE=0;
EECON2=0x55;
EECON2=0xAA;
PPSCONbits.IOLOCK=1;

}
