#include "rtl8019.h"

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
*  November 16, 2003 - Louis Beaudoin
*    The rtl8019Write and Read functions/macros were changed to support
*      three methods of communcating with the NIC
*    Interfacing with the AVR ports changed from sbi/cbi/etc functions
*      to direct port names
*    Renamed functions to be more consistant with the two NIC drivers
*    Overrun function now retransmits if resend is set (thanks Krzysztof)
* 
*  November 15, 2002 - Louis Beaudoin
*    processRTL8019Interrupt() - bit mask mistake fixed
*
*  November 8, 2003 - Louis Beaudoin
*    Changed delay library function calls
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


/*****************************************************************************
*  rtl8019Write( RTL_ADDRESS, RTL_DATA )
*  Args:        1. unsigned char RTL_ADDRESS - register offset of RTL register
*               2. unsigned char RTL_DATA - data to write to register
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Writes byte to RTL8019 register.
*
*  Notes - If using the External SRAM Interface, performs a write to
*            address MEMORY_MAPPED_RTL8019_OFFSET + (RTL_ADDRESS<<8)
*            The address is sent in the non-multiplxed upper address port so
*            no latch is required.
*
*          If using general I/O ports, the data port is left in the input
*            state with pullups enabled
*
*****************************************************************************/
#if NIC_CONNECTION == MEMORY_MAPPED_HIGHADDR
#define rtl8019Write(RTL_ADDRESS,RTL_DATA) do{ *(volatile unsigned char *) \
                             (MEMORY_MAPPED_RTL8019_OFFSET \
                             + (((unsigned char)(RTL_ADDRESS)) << 8)) = \
                             (unsigned char)(RTL_DATA); } while(0)

#endif
                             
#if NIC_CONNECTION == MEMORY_MAPPED
#define rtl8019Write(RTL_ADDRESS,RTL_DATA) do{ *(volatile unsigned char *) \
                             (MEMORY_MAPPED_RTL8019_OFFSET \
                             + (unsigned char)(RTL_ADDRESS)) = \
                             (unsigned char)(RTL_DATA); } while(0)

#endif

#if NIC_CONNECTION == GENERAL_IO

void rtl8019Write(unsigned char address, unsigned char data)
{
    // assert the address, leaving the non-address pins intact
    address |= (RTL8019_ADDRESS_PORT & ~RTL8019_ADDRESS_MASK);
    RTL8019_ADDRESS_PORT = address;
    
	// set data bus as output and place data on bus
    RTL8019_DATA_DDR = 0xFF;
    RTL8019_DATA_PORT = data;
    
	// toggle write pin
    RTL8019_CONTROL_PORT &= ~_BV(RTL8019_CONTROL_WRITEPIN);
    nop();
    RTL8019_CONTROL_PORT |= _BV(RTL8019_CONTROL_WRITEPIN);

    
	// set data port back to input with pullups enabled
    RTL8019_DATA_DDR = 0x00;
    RTL8019_DATA_PORT = 0xFF;
}

#endif

/*****************************************************************************
*  rtl8019Read(RTL_ADDRESS)
*  Args:        unsigned char RTL_ADDRESS - register offset of RTL register
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Reads byte from RTL8019 register
*
*  Notes - If using the External SRAM Interface, performs a read from
*            address MEMORY_MAPPED_RTL8019_OFFSET + (RTL_ADDRESS<<8)
*            The address is sent in the non-multiplxed upper address port so
*            no latch is required.
*
*          If using general I/O ports, the data port is assumed to already be
*            an input, and is left as an input port when done
*
*****************************************************************************/
#if NIC_CONNECTION == MEMORY_MAPPED_HIGHADDR
#define rtl8019Read(RTL_ADDRESS) (*(volatile unsigned char *) \
                       (MEMORY_MAPPED_RTL8019_OFFSET \
                       + (((unsigned char)(RTL_ADDRESS)) << 8)) )
#endif
                             
#if NIC_CONNECTION == MEMORY_MAPPED

#define rtl8019Read(RTL_ADDRESS) (*(volatile unsigned char *) \
                       (MEMORY_MAPPED_RTL8019_OFFSET \
                       + (unsigned char)(RTL_ADDRESS)) )
#endif

#if NIC_CONNECTION == GENERAL_IO

unsigned char rtl8019Read(unsigned char address)
{
    unsigned char byte;
   
    // assert the address, leaving the non-address pins intact
    address |= (RTL8019_ADDRESS_PORT & ~RTL8019_ADDRESS_MASK);
    RTL8019_ADDRESS_PORT = address;
   
    // assert read
    RTL8019_CONTROL_PORT &= ~_BV(RTL8019_CONTROL_READPIN);
    nop();
   
    // read in the data
    byte = RTL8019_DATA_PIN;

    // negate read
    RTL8019_CONTROL_PORT |= _BV(RTL8019_CONTROL_READPIN);

    return byte;
}

