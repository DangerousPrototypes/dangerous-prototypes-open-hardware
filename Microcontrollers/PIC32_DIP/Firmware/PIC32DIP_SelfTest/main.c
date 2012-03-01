/* 
 * File:   main.c
 * Author: Filip Dulic @ DangerousPrototypes.com
 *
 * Created on March 1, 2012, 2:19 PM
 */

#include <p32xxxx.h>
//#include <system.h>
/*
 * 
 */
#pragma config UPLLEN    = ON        // USB PLL Enabled
#pragma config FPLLMUL   = MUL_20        // PLL Multiplier
#pragma config UPLLIDIV  = DIV_2         // USB PLL Input Divider
#pragma config FPLLIDIV  = DIV_2         // PLL Input Divider
#pragma config FPLLODIV  = DIV_2         // PLL Output Divider
#pragma config FPBDIV    = DIV_1         // Peripheral Clock divisor
#pragma config FWDTEN    = OFF           // Watchdog Timer
#pragma config WDTPS     = PS1           // Watchdog Timer Postscale
#pragma config FCKSM     = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC  = OFF           // CLKO Enable
#pragma config POSCMOD   = HS            // Primary Oscillator
#pragma config IESO      = OFF           // Internal/External Switch-over
#pragma config FSOSCEN   = OFF           // Secondary Oscillator Enable (KLO was off)
#pragma config FNOSC     = PRIPLL        // Oscillator Selection
#pragma config CP        = OFF           // Code Protect
#pragma config BWP       = OFF           // Boot Flash Write Protect
#pragma config PWP       = OFF           // Program Flash Write Protect
#pragma config ICESEL    = ICS_PGx1      // ICE/ICD Comm Channel Select
#pragma config DEBUG     = OFF            // Background Debugger Enable
#pragma config JTAGEN    = OFF            // JTAG Disabled
#pragma config FUSBIDIO  = OFF
#pragma config FVBUSONIO = OFF
#pragma config PMDL1WAY  = OFF
#pragma config IOL1WAY   = OFF

#define CLOCK_FREQ 40000000

void delay_sec();

int main()
{
    ANSELA = 0x0000;
    ANSELB = 0x0000;

    TRISA = 0;
    TRISB = 0;
    LATA = 0;
    LATB = 0;
    while (1)
    {
        delay_sec();
        LATA = ~PORTA;
        LATB = ~PORTB;
    }


}

void delay_sec()

{
    unsigned long int i;
    for (i = 0;i<4000000;i++) Nop();
}