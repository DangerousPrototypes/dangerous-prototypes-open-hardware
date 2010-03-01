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
// File Name	: 'ax88796.c'
// Title		: ASIX 88796 L Ethernet Interface Driver
// Author		: Pascal Stang
// Created		: 10/22/2002
// Revised		: 10/26/2002
// Version		: 0.1
// Target MCU	: Atmel AVR series
// Editor Tabs	: 4
//
//	Description : This include file is designed to contain items useful to all
//					code files and projects.
//
// Based in part on code by Louis Beaudoin (www.embedded-creations.com)
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************

#include "ax88796.h"

// pointers to locations in the ax88796 receive buffer
static unsigned char nextPage;
static unsigned int currentRetreiveAddress;

// offsets into ax88796 ethernet packet header
#define  enetpacketstatus     0x00
#define  nextblock_ptr        0x01
#define	 enetpacketLenL		  0x02
#define	 enetpacketLenH		  0x03



#if NIC_CONNECTION == MEMORY_MAPPED_HIGHADDR
#define ax88796Write(AX88796_REG,AX88796_DATA) do{ *(volatile unsigned char *) \
							(MEMORY_MAPPED_AX88796_OFFSET \
							+ (((unsigned char)(AX88796_REG)) << 8)) = \
							(unsigned char)(AX88796_DATA); } while(0)
#endif

#if NIC_CONNECTION == MEMORY_MAPPED
#define ax88796Write(AX88796_REG,AX88796_DATA) do{ *(volatile unsigned char *) \
							(MEMORY_MAPPED_AX88796_OFFSET \
							+ (unsigned char)(AX88796_REG)) = \
							(unsigned char)(AX88796_DATA); } while(0)
#endif                             

#if NIC_CONNECTION == GENERAL_IO
void ax88796Write(u08 address, u08 data)
{
    // assert the address, leaving the non-address pins intact
    address |= (AX88796_ADDRESS_PORT & ~AX88796_ADDRESS_MASK);
    AX88796_ADDRESS_PORT = address;

	// set data bus as output and place data on bus
    AX88796_DATA_DDR = 0xFF;
    AX88796_DATA_PORT = data;
    
	// clock write pin
    AX88796_CONTROL_PORT &= ~_BV(AX88796_CONTROL_WRITEPIN);
	nop();
    AX88796_CONTROL_PORT |= _BV(AX88796_CONTROL_WRITEPIN);    

	// set data bus back to input with pullups enabled
    AX88796_DATA_DDR = 0x00;
    AX88796_DATA_PORT = 0xFF;
}
#endif

#if NIC_CONNECTION == MEMORY_MAPPED_HIGHADDR

#define ax88796Read(AX88796_ADDRESS) (*(volatile unsigned char *) \
                       (MEMORY_MAPPED_AX88796_OFFSET \
                       + (((unsigned char)(AX88796_ADDRESS)) << 8)) )
#endif
                             
#if NIC_CONNECTION == MEMORY_MAPPED
#define ax88796Read(AX88796_ADDRESS) (*(volatile unsigned char *) \
                       (MEMORY_MAPPED_AX88796_OFFSET \
                       + (unsigned char)(AX88796_ADDRESS)) )
#endif

#if NIC_CONNECTION == GENERAL_IO

u08 ax88796Read(u08 address)
{
	u08 byte;
   
    // assert the address, leaving the non-address pins intact
    address |= (AX88796_ADDRESS_PORT & ~AX88796_ADDRESS_MASK);
    AX88796_ADDRESS_PORT = address;
	
    // assert read
    AX88796_CONTROL_PORT &= ~_BV(AX88796_CONTROL_READPIN);
	nop();

	// read in the data
    byte = AX88796_DATA_PIN;
	nop();

	// negate read
    AX88796_CONTROL_PORT |= _BV(AX88796_CONTROL_READPIN);

	return byte;
}
#endif                       


