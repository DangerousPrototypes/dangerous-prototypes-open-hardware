

#include "hardware/HardwareProfile.h"
#include "uipsockettask.h"
#include "lib/multitasker.h"
#include "lib/uip.h"
#include "lib/uip_arp.h"
#include "libConfig/nic.h"
#include "hardware/nic_dma.h"
#include <stdio.h>
#include "lib/socket.h"


#define BUF ((struct uip_eth_hdr *)&uip_buf[0])
unsigned char i;
unsigned char arptimer=0;
unsigned char next_conn_id = 0;
unsigned char next_send_id = 0;

//uip's array of listening ports
extern u16_t uip_listenports[UIP_LISTENPORTS];
//additional external added to uip to hold how many bytes a current ACK is ACK-ing
extern u16_t uip_this_ack;


//The array of callback functions to call 
//when an incoming connection is established on a listening port
file_handle_t (*listenports[UIP_LISTENPORTS])(u16_t, u16_t *, u16_t) ;


/*
*
*
*IMPLEMENTATION OF SOCKET.H FUNCTIONS
*
*
*/


//port number must be in network order (use htons() )
bool socket_listen( unsigned short port, file_handle_t (*accept_callback)(u16_t local_port, u16_t *remote_address, u16_t remote_port) )
{
	int i = uip_listen( port );
	if( i < 0 ) return false;
	listenports[i] = accept_callback;
	return true;
}

//Connect to a remote host and associate the file_handle with the connection.
//returns true on success, false on failure (eg, no more uip connection slots available )
//Note that success does not indicate the connection was establshed; watch the file handle's status for state changes.
bool socket_connect( file_handle_t file_handle, struct inetaddr_t *remote_address )
{
	struct file_t* file = file_get_by_handle( file_handle );
	if( file == NULL ) return false; 
	u16_t ipaddr[2];
	uip_ipaddr(ipaddr, remote_address->addr1,remote_address->addr2,remote_address->addr3,remote_address->addr4);
	struct uip_conn *conn = uip_connect(ipaddr, htons( remote_address->port ) );
	if( conn == NULL ) return false;
	conn->appstate[0] = file_handle;
	file->state = OpenPending;
	return true;
}


/*
*
*
*END IMPLEMENTATION OF SOCKET.H FUNCTIONS
*
*
*/




/*
* This is a co-operative task. This function must NEVER return
*/
void uip_task_main(void)
{
	//initialise all the connections to point to the invalid handle
	for( i = 0 ; i  < UIP_CONNS; i++)
	{
		uip_conns[i].appstate[0] = FILE_INVALID_HANDLE;		
	}

	while(1){
	    
		task_yield();
 	
		if( UIP_DMA_RX_PACKET_READY )
		{
			UIP_DMA_RX_PACKET_READY = 0;
			uip_len = uip_dma_rx_last_packet_length;
			// packet received - buffer is already acquired
	
	      	// process an IP packet
	      	if(BUF->type == HTONS(UIP_ETHTYPE_IP)){
	        	// add the source to the ARP cache
	        	// also correctly set the ethernet packet length before processing
	        	uip_arp_ipin();
	        	uip_input();
	
	     		// transmit a packet, if one is ready
	        	if(uip_len > 0){
	          		uip_arp_out();
	          		nic_send();
	        	}
				else nic_rx_maybe();
			}
			else if(BUF->type == HTONS(UIP_ETHTYPE_ARP)){
	
				// process an ARP packet
	 	  		uip_arp_arpin();
	
	        	// transmit a packet, if one is ready
	        	if(uip_len > 0){

	          		nic_send();
				}
				else{

					nic_rx_maybe();
				}
	      	}
			else //don't know how to process this packet. Discard
			{
				puts("Unknown packet discarded");
				nic_rx_maybe();
			}
		}
		else if(UIP_DMA_PERIODIC_TIMEOUT && uip_acquireBuffer()){
//printf("\nperiodic timeout: id %hhd", next_conn_id);
			if( next_conn_id != UIP_CONNS )
			{
				uip_len = 0;
				while( uip_len == 0 && next_conn_id < UIP_CONNS )
				{
					uip_periodic( next_conn_id );
		    	    // transmit a packet, if one is ready
		        	if(uip_len > 0){
//printf("\n id %hhd sending", next_conn_id);
		            	uip_arp_out();
		            	nic_send();
					}
					next_conn_id++;
//printf(",%hhd", next_conn_id);
				}
			}
			if( next_conn_id == UIP_CONNS )
			{

				UIP_DMA_PERIODIC_TIMEOUT=0;

				//blink LED to show we're alive
	        	LD1_O = !LD1_O;
				next_conn_id = 0;

		        /* Call the ARP timer function every 10 seconds. */
		        if(++arptimer == 20){	
			        uip_arp_timer();
		    	    arptimer = 0;
		        }
				uip_releaseBuffer();
//printf("\n state %04hx", UIP_DMA_STATUS.value);
//possibly change test below to if( uip_len == 0)??
				if( ENC_DMACONbits.CHEN == 0 ) nic_rx_maybe();
			}
		}
		else
		{
			//anyone need to send something or close?
			unsigned char loop_end = next_send_id;
			
			do
			{
				struct uip_conn *connptr = &uip_conns[next_send_id];
				file_handle_t fh = connptr->appstate[0];
				struct file_t *f = file_get_by_handle(fh);
				if(f != NULL && 
					( f->state == ClosePending ||
					 (f->write_buffer != NULL && buffer_available( f->write_buffer) > 0)
					)
				  )
				{
	printf("\n id %hhd state %hhx", next_send_id, f->state);
					if( uip_acquireBuffer() )
					{
						uip_periodic_conn(connptr);
						if(uip_len > 0){
	printf("\n id %hhd sending", next_send_id);
			            	uip_arp_out();
			            	nic_send();
							break;
						}
						else uip_releaseBuffer();
					}
					break; //this connection wants to write. try again later
				}
				
				next_send_id = ++next_send_id < UIP_CONNS ? next_send_id : 0;
				
			}while( next_send_id != loop_end );
		}

		
	} //end while

}

