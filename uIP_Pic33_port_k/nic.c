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


#define IP_TCP_HEADER_LENGTH 40
#define TOTAL_HEADER_LENGTH (IP_TCP_HEADER_LENGTH+ETHERNET_HEADER_LENGTH)


void nic_init(void)
{
	NICInit();
}


void nic_send(void)
{

	if(uip_len<=40+UIP_LLH_LEN){
		NICSendPacketData((u8 *)uip_buf, uip_len);
	}
	else{
		NICSendPacketData2(54, (u8 *)uip_buf, uip_len-40-UIP_LLH_LEN, (u8 *)uip_appdata);
	}

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
#endif /* UIP_BUFSIZE > 255 */
		
}