void ax88796Init(void)
{
	unsigned char delaycount=10;
    unsigned char tcrFduFlag;
	ax88796SetupPorts();
	
	// do a hard reset
	AX88796_RESET_PORT |= _BV(AX88796_RESET_PIN);
	delay_ms(10);
	AX88796_RESET_PORT &= ~_BV(AX88796_RESET_PIN);

	// do soft reset
	ax88796Write(ISR, ax88796Read(ISR));
	delay_ms(50);

	// wait for PHY to come out of reset
	ax88796Read(RSTPORT);
	while(ax88796Read(TR) & RST_B);
   
	ax88796WriteMii(0x10,0x00,0x0800);
	while(delaycount--)
        delay_ms(255);
	ax88796WriteMii(0x10,0x00,0x1200);

	ax88796Write(CR,(RD2|STOP));		// stop the NIC, abort DMA, page 0
	delay_ms(5);						// make sure nothing is coming in or going out
	ax88796Write(DCR,DCR_INIT);    
	ax88796Write(RBCR0,0x00);
	ax88796Write(RBCR1,0x00);
	ax88796Write(IMR,0x00);
	ax88796Write(ISR,0xFF);
	ax88796Write(RCR,0x20);
	ax88796Write(BNRY,RXSTART_INIT);
	ax88796Write(PSTART,RXSTART_INIT);
	ax88796Write(PSTOP,RXSTOP_INIT);
	
	// switch to page 1
	ax88796Write(CR,(PS0|RD2|STOP));
	// write mac address
	ax88796Write(PAR0+0, MYMAC_0);
	ax88796Write(PAR0+1, MYMAC_1);
	ax88796Write(PAR0+2, MYMAC_2);
	ax88796Write(PAR0+3, MYMAC_3);
	ax88796Write(PAR0+4, MYMAC_4);
	ax88796Write(PAR0+5, MYMAC_5);
	// set start point
	ax88796Write(CURR,RXSTART_INIT+1);

	ax88796Write(CR,(RD2|START));
	ax88796Write(RCR,RCR_INIT);

	if(ax88796Read(GPI) & I_SPD)		// check PHY speed setting
		tcrFduFlag = FDU;				// if 100base, do full duplex
	else
		tcrFduFlag = 0;					// if 10base, do half duplex
		
	ax88796Write(TCR,(tcrFduFlag|TCR_INIT));

	ax88796Write(GPOC,MPSEL);			// select media interface
  
	ax88796Write(TPSR,TXSTART_INIT);

	ax88796Write(CR,(RD2|STOP));
	ax88796Write(DCR,DCR_INIT);
	ax88796Write(CR,(RD2|START));
	ax88796Write(ISR,0xFF);
	ax88796Write(IMR,IMR_INIT);
	ax88796Write(TCR,(tcrFduFlag|TCR_INIT));
}



void ax88796SetupPorts(void)
{
#if NIC_CONNECTION == GENERAL_IO
	// set address port to output
    AX88796_ADDRESS_DDR = AX88796_ADDRESS_MASK;
    
	// set data port to input with pull-ups
    AX88796_DATA_DDR = 0x00;
    AX88796_DATA_PORT = 0xFF;

	// initialize the control port read and write pins to de-asserted
    AX88796_CONTROL_PORT |= _BV(AX88796_CONTROL_READPIN);
    AX88796_CONTROL_PORT |= _BV(AX88796_CONTROL_WRITEPIN);    
    // set the read and write pins to output
    AX88796_CONTROL_DDR |= _BV(AX88796_CONTROL_READPIN);
    AX88796_CONTROL_DDR |= _BV(AX88796_CONTROL_WRITEPIN);    

#else
  	// enable external SRAM interface - no wait states
    MCUCR |= _BV(SRE);
#endif    
	// set reset pin to output
    AX88796_RESET_DDR |= _BV(AX88796_RESET_PIN);
}


void ax88796BeginPacketSend(unsigned int packetLength)
{
	unsigned int sendPacketLength;
	sendPacketLength = (packetLength>=ETHERNET_MIN_PACKET_LENGTH) ?
	                 packetLength : ETHERNET_MIN_PACKET_LENGTH ;
	
	//start the NIC
	ax88796Write(CR,0x22);
	
	// still transmitting a packet - wait for it to finish
	while( ax88796Read(CR) & 0x04 );

	//load beginning page for transmit buffer
	ax88796Write(TPSR,TXSTART_INIT);
	
	//set start address for remote DMA operation
	ax88796Write(RSAR0,0x00);
	ax88796Write(RSAR1,0x40);
	
	//clear the packet stored interrupt
	ax88796Write(ISR, PTX);

	//load data byte count for remote DMA
	ax88796Write(RBCR0, (unsigned char)(packetLength));
	ax88796Write(RBCR1, (unsigned char)(packetLength>>8));

	ax88796Write(TBCR0, (unsigned char)(sendPacketLength));
	ax88796Write(TBCR1, (unsigned char)((sendPacketLength)>>8));
	
	//do remote write operation
	ax88796Write(CR,0x12);
}

void ax88796SendPacketData(unsigned char * localBuffer, unsigned int length)
{
	unsigned int i;
	
	for(i=0;i<length;i++)
		ax88796Write(RDMAPORT, localBuffer[i]);
}

