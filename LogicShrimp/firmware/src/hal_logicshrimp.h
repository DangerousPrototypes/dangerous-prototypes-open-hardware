#ifndef HAL_LOGICSHRIMP_H
#define HAL_LOGICSHRIMP_H

//#define CLK_GATE	LATCbits.LATC0
#define hal_logicshrimp_pinsetup() TRISCbits.TRISC0=0; TRISBbits.TRISB5=0
#define hal_logicshrimp_setClockGate(x)				LATCbits.LATC0=x
#define hal_logicshrimp_setBufferEnable(x)			LATBbits.LATB5=x

#endif
