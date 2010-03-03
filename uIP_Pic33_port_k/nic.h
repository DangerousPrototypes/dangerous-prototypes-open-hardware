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

#include "uip.h"
//#include "compiler.h"

#define RTL8019		1
#define AX88796		2
#define ENC28J60	3

#define NIC_CHOICE ENC28J60

#if NIC_CHOICE == RTL8019
#include "rtl8019.h"
#define NICInit rtl8019Init
#define NICBeginPacketSend rtl8019BeginPacketSend
#define NICSendPacketData rtl8019SendPacketData
#define NICEndPacketSend rtl8019EndPacketSend
#define NICBeginPacketRetreive rtl8019BeginPacketRetreive
#define NICRetreivePacketData rtl8019RetreivePacketData
#define NICEndPacketRetreive rtl8019EndPacketRetreive
#endif

#if NIC_CHOICE == AX88796
#include "ax88796.h"
#define NICInit ax88796Init
#define NICBeginPacketSend ax88796BeginPacketSend
#define NICSendPacketData ax88796SendPacketData
#define NICEndPacketSend ax88796EndPacketSend
#define NICBeginPacketRetreive ax88796BeginPacketRetreive
#define NICRetreivePacketData ax88796RetreivePacketData
#define NICEndPacketRetreive ax88796EndPacketRetreive
#endif

#if NIC_CHOICE == ENC28J60
#include "enc28j60.h"
#define NICInit enc28j60Init
#define NICBeginPacketSend enc28j60BeginPacketSend
#define NICSendPacketData enc28j60PacketSend
#define NICEndPacketSend enc28j60EndPacketSend
#define NICBeginPacketRetreive enc28j60BeginPacketReceive
#define NICRetreivePacketData enc28j60PacketReceive
#define NICEndPacketRetreive enc28j60EndPacketReceive
#endif


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

#endif /* __RTL8019DEV_H__ */
