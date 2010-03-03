/*! \file enc28j60.c \brief Microchip ENC28J60 Ethernet Interface Driver. */
//*****************************************************************************
//
// File Name	: 'enc28j60.c'
// Title		: Microchip ENC28J60 Ethernet Interface Driver
// Author		: Pascal Stang (c)2005
// Created		: 9/22/2005
// Revised		: 9/22/2005
// Version		: 0.1
//
// 
// Target MCU	: DsPIC33
// Editor Tabs	: 4
//
// Description	: This driver provides initialization and transmit/receive
//	functions for the Microchip ENC28J60 10Mb Ethernet Controller and PHY.
// This chip is novel in that it is a full MAC+PHY interface all in a 28-pin
// chip, using an SPI interface to the host processor.
//
//*****************************************************************************

/************************************************************
*
*	This is the general driver for the ENC28J60
*	I changed some things to make it work with uIP
*	Some files of uIP have changes too.
*
*								edi87 [at] fibertel.com.ar
*								Jonathan Granade
*
************************************************************/

#include "enc28j60.h"
#include "HardwareProfile.h"
#include "uip.h"

// include configuration
//#include "ax88796conf.h"
u8 Enc28j60Bank;
u16 NextPacketPtr;
/*
void nicInit(void)
{
	enc28j60Init();
}

void nicSend(unsigned int len, unsigned char* packet)
{
	enc28j60PacketSend(len, packet);
}

unsigned int nicPoll(unsigned int maxlen, unsigned char* packet)
{
	return enc28j60PacketReceive(maxlen, packet);
}

void nicGetMacAddress(u8* macaddr)
{
	// read MAC address registers
	// NOTE: MAC address in ENC28J60 is byte-backward
	*macaddr++ = enc28j60Read(MAADR5);
	*macaddr++ = enc28j60Read(MAADR4);
	*macaddr++ = enc28j60Read(MAADR3);
	*macaddr++ = enc28j60Read(MAADR2);
	*macaddr++ = enc28j60Read(MAADR1);
	*macaddr++ = enc28j60Read(MAADR0);
}

void nicSetMacAddress(u8* macaddr)
{
	// write MAC address
	// NOTE: MAC address in ENC28J60 is byte-backward
	enc28j60Write(MAADR5, *macaddr++);
	enc28j60Write(MAADR4, *macaddr++);
	enc28j60Write(MAADR3, *macaddr++);
	enc28j60Write(MAADR2, *macaddr++);
	enc28j60Write(MAADR1, *macaddr++);
	enc28j60Write(MAADR0, *macaddr++);
}

void nicRegDump(void)
{
	enc28j60RegDump();
}
*/

#define CS_EN()    ENC_CS_LAT=0 
#define CS_DIS()   ENC_CS_LAT=1
#define HARDRESET() ENC_RST_LAT = 0;ENC_ENC_RST_LAT = 1
#define SPI_BUF     ENC_SSPBUF
#define SPITXRX() 	while(!SPISTAT_RBF)

u8 enc28j60ReadOp(u8 op, u8 address)
{
	u8 data;
   
	// assert CS
	CS_EN();
	
	// issue read command
	SPI_BUF = op | (address & ADDR_MASK);
	SPITXRX();
	// read data
	SPI_BUF = 0x00;
	SPITXRX();
	// do dummy read if needed
	if(address & 0x80)
	{
		SPI_BUF = 0x00;
		SPITXRX();
	}
	data = SPI_BUF;
	
	// release CS
	CS_DIS();

	return data;
}

void enc28j60WriteOp(u8 op, u8 address, u8 data)
{
	// assert CS
	CS_EN();

	// issue write command
	SPI_BUF = op | (address & ADDR_MASK);
	SPITXRX();
	// write data
	SPI_BUF = data;
	SPITXRX();

	// release CS
    CS_DIS();
}

void enc28j60ReadBuffer(u16 len, u8* data)
{
	// assert CS
	CS_EN();
	
	// issue read command
	SPI_BUF = ENC28J60_READ_BUF_MEM;
	SPITXRX();
	while(len--)
	{
		// read data
		SPI_BUF = 0x00;
		SPITXRX();
		*data++ = SPI_BUF;
	}	
	// release CS
	CS_DIS();
}

