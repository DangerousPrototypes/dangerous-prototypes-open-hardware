/*
*
*	Dangerous Prototypes Flash Destroyer firmware
*	License: creative commons - attribution, share-alike
* 	http://creativecommons.org/licenses/by-sa/2.0/
*	Copyright 2010
*	http://dangerousprototypes.com
*/
#include "globals.h"


//static u8 SevenSegDispMode;
static volatile u8 SeveSegmentArray[7];


static const char SEVENSEGMENTARRAY[][2]=
	{ // A_B, C D E F G
			{3,0x0F}, //0
			{1,0x01}, //1
			{3,0x16}, //2
			{3,0x13}, //3
			{1,0x19}, //4
			{2,0x1B}, //5
			{2,0x1F}, //6
			{3,0x01}, //7
			{3,0x1F}, //8
			{3,0x1B},  //9
			{0,0}, 		// 10 blank
			{2,0x0E}, 	// 11 C
			{2,0x1E}, 	// 12 E
			{3,0x1D}, 	// 13 A
			{1,0x0F},	// 14 V
			{2,0x1C},	// 15 F
			{0,0x0E}, 	// 16 L
			{1,0x1D},	// 17 H
			{1,0x17},	// 18 d
			{0,0x14},	// 19 r
			{1,0x11}	// 20 t
	};



#if 0
u8 hal_7SegDrv_GetDispMode(void)
{
return SevenSegDispMode;
}
#endif


void hal_7SegDrv_SetDispMode(u8 DispMode)
{
//SevenSegDispMode=DispMode;

switch(DispMode)
	{
	case DISP_MODE_I2C_ERR:
		SeveSegmentArray[6]=SEVENSEG_R;
		SeveSegmentArray[5]=SEVENSEG_R;
		SeveSegmentArray[4]=SEVENSEG_E;
		SeveSegmentArray[3]=SEVENSEG_BLANK;
		SeveSegmentArray[2]=SEVENSEG_C;
		SeveSegmentArray[1]=2;
		SeveSegmentArray[0]=SEVENSEG_I;
		break;
	case DISP_MODE_SAVE:
		SeveSegmentArray[6]=SEVENSEG_E;
		SeveSegmentArray[5]=SEVENSEG_V;
		SeveSegmentArray[4]=SEVENSEG_A;
		SeveSegmentArray[3]=SEVENSEG_S;
		SeveSegmentArray[2]=SEVENSEG_BLANK;
		SeveSegmentArray[1]=SEVENSEG_BLANK;
		SeveSegmentArray[0]=SEVENSEG_BLANK;
		break;
	case DISP_MODE_DEAD:
		SeveSegmentArray[6]=SEVENSEG_D;
		SeveSegmentArray[5]=SEVENSEG_A;
		SeveSegmentArray[4]=SEVENSEG_E;
		SeveSegmentArray[3]=SEVENSEG_D;
		SeveSegmentArray[2]=SEVENSEG_BLANK;
		SeveSegmentArray[1]=SEVENSEG_BLANK;
		SeveSegmentArray[0]=SEVENSEG_BLANK;
		break;
	case DISP_MODE_FLASH:
		SeveSegmentArray[6]=SEVENSEG_H;
		SeveSegmentArray[5]=SEVENSEG_S;
		SeveSegmentArray[4]=SEVENSEG_A;
		SeveSegmentArray[3]=SEVENSEG_L;
		SeveSegmentArray[2]=SEVENSEG_F;
		SeveSegmentArray[1]=SEVENSEG_BLANK;
		SeveSegmentArray[0]=SEVENSEG_BLANK;
		break;

	case DISP_MODE_DESTROY:
		SeveSegmentArray[6]=SEVENSEG_Y;
		SeveSegmentArray[5]=0;
		SeveSegmentArray[4]=SEVENSEG_R;
		SeveSegmentArray[3]=SEVENSEG_T;
		SeveSegmentArray[2]=SEVENSEG_S;
		SeveSegmentArray[1]=SEVENSEG_E;
		SeveSegmentArray[0]=SEVENSEG_D;
		break;
	case DISP_MODE_ERASING:
		SeveSegmentArray[6]=SEVENSEG_D;
		SeveSegmentArray[5]=SEVENSEG_E;
		SeveSegmentArray[4]=SEVENSEG_S;
		SeveSegmentArray[3]=SEVENSEG_A;
		SeveSegmentArray[2]=SEVENSEG_R;
		SeveSegmentArray[1]=SEVENSEG_E;
		SeveSegmentArray[0]=SEVENSEG_BLANK;
		break;
	case DISP_MODE_ERASE:
		//SeveSegmentArray[6]=SEVENSEG_D;
		SeveSegmentArray[6]=SEVENSEG_E;
		SeveSegmentArray[5]=SEVENSEG_S;
		SeveSegmentArray[4]=SEVENSEG_A;
		SeveSegmentArray[3]=SEVENSEG_R;
		SeveSegmentArray[2]=SEVENSEG_E;
		SeveSegmentArray[1]=SEVENSEG_BLANK;
		SeveSegmentArray[0]=SEVENSEG_BLANK;
		break;
	}
}



void hal_7SegDrv_ExtractNumToArray(volatile u32 Ctr)
{
SeveSegmentArray[6]=Ctr%10;
SeveSegmentArray[5]=(Ctr%100)     /10;
SeveSegmentArray[4]=(Ctr%1000)    /100;
SeveSegmentArray[3]=(Ctr%10000)   /1000;
SeveSegmentArray[2]=(Ctr%100000)  /10000;
SeveSegmentArray[1]=(Ctr%1000000) /100000;
SeveSegmentArray[0]=(Ctr%10000000)/1000000;
}








////////////////////////// INTERRUPT ROUTINE //////////////////////

#if 0
#pragma interrupt MyISR
 void high_vector (void)
{
   _asm GOTO hal_7SegmentISR _endasm
}
#pragma code
#endif

#pragma interrupt hal_7SegmentISR
void hal_7SegmentISR (void)
{
static u8 CurrentDigit=0;
static u8 NumToDisplay;

if(INTCONbits.TMR0IF)
	{
	//Cathode off
	LATCbits.LATC7=0;
	LATB=0;

	SevenSegment_DispOneDigit(SeveSegmentArray[CurrentDigit]);

	//Select Cathode
	if(CurrentDigit==6)
		{
		LATCbits.LATC7=1;
		LATB=0;
		}
	else
		{
		LATCbits.LATC7=0;
		LATB=1<<(7-CurrentDigit);
		}

	CurrentDigit++;
	if(CurrentDigit==7) // up to 6 only (0 to 6 is 7digits)
		CurrentDigit=0;

	INTCONbits.TMR0IF=0;
	}
}



//////////////////////////////////////////////////////////////////
