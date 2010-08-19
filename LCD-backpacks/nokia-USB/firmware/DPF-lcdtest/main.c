#include "LCD_driver.h"

//HACKADAY: set custom configuration for PIC 24F
_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE)		// Internal FRC OSC with 4x PLL = 32MHz
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1) //turn off junk we don't need

int main(void){
	unsigned char clr[]={0b11100000,0b00011100,0b00000011, 0b11111100, 0b11100011, 0b00011111};
	int i,j;
	int m;
	long k;

	AD1PCFG = 0xFFFF;				//All digital inputs 
	OSCCONbits.SOSCEN=0;
	
	LATBbits.LATB13=1;
	TRISBbits.TRISB13=0;
	
	LCD_init(); //init the LCD


	while(1){
		//draw screen with colors from the clr pallet...
		for(j=0;j<sizeof(clr);j++){
			for(i=0; i<ENDPAGE; i++){
				for(m=0;m<ENDCOL;m++){
					pset(clr[j],i,m);
				}
			}
		    //for (k = 0; k < 300000; k++);	//delay_ms(100);
		}
	
	}

}
