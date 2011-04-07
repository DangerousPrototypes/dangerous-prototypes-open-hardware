//The compiled firmware can be used 'as-is' with the ds30 Loader bootloader
//you may need to locate your own p33FJ128gp204.gld file.
//   It's in the C30 compiler directory:
/* \C30\support\dsPIC33F\gld\ */

#include "HardwareProfile.h"

//it's important to keep configuration bits that are compatibale with the bootloader
//if you change it from the internall/PLL clock, the bootloader won't run correctly
_FOSCSEL(FNOSC_FRCPLL)		//INT OSC with PLL (always keep this setting)
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)	//disable external OSC (always keep this setting)
_FWDT(FWDTEN_OFF)				//watchdog timer off
_FICD(JTAGEN_OFF & ICS_PGD1);//JTAG debugging off, debugging on PG1 pins enabled

#include "defines.h"
#include "sidtune_1988_Top_40_MEGAMIX.h"
//#include "sidtune_Commando_REMIX.h"
#include "sidtune_D_Y_S_P_I_D_C_E.h"
//#include "sidtune_Des_Magiers_Kugel.h"
//#include "sidtune_FAME_On_The_Run_1.h"
#include "sidtune_Gyruss.h"
#include "sidtune_Hawkeye_Remix.h"
#include "sidtune_Ikari_Intro.h"
#include "sidtune_Ikari_Intro_Song.h"
//#include "sidtune_Ikari_Warriors_USA_Version.h"
//#include "sidtune_Jump_Out.h"
#include "sidtune_Layla_Mix.h"
#include "sidtune_MCG_Intromusic.h"
#include "sidtune_Musique.h"
#include "sidtune_Nexion.h"
#include "sidtune_PCW_Tune_88.h"
#include "sidtune_R1D1.h"
#include "sidtune_Sad_Intro.h"
#include "sidtune_S_Express.h"
//#include "sidtune_Starman.h"
//#include "sidtune_Treasure_Island.h"

static const unsigned char * tunes[] = {
    sidtune_1988_Top_40_MEGAMIX,
    //sidtune_Commando_REMIX,
    sidtune_D_Y_S_P_I_D_C_E,
    //sidtune_Des_Magiers_Kugel,
    //sidtune_FAME_On_The_Run_1,
    sidtune_Gyruss,
    sidtune_Hawkeye_Remix,
    sidtune_Ikari_Intro,
    sidtune_Ikari_Intro_Song,
    //sidtune_Ikari_Warriors_USA_Version,
    //sidtune_Jump_Out,
    sidtune_Layla_Mix,
    sidtune_MCG_Intromusic,
    sidtune_Musique,
    sidtune_Nexion,
    sidtune_PCW_Tune_88,
    sidtune_R1D1,
    sidtune_Sad_Intro,
    sidtune_S_Express,
    //sidtune_Starman,
    //sidtune_Treasure_Island,
};

static const unsigned int tune_sizes[] = {
    sizeof( sidtune_1988_Top_40_MEGAMIX ),
    //sizeof( sidtune_Commando_REMIX ),
    sizeof( sidtune_D_Y_S_P_I_D_C_E ),
    //sizeof( sidtune_Des_Magiers_Kugel ),
    //sizeof( sidtune_FAME_On_The_Run_1 ),
    sizeof( sidtune_Gyruss ),
    sizeof( sidtune_Hawkeye_Remix ),
    sizeof( sidtune_Ikari_Intro ),
    sizeof( sidtune_Ikari_Intro_Song ),
    //sizeof( sidtune_Ikari_Warriors_USA_Version ),
    //sizeof( sidtune_Jump_Out ),
    sizeof( sidtune_Layla_Mix ),
    sizeof( sidtune_MCG_Intromusic ),
    sizeof( sidtune_Musique ),
    sizeof( sidtune_Nexion ),
    sizeof( sidtune_PCW_Tune_88 ),
    sizeof( sidtune_R1D1 ),
    sizeof( sidtune_Sad_Intro ),
    sizeof( sidtune_S_Express ),
    //sizeof( sidtune_Starman ),
    //sizeof( sidtune_Treasure_Island ),
};

#define MIXFREQUENCY 39062 // 10 bit resolution @ 40 MHz (11 bit resolution @ 80 MHz)
//#define MIXFREQUENCY 19531 // 11 bit resolution @ 40 MHz
#define MINIBUFFERS 4