#endif                       



/*****************************************************************************
*  rtl8019SetupPorts(void);
*
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Sets up the ports used for communication with the RTL8019 NIC
*                 (data bus, address bus, read, write, and reset)
*****************************************************************************/
void rtl8019SetupPorts(void)
{

#if NIC_CONNECTION == GENERAL_IO

    // make the address port output
	RTL8019_ADDRESS_DDR = RTL8019_ADDRESS_MASK;
    
    // make the data port input with pull-ups
    RTL8019_DATA_PORT = 0xFF;

	// make the control port read and write pins outputs and asserted
	RTL8019_CONTROL_DDR |= _BV(RTL8019_CONTROL_READPIN);
    RTL8019_CONTROL_DDR |= _BV(RTL8019_CONTROL_WRITEPIN);
	          
	RTL8019_CONTROL_PORT |= _BV(RTL8019_CONTROL_READPIN);
	RTL8019_CONTROL_PORT |= _BV(RTL8019_CONTROL_WRITEPIN);

#else

  	// enable external SRAM interface - no wait states
    MCUCR |= _BV(SRE);

#endif

	// enable output pin for Resetting the RTL8019
	RTL8019_RESET_DDR |= _BV(RTL8019_RESET_PIN);
}



/*****************************************************************************
*  HARD_RESET_RTL8019()
*
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: Simply toggles the pin that resets the NIC
*****************************************************************************/
#define HARD_RESET_RTL8019() do{ RTL8019_RESET_PORT |= _BV(RTL8019_RESET_PIN);\
                                delay_ms(10); \
                                RTL8019_RESET_PORT &= ~_BV(RTL8019_RESET_PIN);}\
                                while(0)



/*****************************************************************************
*  rtl8019Overrun(void);
*
*  Created By:  Louis Beaudoin
*  Date:        September 21, 2002
*  Description: "Canned" receive buffer overrun function originally from
*                 a National Semiconductor appnote
*  Notes:       This function must be called before retreiving packets from
*                 the NIC if there is a buffer overrun
*****************************************************************************/
void rtl8019Overrun(void);




//******************************************************************
//*	REALTEK CONTROL REGISTER OFFSETS
//*   All offsets in Page 0 unless otherwise specified
//*	  All functions accessing CR must leave CR in page 0 upon exit
//******************************************************************
#define CR		 	0x00
#define PSTART		0x01
#define PAR0      	0x01    // Page 1
#define CR9346    	0x01    // Page 3
#define PSTOP		0x02
#define BNRY		0x03
#define TSR			0x04
#define TPSR		0x04
#define TBCR0		0x05
#define NCR			0x05
#define TBCR1		0x06
#define ISR			0x07
#define CURR		0x07   // Page 1
#define RSAR0		0x08
#define CRDA0		0x08
#define RSAR1		0x09
#define CRDA1		0x09
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
#define RSTPORT   	0x18
#define CONFIG2     0x05    // page 3
#define CONFIG3     0x06    // page 3
#define RTL_EECR        0x01    // page 3



/*****************************************************************************
*
* RTL ISR Register Bits
*
*****************************************************************************/
#define ISR_RST	7
#define ISR_OVW 4
#define ISR_PRX 0
#define ISR_RDC 6
#define ISR_PTX 1


/*****************************************************************************
*
*  RTL Register Initialization Values
*
*****************************************************************************/
// RCR : accept broadcast packets and packets destined to this MAC
//         drop short frames and receive errors
#define RCR_INIT		0x04

// TCR : default transmit operation - CRC is generated 
#define TCR_INIT		0x00

// DCR : allows send packet to be used for packet retreival
//         FIFO threshold: 8-bits (works)
//         8-bit transfer mode
#define DCR_INIT		0x58

// IMR : interrupt enabled for receive and overrun events
#define IMR_INIT		0x11

// buffer boundaries - transmit has 6 256-byte pages
//   receive has 26 256-byte pages
//   entire available packet buffer space is allocated
#define TXSTART_INIT   	0x40
#define RXSTART_INIT   	0x46
#define RXSTOP_INIT    	0x60



