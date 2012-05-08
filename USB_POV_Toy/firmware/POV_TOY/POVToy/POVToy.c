/*

Copyright (c) 2012 dangerousprototypes.com.

The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include "POVToy.h"
#include "MMA7455L.h"
#include "SPI.h"
#include "SPIFlash.h"


volatile uint8_t  POVToy_XAccel_TransitionLock=0;						// A variable to lock sampling a side, only once.
volatile uint8_t  POVToy_Display_Direction = POVTOY_DIRECTION_RIGHT;    // Wave direction
volatile uint8_t  POVToy_Display_Index=0;        						// Display column index
volatile uint8_t  POVToy_AccelTicks_Diff=0;        					 	// Number of timer 0 ticks, between left and right extremes of X Accel 
volatile sint8_t  POVToy_AccelX;                                        // X Acceleration from Accelerometer
volatile uint8_t  POVToy_TMR0L_Reload = 178;                            // Timer reload value
volatile uint8_t  POVToy_TMR0L_ReloadCalc;                              // Temporary value to calcualte timer reload value
volatile uint16_t POVToy_AccelTicks=0;           						// Increments every (1/250) seconds
volatile sint16_t POVToy_AccelXFiltered=0;                              // Digitally filtered accelerometer data

uint8_t POVTOY_BITMAP[POVTOY_DISPLAY_TOTAL_COLUMNS];                    // RAM area to hold bitmap

//The following bitmap arrays are used for testing. Should be removed in final version
uint8_t POVTOY_BITMAPx[] = 
{
    0x0,
    0xFF,
    0xFF,
    0x18,
    0x18,
    0x18,
    0xFF,
    0xFF,
    0x0,
    0x0,
    0x1E,
    0x3F,
    0x29,
    0x29,
    0x39,
    0x19,
    0x0,
    0x0,
    0x0,
    0x80,
    0xFF,
    0xFF,
    0x0,
    0x0,
    0x80,
    0xFF,
    0xFF,
    0x0,
    0x0,
    0x1E,
    0x3F,
    0x21,
    0x21,
    0x3F,
    0x1E,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x60,
    0xF9,
    0xF9,
    0x60,
    0x0,
    0x0,
    0x0,
};

uint8_t POVTOY_BITMAPy[]={ //48
                           0b00000000,
                           0b11111111,
                           0b00011000,
                           0b00011000,
                           0b00011000,
                           0b11111111,
                           0b00000000,
                           0b00000000,
                           0b11111111,
                           0b10011001,
                           0b10011001,
                           0b10011001,
                           0b10000000,
                           0b00000000,
                           0b11111111,
                           0b00000001,
                           0b00000001,
                           0b00000001,
                           0b00000001,
                           0b00000000,
                           0b00000000,
                           0b11111111,
                           0b00000001,
                           0b00000001,
                           0b00000001,
                           0b00000001,
                           0b00000001,
                           0b00000000,
                           0b11111111,
                           0b10000001,
                           0b10000001,
                           0b10000001,
                           0b10000001,
                           0b11111111,
                           0b00000000,
                           0b00000000,
                           0b00000000,
                           0b00000000,
                           0b00000000,
                           0b00000000,
                           0b00000000,
                           0b00000000,
                           0b00000000,
                           0b00000000,
                           0b00000000,
                           0b00000000,
                           0b11100000,
                           0b00000000,
                         };

void POVToy_LEDPortInit(void)
{
    //8 LED's Anodes are connected to PORTB
    //Config PORTB as output
    TRISB=0x00;
    LATB=0x00;

    //LEDs common cathode connected to PORTA.RA0 port pin.
    //Configuring PWM on this pin controls the brightness of LEDs
    //Config PORTA.RA0 as output
    TRISAbits.TRISA0=0;
	LATAbits.LATA0=1;
    //POVToy_SetBrightness(POVTOY_DISPLAY_BRIGHTNESS); //Set Brightness of LED using PWM
}

void POVToy_PortsInit(void)
{   
    TRISAbits.TRISA1 = 1;   //RA1 is input. INT/Data Ready
    RPINR1 = 1;             //INT1 mapped to RP1 (i.e RA1 pin)

    TRISCbits.TRISC6 = 1;   //RC6 is input. Configured for switch.
}

void POVToy_Int1Init(void)
{
    // Config INT1. This is connected to Data Ready pin of accelerometer
    INTCON2bits.INTEDG1 = 1;          // INT1 external interrupt on rising edge

    // Config INT1 Interrupt registers
    INTCON3bits.INT1IF = 0;          // clear interrupt flag
    INTCON3bits.INT1IP = 0;          // config INT1 interrupt as low priority interrupt
    INTCON3bits.INT1IE = 1;          // Enable INT1 external interrupt
}

void POVToy_Timer0Init(void)
{
    // Config Timer0 Interrupt registers. This timer is used for display column refresh rate.
    INTCONbits.TMR0IF = 0;          // clear interrupt flag
    INTCON2bits.TMR0IP = 0;         // config Timer0 interrupt as low priority interrupt
    INTCONbits.TMR0IE = 1;          // enable the Timer0 interrupt.
    
    // Config Timer0 prescaler and preload values
    T0CON = 0b01000111;             // Timer 0 is configured as 8 bit clock, prescale 1:256
    //TMR0H = 0;                    // Reload Value. Generates interrupts @ 1250 Hz
    TMR0L = 178;
    T0CONbits.TMR0ON = 1;           // start timer
}

void POVToy_IncrementIndex(void)
{
    if(POVToy_Display_Index == (POVTOY_DISPLAY_TOTAL_COLUMNS-1))
    {
        //Reached highest index level
		//POVToy_Display_Index=0;
    }
    else
    {
        POVToy_Display_Index++;
    }
}

void POVToy_DecrementIndex()
{
    if(POVToy_Display_Index == 0)
    {
        //Reached lowest index level
    }
    else
    {

#ifndef POVTOY_DISABLE_BIDIRECTIONAL

        POVToy_Display_Index--;

#endif 
    }
}

void POVToy_LowPriorityISR()
{
    // Check for Timer0 Interrupt. This handles the bitmap display.
    if  (INTCONbits.TMR0IF)
    {

        LATB = POVTOY_BITMAP[POVToy_Display_Index];
        if(POVToy_Display_Direction == POVTOY_DIRECTION_RIGHT)
        {
            POVToy_IncrementIndex();
        }
        else
        {
            POVToy_DecrementIndex();
        }

        // Reload Value for display refresh interrupt
        TMR0L = POVToy_TMR0L_Reload;
        INTCONbits.TMR0IF = 0;          // clear Timer interrupt flag
    }

    //check INT1 ( external interrupt )
    if(INTCON3bits.INT1IF)	//Accel Data is Ready
    {
        POVToy_AccelTicks++;	//Acceleration sampling freq as ticks. (increments @ approx 250Hz)
        POVToy_AccelX = MMA7455L_ReadAcceleration(MMA7455L_XOUT8);  //Read X Accel.

        //Single Pole IIR Low Pass Filter. Expression: Filtered= 0.9 * Filtered + (1-0.9) AccelX
        POVToy_AccelXFiltered = ((9 * POVToy_AccelXFiltered) + POVToy_AccelX )/10;

        if((((uint8_t)POVToy_AccelXFiltered) > POVTOY_ACCELERATION_THRESHOLD)  && ((uint8_t)POVToy_AccelXFiltered) < 127)
        {
            if(POVToy_XAccel_TransitionLock==0)
            {
                POVToy_Display_Direction = POVTOY_DIRECTION_RIGHT;

#ifdef POVTOY_FIXED_FREQ_REFESH
                POVToy_TMR0L_ReloadCalc = POVTOY_FIXED_FREQ_RELOAD_VALUE;
#else
                POVToy_TMR0L_ReloadCalc = 255 -  (((2 * POVToy_AccelTicks_Diff ) )) + 2;  //Adaptive timer0 reload value
#endif
                if( POVToy_TMR0L_ReloadCalc > 40 && POVToy_TMR0L_ReloadCalc < 225) //Put a limit to display refresh speed.
                {
                    POVToy_TMR0L_Reload = POVToy_TMR0L_ReloadCalc;
                }
                POVToy_Display_Index = 0;        //Reset display index. Reached left end
                POVToy_AccelTicks = 0;           //Reset ticks. Reached left end.
                POVToy_XAccel_TransitionLock=1;
            }
        }

        if((((uint8_t)POVToy_AccelXFiltered ) > -127) && (((uint8_t)POVToy_AccelXFiltered ) < -POVTOY_ACCELERATION_THRESHOLD))
        {
            if(POVToy_XAccel_TransitionLock==1)
            {
                POVToy_Display_Direction = POVTOY_DIRECTION_LEFT;
                POVToy_AccelTicks_Diff   = POVToy_AccelTicks;
                POVToy_XAccel_TransitionLock=0;
            }
        }
        INTCON3bits.INT1IF = 0;
    }

}

void POVToy_SetBrightness(uint8_t brightness)
{

    T2CON = 0b00000111;    // 1:16 Prescale, Timer2 On
    PR2 = 254;             // Slowest PWM frequency possible (16 Mhz Crystal).
    CCPR1L = brightness;   // 0-0% Duty, 255-100% duty.
    CCP1CON = 0b00001100;
    RPOR0 = 14;           //Remap CCP1 pin to RA0
    PSTR1CONbits.STRA=1;  //Set Steering Enable bit A (i.e PxA is for PWM)
}

// Loads bitmap from EEPROM to RAM. BitmapAddress is used for
// specifiying which bitmap to read (starting from address 0). Take care of page boundry. 
// BitmapAddress can be 0, 48, 96 etc..

void POVToy_LoadBitmap(uint8_t BitmapAddress)
{
	uint8_t i;
    //Test code : This writes the sample bitmap to SPI Flash. Remove this code in final version
    //SPIFlash_WritePage( 0, &POVTOY_BITMAPx[0]);
    //SPIFlash_WritePage( 16, &POVTOY_BITMAPx[16]);
    //SPIFlash_WritePage( 32, &POVTOY_BITMAPx[32]);


    //SPIFlash_ReadPage(BitmapAddress + 0, &POVTOY_BITMAP[0]);
    //SPIFlash_ReadPage(BitmapAddress + 16, &POVTOY_BITMAP[16]);
    //SPIFlash_ReadPage(BitmapAddress + 32, &POVTOY_BITMAP[32]);

	for(i=0; i<48; i++){

		POVTOY_BITMAP[i]=POVTOY_BITMAPx[i];
		
	}
}

uint8_t POVToy_ReadSwitch(void)
{
    return(LATCbits.LATC6); // Implement suitable debouncing when using this value.
}


