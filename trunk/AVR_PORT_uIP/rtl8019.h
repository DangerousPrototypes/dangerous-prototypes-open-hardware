#ifndef __RTL8019_H__
#define __RTL8019_H__

/*****************************************************************************
*  Module Name:       Realtek 8019AS Driver
*  
*  Created By:        Louis Beaudoin (www.embedded-creations.com)
*
*  Original Release:  September 21, 2002 
*
*  Module Description:  
*  Provides functions to initialize the Realtek 8019AS, and send and retreive
*  packets
*
*  September 30, 2002 - Louis Beaudoin
*    Receive functions modified to handle errors encountered when receiving a
*      fast data stream.  Functions now manually retreive data instead of
*      using the send packet command.  Interface improved by checking for
*      overruns and data in the buffer internally.
*    Corrected the overrun function - overrun flag was not reset after overrun
*    Added support for the Imagecraft Compiler
*    Added support to communicate with the NIC using general I/O ports
*
*****************************************************************************/

#include "delay.h"

#include "compiler.h"

// get the MAC address from the uIP MAC address
#include "uipopt.h"


/*****************************************************************************
*  rtl8019BeginPacketSend(unsigned int packetLength)
*  Args:        unsigned int - length of the Ethernet frame (see note)
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Sets up the NIC to send a packet
*  Notes:       The NIC will not send packets less than 60 bytes long (the min
*                 Ethernet frame length.  The transmit length is automatically
*                 increased to 60 bytes if packetLength is < 60
*****************************************************************************/
void rtl8019BeginPacketSend(unsigned int packetLength);


/*****************************************************************************
*  rtl8019SendPacketData(unsigned char * localBuffer, unsigned int length)
*  Args:        1. unsigned char * localBuffer - Pointer to the beginning of
*                    the buffer to load into the NIC
*               2. unsigned char length - number of bytes to copy to
*                    the NIC
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Loads length # of bytes from a local buffer to the transmit
*                 packet buffer
*  Notes:       RTL8019beginPacketSend() must be called before sending
*                 any data.
*               Several calls to RTL8019retreivePacketData() may be made to 
*                 copy packet data from different buffers
*****************************************************************************/
void rtl8019SendPacketData(unsigned char * localBuffer, unsigned int length);


/*****************************************************************************
*  rtl8019EndPacketSend()
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Ends a packet send operation and instructs the NIC to transmit
*                 the frame over the network
*****************************************************************************/
void rtl8019EndPacketSend(void);


/*****************************************************************************
*  rtl8019Init(void);
*
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Sets up the RTL8019 NIC hardware interface, and initializes
*                 the buffers and configuration of the NIC
*****************************************************************************/
void rtl8019Init(void);


/*****************************************************************************
*  rtl8019ProcessInterrupt(void);
*
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Reads the NIC's ISR register looking for a receive buffer
*                 overrun - which is then handled.
*  Notes:       The function does not need to be called in response to an
*                 interrupt.  The function can be polled and the NIC's INT
*                 line not used.  This function should be called before
*                 attempting to retreive a packet from the NIC
*****************************************************************************/
void rtl8019ProcessInterrupt(void);


/*****************************************************************************
*  unsigned int rtl8019BeginPacketRetreive()
*  Returns:     unsigned int - length of the Ethernet frame (see note)
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Sets up the NIC to retreive a packet
*  Notes:       The size returned is the size of all the data in the Ethernet
*                 frame minus the Ethernet checksum.  This may include unused
*                 trailer bytes appended if data is less than the minimum
*                 Ethernet frame length (60 bytes).  A size of zero indicates
*                 there are no packets available.
*               A call to RTL8019beginPacketRetreive() must be followed by a
*                 call to RTL8019endPacketRetreive() regardless if data is
*                 retreived, unless 0 is returned.
*****************************************************************************/
unsigned int rtl8019BeginPacketRetreive(void);


