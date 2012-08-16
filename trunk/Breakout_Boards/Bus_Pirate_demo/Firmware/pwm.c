/* header */

#include <pic.h>
#include "./pwm.h"

unsigned char PWMduty;
unsigned char PWMperiod;
void enablePWM(void)
{
	unsigned int tempP;
	TRISAbits.TRISA5 =1;
	APFCON1bits.CCP2SEL=1;
	PR2 = 0x02;	//longest period	at32MHZ is 32~Khz...
				//76543210
	PWMperiod = PR2;

	CCP2CON =0b00001100;	
	//Single output; PxA modulated; PxB, PxC, PxD assigned as port pins
	//2LSBs 00, 1100 = PWM mode: PxA, PxC active-high; PxB, PxD active-high
	CCPR2L =0x01; //50%duty cycle

	tempP=(unsigned int)CCPR2L*100;
	PWMduty = tempP/PWMperiod;
	

	CCPTMRS=0;	//timer2 selected
	TMR2IF=0;
				//76543210
	T2CON =	0; //t2 off, post and prescaler =1:1
	T2CONbits.TMR2ON =1;	//t2 on;
	TRISAbits.TRISA5 =0;	//output enable;	
}

void setPeriod(unsigned char P)
{
	unsigned int temp;
	if(P>1)
	{
		temp=P*PWMduty;
		temp = temp/100;
		CCPR2L = temp;
		PWMperiod = P;
		PR2=P;	
	}
	else
	{
		PWMperiod = 2;
		PR2 = 2;
		CCPR2L = 1;
	}

}

void setDuty(unsigned char D)
{
	unsigned int temp;
	
	if(D<100)
	{
		PWMduty = D;
		temp = PWMduty*PWMperiod;
		temp = temp/100;
		CCPR2L = temp;
	}
	else
	{
		PWMduty = 99;
		temp = PWMduty*PWMperiod;
		temp = temp/100;
		CCPR2L = temp;
	}
}

void disablePWM(void)
{
	TRISAbits.TRISA5=1;
	T2CONbits.TMR2ON =0;
}//output disabled