volatile unsigned long count = 0;
volatile signed short buffer0[MIXFREQUENCY/(50*MINIBUFFERS)]; // 781 = 39062 / 50
volatile signed short buffer1[MIXFREQUENCY/(50*MINIBUFFERS)];
volatile unsigned long nSamplesPerCall;
volatile int playingBuffer1;
volatile int done;

void __attribute__((__interrupt__)) _T2Interrupt( void )
{
    LD1_O = 0;

    //++OC1RS;
    //if ( OC1RS >= (1<<11) ) {
    //    OC1RS = 0;
    //}

	if ( ! done ) {
		if ( playingBuffer1 ) {
			OC1RS = ((long)buffer1[count] + 32768) >> 6; // 16 - 6 = 10 bit (must match with the selected MIXFREQUENCY)
		} else {
			OC1RS = ((long)buffer0[count] + 32768) >> 6;
		}
		++count;
		if ( count >= nSamplesPerCall ) {
			count = 0;
			done = 1;
			playingBuffer1 = ! playingBuffer1;
		}
	}
    LD1_O = 1;

	/* reset Timer 1 interrupt flag */
 	IFS0bits.T2IF = 0;
}

void Init_Output_Compare_1()
{
    OC1CONbits.OCM = 0b110;
    RP8_O = OC1_O;
}

void Init_Timer2( unsigned long samplerate )
{
	/* ensure Timer 1 is in reset state */
	T2CON = 0;

	/* reset Timer 1 interrupt flag */
 	IFS0bits.T2IF = 0;

	/* enable Timer 1 interrupt */
 	IEC0bits.T2IE = 1;

    T2CONbits.TCKPS = 0; // 1:1 prescale value

	/* set Timer 1 period register */
	PR2 = 50e6 / samplerate - 1; // 50 MHz due to overclocking.

 	/* enable Timer 1 and start the count */
	T2CONbits.TON = 1;
}

int main(void){ //main function, execution starts here
	char c;

	AD1PCFGL = 0xFFFF; //digital pins

	//setup internal clock for 80MHz/40MIPS
	//7.37/2=3.685*43=158.455/2=79.2275
	CLKDIVbits.PLLPRE=0; // PLLPRE (N2) 0=/2
	//PLLFBD=41; //pll multiplier (M) = +2
	PLLFBD=52; //pll multiplier (M) = +2 // 7.37/2*54/2=99.495 -> 50 MHz overclocking.
	CLKDIVbits.PLLPOST=0;// PLLPOST (N1) 0=/2
    while(!OSCCONbits.LOCK);//wait for PLL ready

	//setup LEDs
	SD_TRIS = 0; // set pin direction to output
	LD1_TRIS = 0;
	IO1_TRIS = 0;
	SD_O = 1;	//set pins high (LED on)
	IO1_O = 1;
	LD1_O = 1;

	IO8_TRIS = 1; // set pin direction to input
    CNPU2bits.CN23PUE = 1;

	int tune = 0;
    while(1){//never ending loop
		word load_addr;
		word init_addr;
		word play_addr;
		byte subsongs;
		byte startsong;
		byte speed;

        c64Init();
        synth_init(MIXFREQUENCY);
        LoadSIDFromMemory( tunes[ tune ] , &load_addr, &init_addr, &play_addr, &subsongs, &startsong, &speed, tune_sizes[ tune ]  );
		++tune;
        if ( tune == sizeof( tune_sizes ) / sizeof(unsigned int) ) {
            tune = 0;
        }

        cpuJSR(init_addr, 0); // subsong

        Init_Output_Compare_1();
        Init_Timer2( MIXFREQUENCY );

        while (1) {
			cpuJSR(play_addr, 0);

            int mb;
            for ( mb=0; mb < MINIBUFFERS; ++mb ) {
                SD_O = 1;
                unsigned long nRefreshCIA = (unsigned long)(20000*(getmem(0xdc04)|(getmem(0xdc05)<<8))/0x4c00);

                if ((nRefreshCIA == 0) || (speed == 0)) nRefreshCIA = 20000;
                nSamplesPerCall = (MIXFREQUENCY*nRefreshCIA)/(1000000*MINIBUFFERS);
                if ( playingBuffer1 ) {
                    synth_render(buffer0, nSamplesPerCall);
                } else {
                    synth_render(buffer1, nSamplesPerCall);
                }
                SD_O = 0;
                while ( ! done ) {}
                done = 0;
            }

            if ( IO8_I == 0 ) {
                while ( IO8_I == 0 ) {};
                break;
            }
		}
	}
}
