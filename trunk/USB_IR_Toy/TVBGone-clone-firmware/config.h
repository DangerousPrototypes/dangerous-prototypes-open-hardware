/*
This is a simple player for TVBGONE power codes.
Our player is simple because PIC C18 has easy 
reads from program memory. 

This code was written based on the description 
of the data packing method published on the Adafruit 
website. It should be a clean, black-box rewrite, but 
we'll release it as CC 2.5 Attrib & Share Alike 
out of respect for the original authors.

PIC C18 Player (c) Ian Lesnet 2009
for use with IR Toy v1.0 hardware.
http://dangerousprototypes.com

With credits to:

TV-B-Gone Firmware version 1.2
for use with ATtiny85v and v1.2 hardware
(c) Mitch Altman + Limor Fried 2009
Last edits, August 16 2009

With some code from:
Kevin Timmerman & Damien Good 7-Dec-07

Distributed under Creative Commons 2.5 -- Attib & Share Alike

Ported to PIC (18F2550) by Ian Lesnet 2009
*/
        #pragma config PLLDIV   = 5         
        #pragma config CPUDIV   = OSC1_PLL2   
        #pragma config USBDIV   = 2         
        #pragma config FOSC     = HSPLL_HS
        #pragma config FCMEN    = OFF
        #pragma config IESO     = OFF
        #pragma config PWRT     = OFF
        #pragma config BOR      = ON
        #pragma config BORV     = 3
        #pragma config VREGEN   = ON      
        #pragma config WDT      = OFF
        #pragma config WDTPS    = 32768
        #pragma config MCLRE    = ON
        #pragma config LPT1OSC  = OFF
        #pragma config PBADEN   = OFF
//      #pragma config CCP2MX   = ON
        #pragma config STVREN   = ON
        #pragma config LVP      = OFF
//      #pragma config ICPRT    = OFF       
        #pragma config XINST    = OFF       
        #pragma config CP0      = OFF
        #pragma config CP1      = OFF
//      #pragma config CP2      = OFF
//      #pragma config CP3      = OFF
        #pragma config CPB      = OFF
//      #pragma config CPD      = OFF
        #pragma config WRT0     = OFF
        #pragma config WRT1     = OFF
//      #pragma config WRT2     = OFF
//      #pragma config WRT3     = OFF
        #pragma config WRTB     = OFF   
        #pragma config WRTC     = OFF
//      #pragma config WRTD     = OFF
        #pragma config EBTR0    = OFF
        #pragma config EBTR1    = OFF
//      #pragma config EBTR2    = OFF
//      #pragma config EBTR3    = OFF
        #pragma config EBTRB    = OFF
