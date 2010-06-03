/*
*
*	Dangerous Prototypes Flash Destroyer firmware
*	License: creative commons - attribution, share-alike
* 	http://creativecommons.org/licenses/by-sa/2.0/
*	Copyright 2010
*	http://dangerousprototypes.com
*/
#ifndef HAL_7SEGDRV_H
#define HAL_7SEGDRV_H


#define SEVENSEG_BLANK 	10
#define SEVENSEG_I		1
#define SEVENSEG_C		11
#define SEVENSEG_E		12
#define SEVENSEG_R		19
#define SEVENSEG_S		5
#define SEVENSEG_A		13
#define SEVENSEG_V		14
#define SEVENSEG_D		18
#define SEVENSEG_F		15
#define SEVENSEG_L		16
#define SEVENSEG_H		17
#define SEVENSEG_Y		4
#define SEVENSEG_T		20



enum SEVEN_SEG_DISP_MODE
	{
//	DISP_MODE_NUM=0x00,
	DISP_MODE_I2C_ERR,
	DISP_MODE_SAVE,
	DISP_MODE_DEAD,
	DISP_MODE_FLASH,
	DISP_MODE_DESTROY,
	DISP_MODE_ERASING,
	DISP_MODE_ERASE
	};


// definition
#define SevenSegment_InitPort()		{TRISC&=~0x03;TRISA=0;}
//#define SevenSegment_Disable()		{LATCbits.LATC7=0;LATB=0;}
#define SevenSegment_Disable()		{TRISC|=0x03;TRISA=0xFF;}
#define PORT_7SEG_A_B				LATC
#define PORT_7SEG_C_D_E_F_G			LATA
#define PORT_7SEG_DP				LATA

#define SevenSegment_DispOneDigit(Number)  PORT_7SEG_A_B&=~0x03; \
	PORT_7SEG_C_D_E_F_G=0; \
	PORT_7SEG_A_B|=SEVENSEGMENTARRAY[(Number)][0]; \
	PORT_7SEG_C_D_E_F_G=SEVENSEGMENTARRAY[(Number)][1]

void ExtractEEPROMCtrToArray(void);

u8 hal_7SegDrv_GetDispMode(void);
void hal_7SegDrv_SetDispMode(u8 DispMode);
void hal_7SegDrv_ExtractNumToArray(volatile u32 Ctr);

void hal_7SegmentISR (void);


#endif
