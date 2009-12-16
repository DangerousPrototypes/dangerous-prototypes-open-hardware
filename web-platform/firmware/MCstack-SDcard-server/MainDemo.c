// DangerousPrototypes.com web platform demo
// SD card web server
//
//BEFORE YOU COMPILE!!!!
//Due to licensing issues, we can't redistribute the "Microchip Applications Libraries" (TCPIP stack, etc). 
//You can get them from the Microchip website for free: 
//http://www.microchip.com/tcpip
//
//1.Download and install the "Microchip Applications Libraries". 
//   These files install to c:\Microchip Soultions\ by default.
//2.Put the replacement files in this folder into the Microchip MDD HTTP demo 
//   directory (C:\Microchip Solutions\TCPIP MDD Demo App\)
//   Replace 6 files in total: 
//	 Maindemo.c/.h, HardwareProfile.h, TCPIPConfig.h, TCPIP MDD SD Card Demo App-C30.mcw/.mcp
//3.That's it. You've got the latest source and we're compliant with the license.
//4.Depending on the install location you may need to tweak the include paths 
//   under Project->build options. 
//
// See C:\Microchip Solutions\Microchip\Help\ for the MDD Server help document
//
//EXTRA STEPS FOR BOOTLOADER:
//To use this firmware with the dsPIC30 bootloader:
//1. Export the firmware (File->Export)
//2. Set 0x153FE as the end memory address
//3. Save the firmware and bootload as normal

#define THIS_IS_STACK_APPLICATION //define as entry point, include config bit settings
									//also needed by StackTsk.h, so don't change the name

#include "TCPIP Stack/TCPIP.h" //include TCPIP headers
#include "MDD File System/FSIO.h" //include FAT file system

APP_CONFIG AppConfig;
static void InitHardware(void);
unsigned char UART1RXRdy(void);
unsigned char UART1RX(void);
void UART1TX(char c);
void InitializeUART1(void);

volatile BOOL MemInterfaceAttached=TRUE; //HTTP2 server requires this external variable (don't change the name)
										//could be used to detect media, but we just set it to always true
										//be sure to have an SD card in the slot at startup...
int main(void){

	static long ticks = 0;
	static long prevIP = 0;
	BOOL FSready=FALSE; //FileSystemInit() returns type BOOL
	
	InitHardware(); //setup hardware

    TickInit();	//setup the tick timer

	//MPFSInit(); //setup MPFS EEPROM file system

	//setup the TCPIP stack config variable
	AppConfig.Flags.bIsDHCPEnabled = TRUE;
	AppConfig.Flags.bInConfigMode = TRUE;
	AppConfig.MyMACAddr.v[0] = MY_DEFAULT_MAC_BYTE1;
	AppConfig.MyMACAddr.v[1] = MY_DEFAULT_MAC_BYTE2;
	AppConfig.MyMACAddr.v[2] = MY_DEFAULT_MAC_BYTE3;
	AppConfig.MyMACAddr.v[3] = MY_DEFAULT_MAC_BYTE4;
	AppConfig.MyMACAddr.v[4] = MY_DEFAULT_MAC_BYTE5;
	AppConfig.MyMACAddr.v[5] = MY_DEFAULT_MAC_BYTE6;
	AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul;
	AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
	AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
	AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
	AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul;
	AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul  | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul  | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul;
	AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul  | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul  | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul;

    StackInit();	//setup the stack

    while(1){//never ending loop

		if(FSready==FALSE) FSready=FileSystemInit(); //attempt to initialize the FAT SD card library

        if((TickGet() - ticks) >= (TICK_SECOND/2)){ //blink LED
            ticks = TickGet();
            LED0_IO ^= 1;
        }
		
		//service the stack, includes PING, DHCP client, HTTP2 server, etc (see stacktask.c)
        StackTask();   
        StackApplications();

		#ifdef STACK_USE_ANNOUNCE //announce IP address change if enabled
		if(prevIP != AppConfig.MyIPAddr.Val){
			prevIP = AppConfig.MyIPAddr.Val;
			AnnounceIP();
		}
		#endif

	}
}

