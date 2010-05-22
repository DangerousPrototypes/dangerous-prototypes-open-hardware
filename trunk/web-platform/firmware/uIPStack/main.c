//The compiled firmware can be used 'as-is' with the ds30 Loader bootloader
//you may need to locate your own p33FJ128gp204.gld file.
//   It's in the C30 compiler directory:
/* \C30\support\dsPIC33F\gld\ */

#include "hardware/HardwareProfile.h"
#include "lib/uip.h"
#include "lib/uip_arp.h"
#include "libConfig/nic.h"
#include "hardware/nic_dma.h"
#include "hardware/rtcc.h"
#include <stdio.h>

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])
//it's important to keep configuration bits that are compatibale with the bootloader
//if you change it from the internall/PLL clock, the bootloader won't run correctly
_FOSCSEL(FNOSC_FRCPLL)		//INT OSC with PLL (always keep this setting)
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)	//disable external OSC (always keep this setting)
_FWDT(FWDTEN_OFF)				//watchdog timer off
_FICD(JTAGEN_OFF & ICS_PGD1);//JTAG debugging off, debugging on PG1 pins enabled



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
//auto baud disabled for now
//	U1MODEbits.ABAUD = 1;
}


//configures the PIC hardware
void InitHardware(void){	
	AD1PCFGL = 0xFFFF; //digital pins


	//setup internal clock for 80MHz/40MIPS
	//7.37/2=3.685*43=158.455/2=79.2275
	PLLFBD=41; //pll multiplier (M) = +2
	CLKDIVbits.PLLPOST=0;// PLLPOST (N1) 0=/2
	CLKDIVbits.PLLPRE=0; // PLLPRE (N2) 0=/2 
    
    while(!OSCCONbits.LOCK);//wait for PLL ready



	//setup LEDs
	LD1_TRIS = 0;
//	LD2_TRIS = 0;
	LD1_O=1;
//	LD2_O=1;

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

//setup a logger for uip
//Just sends the msg to stdout ( UART 1 )
void uip_log(char *msg){
	puts( msg );
	putchar('\n');
}

//main function, execution starts here
int main(void){
	unsigned char i;
	unsigned char arptimer=0;

	InitHardware();
	rtcc_init();

	//TODO: set some sensible rtcc defaults until we can do NTP
	struct tm time;
	time.tm_year = 2010 - 1900;
	time.tm_mon = 5;
	time.tm_mday = 16;
	time.tm_hour = 15;
	time.tm_min = 34;
	time.tm_sec = 0;
	time.tm_wday = 0;
	rtcc_set_tm( time );
	

	puts("READY\n");

	// Initialize ENC28j60. At this point uIP is not used yet
    nic_init(); 
    puts("nic init\n");

    // init uIP
    uip_init();
    puts("uip init\n");

    // init ARP cache
    uip_arp_init();
    puts("arp init\n");

    // init periodic timer
    rtcc_set_alarm( time, 0, 0, true );
	rtcc_enable_alarm();
    puts("timer init\n");

	// init app
    example1_init();
    puts("example1 init\n");
	while(1){
	    // look for a packet
		uip_len = nic_poll();
		//printf("uip_len: %u", uip_len );
		
	    if(uip_len == 0){
			//no packet rxed
			if(UIP_DMA_PERIODIC_TIMEOUT && uip_acquireBuffer()){
				UIP_DMA_PERIODIC_TIMEOUT=0;
	
				//blink LED to show we're alive
		        LD1_O = !LD1_O;
	
		        for(i = 0; i < UIP_CONNS; i++){
					uip_periodic(i);
				
		    	    // transmit a packet, if one is ready
		        	if(uip_len > 0){
		            	uip_arp_out();
		            	nic_send();
	//the problem here is that we can't send from the second connection 
	//until the first finishes. Need to address that
		          	}
		        }
		
		        /* Call the ARP timer function every 10 seconds. */
		        if(++arptimer == 20){	
			        uip_arp_timer();
		    	    arptimer = 0;
		        }
				if( ENC_DMACONbits.CHEN == 0 ) nic_rx_maybe();
			}
		}
		else
		{
			// packet received - buffer is already acquired
	
	      	// process an IP packet
	      	if(BUF->type == HTONS(UIP_ETHTYPE_IP)){
	        	// add the source to the ARP cache
	        	// also correctly set the ethernet packet length before processing
	        	uip_arp_ipin();
	        	uip_input();
	
	     		// transmit a packet, if one is ready
	        	if(uip_len > 0){
	          		uip_arp_out();
	          		nic_send();
	        	}
				else nic_rx_maybe();
			}
			else if(BUF->type == HTONS(UIP_ETHTYPE_ARP)){
	
				// process an ARP packet
	 	  		uip_arp_arpin();
	
	        	// transmit a packet, if one is ready
	        	if(uip_len > 0)
	          		nic_send();
				else nic_rx_maybe();
	      	}
			else //don't know how to process this packet. Discard
			{
				puts("Unknown packet discarded");
				nic_rx_maybe();
			}
		}
	} //end while

} //end main

//This occurs every half second, driven by the RTCC chime
//This is being used to drive the uip periodic processing
void __attribute__ ((interrupt, auto_psv)) _RTCCInterrupt()
{
	UIP_DMA_PERIODIC_TIMEOUT=1;
	IFS3bits.RTCIF = 0;
}

//Address Error Trap
union DWORD
{
	struct
	{
		unsigned short low;
		unsigned short high;
	} word;
	unsigned long value;
};

static union DWORD StkAddress;
void __attribute__((no_auto_psv,__interrupt__(__preprologue__( \
	"mov #_StkAddress+2,w1\n 	\
	pop [w1--]\n			\
	pop [w1]\n			\
	push [w1]\n			\
	push [++w1]")))) _AddressError(){
	
	INTCON1bits.ADDRERR = 0;
	StkAddress.value -= 2;
	printf("\nAddress Error @ %08lx",StkAddress.value );
}


