//The compiled firmware can be used 'as-is' with the ds30 Loader bootloader
//you may need to locate your own p33FJ128gp204.gld file.
//   It's in the C30 compiler directory:
/* \C30\support\dsPIC33F\gld\ */

#include "HardwareProfile.h"
#include "uip.h"
#include "uip_arp.h"
#include "enc28j60.h"
#include "nic.h"
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])
//it's important to keep configuration bits that are compatibale with the bootloader
//if you change it from the internall/PLL clock, the bootloader won't run correctly
_FOSCSEL(FNOSC_FRCPLL)		//INT OSC with PLL (always keep this setting)
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)	//disable external OSC (always keep this setting)
_FWDT(FWDTEN_OFF)				//watchdog timer off
_FICD(JTAGEN_OFF & ICS_PGD1);//JTAG debugging off, debugging on PG1 pins enabled

void _T1Interrupt(void);

void initTimer(void);

void initTimer(void)
{
//timer init routine here.
// Set up the timer interrupt
IPC0  = IPC0 | 0x1000;  // Priority level is 1
IEC0  = IEC0 | 0x0008;  // Timer1 interrupt enabled
PR1   = 0xffff;
T1CON = 0x8030;

}

#define TIMERCOUNTER_PERIODIC_TIMEOUT 2000000
static int irqFlag=0;


//I don't know how to call interrupts in DSPIC
int main(void){ //main function, execution starts here
  unsigned char i;
  unsigned char arptimer=0;

	AD1PCFGL = 0xFFFF; //digital pins

	//setup internal clock for 80MHz/40MIPS
	//7.37/2=3.685*43=158.455/2=79.2275
	CLKDIVbits.PLLPRE=0; // PLLPRE (N2) 0=/2 
	PLLFBD=41; //pll multiplier (M) = +2
	CLKDIVbits.PLLPOST=0;// PLLPOST (N1) 0=/2
    
   
    while(!OSCCONbits.LOCK);//wait for PLL ready
    nic_init(); // Initialize ENC28j60. At this point uIP is not used yet

    // init uIP
    uip_init();

    // init app
    example1_init();

    // init ARP cache
    uip_arp_init();

    // init periodic timer
    initTimer();

     
    
 while(1){
    // look for a packet
    uip_len = nic_poll();
    if(uip_len == 0){
      // if timed out, call periodic function for each connection
     // if(timerCounter > TIMERCOUNTER_PERIODIC_TIMEOUT){
        if(irqFlag){
        irqFlag=0;
        
        for(i = 0; i < UIP_CONNS; i++){
          uip_periodic(i);
		
          // transmit a packet, if one is ready
          if(uip_len > 0){
            uip_arp_out();
            nic_send();
          }
        }

        /* Call the ARP timer function every 10 seconds. */
        if(++arptimer == 20){	
          uip_arp_timer();
          arptimer = 0;
        }
      }
 }else{  // packet received
      // process an IP packet
      if(BUF->type == htons(UIP_ETHTYPE_IP)){
        // add the source to the ARP cache
        // also correctly set the ethernet packet length before processing
        uip_arp_ipin();
        uip_input();

        // transmit a packet, if one is ready
        if(uip_len > 0){
          uip_arp_out();
          nic_send();
        }
       // process an ARP packet
 	  }else if(BUF->type == htons(UIP_ETHTYPE_ARP)){
        uip_arp_arpin();

        // transmit a packet, if one is ready
        if(uip_len > 0)
          nic_send();
      }
    }
  }

}

//this interrupt triggers every
void __attribute__ ((interrupt,address(0xF00), no_auto_psv)) _T1Interrupt(){
	IFS0bits.T1IF = 0;
	IEC0bits.T1IE = 0;
	T1CON = 0;
	irqFlag=1;
	IEC0bits.T1IE = 1;
}