void ax88796EndPacketSend(void)
{
	//send the contents of the transmit buffer onto the network
	ax88796Write(CR,0x24);
	
	// clear the remote DMA interrupt
	ax88796Write(ISR, RDC);
}


unsigned int ax88796BeginPacketRetreive(void)
{
	unsigned char writePagePtr;
	unsigned char readPagePtr;
	unsigned char bnryPagePtr;
	unsigned char i;
	
	unsigned char pageheader[4];
	unsigned int rxlen;
	
	// check for and handle an overflow
	ax88796ProcessInterrupt();
	
	// read CURR from page 1
	ax88796Write(CR,(PS0|RD2|START));
	writePagePtr = ax88796Read(CURR);
	// read the boundary register from page 0
	ax88796Write(CR,(RD2|START));
	bnryPagePtr = ax88796Read(BNRY);

	// first packet is at page bnryPtr+1
	readPagePtr = bnryPagePtr+1;
	if(readPagePtr >= RXSTOP_INIT) readPagePtr = RXSTART_INIT;
	
	// return if there is no packet in the buffer
	if( readPagePtr == writePagePtr )
	{
		return 0;
	}
	
	// clear the packet received interrupt flag
	ax88796Write(ISR, PRX);
	
	// if the boundary pointer is invalid,
	// reset the contents of the buffer and exit
	if( (bnryPagePtr < RXSTART_INIT) || (bnryPagePtr >= RXSTOP_INIT) )
	{
		ax88796Write(BNRY, RXSTART_INIT);
		ax88796Write(CR, (PS0|RD2|START));
		ax88796Write(CURR, RXSTART_INIT+1);
		ax88796Write(CR, (RD2|START));
		return 0;
	}

	// initiate DMA to transfer the RTL8019 packet header
	ax88796Write(RBCR0, 4);
	ax88796Write(RBCR1, 0);
	ax88796Write(RSAR0, 0);
	ax88796Write(RSAR1, readPagePtr);
	ax88796Write(CR, (RD0|START));
	for(i=0;i<4;i++)
		pageheader[i] = ax88796Read(RDMAPORT);

	// end the DMA operation
    ax88796Write(CR, (RD2|START));
    for(i = 0; i <= 20; i++)
        if(ax88796Read(ISR) & RDC)
            break;
    ax88796Write(ISR, RDC);
	
	rxlen = (pageheader[enetpacketLenH]<<8) + pageheader[enetpacketLenL];
	nextPage = pageheader[nextblock_ptr] ;
	
	currentRetreiveAddress = (readPagePtr<<8) + 4;
	
	// if the nextPage pointer is invalid, the packet is not ready yet - exit
	if( (nextPage >= RXSTOP_INIT) || (nextPage < RXSTART_INIT) )
	{
		return 0;
	}

    return rxlen-4;
}


void ax88796RetreivePacketData(unsigned char * localBuffer, unsigned int length)
{
	unsigned int i;
	
	// initiate DMA to transfer the data
	ax88796Write(RBCR0, (unsigned char)length);
	ax88796Write(RBCR1, (unsigned char)(length>>8));
	ax88796Write(RSAR0, (unsigned char)currentRetreiveAddress);
	ax88796Write(RSAR1, (unsigned char)(currentRetreiveAddress>>8));
	ax88796Write(CR, (RD0|START));
	for(i=0;i<length;i++)
		localBuffer[i] = ax88796Read(RDMAPORT);

	// end the DMA operation
	ax88796Write(CR, (RD2|START));
	for(i = 0; i <= 20; i++)
		if(ax88796Read(ISR) & RDC)
			break;
	ax88796Write(ISR, RDC);
    
	currentRetreiveAddress += length;
	if( currentRetreiveAddress >= 0x6000 )
    	currentRetreiveAddress -= (0x6000-0x4600) ;
}



void ax88796EndPacketRetreive(void)
{
	unsigned char i;
	unsigned char bnryPagePtr;

	// end the DMA operation
    ax88796Write(CR, (RD2|START));
    for(i = 0; i <= 20; i++)
        if(ax88796Read(ISR) & RDC)
            break;
    ax88796Write(ISR, RDC);

	// set the boundary register to point
	// to the start of the next packet-1
    bnryPagePtr = nextPage-1;
	if(bnryPagePtr < RXSTART_INIT) bnryPagePtr = RXSTOP_INIT-1;

	ax88796Write(BNRY, bnryPagePtr);
}


