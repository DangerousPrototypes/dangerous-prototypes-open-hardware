/*****************************************************************************
*  "A Very Simple Application" from the uIP 0.9 documentation
*****************************************************************************/

#include "app.h"
#include <stdio.h>
#include <string.h>

unsigned char sendBuf[UIP_TCP_MSS] __attribute__((aligned(2)));
unsigned int last_sent_size;
static unsigned char connectionID = 0;

void example1_init(void)
{
	uip_listen(HTONS(23));
}

void tcp_copy_send( const char * data, unsigned int size )
{
	strcpy(sendBuf,data);
	uip_send(sendBuf,size);
	last_sent_size = size;
}
void tcp_send( unsigned int size )
{
	uip_send(sendBuf,size);
	last_sent_size = size;
}

void example1_app(void)
{
	unsigned char conn_id =  *(uip_conn->appstate);
	if(uip_connected()){
		*(uip_conn->appstate) = connectionID;
		conn_id = connectionID++;
		printf("app: connected. Connection ID: %hhd", conn_id);
		tcp_copy_send("welcome\n", 8);
	}
	else if(uip_rexmit()){
		printf("app: rexmit. Connection ID: %hhd", conn_id);
		tcp_send(last_sent_size);
	}
	else if(uip_newdata())
	{
		printf("app: newdata. Connection ID: %hhd. len=%u\n", conn_id, uip_datalen() );
		u16_t i;
		for( i = 0; i < uip_datalen() ; i++ ){
			printf("%hhx ", uip_appdata[i]);
			sendBuf[i] = uip_appdata[i];
		}
		puts("\n");
		strcpy(&(sendBuf[i])," - ok\n");
		tcp_send(i + 6);
	}
	else if( uip_closed() )
	{
		printf("app: connection id %hhd closed\n", conn_id );
	}
	else if( uip_aborted() )
	{
		printf("app: connection id %hhd aborted\n", conn_id );
	}
	else if( uip_timedout() )
	{
		printf("app: connection id %hhd timed out\n", conn_id );
	}
}