void enc28j60WriteBuffer(u16 len, u8* data)
{
	// assert CS
	CS_EN();
	
	// issue write command
	SPI_BUF = ENC28J60_WRITE_BUF_MEM;
	SPITXRX();
	while(len--)
	{
		// write data
		SPI_BUF = *data++;
		SPITXRX();
	}	
	// release CS
	CS_DIS();
}

void enc28j60SetBank(u8 address)
{
	// set the bank (if needed)
	if((address & BANK_MASK) != Enc28j60Bank)
	{
		// set the bank
		enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, (ECON1_BSEL1|ECON1_BSEL0));
		enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, (address & BANK_MASK)>>5);
		Enc28j60Bank = (address & BANK_MASK);
	}
}

u8 enc28j60Read(u8 address)
{
	// set the bank
	enc28j60SetBank(address);
	// do the read
	return enc28j60ReadOp(ENC28J60_READ_CTRL_REG, address);
}

void enc28j60Write(u8 address, u8 data)
{
	// set the bank
	enc28j60SetBank(address);
	// do the write
	enc28j60WriteOp(ENC28J60_WRITE_CTRL_REG, address, data);
}

u16 enc28j60PhyRead(u8 address)
{
	u16 data;

	// Set the right address and start the register read operation
	enc28j60Write(MIREGADR, address);
	enc28j60Write(MICMD, MICMD_MIIRD);

	// wait until the PHY read completes
	while(enc28j60Read(MISTAT) & MISTAT_BUSY);

	// quit reading
	enc28j60Write(MICMD, 0x00);
	
	// get data value
	data  = enc28j60Read(MIRDL);
	data |= enc28j60Read(MIRDH);
	// return the data
	return data;
}

void enc28j60PhyWrite(u8 address, u16 data)
{
	// set the PHY register address
	enc28j60Write(MIREGADR, address);
	
	// write the PHY data
	enc28j60Write(MIWRL, data);	
	enc28j60Write(MIWRH, data>>8);

	// wait until the PHY write completes
	while(enc28j60Read(MISTAT) & MISTAT_BUSY);
}

