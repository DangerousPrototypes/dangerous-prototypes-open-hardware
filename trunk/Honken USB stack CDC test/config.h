/*
*
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/

#ifndef CONFIG_H
#define CONFIG_H

#ifdef __18F14K50

// configword 0x300000
#pragma config CPUDIV = NOCLKDIV
#pragma config USBDIV = OFF

// configword 0x300001
#pragma config FOSC = HS
#pragma config PLLEN = ON
#pragma config PCLKEN = OFF
#pragma config FCMEN = OFF
#pragma config IESO = OFF

// configword 0x300002
#pragma config PWRTEN = OFF
#pragma config BOREN = OFF
#pragma config BORV = 30

// configword 0x300003
#pragma config WDTEN = OFF
#pragma config WDTPS = 32768

// configword 0x300005
#pragma config HFOFST = ON
#pragma config MCLRE = ON   

// configword 0x300006
#pragma config STVREN = ON
#pragma config LVP = OFF
#pragma config XINST = OFF

// configword 0x300008
#pragma config CP0 = OFF 
#pragma config CP1 = OFF 

// configword 0x300009
#pragma config CPB = OFF 
#pragma config CPD = OFF

// configword 0x30000a 
#pragma config WRT0 = OFF 
#pragma config WRT1 = OFF

// configword 0x30000b 
#pragma config WRTB = OFF 
#pragma config WRTC = OFF  
#pragma config WRTD = OFF

// configword 0x30000c 
#pragma config EBTR0 = OFF 
#pragma config EBTR1 = OFF 

// configword 0x30000d
#pragma config EBTRB = OFF

#endif


#ifdef __18F2550
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
#endif

#ifdef __18F24J50
     #pragma config WDTEN = OFF       

    //#ifdef XTAL_20MHZ
     //#pragma config PLLDIV = 5           //Divide by 5 (20 MHz oscillator input) 
	//#else
     #pragma config PLLDIV = 4           //Divide by 4 (16 MHz oscillator input) 
	//#endif

     #pragma config STVREN = ON         
     #pragma config XINST = OFF          
     #pragma config CPUDIV = OSC1        
     #pragma config CP0 = OFF            
     #pragma config OSC = HSPLL          
     #pragma config T1DIG = ON           
     #pragma config LPT1OSC = OFF        
     #pragma config FCMEN = OFF          
     #pragma config IESO = OFF           
     #pragma config WDTPS = 32768        
     #pragma config DSWDTOSC = INTOSCREF 
     #pragma config RTCOSC = T1OSCREF    
     #pragma config DSBOREN = OFF        
     #pragma config DSWDTEN = OFF       
     #pragma config DSWDTPS = 8192       
     #pragma config IOL1WAY = OFF        
     #pragma config MSSP7B_EN = MSK7     
     #pragma config WPFP = PAGE_1        
     #pragma config WPEND = PAGE_0       
     #pragma config WPCFG = OFF          
     #pragma config WPDIS = OFF       

#endif

#if defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)
	#include <p24fxxxx.h>
	_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2) 
	_CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV3 & IOL1WAY_ON & PLL_96MHZ_ON)
#endif

#endif