//This is the implementation of the UIPAPP that uIP will call when
//something network data related happens.
//The purpose of this app is to move buffer data to and from the network
void uip_socket_app(void)
{
	int i;
	file_handle_t file_handle =  (uip_conn->appstate)[0];
	struct file_t* file = NULL;
	struct buffer_t *rxbuf = NULL;
	struct buffer_t *txbuf = NULL;
	bool may_send = true;

	

	if(uip_connected())
	{
		printf("app: connected. Ports %hd:%hd", uip_conn->lport, uip_conn->rport);

		if( file_handle == FILE_INVALID_HANDLE )
		{
			//it's an incoming connection (no assigned handle)
			//find the index of the listening port
			for( i = 0; i < UIP_LISTENPORTS ; i++ )
			{
				if( uip_listenports[i] == uip_conn->lport )
				{
					file_handle = listenports[i](uip_conn->lport, uip_conn->ripaddr, uip_conn->rport);
					if( file_handle != FILE_INVALID_HANDLE ) 
					{	
						uip_conn->appstate[0] = file_handle;
					}
					break;
				}
			}
		}
	}
	if( file_handle == FILE_INVALID_HANDLE)
	{ 
		goto close_or_abort;
	}
	
	file =  file_get_by_handle(file_handle);
	rxbuf = file->read_buffer;
	txbuf = file->write_buffer;


	if( file->state == ClosePending )
	{
		printf("\napp: freeing handle %hhd",uip_conn->appstate[0]);
		file_free(uip_conn->appstate[0]);
		uip_conn->appstate[0] = FILE_INVALID_HANDLE;
		goto close_or_abort;
	}


	if( rxbuf == NULL || txbuf == NULL )
	{
		goto close_or_abort;
	}

	if( uip_connected() ) file->state = Open;

	if( uip_acked() ){
		//TODO: get size of last send data from uip_conn
		printf("\napp: acked %d bytes", uip_this_ack);
		buffer_seek( txbuf, uip_this_ack );
	}

	int free = buffer_free( rxbuf );//free to write to
	int available = buffer_available( txbuf );//available to read

	if(uip_rexmit()){
		printf("app: rexmit. Handle: %hhd", file_handle);

		buffer_peek( txbuf, (char*)uip_appdata, uip_conn->len);
		uip_send(uip_appdata, uip_conn->len);
		may_send = false;
	}
	else if(uip_newdata())
	{
		printf("app: newdata. Handle: %hhd. len=%u\n", file_handle, uip_datalen() );

		if( free >= uip_datalen() )
		{
			free -= buffer_write( rxbuf, (char*)uip_appdata, uip_datalen() );
		}
		else{
			puts("buffer overflow\n");
		}
	}
	else if( uip_closed() )
	{
		printf("app: connection id %hhd closed\n", file_handle );
		file->state = Closed;
		may_send = false;
	}
	else if( uip_aborted() )
	{
		printf("app: connection id %hhd aborted\n", file_handle );
		file->state = Aborted;
		may_send = false;
	}
	else if( uip_timedout() )
	{
		printf("app: connection id %hhd timed out\n", file_handle );
		file->state = TimedOut;
		may_send = false;
	}
	if( available > 0 && may_send && uip_conn->len == 0){
		//we can send the smaller of what's available or the connection mss
		int size = available < uip_mss() ? available : uip_mss() ;
		int peek = buffer_peek( txbuf, (char*)uip_appdata, size);
		uip_appdata[peek] = '\0';
		printf("app: sending %d of %d available bytes: [%s] ", peek,available, (char*)uip_appdata);
		
		uip_send(uip_appdata, peek);
		
	}
	if( free < rxbuf->size / 2 )
	{
		puts("\napp: stopping rx\n");
		uip_stop();
	}
	else if( uip_stopped(uip_conn) )
	{
		puts("\napp: restarting rx\n");
		uip_restart(); //TODO NEED to be able to set the window size?
	}

	return;

close_or_abort:
	if( uip_closed() || uip_aborted() || uip_timedout() )
	{
		puts("\napp: abort chosen");
		uip_abort();
	}
	else
	{
		puts("\napp: close chosen");
		uip_close();
	}

}
