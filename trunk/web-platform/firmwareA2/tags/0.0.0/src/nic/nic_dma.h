#ifndef _NIC_DMA_H_
#define _NIC_DMA_H_
/*
nic_dma.h
*/


union SHORT_BITFIELD
{
	struct
	{
		unsigned bit1:1;
		unsigned bit2:1;
		unsigned bit3:1;
		unsigned bit4:1;
		unsigned bit5:1;
		unsigned bit6:1;
		unsigned bit7:1;
		unsigned bit8:1;
		unsigned bit9:1;
		unsigned bit10:1;
		unsigned bit11:1;
		unsigned bit12:1;
		unsigned bit13:1;
		unsigned bit14:1;
		unsigned bit15:1;
		unsigned bit16:1;
	} bits;
	unsigned short value;
};

extern volatile union SHORT_BITFIELD UIP_DMA_STATUS ;

//buffer is not in use at this time
#define UIP_DMA_BUFFER_FREE ( UIP_DMA_STATUS.bits.bit1 )
//a packet has been RX DMA'd, and is in the buffer
//#define UIP_DMA_RX_PACKET_READY ( UIP_DMA_STATUS.bits.bit2 )
//a periodic timer event had occurred
#define UIP_DMA_PERIODIC_TIMEOUT ( UIP_DMA_STATUS.bits.bit3 )

#define UIP_DMA_BUFFER_STATUS_RESET() 	UIP_DMA_BUFFER_FREE = 1

//number of packets that are waiting in the ENC for retrieval.
//This is incremented in the INT handler if the buffer is not 
//available to start RX DMA at that time.
//If it's non-zero at the end of TX DMA, start RX DMA immediately
extern volatile unsigned int uip_dma_rx_pending_packets;

//length of last packet recieved via dma
extern unsigned int uip_dma_rx_last_packet_length;
extern unsigned int uip_dma_tx_last_packet_length;


unsigned int uip_acquireBuffer();
void uip_releaseBuffer();


#endif
