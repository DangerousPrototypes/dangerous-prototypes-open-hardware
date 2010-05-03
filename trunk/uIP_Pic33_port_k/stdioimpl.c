/*
* Implementations of the stdlib functions required
* for using stdlib with the Dangerous Prototypes Web Server Platform
*/

#include "HardwareProfile.h"


/*
Initialize the terminal UART for stdin/stdout
NOTE: Configures with TX disabled, and RX in Auto-baud rate mode
This will require the sync char 'U' to be received
before the TX is enabled and ANYTHING is sent 
*/ 
void InitializeUART1(void){
	//setup UART
	//U1BRG = 0x270; //9600 @ Fcy=24Mhz
	//U1BRG = 0x137; //19200 @ Fcy=24Mhz
	//U1BRG = 0x0204;  //19200 @ Fcy=40Mhz
	//U1BRG = 0x00ab;  //57600 @ Fcy=40Mhz
	U1BRG = 0x0055;  //115200 @ Fcy=40Mhz
    U1MODE = 0;
    U1MODEbits.BRGH = 1;
    U1STA = 0;
    U1MODEbits.UARTEN = 1;
    IFS0bits.U1RXIF = 0;
	U1STAbits.UTXEN = 0;	//disable TX to avoid backpowering FTDI chip when no USB attached
	U1MODEbits.ABAUD = 0;
}

/*
_mon_putc - required for puts(), printf() and friends
Outputs to UART1 ( USB Serial port )
NOTE: Nothing is output until the sync char "U" is received on UART1
for the auto-baud rate detection.
*/
void _mon_putc(char c){
	if( U1MODEbits.ABAUD == 1) return; //still waiting for auto baud. Don't transmit
	U1STAbits.UTXEN = 1; //enable UART TX
	while(U1STAbits.UTXBF == 1); //if buffer is full, wait
    U1TXREG = c;
}


int __attribute__((__section__(".libc"))) read(int handle, void *buffer, unsigned int len){
	
 	if( U1STAbits.OERR ) U1STAbits.OERR = 0; //clear any overrun
	int readCount = 0;
	char* p = (char*) buffer;
	for( ; readCount < len ; readCount ++ )
	{	
		if( U1STAbits.URXDA == 0) break;
		*p = U1RXREG;
		p++;
	}
	return readCount;
}

/*
_mon_getc - required for getchar() , gets() etc
Reads from UART1 (USB Serial port )
*/
int _mon_getc(){
	char buf;
	int count = read(1,(void*)&buf,1);
	if(count == 0) return -1;
	return (int)buf;
}



//configures the PIC hardware
void InitHardware(void){	
	AD1PCFGL = 0xFFFF; //digital pins

	//setup LEDs
/*	LED0_TRIS = 0;
	LED1_TRIS = 0;
	LED2_TRIS = 0;
	LED0_IO=1;
	LED1_IO=1;
	LED2_IO=1;
*/
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



	InitializeUART1();

	//lock PPS
/*
asm volatile (	"mov #OSCCON,w1 \n"
					"mov #0x46, w2 \n"
					"mov #0x57, w3 \n"
					"mov.b w2,[w1] \n"
					"mov.b w3,[w1] \n"
					"bset OSCCON, #6");
*/
}