void rtl8019BeginPacketSend(unsigned int packetLength)
{
	unsigned int sendPacketLength;
	sendPacketLength = (packetLength>=ETHERNET_MIN_PACKET_LENGTH) ?
	                 packetLength : ETHERNET_MIN_PACKET_LENGTH ;
	
	//start the NIC
	rtl8019Write(CR,0x22);
	
	// still transmitting a packet - wait for it to finish
	while( rtl8019Read(CR) & 0x04 );

	//load beginning page for transmit buffer
	rtl8019Write(TPSR,TXSTART_INIT);
	
	//set start address for remote DMA operation
	rtl8019Write(RSAR0,0x00);
	rtl8019Write(RSAR1,0x40);
	
	//clear the packet stored interrupt
	rtl8019Write(ISR,(1<<ISR_PTX));

	//load data byte count for remote DMA
	rtl8019Write(RBCR0, (unsigned char)(packetLength));
	rtl8019Write(RBCR1, (unsigned char)(packetLength>>8));

	rtl8019Write(TBCR0, (unsigned char)(sendPacketLength));
	rtl8019Write(TBCR1, (unsigned char)((sendPacketLength)>>8));
	
	//do remote write operation
	rtl8019Write(CR,0x12);
}



void rtl8019SendPacketData(unsigned char * localBuffer, unsigned int length)
{
	unsigned int i;
	
	for(i=0;i<length;i++)
		rtl8019Write(RDMAPORT, localBuffer[i]);
}



void rtl8019EndPacketSend(void)
{
	//send the contents of the transmit buffer onto the network
	rtl8019Write(CR,0x24);
	
	// clear the remote DMA interrupt
	rtl8019Write(ISR, (1<<ISR_RDC));
}




// pointers to locations in the RTL8019 receive buffer
static unsigned char nextPage;
static unsigned int currentRetreiveAddress;

// location of items in the RTL8019's page header
#define  enetpacketstatus     0x00
#define  nextblock_ptr        0x01
#define	 enetpacketLenL		  0x02
#define	 enetpacketLenH		  0x03

unsigned int rtl8019BeginPacketRetreive(void)
{
	unsigned char i;
	unsigned char bnry;
	
	unsigned char pageheader[4];
	unsigned int rxlen;
	
	// check for and handle an overflow
	rtl8019ProcessInterrupt();
	
	// read CURR from page 1
	rtl8019Write(CR,0x62);
	i = rtl8019Read(CURR);
	
	// return to page 0
	rtl8019Write(CR,0x22);
	
	// read the boundary register - pointing to the beginning of the packet
	bnry = rtl8019Read(BNRY) ;
	
	// return if there is no packet in the buffer
	if( bnry == i )
		return 0;
	

	// clear the packet received interrupt flag
	rtl8019Write(ISR, (1<<ISR_PRX));
	
	// the boundary pointer is invalid, reset the contents of the buffer and exit
	if( (bnry >= RXSTOP_INIT) || (bnry < RXSTART_INIT) )
	{
		rtl8019Write(BNRY, RXSTART_INIT);
		rtl8019Write(CR, 0x62);
		rtl8019Write(CURR, RXSTART_INIT);
		rtl8019Write(CR, 0x22);
		
		return 0;
	}

	// initiate DMA to transfer the RTL8019 packet header
    rtl8019Write(RBCR0, 4);
    rtl8019Write(RBCR1, 0);
    rtl8019Write(RSAR0, 0);
    rtl8019Write(RSAR1, bnry);
    rtl8019Write(CR, 0x0A);
	for(i=0;i<4;i++)
		pageheader[i] = rtl8019Read(RDMAPORT);
	
	// end the DMA operation
    rtl8019Write(CR, 0x22);
    for(i = 0; i <= 20; i++)
        if(rtl8019Read(ISR) & 1<<6)
            break;
    rtl8019Write(ISR, 1<<6);

	
	rxlen = (pageheader[enetpacketLenH]<<8) + pageheader[enetpacketLenL];
	nextPage = pageheader[nextblock_ptr] ;
	
	currentRetreiveAddress = (bnry<<8) + 4;
	
	// if the nextPage pointer is invalid, the packet is not ready yet - exit
	if( (nextPage >= RXSTOP_INIT) || (nextPage < RXSTART_INIT) )
		return 0;
    
    return rxlen-4;
}


