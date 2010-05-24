

#include "hardware/HardwareProfile.h"
#include "uipsockettask.h"
#include "lib/multitasker.h"
#include "lib/uip.h"
#include "lib/uip_arp.h"
#include "libConfig/nic.h"
#include "hardware/nic_dma.h"
#include <stdio.h>

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])
unsigned char i;
unsigned char arptimer=0;

/*
* This is a co-operative task. This function must NEVER return
*/
void uip_task_main(void)
{
	while(1){
	    
		task_yield();
 	
		if( UIP_DMA_RX_PACKET_READY )
		{
			UIP_DMA_RX_PACKET_READY = 0;
			uip_len = uip_dma_rx_last_packet_length;
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
	        	if(uip_len > 0){

	          		nic_send();
				}
				else{

					nic_rx_maybe();
				}
	      	}
			else //don't know how to process this packet. Discard
			{
				puts("Unknown packet discarded");
				nic_rx_maybe();
			}
		}
		else if(UIP_DMA_PERIODIC_TIMEOUT && uip_acquireBuffer()){

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

		
	} //end while

}


