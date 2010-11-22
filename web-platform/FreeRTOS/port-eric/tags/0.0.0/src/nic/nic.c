/*****************************************************************************
*  Module Name:       NIC Driver Interface for uIP-AVR Port
*  
*  Created By:        Louis Beaudoin (www.embedded-creations.com)
*
*  Original Release:  November 16, 2003 
*
*  Module Description:  
*  Provides three functions to interface with a NIC driver
*  These functions can be called directly from the main uIP control loop
*  to send packets from uip_buf and uip_appbuf, and store incoming packets to
*  uip_buf
*
*
*****************************************************************************/

#include "nic.h"
#include "nic_dma.h"
#include <string.h>
#include <stdio.h>

#define IP_TCP_HEADER_LENGTH 40
#define TOTAL_HEADER_LENGTH (IP_TCP_HEADER_LENGTH+ETHERNET_HEADER_LENGTH)


xSemaphoreHandle nic_init(void)
{
	return NICInit();
}


void nic_send(void)
{
	if(uip_len<=40+UIP_LLH_LEN){
		NICBeginPacketSendDMA(uip_len);
	}
	else{
		//TODO: replace memcpy with the REPEAT opcode
		//copy uip_appdata into the ui_buf, so we can DMA the whole thing out
		u16_t count = (uip_len - 40 - UIP_LLH_LEN );
		memcpy( (u8_t *)(uip_buf+54), (u8_t *)uip_appdata, count);

		/*
		u16 dest = ((u16) &uip_buf) + 54 ;
		u16 src = (u16) uip_appdata;
		u16 count = (uip_len - 40 - UIP_LLH_LEN ) / 2;
		count--;
		asm volatile (	
			"repeat %0\n"
			"mov.w [%1++],[%2++]\n"
			:: "r"(count), "r"(src), "r"(dest)
		);*/


		NICBeginPacketSendDMA(uip_len);
	}

}


/*
Try to initiate receive of a packet. If no packet pending, reset buffer state
Buffer must be acquired before calling this.
*/
void nic_rx_maybe()
{
	//TODO: ASSERT that buffer is already acquired
	if( uip_dma_rx_pending_packets == 0 || NICBeginPacketRetrieveDMA() == 0 )
	{
		UIP_DMA_BUFFER_STATUS_RESET();
	}

}