void rtl8019RetreivePacketData(unsigned char * localBuffer, unsigned int length)
{
	unsigned int i;
	
	// initiate DMA to transfer the data
    rtl8019Write(RBCR0, (unsigned char)length);
    rtl8019Write(RBCR1, (unsigned char)(length>>8));
    rtl8019Write(RSAR0, (unsigned char)currentRetreiveAddress);
    rtl8019Write(RSAR1, (unsigned char)(currentRetreiveAddress>>8));
    rtl8019Write(CR, 0x0A);
	for(i=0;i<length;i++)
		localBuffer[i] = rtl8019Read(RDMAPORT);

	// end the DMA operation
    rtl8019Write(CR, 0x22);
    for(i = 0; i <= 20; i++)
        if(rtl8019Read(ISR) & 1<<6)
            break;
    rtl8019Write(ISR, 1<<6);
    
    currentRetreiveAddress += length;
    if( currentRetreiveAddress >= 0x6000 )
    	currentRetreiveAddress = currentRetreiveAddress - (0x6000-0x4600) ;
}



void rtl8019EndPacketRetreive(void)
{
	unsigned char i;

	// end the DMA operation
    rtl8019Write(CR, 0x22);
    for(i = 0; i <= 20; i++)
        if(rtl8019Read(ISR) & 1<<6)
            break;
    rtl8019Write(ISR, 1<<6);

	// set the boundary register to point to the start of the next packet
    rtl8019Write(BNRY, nextPage);
}


void rtl8019Overrun(void)
{
	unsigned char data_L, resend;	

	data_L = rtl8019Read(CR);
	rtl8019Write(CR, 0x21);
	delay_ms(2);
	rtl8019Write(RBCR0, 0x00);
	rtl8019Write(RBCR1, 0x00);
	if(!(data_L & 0x04))
		resend = 0;
	else if(data_L & 0x04)
	{
		data_L = rtl8019Read(ISR);
		if((data_L & 0x02) || (data_L & 0x08))
	    	resend = 0;
	    else
	    	resend = 1;
	}
	
	rtl8019Write(TCR, 0x02);
	rtl8019Write(CR, 0x22);
	rtl8019Write(BNRY, RXSTART_INIT);
	rtl8019Write(CR, 0x62);
	rtl8019Write(CURR, RXSTART_INIT);
	rtl8019Write(CR, 0x22);
	rtl8019Write(ISR, 0x10);
	rtl8019Write(TCR, TCR_INIT);
	
    if(resend)
        rtl8019Write(CR, 0x26);

    rtl8019Write(ISR, 0xFF);
}


void rtl8019Init(void)
{
	rtl8019SetupPorts();
	
	HARD_RESET_RTL8019();
	
	// do soft reset
	rtl8019Write( ISR, rtl8019Read(ISR) ) ;
	delay_ms(50);

    // switch to page 3 to load config registers
    rtl8019Write(CR, 0xE1);

    // disable EEPROM write protect of config registers
    rtl8019Write(RTL_EECR, 0xC0);

    // set network type to 10 Base-T link test
    rtl8019Write(CONFIG2, 0x20);

    // disable powerdown and sleep
    rtl8019Write(CONFIG3, 0);
    delay_ms(255);

    // reenable EEPROM write protect
    rtl8019Write(RTL_EECR, 0);

    // go back to page 0
    rtl8019Write(CR, 0x21);

    rtl8019Write(CR,0x21);       // stop the NIC, abort DMA, page 0
	delay_ms(2);               // make sure nothing is coming in or going out
	rtl8019Write(DCR, DCR_INIT);    // 0x58
	rtl8019Write(RBCR0,0x00);
	rtl8019Write(RBCR1,0x00);
	rtl8019Write(RCR,0x04);
	rtl8019Write(TPSR, TXSTART_INIT);
	rtl8019Write(TCR,0x02);
	rtl8019Write(PSTART, RXSTART_INIT);
	rtl8019Write(BNRY, RXSTART_INIT);
	rtl8019Write(PSTOP, RXSTOP_INIT);
	rtl8019Write(CR, 0x61);
	delay_ms(2);
	rtl8019Write(CURR, RXSTART_INIT);
	
	rtl8019Write(PAR0+0, MYMAC_0);
	rtl8019Write(PAR0+1, MYMAC_1);
	rtl8019Write(PAR0+2, MYMAC_2);
	rtl8019Write(PAR0+3, MYMAC_3);
	rtl8019Write(PAR0+4, MYMAC_4);
	rtl8019Write(PAR0+5, MYMAC_5);
     	  
	rtl8019Write(CR,0x21);
	rtl8019Write(DCR, DCR_INIT);
	rtl8019Write(CR,0x22);
	rtl8019Write(ISR,0xFF);
	rtl8019Write(IMR, IMR_INIT);
	rtl8019Write(TCR, TCR_INIT);
	
	rtl8019Write(CR, 0x22);	// start the NIC
}


void rtl8019ProcessInterrupt(void)
{
	unsigned char byte = rtl8019Read(ISR);
	
	if( byte & (1<<ISR_OVW) )
		rtl8019Overrun();
}