void ax88796Overrun(void)
{
	unsigned char cmdReg, resend;	

	// check if we were transmitting something
	cmdReg = ax88796Read(CR);
	// stop the interface
	ax88796Write(CR, (RD2|STOP));
	// wait for timeout
	delay_ms(2);
	// clear remote byte count registers
	ax88796Write(RBCR0, 0x00);
	ax88796Write(RBCR1, 0x00);
	
	if(!(cmdReg & TXP))
	{
		resend = 0;
	}
	else
	{
		cmdReg = ax88796Read(ISR);
		if((cmdReg & PTX) || (cmdReg & TXE))
	    	resend = 0;
	    else
	    	resend = 1;
	}
	// switch to loopback mode
	ax88796Write(TCR, LB0);
	// start the interface
	ax88796Write(CR, (RD2|START));
	// set boundary
	ax88796Write(BNRY, RXSTART_INIT);
	// go to page 1
	ax88796Write(CR, (PS0|RD2|START));
	// set current page register
	ax88796Write(CURR, RXSTART_INIT+1);
	// go to page 0
	ax88796Write(CR, (RD2|START));
	// clear the overflow int
	ax88796Write(ISR, OVW);
	// switch to normal (non-loopback mode)
	ax88796Write(TCR, TCR_INIT);

	if(resend)
		ax88796Write(CR, (RD2|TXP|START));
	
	//ax88796Write(ISR, 0xFF);
}

#define set_mdc		ax88796Write(MEMR,ax88796Read(MEMR)|0x01);
#define clr_mdc		ax88796Write(MEMR,ax88796Read(MEMR)&0xFE);

#define mii_clk		set_mdc; clr_mdc;				  
					
#define set_mdir	ax88796Write(MEMR,ax88796Read(MEMR)|0x02);
#define clr_mdir	ax88796Write(MEMR,ax88796Read(MEMR)&0xFD);
					
#define set_mdo		ax88796Write(MEMR,ax88796Read(MEMR)|0x08)
#define clr_mdo		ax88796Write(MEMR,ax88796Read(MEMR)&0xF7)

#define mii_write	clr_mdo;  	 			  \
					mii_clk;				  \
					set_mdo;				  \
					mii_clk;				  \
					clr_mdo;  	 			  \
					mii_clk;				  \
					set_mdo;				  \
					mii_clk;				  
					
#define mii_read	clr_mdo;  	 			  \
					mii_clk;				  \
					set_mdo;				  \
					mii_clk;				  \
					set_mdo;  	 			  \
					mii_clk;				  \
					clr_mdo;				  \
					mii_clk;				  

#define mii_r_ta    mii_clk;				  \
								  
					
#define mii_w_ta    set_mdo;				  \
					mii_clk;				  \
					clr_mdo;				  \
					mii_clk;				  
			
void ax88796WriteMii(unsigned char phyad,unsigned char regad,unsigned int mii_data)
{
	unsigned char mask8;
	unsigned int  i,mask16;

	mii_write;
 
	mask8 = 0x10;
	for(i=0;i<5;++i)
	{
  	   	if(mask8 & phyad)
			set_mdo;
		else
			clr_mdo;
		mii_clk;
		mask8 >>= 1;	 
	}   
	mask8 = 0x10;
	for(i=0;i<5;++i)
	{
  		if(mask8 & regad)
			set_mdo;
		else
			clr_mdo;
		mii_clk;
		mask8 >>= 1;	 
	}    					
	mii_w_ta;
 
	mask16 = 0x8000;
	for(i=0;i<16;++i)
	{
		if(mask16 & mii_data)
			set_mdo;
		else
			clr_mdo;
		mii_clk;	 
		mask16 >>= 1;	 
	}   			
}
 
unsigned int ax88796ReadMii(unsigned char phyad,unsigned char regad)
{
	unsigned char mask8,i;
	unsigned int  mask16,result16;
 
	mii_read;

	mask8 = 0x10;
	for(i=0;i<5;++i)
	{
		if(mask8 & phyad)
			set_mdo;
		else
			clr_mdo;
		mii_clk;	 
		mask8 >>= 1;
	}
	mask8 = 0x10;
	for(i=0;i<5;++i)
	{
		if(mask8 & regad)
			set_mdo;
		else
			clr_mdo;
		mii_clk;
		mask8 >>= 1;
	}
   			
	mii_r_ta;
 
	mask16 = 0x8000;
	result16 = 0x0000;
	for(i=0;i<16;++i)
	{
		mii_clk;
		if(ax88796Read(MEMR) & 0x04)
		{
			result16 |= mask16;
		}
		else
		{
			nop();
			break;
		}
		mask16 >>= 1;
	}
	return result16;
}


void ax88796ProcessInterrupt(void)
{
	unsigned char byte = ax88796Read(ISR);
	
	if( byte & OVW )
		ax88796Overrun();

}