void enc28j60Init(void)
{
	u8 i,j;
	// initialize I/O
	/* Atmega style
    sbi(ENC28J60_CONTROL_DDR, ENC28J60_CONTROL_CS); replaced with
   
    sbi(ENC28J60_CONTROL_PORT, ENC28J60_CONTROL_CS); replaced with
   

	// setup SPI I/O pins
	sbi(PORTB, ENC28J60_SCK_PIN);	// set SCK hi
	sbi(DDRB, ENC28J60_SCK_PIN);	// set SCK as output
	cbi(DDRB, ENC28J60_MISO_PIN);	// set MISO as input
	sbi(DDRB, ENC28J60_MOSI_PIN);	// set MOSI as output
	sbi(DDRB, ENC28J60_SS_PIN);	// SS must be output for Master mode to work
	// initialize SPI interface
	// master mode
	sbi(SPCR, MSTR);
	// select clock phase positive-going in middle of data
	cbi(SPCR, CPOL);
	// Data order MSB first
	cbi(SPCR,DORD);
	// switch to f/4 2X = f/2 bitrate
	cbi(SPCR, SPR0);
	cbi(SPCR, SPR1);
	sbi(SPSR, SPI2X);
	// enable SPI
	sbi(SPCR, SPE);
    */

    //custom pin assignments for our hardware
        // ENC28J60 I/O pins
        //mapping:
        //A2 ETH-INT
        //C2 MISO
        //C1 MOSI
        //C0 CLK
        //B3 CS
        //B2 RST
        //CS and RST pins
        
    ENC_CS_TRIS  = 0; //set direction of CS pin as output (master)
    ENC_RST_TRIS = 0; //set direction of RST pin as output
    
    //MISO1 C2/RP18 (input)
    SDI1R_I = 18;                   
    //CLK1 C0/RP16 (output)
    RP16_O = SCK1OUT_O;     
    //MOSI1 C1/RP17 (output)
    RP17_O = SDO1_O;
    ENC_SPICON1bits.MSTEN = 1;
    ENC_SPICON1bits.CKP = 0;
	ENC_SPICON1bits.SSEN = 0;
    ENC_SPICON1bits.CKE = 1;
    ENC_SPISTATbits.SPIEN = 1;
    CS_DIS();
	// perform system reset
   
	enc28j60WriteOp(ENC28J60_SOFT_RESET, 0, ENC28J60_SOFT_RESET);
	// check CLKRDY bit to see if reset is complete
	for(i=0;i<0x10;i++){
		for(j=0;j<0xff;j++) ;
	}
	while(!(enc28j60Read(ESTAT) & ESTAT_CLKRDY));

	// do bank 0 stuff
	// initialize receive buffer
	// 16-bit transfers, must write low byte first
	// set receive buffer start address
	NextPacketPtr = RXSTART_INIT;
	enc28j60Write(ERXSTL, RXSTART_INIT&0xFF);
	enc28j60Write(ERXSTH, RXSTART_INIT>>8);
	// set receive pointer address
	enc28j60Write(ERXRDPTL, RXSTART_INIT&0xFF);
	enc28j60Write(ERXRDPTH, RXSTART_INIT>>8);
	// set receive buffer end
	// ERXND defaults to 0x1FFF (end of ram)
	enc28j60Write(ERXNDL, RXSTOP_INIT&0xFF);
	enc28j60Write(ERXNDH, RXSTOP_INIT>>8);
	// set transmit buffer start
	// ETXST defaults to 0x0000 (beginnging of ram)
	enc28j60Write(ETXSTL, TXSTART_INIT&0xFF);
	enc28j60Write(ETXSTH, TXSTART_INIT>>8);

	// do bank 2 stuff
	// enable MAC receive
	enc28j60Write(MACON1, MACON1_MARXEN|MACON1_TXPAUS|MACON1_RXPAUS);
	// bring MAC out of reset
	enc28j60Write(MACON2, 0x00);
	// enable automatic padding and CRC operations
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, MACON3, MACON3_PADCFG0|MACON3_TXCRCEN|MACON3_FRMLNEN);
//	enc28j60Write(MACON3, MACON3_PADCFG0|MACON3_TXCRCEN|MACON3_FRMLNEN);
	// set inter-frame gap (non-back-to-back)
	enc28j60Write(MAIPGL, 0x12);
	enc28j60Write(MAIPGH, 0x0C);
	// set inter-frame gap (back-to-back)
	enc28j60Write(MABBIPG, 0x12);
	// Set the maximum packet size which the controller will accept
	enc28j60Write(MAMXFLL, MAX_FRAMELEN&0xFF);	
	enc28j60Write(MAMXFLH, MAX_FRAMELEN>>8);

	// do bank 3 stuff
	// write MAC address
	// NOTE: MAC address in ENC28J60 is byte-backward
	enc28j60Write(MAADR5, UIP_ETHADDR0);
	enc28j60Write(MAADR4, UIP_ETHADDR1);
	enc28j60Write(MAADR3, UIP_ETHADDR2);
	enc28j60Write(MAADR2, UIP_ETHADDR3);
	enc28j60Write(MAADR1, UIP_ETHADDR4);
	enc28j60Write(MAADR0, UIP_ETHADDR5);

	// no loopback of transmitted frames
	enc28j60PhyWrite(PHCON2, PHCON2_HDLDIS);

	// switch to bank 0
	enc28j60SetBank(ECON1);
	// enable interrutps
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, EIE, EIE_INTIE|EIE_PKTIE);
	// enable packet reception
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN);
/*
	enc28j60PhyWrite(PHLCON, 0x0AA2);

	// setup duplex ----------------------

	// Disable receive logic and abort any packets currently being transmitted
	enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRTS|ECON1_RXEN);
	
	{
		u16 temp;
		// Set the PHY to the proper duplex mode
		temp = enc28j60PhyRead(PHCON1);
		temp &= ~PHCON1_PDPXMD;
		enc28j60PhyWrite(PHCON1, temp);
		// Set the MAC to the proper duplex mode
		temp = enc28j60Read(MACON3);
		temp &= ~MACON3_FULDPX;
		enc28j60Write(MACON3, temp);
	}

	// Set the back-to-back inter-packet gap time to IEEE specified 
	// requirements.  The meaning of the MABBIPG value changes with the duplex
	// state, so it must be updated in this function.
	// In full duplex, 0x15 represents 9.6us; 0x12 is 9.6us in half duplex
	//enc28j60Write(MABBIPG, DuplexState ? 0x15 : 0x12);	
	
	// Reenable receive logic
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN);

	// setup duplex ----------------------
*/
}

