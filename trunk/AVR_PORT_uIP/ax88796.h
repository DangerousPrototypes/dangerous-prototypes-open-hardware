/***************************************************************************** 
*  modified by Louis Beaudoin for uIP-AVR port - November 16, 2003
*  www.embedded-creations.com
*
*  Removed: The debugging calls to the Procyon AVRLIB UART functions and the
*             register dump function was removed
*
*  Modified:
*          The ax88796Write and Read functions/macros were changed to support
*            three methods of communcating with the NIC
*          Interfacing with the AVR ports changed from sbi/cbi/etc functions
*            to direct port names
*****************************************************************************/

//*****************************************************************************
//
// File Name	: 'ax88796.h'
// Title		: ASIX 88796 L Ethernet Interface Driver
// Author		: Pascal Stang
// Created		: 10/22/2002
// Revised		: 10/26/2002
// Version		: 0.1
// Target MCU	: Atmel AVR series
// Editor Tabs	: 4
//
// Description	: This include file is designed to contain items useful to all
//					code files and projects.
//
// Based in part on code by Louis Beaudoin (www.embedded-creations.com)
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************

#ifndef AX88796_H
#define AX88796_H

#include "delay.h"
#include "compiler.h"
#include "uipopt.h"

#define u08 unsigned char

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
#define NIC_CONNECTION GENERAL_IO

#if NIC_CONNECTION != GENERAL_IO
/*** NIC Interface through External SRAM Interface ****/
#define MEMORY_MAPPED_AX88796_OFFSET 0x8000
#else
/************ NIC Interface through General I/O *******************/
// AX88796 address port
#define AX88796_ADDRESS_PORT        PORTC
#define AX88796_ADDRESS_DDR         DDRC
#define AX88796_ADDRESS_MASK		0x1F

// AX88796 data port
#define AX88796_DATA_PORT           PORTA
#define AX88796_DATA_DDR            DDRA
#define AX88796_DATA_PIN            PINA

// AX88796 control port
#define AX88796_CONTROL_PORT        PORTC
#define AX88796_CONTROL_DDR         DDRC
#define AX88796_CONTROL_READPIN     5
#define AX88796_CONTROL_WRITEPIN    6

#endif /** NIC Interface **/

// AX88796 RESET pin
#define AX88796_RESET_PORT 	PORTD
#define AX88796_RESET_DDR 	DDRD
#define AX88796_RESET_PIN 	2



/*****************************************************************************
*
* MAC address for this interface
*
*****************************************************************************/
#define MYMAC_0 UIP_ETHADDR0
#define MYMAC_1 UIP_ETHADDR1
#define MYMAC_2 UIP_ETHADDR2
#define MYMAC_3 UIP_ETHADDR3
#define MYMAC_4 UIP_ETHADDR4
#define MYMAC_5 UIP_ETHADDR5


/*****************************************************************************
*
*  Ethernet constants
*
*****************************************************************************/
#define ETHERNET_MIN_PACKET_LENGTH	0x3C
#define ETHERNET_HEADER_LENGTH		0x0E

//******************************************************************
//*	ASIX 88796 L CONTROL REGISTER OFFSETS
//******************************************************************
// Page 0
#define CR		 	0x00
#define PSTART		0x01
#define PSTOP		0x02
#define BNRY		0x03
#define TSR			0x04
#define TPSR		0x04
#define TBCR0		0x05
#define NCR			0x05
#define TBCR1		0x06
#define ISR			0x07
#define RSAR0		0x08
#define CRDA0		0x08
#define RSAR1		0x09
#define CRDAL		0x09
#define RBCR0		0x0A
#define RBCR1		0x0B
#define RSR			0x0C
#define RCR			0x0C
#define TCR			0x0D
#define CNTR0		0x0D
#define DCR			0x0E
#define CNTR1		0x0E
#define IMR			0x0F
#define CNTR2		0x0F
#define RDMAPORT  	0x10
#define MEMR		0x14
#define TR			0x15
#define GPOC		0x17
#define GPI			0x17
#define SPP_DPR    	0x18
#define SSP_SPR		0x19
#define SSP_CPR		0x1A
#define RSTPORT		0x1F
// Page 1
#define PAR0      	0x01	// Page 1
#define PAR1      	0x02	// Page 1
#define PAR2      	0x03	// Page 1
#define PAR3      	0x04	// Page 1
#define PAR4      	0x05	// Page 1
#define PAR5      	0x06	// Page 1
#define CURR		0x07	// Page 1
#define CPR			0x07	// Page 1

