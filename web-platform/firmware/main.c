//The compiled firmware can be used 'as-is' with the ds30 Loader bootloader
//you may need to locate your own p33FJ128gp204.gld file.
//   It's in the C30 compiler directory:
/* \C30\support\dsPIC33F\gld\ */

#include "hardware/HardwareProfile.h"
#include "lib/delay.h"
#include "lib/uip.h"
#include "lib/uip_arp.h"
#include "hardware/enc28j60.h"
#include "libConfig/nic.h"
#include "hardware/nic_dma.h"
#include <stdio.h>

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])
//it's important to keep configuration bits that are compatibale with the bootloader
//if you change it from the internall/PLL clock, the bootloader won't run correctly
_FOSCSEL(FNOSC_FRCPLL)		//INT OSC with PLL (always keep this setting)
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)	//disable external OSC (always keep this setting)
_FWDT(FWDTEN_OFF)				//watchdog timer off
_FICD(JTAGEN_OFF & ICS_PGD1);//JTAG debugging off, debugging on PG1 pins enabled

void _T1Interrupt(void);

void initTimer(void){
	//timer init routine here.
	// Set up the timer interrupt
	IPC0  = IPC0 | 0x1000;  // Priority level is 1
	IEC0  = IEC0 | 0x0008;  // Timer1 interrupt enabled
	PR1   = 0xffff;
	T1CON = 0x8030;
}

#define TIMERCOUNTER_PERIODIC_TIMEOUT 2000000
static long timerCounter=0;
static int irqFlag=0;

extern void InitHardware(void);

void uip_log(char *msg){
	puts( msg );
	putchar('\n');
}

//I don't know how to call interrupts in DSPIC
int main(void){ //main function, execution starts here
  unsigned char i;
  unsigned char arptimer=0;

	//setup internal clock for 80MHz/40MIPS
	//7.37/2=3.685*43=158.455/2=79.2275
	PLLFBD=41; //pll multiplier (M) = +2
	CLKDIVbits.PLLPOST=0;// PLLPOST (N1) 0=/2
	CLKDIVbits.PLLPRE=0; // PLLPRE (N2) 0=/2 
    
    while(!OSCCONbits.LOCK);//wait for PLL ready

	InitHardware();
puts("READY\n");

    nic_init(); // Initialize ENC28j60. At this point uIP is not used yet
    puts("nic init\n");

    // init uIP
    uip_init();
    puts("uip init\n");

    // init ARP cache
    uip_arp_init();
    puts("arp init\n");

    // init periodic timer
    initTimer();
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
      	// if timed out, call periodic function for each connection
		//TODO: The periodic timer is not currently occuring (nothing is advancing timerCounter)
		//We need to setup a timer and interrupt for this.
     	if(timerCounter > TIMERCOUNTER_PERIODIC_TIMEOUT && uip_acquireBuffer()==1){
putchar('N');
	        LD1_O = !LD1_O;
			timerCounter=0;
	        for(i = 0; i < UIP_CONNS; i++){
		        uip_periodic(i);
			
	    	    // transmit a packet, if one is ready
	        	if(uip_len > 0){
	            	uip_arp_out();
	            	nic_send();
//the problem here is that we can't send from the second connection 
//until the first finishes
	          	}
	        }
	
	        /* Call the ARP timer function every 10 seconds. */
	        if(++arptimer == 20){	
		        uip_arp_timer();
	    	    arptimer = 0;
	        }
			UIP_DMA_BUFFER_STATUS_RESET();
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
  }

}



//this interrupt triggers every
void __attribute__ ((interrupt,address(0xF00), no_auto_psv)) _T1Interrupt(){
	IFS0bits.T1IF = 0;
//	IEC0bits.T1IE = 0;
//	T1CON = 0;
	irqFlag=1;
//	IEC0bits.T1IE = 1;
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

	
//static unsigned short StkAddrLo;  // order matters
//static unsigned short StkAddrHi;
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