void enc28j60BeginPacketSend(unsigned int packetLength)
{
//
}

void enc28j60PacketSend(unsigned char * packet, unsigned int len)
{
	//Errata: Transmit Logic reset
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRST);
	enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRST);

	// Set the write pointer to start of transmit buffer area
	enc28j60Write(EWRPTL, TXSTART_INIT&0xff);
	enc28j60Write(EWRPTH, TXSTART_INIT>>8);
	// Set the TXND pointer to correspond to the packet size given
	enc28j60Write(ETXNDL, (TXSTART_INIT+len));
	enc28j60Write(ETXNDH, (TXSTART_INIT+len)>>8);

	// write per-packet control byte
	enc28j60WriteOp(ENC28J60_WRITE_BUF_MEM, 0, 0x00);

	// copy the packet into the transmit buffer
	enc28j60WriteBuffer(len, packet);

	// send the contents of the transmit buffer onto the network
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS);
}
	
void enc28j60EndPacketSend(void)
{
//
}

void enc28j60PacketSend2(unsigned int len1, unsigned char* packet1, unsigned int len2, unsigned char* packet2)
{
	//Errata: Transmit Logic reset
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRST);
	enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRST);

	// Set the write pointer to start of transmit buffer area
	enc28j60Write(EWRPTL, TXSTART_INIT&0xff);
	enc28j60Write(EWRPTH, TXSTART_INIT>>8);
	// Set the TXND pointer to correspond to the packet size given
	enc28j60Write(ETXNDL, (TXSTART_INIT+len1+len2));
	enc28j60Write(ETXNDH, (TXSTART_INIT+len1+len2)>>8);

	// write per-packet control byte
	enc28j60WriteOp(ENC28J60_WRITE_BUF_MEM, 0, 0x00);

	// copy the packet into the transmit buffer
	enc28j60WriteBuffer(len1, packet1);
	if(len2>0) enc28j60WriteBuffer(len2, packet2);
	
	// send the contents of the transmit buffer onto the network
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS);
}

unsigned int enc28j60BeginPacketReceive(void)
{
	u16 rxstat;
	u16 len;

	// check if a packet has been received and buffered
	if( !(enc28j60Read(EIR) & EIR_PKTIF) )
		return 0;
	
	// Make absolutely certain that any previous packet was discarded	
	//if( WasDiscarded == FALSE)
	//	MACDiscardRx();

	// Set the read pointer to the start of the received packet
	enc28j60Write(ERDPTL, (NextPacketPtr));
	enc28j60Write(ERDPTH, (NextPacketPtr)>>8);
	// read the next packet pointer
	NextPacketPtr  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
	NextPacketPtr |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)<<8;
	// read the packet length
	len  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
	len |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)<<8;
	// read the receive status
	rxstat  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
	rxstat |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)<<8;

	// limit retrieve length
	// (we reduce the MAC-reported length by 4 to remove the CRC)
//	if(len>maxlen) len=maxlen;
//	if(len<=0) return 0;
//	else return len;
	return len;
}

void enc28j60PacketReceive(unsigned char * packet, unsigned int maxlen)
{
	// copy the packet from the receive buffer
	enc28j60ReadBuffer(maxlen, packet);
}

void enc28j60EndPacketReceive(void)
{
	// Move the RX read pointer to the start of the next received packet
	// This frees the memory we just read out
	enc28j60Write(ERXRDPTL, (NextPacketPtr));
	enc28j60Write(ERXRDPTH, (NextPacketPtr)>>8);

	// decrement the packet counter indicate we are done with this packet
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON2, ECON2_PKTDEC);
}

void enc28j60ReceiveOverflowRecover(void)
{
	// receive buffer overflow handling procedure

	// recovery completed
}

