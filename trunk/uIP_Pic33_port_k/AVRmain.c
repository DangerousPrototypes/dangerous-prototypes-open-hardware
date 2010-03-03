/*****************************************************************************
*  Module Name:       uIP-AVR Port - main control loop shell
*  
*  Created By:        Louis Beaudoin (www.embedded-creations.com)
*
*  Original Release:  September 21, 2002 
*
*  Module Description:  
*  This main control loop shell provides everything required for a basic uIP
*  application using the RTL8019AS NIC
*
*   
*  November 16, 2003
*    Changed NIC interface from RTL8019 specific to general NIC calls
*    Calls the uip_arp_timer function every 10 seconds
*    
*  September 30, 2002
*    Added support for Imagecraft Compiler
*****************************************************************************/


#include "uip.h"
#include "nic.h"
#include "uip_arp.h"

//#include "compiler.h"

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])



/*****************************************************************************
*  Periodic Timout Functions and variables
*
*  The periodic timeout rate can be changed depeding on your application
*  Modify these functions and variables based on your AVR device and clock
*    rate
*  The current setup will interrupt every 256 timer ticks when the timer
*    counter overflows.  timerCounter must count until 0.5 seconds have
*    alapsed
*****************************************************************************/

#define TIMER_PRESCALE    1024
#define F_CPU             20000000

//#define TIMERCOUNTER_PERIODIC_TIMEOUT (F_CPU / TIMER_PRESCALE / 2 / 256)
#define TIMERCOUNTER_PERIODIC_TIMEOUT 39/5

static unsigned char timerCounter;

void initTimer(void)
{
/*
  outp( 7, TCCR0 ) ;  // timer0 prescale 1/1024 (7)
  // interrupt on overflow
  sbi( TIMSK, TOIE0 ) ;
  timerCounter = 0;
*/

  TCCR0=0x05;
  TCNT0=0x00;
  OCR0=0x00;
  TIMSK |= _BV(TOIE0);
  timerCounter = 0;
}

#ifdef __IMAGECRAFT__
#pragma interrupt_handler SIG_OVERFLOW0:iv_TIMER0_OVF
#endif

//SIGNAL(SIG_OVERFLOW0)
ISR(TIMER0_OVF_vect)
{
  timerCounter++;
}



/*****************************************************************************
*  Main Control Loop
*
*  
*****************************************************************************/
int main(void)
{
  unsigned char i;
  unsigned char arptimer=0;

  // init NIC device driver
  nic_init();

  // init uIP
  uip_init();

  // init app
  example1_init();

  // init ARP cache
  uip_arp_init();

  // init periodic timer
  initTimer();
  
  sei();

  while(1)
  {

    // look for a packet
    uip_len = nic_poll();
    if(uip_len == 0)
    {
      // if timed out, call periodic function for each connection
      if(timerCounter > TIMERCOUNTER_PERIODIC_TIMEOUT)
      {
        timerCounter = 0;
        
        for(i = 0; i < UIP_CONNS; i++)
        {
          uip_periodic(i);
		
          // transmit a packet, if one is ready
          if(uip_len > 0)
          {
            uip_arp_out();
            nic_send();
          }
        }

        /* Call the ARP timer function every 10 seconds. */
        if(++arptimer == 20)
        {	
          uip_arp_timer();
          arptimer = 0;
        }
      }
    }
    else  // packet received
    {
      // process an IP packet
      if(BUF->type == htons(UIP_ETHTYPE_IP))
      {
        // add the source to the ARP cache
        // also correctly set the ethernet packet length before processing
        uip_arp_ipin();
        uip_input();

        // transmit a packet, if one is ready
        if(uip_len > 0)
        {
          uip_arp_out();
          nic_send();
        }
      }
      // process an ARP packet
      else if(BUF->type == htons(UIP_ETHTYPE_ARP))
      {
        uip_arp_arpin();

        // transmit a packet, if one is ready
        if(uip_len > 0)
          nic_send();
      }
    }
  }

  return 1;
}
