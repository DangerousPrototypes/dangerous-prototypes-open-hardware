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
#include "../hardware/nic_dma.h"
#include <string.h>
#include <stdio.h>

#define IP_TCP_HEADER_LENGTH 40
#define TOTAL_HEADER_LENGTH (IP_TCP_HEADER_LENGTH+ETHERNET_HEADER_LENGTH)


void nic_init(void)
{
	NICInit();
}


void nic_send(void)
{
//printf("\nnic_send: uip_len: %u\n", uip_len);
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

/*
//WORKING IMPLEMENTATION

	if(uip_len<=40+UIP_LLH_LEN){
		NICSendPacketData((u8 *)uip_buf, uip_len);
	}
	else{
		NICSendPacketData2(54, (u8 *)uip_buf, uip_len-40-UIP_LLH_LEN, (u8 *)uip_appdata);
	}
*/
/*



	NICBeginPacketSend(uip_len);
	
	// send packet, using data in uip_appdata if over the IP+TCP header size
	if( uip_len <= TOTAL_HEADER_LENGTH )
	{
      NICSendPacketData(uip_buf, uip_len);
	}
	else
	{
      uip_len -= TOTAL_HEADER_LENGTH;
      NICSendPacketData(uip_buf, TOTAL_HEADER_LENGTH);
	  NICSendPacketData((unsigned char *)uip_appdata, uip_len);
	}

	NICEndPacketSend();
*/
}



#if UIP_BUFSIZE > 255
unsigned int nic_poll(void)
#else 
unsigned char nic_poll(void)
#endif /* UIP_BUFSIZE > 255 */
{
int x = _mon_getc();
if( x != -1 ){
	
	if( (char) x == 'r' ){
		u16_t i;
		printf("\nlast rx: %u bytes:\n", uip_dma_rx_last_packet_length);
		for( i = 0; i < uip_dma_rx_last_packet_length ; i++ ){
			printf("%02hhx ", uip_buf[i]);
		}
		puts("\n");
	}
	if( (char) x == 't' ){
		u16_t i;
		printf("\nlast tx: %u bytes:\n", uip_dma_tx_last_packet_length);
		for( i = 0; i < uip_dma_tx_last_packet_length ; i++ ){
			printf("%02hhx ", uip_buf[i]);
		}
		puts("\n");
	}
	if( (char) x == 's' ){
		printf("\nUIP_DMA_STATUS: %04x ", UIP_DMA_STATUS.value);
		printf("\nlast tx: %u ", uip_dma_tx_last_packet_length);
		printf("\nlast rx: %u ", uip_dma_rx_last_packet_length);
		printf("\nrx pending count: %u ", uip_dma_rx_pending_packets);
		puts("\n");
	}
	if( (char) x == 'x' ){
		puts("\nbuf status reset");
		UIP_DMA_BUFFER_FREE=0;
		
		CS_DIS();
		printf("\nNICBeginPacketRetrieveDMA: %04x ",NICBeginPacketRetrieveDMA());
	}
	
	putchar((char)x);
}
	if( UIP_DMA_RX_PACKET_READY == 1 )
	{
		UIP_DMA_RX_PACKET_READY = 0;
//		printf("\nPOLL: uip_dma_rx_last_packet_length: %d",uip_dma_rx_last_packet_length);
		return uip_dma_rx_last_packet_length;

	}
/*
	else if( uip_dma_rx_pending_packets > 0 )
	{
		if( uip_acquireBuffer() )
		{
			if( ! NICBeginPacketRetrieveDMA() ) UIP_DMA_BUFFER_FREE=1;
		}
	}
*/
	return 0;
}

/*
WORKING IMPLEMENTATION
	unsigned int packetLength;
	
	packetLength = NICBeginPacketRetreive();

	// if there's no packet or an error - exit without ending the operation
	if( !packetLength )
	  return 0;

	// drop anything too big for the buffer
	if( packetLength > UIP_BUFSIZE )
	{
	  NICEndPacketRetreive();
      return 0;
	}
	
	// copy the packet data into the uIP packet buffer
	NICRetreivePacketData( uip_buf, packetLength );
	NICEndPacketRetreive();
		
#if UIP_BUFSIZE > 255
	return packetLength;
#else 
	return (unsigned char)packetLength;
#endif // UIP_BUFSIZE > 255 
		
}
*/

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

