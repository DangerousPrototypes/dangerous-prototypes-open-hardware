#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

//Hardware defines
#define R0_DIR	TRISB
#define R0_OUT	LATB
#define R0_IN	PORTB

#define R680_DIR TRISD
#define R680_OUT LATD

#define R470K_DIR TRISB
#define R470K_OUT LATB

#define CMP_INTE PIE2bits.CMIE
#define CMP_INTF PIR2bits.CMIF

#endif 
