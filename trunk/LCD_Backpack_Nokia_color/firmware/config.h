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
     