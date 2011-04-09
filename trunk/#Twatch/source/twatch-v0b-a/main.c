/*
 * This file is part of the #twatch project (dangerousprototypes.com).
 * NOTE: This code requires the Microchip TCP/IP stack, which is released under the Microchip license.
 *       Code written by the #twatch project is released into the public domain, 
 *		 The Microchip license still applies to the Microchip TCP/IP stack and origional code.
 *  	 Navigate this copyright and patent minefield at your own risk!
 *
 * Originally written by Ian Lesnet <ian@dangerousprototypes.com>
 *
 * To the extent possible under law, Ian Lesnet <ian@dangerousprototypes.com> has
 * waived all copyright and related or neighboring rights to this code. This
 * work is published from United States.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#define SCROLL_FPS 2
#define THIS_IS_STACK_APPLICATION //defines config bits from hardwareprofile.h here

#include "TCPIP Stack/TCPIP.h" //include the TCPIP stack

//Include #twatch modules
#include "HD44780.h" //LCD screen driver
#include "LCDTCPServer.h" //Matrix Orbital TCP server
#include "twatchv1.h" //Twitter watcher

//setup variables for TCPIP stack
//these are used externally by the stack and must have these names
APP_CONFIG AppConfig; 
static ROM BYTE SerializedMACAddress[6] = {MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3, MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};

static void InitHW(void);	//setup hardware
void LCDDHCP(IP_ADDR IPVal); //display current address on the LCD
void InterruptHandlerLow(void); //for clock tick updates
void InterruptHandlerHigh(void);