void enc28j60RegDump(void)
{
//	unsigned char macaddr[6];
//	result = ax88796Read(TR);
	
//	rprintf("Media State: ");
//	if(!(result & AUTOD))
//		rprintf("Autonegotiation\r\n");
//	else if(result & RST_B)
//		rprintf("PHY in Reset   \r\n");
//	else if(!(result & RST_10B))
//		rprintf("10BASE-T       \r\n");
//	else if(!(result & RST_TXB))
//		rprintf("100BASE-T      \r\n");
/*				
	rprintf("RevID: 0x%x\r\n", enc28j60Read(EREVID));

	rprintfProgStrM("Cntrl: ECON1 ECON2 ESTAT  EIR  EIE\r\n");
	rprintfProgStrM("         ");
	rprintfu8(enc28j60Read(ECON1));
	rprintfProgStrM("    ");
	rprintfu8(enc28j60Read(ECON2));
	rprintfProgStrM("    ");
	rprintfu8(enc28j60Read(ESTAT));
	rprintfProgStrM("    ");
	rprintfu8(enc28j60Read(EIR));
	rprintfProgStrM("   ");
	rprintfu8(enc28j60Read(EIE));
	rprintfCRLF();

	rprintfProgStrM("MAC  : MACON1  MACON2  MACON3  MACON4  MAC-Address\r\n");
	rprintfProgStrM("        0x");
	rprintfu8(enc28j60Read(MACON1));
	rprintfProgStrM("    0x");
	rprintfu8(enc28j60Read(MACON2));
	rprintfProgStrM("    0x");
	rprintfu8(enc28j60Read(MACON3));
	rprintfProgStrM("    0x");
	rprintfu8(enc28j60Read(MACON4));
	rprintfProgStrM("   ");
	rprintfu8(enc28j60Read(MAADR5));
	rprintfu8(enc28j60Read(MAADR4));
	rprintfu8(enc28j60Read(MAADR3));
	rprintfu8(enc28j60Read(MAADR2));
	rprintfu8(enc28j60Read(MAADR1));
	rprintfu8(enc28j60Read(MAADR0));
	rprintfCRLF();

	rprintfProgStrM("Rx   : ERXST  ERXND  ERXWRPT ERXRDPT ERXFCON EPKTCNT MAMXFL\r\n");
	rprintfProgStrM("       0x");
	rprintfu8(enc28j60Read(ERXSTH));
	rprintfu8(enc28j60Read(ERXSTL));
	rprintfProgStrM(" 0x");
	rprintfu8(enc28j60Read(ERXNDH));
	rprintfu8(enc28j60Read(ERXNDL));
	rprintfProgStrM("  0x");
	rprintfu8(enc28j60Read(ERXWRPTH));
	rprintfu8(enc28j60Read(ERXWRPTL));
	rprintfProgStrM("  0x");
	rprintfu8(enc28j60Read(ERXRDPTH));
	rprintfu8(enc28j60Read(ERXRDPTL));
	rprintfProgStrM("   0x");
	rprintfu8(enc28j60Read(ERXFCON));
	rprintfProgStrM("    0x");
	rprintfu8(enc28j60Read(EPKTCNT));
	rprintfProgStrM("  0x");
	rprintfu8(enc28j60Read(MAMXFLH));
	rprintfu8(enc28j60Read(MAMXFLL));
	rprintfCRLF();

	rprintfProgStrM("Tx   : ETXST  ETXND  MACLCON1 MACLCON2 MAPHSUP\r\n");
	rprintfProgStrM("       0x");
	rprintfu8(enc28j60Read(ETXSTH));
	rprintfu8(enc28j60Read(ETXSTL));
	rprintfProgStrM(" 0x");
	rprintfu8(enc28j60Read(ETXNDH));
	rprintfu8(enc28j60Read(ETXNDL));
	rprintfProgStrM("   0x");
	rprintfu8(enc28j60Read(MACLCON1));
	rprintfProgStrM("     0x");
	rprintfu8(enc28j60Read(MACLCON2));
	rprintfProgStrM("     0x");
	rprintfu8(enc28j60Read(MAPHSUP));
	rprintfCRLF();
*/
}