//******************************************************************
//*	ASIX 88796 L CR REGISTER BIT DEFINITIONS
//******************************************************************
#define  PS1		0x80 
#define  PS0		0x40 
#define  RD2		0x20 
#define  RD1		0x10 
#define  RD0		0x08 
#define  TXP		0x04 
#define  START		0x02 
#define  STOP		0x01 
//******************************************************************
//*	ASIX 88796 L RCR REGISTER BIT DEFINITIONS
//******************************************************************
#define  INTT		0x40 
#define  MON		0x20 
#define  PRO		0x10 
#define  AM			0x08 
#define  AB			0x04 
#define  AR			0x02 
#define  SEP		0x01 
//******************************************************************
//*	ASIX 88796 L ISR REGISTER BIT DEFINITIONS
//******************************************************************
#define  RST		0x80
#define  RDC		0x40
#define  OVW		0x10
#define  RXE		0x08
#define  TXE		0x04
#define  PTX		0x02
#define  PRX		0x01
//******************************************************************
//*	ASIX 88796 L TEST REGISTER DEFINITIONS
//******************************************************************
#define  AUTOD		0x01 
#define  RST_B		0x02
#define  RST_10B	0x04
#define  RST_TXB	0x08
//******************************************************************
//*	ASIX 88796 L GPOC BITS DEFINITIONS
//******************************************************************
#define  GPO0		0x01
#define	 MPSEL		0x10
#define  MPSET		0x20
#define  PPDSET		0x40
//******************************************************************
//*	ASIX 88796 L MEMR BITS DEFINITIONS
//******************************************************************
#define  MDC		0x01
#define  MDIR		0x02
#define  MDI		0x04
#define  MDO		0x08
#define  EECS		0x10
#define  EEI		0x20
#define  EEO		0x40
#define  EECLK		0x80
//******************************************************************
//*	ASIX 88796 L GPI BITS DEFINITIONS
//******************************************************************
#define  GPI2		0x40
#define  GPI1		0x20
#define  GPI0		0x10
#define  I_SPD		0x04
#define  I_DPX		0x02
#define  I_LINK		0x01
//******************************************************************
//*	ASIX 88796 L TCR BITS DEFINITIONS
//******************************************************************
#define  FDU		0x80	// full duplex
#define  PD			0x40	// pad disable
#define  RLO		0x20	// retry of late collisions
#define  TCR_LB1		0x04	// loopback 1
#define  LB0		0x02	// loopback 0
#define  CRC		0x01	// generate CRC

//******************************************************************
//*	ASIX 88796 L INITIAL REGISTER VALUES
//******************************************************************
// RCR : INT trigger active high and Accept Broadcast enet packets
#define RCR_INIT		(INTT | AB)
#define DCR_INIT		0x00   // was 0x58 for realtek RTL8019
// TCR : default transmit operation - CRC is generated
#define TCR_INIT		0x00
// IMR : interrupt enabled for receive and overrun events
#define IMR_INIT		0x11    // PRX and OVW interrupt enabled
// buffer boundaries - transmit has 6 256-byte pages
//   receive has 26 256-byte pages
//   entire available packet buffer space is allocated
#define TXSTART_INIT   	0x40
#define RXSTART_INIT   	0x46
#define RXSTOP_INIT    	0x60

/*****************************************************************************
*  RTL8019setupPorts(void);
*
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Sets up the ports used for communication with the RTL8019 NIC
*                 (data bus, address bus, read, write, and reset)
*****************************************************************************/
void ax88796SetupPorts(void);

