#include "nic_dma.h"
#include "../libConfig/nic.h"
#include "HardwareProfile.h"
#include <stdio.h>

volatile union SHORT_BITFIELD UIP_DMA_STATUS ;
volatile unsigned int uip_dma_rx_pending_packets;

unsigned int uip_dma_rx_last_packet_length;
unsigned int uip_dma_tx_last_packet_length;






//process INT from ENC. Start RX DMA if buffer free, otherwise
//note theres one more packet waiting to be read.
void __attribute__ ((interrupt,auto_psv)) _CNInterrupt(){
	
	if( ENC_INT_IO == 0 ) //INT pin gone low...it's real
	{
		
		if( UIP_DMA_BUFFER_FREE )
		{
			UIP_DMA_BUFFER_FREE=0;			
			if( 0 == ( uip_dma_rx_pending_packets = NICBeginPacketRetrieveDMA()) )
			{
				//got the interrupt, but no packet to read??? Reset buffer status
				UIP_DMA_BUFFER_STATUS_RESET();
			}
		}
		else
		{
			//dma not free, will have to collect later
			uip_dma_rx_pending_packets++;
		}
	}	
	IFS1bits.CNIF = 0; //clear CN int flag
}

/*
* We'll have this interrupt handler for the dummy DMA channel
* It will trigger the end of packet transmission because
* we cannot lower CS until the END of the transmission 
* (ie, AFTER the dummy has READ the last byte )
*/
void ENC_DMADUMMY_INTERRUPT(){
	enc28j60EndPacketSend();
	if( 0 == ( uip_dma_rx_pending_packets = NICBeginPacketRetrieveDMA() ) )
	{
		UIP_DMA_BUFFER_STATUS_RESET();
	}
	ENC_DMADUMMY_INTIF = 0;	
}

void ENC_DMA_INTERRUPT(){
	if( ENC_DMACONbits.DIR == 0 ) //DIR 0 = read from peripheral to RAM
	{
		//do rx finished cleanup
		enc28j60EndPacketReceive();
		UIP_DMA_RX_PACKET_READY = 1;
	}
	else
	{
		//end of packet send handled by other DMA channel
	}
	
	ENC_DMA_INTIF = 0; //clear DMA int flag

}

//I want to write to the buffer, if this returns non-zero, I can
unsigned int uip_acquireBuffer(){
	unsigned int retval = 0;
	if( UIP_DMA_BUFFER_FREE == 0 ) return 0;//quick test
	IEC1bits.CNIE = 0; //disable CN int
	if( UIP_DMA_BUFFER_FREE == 1 )
	{
		UIP_DMA_BUFFER_FREE=0;
		retval = 1;
	}
	IEC1bits.CNIE = 1; //enable CN int

	return retval;
}

