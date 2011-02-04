#ifndef HAL_LOGICSHRIMP_H
#define HAL_LOGICSHRIMP_H

//#define CLK_GATE	LATCbits.LATC0
//pin setup: clock/buffer direction and initial state, LED direction, uC clock pin
#define hal_logicshrimp_pinsetup() LATBbits.LATB5=1; TRISBbits.TRISB5=0; TRISCbits.TRISC6=0; LATCbits.LATC7=1; TRISCbits.TRISC7=0

//#define hal_logicshrimp_ClockGateEnable()				LATCbits.LATC0=0
//#define hal_logicshrimp_ClockGateDisable()				LATCbits.LATC0=1
#define hal_logicshrimp_BufferEnable()					LATBbits.LATB5=0
#define hal_logicshrimp_BufferDisable()					LATBbits.LATB5=1

#define HAL_LOGICSHRIMP_LED_LAT				LATCbits.LATC6
#define HAL_LOGICSHRIMP_LED_TRIS			TRISCbits.TRISC6

#define hal_logicshrimp_setLed(x)			HAL_LOGICSHRIMP_LED_LAT=x


#define hal_logicshrimp_setInputs()			;; //TODO
void hal_logicshrimp_configPPS(void);

#endif
