#ifndef __NIC_H__
#define __NIC_H__

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

#include "../lib/uip.h"
#include "../hardware/enc28j60.h"



#define NICInit                  enc28j60Init
#define NICBeginPacketSend       enc28j60BeginPacketSend
#define NICSendPacketData        enc28j60PacketSend
#define NICSendPacketData2       enc28j60PacketSend2
#define NICEndPacketSend         enc28j60EndPacketSend
#define NICBeginPacketRetreive   enc28j60BeginPacketReceive
#define NICRetreivePacketData    enc28j60PacketReceive
#define NICEndPacketRetreive     enc28j60EndPacketReceive
#define NICBeginPacketRetrieveDMA   enc28j60BeginPacketReceiveDMA
#define NICBeginPacketSendDMA 		enc28j60BeginPacketSendDMA


/*****************************************************************************
*  nic_init()
*  Created By:  Louis Beaudoin
*  Date:        November 16, 2003 
*  Description: Power-up initialization of the NIC
*****************************************************************************/
void nic_init(void);


/*****************************************************************************
*  nic_send()
*  Created By:  Louis Beaudoin
*  Date:        November 16, 2003 
*  Description: Sends the packet contained in uip_buf and uip_appdata over
*                 the network
*****************************************************************************/
void nic_send(void);


/*****************************************************************************
*  unsigned char/int nic_poll()
*  Returns:     Length of the packet retreived, or zero if no packet retreived
*  Created By:  Louis Beaudoin
*  Date:        November 16, 2003 
*  Description: Polls the NIC looking for an overflow condition or a new
*                 packet in the receive buffer.  If a new packet exists and
*                 will fit in uip_buf, it is retreived, and the length is
*                 returned.  A packet bigger than the buffer is discarded
*****************************************************************************/
#if UIP_BUFSIZE > 255
unsigned int nic_poll(void);
#else 
unsigned char nic_poll(void);
#endif /* UIP_BUFSIZE > 255 */



/*
Try to initiate receive of a packet. If no packet pending, reset buffer state
Buffer must be acquired before calling this.
*/
void nic_rx_maybe(void);

#endif /* __NIC_H__ */