//
// main 
//
#pragma code
#if defined(__18CXX)
void main(void)
#else //twatch v1 (24FJ)
int main(void)
#endif
{
	static enum _mode{
		TWATCH=0,
		MATRIX_ORBITAL,
	}mode=TWATCH; //switch between twitter client and matrix orbital mode
    static TICK tmr1 = 0, tmr2=0;
	static char seconds=0, minutes=0;
	static DWORD myLastIP = 0; 

    InitHW();//initialize CPU and hardware
	HD44780_Reset();//reset LCD to proper bit mode
	HD44780_Init(); //initialize with default settings
	LCD_Backlight(1);
    TickInit(); //setup stack timer

	//setup the APPConfig variable
	AppConfig.Flags.bIsDHCPEnabled = TRUE;
	AppConfig.Flags.bInConfigMode = TRUE;
	memcpypgm2ram((void*)&AppConfig.MyMACAddr, (ROM void*)SerializedMACAddress, sizeof(AppConfig.MyMACAddr));
	AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul;
	AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
	AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
	AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
	AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul;
	AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul  | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul  | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul;
	AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul  | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul  | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul;
	memcpypgm2ram(AppConfig.NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
	FormatNetBIOSName(AppConfig.NetBIOSName);

    StackInit(); //init stack layers

    while(1){
		#if defined(__18CXX)
			ClrWdt();//clear the watchdog timer
		#endif

        //Update the LCD screen scroll on this timer
        if(TickGet() - tmr1 >= (TICK_SECOND/SCROLL_FPS)){ //default is 5
            tmr1 = TickGet();
            if(mode==TWATCH) LCD_refresh();//LCD refresh/scroll routine in twatch.c
        }

		//a minutes counter for determining when to refresh the search results
        if(TickGet() - tmr2 >= TICK_SECOND){
            tmr2 = TickGet();
			seconds++;
			if(seconds>59){
				seconds=0;
				minutes=1;
			}
        }

        StackTask(); //updates TCPIP stack state machines
        
        StackApplications(); //handles applications like DHCP, PING, etc.

		if(mode==TWATCH) twatchTasks(minutes);//do twatch tasks
		minutes=0;//reset minutes timer
		
		//process the TCP server/Matrix Orbital input
		switch(MatrixOrbitalTCPServer()){ //switch modes depending on return code
			case 1:	mode=MATRIX_ORBITAL; break; //got command to end twatch, Matrix Orbital mode
			case 2: mode=TWATCH; break; //got command to result twatch
		}
			
		if(myLastIP != AppConfig.MyIPAddr.Val){ //if IP address has changed
			myLastIP = AppConfig.MyIPAddr.Val; //store a copy for next time
			LCDDHCP(AppConfig.MyIPAddr); //show on LCD
			#if defined(STACK_USE_ANNOUNCE) //announce IP address change if enabled
				AnnounceIP();
			#endif
		}

	}
}

//setup the CPU and other hardware
static void InitHW(void){	

#if defined(__18CXX)//twatch v2
    OSCTUNE = 0x40;//96MHz PLL

	ClrWdt();//clear watch dog timer

	ADCON1|=0b1111;//disable all ADC

	RCONbits.IPEN = 1;	//setup interrupt stuff
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;

#else //twatch v1
	CLKDIVbits.RCDIV0=0; //clock divider to 0
    AD1PCFG = 0xFFFF;    //digital pins
	OSCCONbits.SOSCEN=0;	


	TRISBbits.TRISB13=0;//turn backlight off
	PORTBbits.RB13=0;
	
	//configure peripheral pin select for SPI interface
	//SPI1 ->enc28j60
	//B3 MISO
	//B2 MOSI
	//B12 CLK
	// Inputs
	RPINR20bits.SDI1R = 3;			//MISO1 = RP3
	
	//outputs
	RPOR1bits.RP2R = SDO1_IO; 		//RP2 = MOSI1
	RPOR6bits.RP12R = SCK1OUT_IO; 	//RP12 = SCK1

	//lock PPS
	asm volatile (	"mov #OSCCON,w1 \n" 
					"mov #0x46, w2 \n"
					"mov #0x57, w3 \n"
					"mov.b w2,[w1] \n"
					"mov.b w3,[w1] \n"
					"bset OSCCON, #6");

#endif

}

//display updated DHCP info on LCD
void LCDDHCP(IP_ADDR IPVal){
	LCD_Clear();
	LCD_CursorPosition(1);
	LCD_WriteString("IP:");
	LCD_WriteByteVal(AppConfig.MyIPAddr.v[0]);
	LCD_WriteChar('.');
	LCD_WriteByteVal(AppConfig.MyIPAddr.v[1]);
	LCD_WriteChar('.');
	LCD_WriteByteVal(AppConfig.MyIPAddr.v[2]);
	LCD_WriteChar('.');
	LCD_WriteByteVal(AppConfig.MyIPAddr.v[3]);

	LCD_CursorPosition(21);
	LCD_WriteString("MASK:");
	LCD_WriteByteVal(AppConfig.MyMask.v[0]);
	LCD_WriteChar('.');
	LCD_WriteByteVal(AppConfig.MyMask.v[1]);
	LCD_WriteChar('.');
	LCD_WriteByteVal(AppConfig.MyMask.v[2]);
	LCD_WriteChar('.');
	LCD_WriteByteVal(AppConfig.MyMask.v[3]);

	LCD_CursorPosition(41);
	LCD_WriteString("GATE:");
	LCD_WriteByteVal(AppConfig.MyGateway.v[0]);
	LCD_WriteChar('.');
	LCD_WriteByteVal(AppConfig.MyGateway.v[1]);
	LCD_WriteChar('.');
	LCD_WriteByteVal(AppConfig.MyGateway.v[2]);
	LCD_WriteChar('.');
	LCD_WriteByteVal(AppConfig.MyGateway.v[3]);

	LCD_CursorPosition(61);
	LCD_WriteString("DNS1:");
	LCD_WriteByteVal(AppConfig.PrimaryDNSServer.v[0]);
	LCD_WriteChar('.');
	LCD_WriteByteVal(AppConfig.PrimaryDNSServer.v[1]);
	LCD_WriteChar('.');
	LCD_WriteByteVal(AppConfig.PrimaryDNSServer.v[2]);
	LCD_WriteChar('.');
	LCD_WriteByteVal(AppConfig.PrimaryDNSServer.v[3]);
}

//ISR for interrupt based clock tick
#if defined(__18CXX)
	#pragma interruptlow InterruptHandlerLow
	void InterruptHandlerLow(void){TickUpdate();} //increment the tick counter
	#pragma interrupt InterruptHandlerHigh
	void InterruptHandlerHigh(void){}
	#pragma code lowVector=0x18
	void Low_ISR(void){_asm goto InterruptHandlerLow _endasm}
	#pragma code highVector=0x8
	void High_ISR(void){_asm goto InterruptHandlerHigh _endasm}
	#pragma code // Return to default code section
#endif