//configures the PIC hardware
static void InitHardware(void){	
	AD1PCFGL = 0xFFFF; //digital pins

	//setup internal clock for 80MHz/40MIPS
	//7.37/2=3.685*43=158.455/2=79.2275
	CLKDIVbits.PLLPRE=0; // PLLPRE (N2) 0=/2 
	PLLFBD=41; //pll multiplier (M) = +2
	CLKDIVbits.PLLPOST=0;// PLLPOST (N1) 0=/2
    while(!OSCCONbits.LOCK);//wait for PLL ready

	//setup LEDs
	LED0_TRIS = 0;
	LED1_TRIS = 0;
	LED2_TRIS = 0;
	LED0_IO=1;
	LED1_IO=1;
	LED2_IO=1;

	//custom pin assignments for our hardware
	// ENC28J60 I/O pins
	//mapping:
	//A2 ETH-INT
	//C2 MISO
	//C1 MOSI
	//C0 CLK
	//B3 CS
	//B2 RST
	//CS and RST pins
	//MISO1 C2/RP18 (input)
	SDI1R_I = 18;			
	//CLK1 C0/RP16 (output)
	RP16_O = SCK1OUT_O; 	
	//MOSI1 C1/RP17 (output)
	RP17_O = SDO1_O;		

	//SD CARD PPS
	//MISO1 B10/RP10 (input)
	SDI2R_I = 10;			
	//CLK1 B11/RP11 (output)
	RP11_O = SCK2OUT_O; 	
	//MOSI1 B12/RP12 (output)
	RP12_O = SDO2_O;
	
/*	//EEPROM PPS
	//MISO2 C8/RP24 (input)
	SDI2R_I = 24;			
	//CLK2 C6/RP22 (output)
	RP22_O = SCK2OUT_O; 	
	//MOSI2 B9/RP9 (output)
	RP9_O = SDO2_O;		
	XEEInit();
*/
	//uart
	//RX PR14 (input)
	U1RXR_I = 14;
	//TX RP15 (output)
	RP15_O=U1TX_O;

	//InitializeUART1();

	//lock PPS
	asm volatile (	"mov #OSCCON,w1 \n"
					"mov #0x46, w2 \n"
					"mov #0x57, w3 \n"
					"mov.b w2,[w1] \n"
					"mov.b w3,[w1] \n"
					"bset OSCCON, #6");
}


//is data available in RX buffer?
//#define UART1RXRdy() U1STAbits.URXDA
unsigned char UART1RXRdy(void){
    return U1STAbits.URXDA;
}

//get a byte from UART
unsigned char UART1RX(void){

    while(U1STAbits.URXDA == 0);
	return U1RXREG;
}

//add byte to buffer, pause if full
//uses PIC 4 byte UART FIFO buffer
void UART1TX(char c){
	U1STAbits.UTXEN = 1; //enable UART TX
	while(U1STAbits.UTXBF == 1); //if buffer is full, wait
    U1TXREG = c;
	while(U1STAbits.TRMT== 0); //wait for UART to empty
	U1STAbits.UTXEN = 0;	//disable TX to avoid backpowering FTDI chip when no USB attached
}

//Initialize the terminal UART
void InitializeUART1(void){
	//setup UART
    U1BRG = 85;//86@80mhz, 85@79.xxx=115200
    U1MODE = 0;
    U1MODEbits.BRGH = 1;
    U1STA = 0;
    U1MODEbits.UARTEN = 1;
    IFS0bits.U1RXIF = 0;
}

//stack overslow interrupt vectors
void _ISR __attribute__((__no_auto_psv__)) _AddressError(void)
{
    Nop();
	Nop();
}
void _ISR __attribute__((__no_auto_psv__)) _StackError(void)
{
    Nop();
	Nop();
}