/*****************************************************************************
*  readRTL(RTL_ADDRESS)
*  Args:        unsigned char RTL_ADDRESS - register offset of RTL register
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Reads byte from RTL8019 register
*
*  Notes - If using the External SRAM Interface, performs a read from
*            address MEMORY_MAPPED_AX88796_OFFSET + (RTL_ADDRESS<<8)
*            The address is sent in the non-multiplxed upper address port so
*            no latch is required.
*
*          If using general I/O ports, the data port is assumed to already be
*            an input, and is left as an input port when done
*
*****************************************************************************/
u08 ax88796Read(u08 address);

/*****************************************************************************
*  writeRTL( RTL_ADDRESS, RTL_DATA )
*  Args:        1. unsigned char RTL_ADDRESS - register offset of RTL register
*               2. unsigned char RTL_DATA - data to write to register
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Writes byte to RTL8019 register.
*
*  Notes - If using the External SRAM Interface, performs a write to
*            address MEMORY_MAPPED_AX88796_OFFSET + (RTL_ADDRESS<<8)
*            The address is sent in the non-multiplxed upper address port so
*            no latch is required.
*
*          If using general I/O ports, the data port is left in the input
*            state with pullups enabled
*
*****************************************************************************/
void ax88796Write(u08 address, u08 data);

/*****************************************************************************
*  initRTL8019(void);
*
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Sets up the RTL8019 NIC hardware interface, and initializes
*                 the buffers and configuration of the NIC
*****************************************************************************/
void ax88796Init(void);

/*****************************************************************************
*  RTL8019beginPacketSend(unsigned int packetLength)
*  Args:        unsigned int - length of the Ethernet frame (see note)
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Sets up the NIC to send a packet
*  Notes:       The NIC will not send packets less than 60 bytes long (the min
*                 Ethernet frame length.  The transmit length is automatically
*                 increased to 60 bytes if packetLength is < 60
*****************************************************************************/
void ax88796BeginPacketSend(unsigned int packetLength);

/*****************************************************************************
*  RTL8019sendPacketData(unsigned char * localBuffer, unsigned int length)
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
void ax88796SendPacketData(unsigned char * localBuffer, unsigned int length);

/*****************************************************************************
*  RTL8019endPacketSend()
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Ends a packet send operation and instructs the NIC to transmit
*                 the frame over the network
*****************************************************************************/
void ax88796EndPacketSend(void);

/*****************************************************************************
*  overrun(void);
*
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: "Canned" receive buffer overrun function originally from
*                 a National Semiconductor appnote
*  Notes:       This function must be called before retreiving packets from
*                 the NIC if there is a buffer overrun
*****************************************************************************/
void ax88796Overrun(void);

/*****************************************************************************
*  processRTL8019Interrupt(void);
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
void ax88796ProcessInterrupt(void);

/*****************************************************************************
*  unsigned char RTL8019ReceiveEmpty(void);
*
*  Returns:     non-zero (true) if buffer is empty, zero if data in buffer
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Compares the BNRY and CURR receive buffer pointers to see if
*                 there is a packet in the receive buffer
*  ** Removed as of version 0.60.1 **
*****************************************************************************/
//unsigned char RTL8019ReceiveEmpty(void);

/*****************************************************************************
*  unsigned int RTL8019beginPacketRetreive()
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
unsigned int ax88796BeginPacketRetreive(void);

/*****************************************************************************
*  RTL8019retreivePacketData(unsigned char * localBuffer, unsigned int length)
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
void ax88796RetreivePacketData(unsigned char * localBuffer,
                               unsigned int length);

/*****************************************************************************
*  RTL8019endPacketRetreive()
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Ends a packet retreive operation begun by calling
*                 RTL8019beginPacketRetreive().  The NIC buffer space used by
*                 the retreived packet is freed
*  Notes:       A packet may be removed from the buffer without being read
*                 by calling RTL8019endPacketRetreive() after
*                 RTL8019beginPacketRetreive().
*****************************************************************************/
void ax88796EndPacketRetreive(void);


//******************************************************************
//*	WRITE MII REGISTERS
//******************************************************************
void ax88796WriteMii(unsigned char phyad,unsigned char regad,unsigned int mii_data);

//******************************************************************
//*	READ MII REGISTERS
//******************************************************************
unsigned int ax88796ReadMii(unsigned char phyad,unsigned char regad);

#endif