/*****************************************************************************
*  rtl8019RetreivePacketData(unsigned char * localBuffer, unsigned int length)
*  Args:        1. unsigned char * localBuffer - Pointer to the beginning of
*                    the buffer to store the ethernet frame.
*               2. unsigned char length - number of bytes to copy to
*                    localBuffer
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Loads length # of bytes from the receive packet buffer to
*                 a local buffer
*  Notes:       RTL8019beginPacketRetreive() must be called before retreiving
*                 any data.
*               Several calls to RTL8019retreivePacketData() may be made to 
*                 copy packet data to different buffers
*****************************************************************************/
void rtl8019RetreivePacketData(unsigned char * localBuffer,
                               unsigned int length);

/*****************************************************************************
*  rtl8019EndPacketRetreive()
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Ends a packet retreive operation begun by calling
*                 RTL8019beginPacketRetreive().  The NIC buffer space used by
*                 the retreived packet is freed
*  Notes:       A packet may be removed from the buffer without being read
*                 by calling RTL8019endPacketRetreive() after
*                 RTL8019beginPacketRetreive().
*****************************************************************************/
void rtl8019EndPacketRetreive(void);


/*****************************************************************************
*
*  AVR hardware setup
*
*    External SRAM Interfaces:
*    -------------------------------------------------------------------------
*    NIC_CONNECTION == MEMORY_MAPPED
*      The NIC is mapped into memory at the OFFSET location.  The five NIC
*        address lines are taken from the externally latched signals A0-A4.
*        
*    NIC_CONNECTION == MEMORY_MAPPED_HIGHADDR
*      The five NIC address lines are taken from A8-A12 (uses the
*        non-multiplexed address port so no latch is required).  The OFFSET is
*        added to this value, so for example, you can use an offset of 0x8000 
*        and use the A15 pin as a chip select signal
*
*    General I/O Interface:
*    -------------------------------------------------------------------------
*    NIC_CONNECTION == GENERAL_IO
*      One full port is required for the data, and the first five pins from
*        another port is required for address.  The read and write pins can
*        come from another port, or be held in two of the remaining three
*        pins on the address port
*
*    One output pin is required for hard resetting the NIC (In the General I/O
*      this can be from the same port as the address and/or read/write pins)
*
*****************************************************************************/

#define GENERAL_IO 0
#define MEMORY_MAPPED_HIGHADDR 1
#define MEMORY_MAPPED 2

// set the connection type used to communicate with the NIC
#define NIC_CONNECTION MEMORY_MAPPED

#if NIC_CONNECTION != GENERAL_IO
/*** NIC Interface through External SRAM Interface ****/
#define MEMORY_MAPPED_RTL8019_OFFSET 0x8300
#else 
/************ NIC Interface through General I/O *******************/

// RTL8019 address port
#define RTL8019_ADDRESS_PORT        PORTD
#define RTL8019_ADDRESS_DDR         DDRD
#define RTL8019_ADDRESS_MASK        0x1F

// RTL8019 data port
#define RTL8019_DATA_PORT           PORTA
#define RTL8019_DATA_DDR            DDRA
#define RTL8019_DATA_PIN            PINA

// RTL8019 control port
#define RTL8019_CONTROL_PORT        PORTB
#define RTL8019_CONTROL_DDR         DDRB
#define RTL8019_CONTROL_READPIN     2
#define RTL8019_CONTROL_WRITEPIN    1

#endif /** NIC Interface **/

// RTL8019 RESET pin
#define RTL8019_RESET_PORT 	PORTD
#define RTL8019_RESET_DDR 	DDRD
#define RTL8019_RESET_PIN 	7


/*****************************************************************************
*
*  Ethernet constants
*
*****************************************************************************/
#define ETHERNET_MIN_PACKET_LENGTH	0x3C
#define ETHERNET_HEADER_LENGTH		0x0E



/*****************************************************************************
*
* MAC address assigned to the RTL8019
*
*****************************************************************************/
#define MYMAC_0 UIP_ETHADDR0
#define MYMAC_1 UIP_ETHADDR1
#define MYMAC_2 UIP_ETHADDR2
#define MYMAC_3 UIP_ETHADDR3
#define MYMAC_4 UIP_ETHADDR4
#define MYMAC_5 UIP_ETHADDR5










#endif /* __RTL8019_H__ */
