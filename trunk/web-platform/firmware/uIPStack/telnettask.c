#include "telnettask.h"
#include "lib/socket.h"
#include "lib/multitasker.h"
#include "lib/uip.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "hardware/rtcc.h"

#define CMDS_SIZE 3
#define SEND_BUF_SIZE 200
#define REC_BUF_SIZE 100

struct command
{
	char * command;
	void(* exec)(file_handle_t );		
};

struct command commands[CMDS_SIZE];

char send_buf[SEND_BUF_SIZE];
char receive_buf[REC_BUF_SIZE];
file_handle_t telnet_handle;
struct buffer_t telnet_receive_buffer;
struct buffer_t telnet_send_buffer;
struct file_event_query_t connection_event;



void telnet_help( file_handle_t handle )
{
	file_puts(  "Configured commands:\n" , handle);
	int i = 0;
	for( ; i < CMDS_SIZE ; i++ )
	{
		file_puts(  commands[i].command , handle);
		file_putchar( '\n' , handle );
	}
}


void telnet_time( file_handle_t handle )
{
	file_puts( "RTCC Date/Time: 20", handle );
	struct rtcc_bcd_tm time;
	rtcc_get_bcd_tm( &time );
	file_putchar('0'+ (time.year >> 4), handle);
	file_putchar('0'+ (time.year & 0x0f), handle);
	file_putchar('-', handle);
	file_putchar('0'+ (time.mon >> 4), handle);
	file_putchar('0'+ (time.mon & 0x0f), handle);
	file_putchar('-', handle);
	file_putchar('0'+ (time.day >> 4), handle);
	file_putchar('0'+ (time.day & 0x0f), handle);
	file_putchar(' ', handle);
	file_putchar('0'+ (time.hour >> 4), handle);
	file_putchar('0'+ (time.hour & 0x0f), handle);
	file_putchar(':', handle);
	file_putchar('0'+ (time.min >> 4), handle);
	file_putchar('0'+ (time.min & 0x0f), handle);
	file_putchar(':', handle);
	file_putchar('0'+ (time.sec >> 4), handle);
	file_putchar('0'+ (time.sec & 0x0f), handle);
	file_putchar('\n', handle);
}


void telnet_quit( file_handle_t handle )
{
	file_close( handle );
	telnet_handle = FILE_INVALID_HANDLE;
}



//A pointer to this function is passed into the socket_listen call
//It will be called whenever an incoming connection is setup on the listening port
file_handle_t telnet_connect_accept(u16_t local_port, u16_t *remote_address, u16_t remote_port)
{
	printf("\necho: connect from %04x%04x", remote_address[0],remote_address[1]  );
	if( telnet_handle != FILE_INVALID_HANDLE ) return FILE_INVALID_HANDLE;
	buffer_init( &telnet_send_buffer, send_buf, SEND_BUF_SIZE );
	buffer_init( &telnet_receive_buffer, receive_buf, REC_BUF_SIZE );
	telnet_handle = file_handle_create( &telnet_receive_buffer, &telnet_send_buffer );
	printf("\necho: using handle %hhd", telnet_handle );
	return telnet_handle;
}

//The main telnet task
void telnet_task_main(void)
{
	commands[0].command="help";
	commands[0].exec = &telnet_help;

	commands[1].command="time";
	commands[1].exec = &telnet_time;

	commands[2].command="quit";
	commands[2].exec = &telnet_quit;

	connection_event.event_mask = ReadableOrException;
	telnet_handle = FILE_INVALID_HANDLE;
	socket_listen(HTONS(23), &telnet_connect_accept );

	while(1)
	{
		while( ! file_get_next_event( &telnet_handle, 1, &connection_event) )
		{
			task_yield();
		}
		printf("\necho: file state %hhx", file_get_by_handle(telnet_handle)->state );
	
		printf("\necho: event %hhx", connection_event.event );
		if( connection_event.event & Exception )
		{
			file_close( telnet_handle );
			telnet_handle = FILE_INVALID_HANDLE;
		}
		else
		{
			unsigned short can_read = buffer_available( &telnet_receive_buffer );
			const char * data = buffer_read_const_ptr( &telnet_receive_buffer );
			unsigned short i = 0;
			//trim leading whitespace
		printf("\necho: can_read %hd @ %04x", can_read, data );
			while(i < can_read )
			{
				if(! isspace(data[i] ) ) break;
				i++;
			}
		printf("\necho: seek %hd",i );

			buffer_seek( &telnet_receive_buffer, i ); //trim leading whitespace
			data += i;
			can_read -= i;
			i =0;
			while(i < can_read )
			{
				if( isspace(data[i] ) )
				{
		printf("\necho: cmd end at %hd",i );
					//i contains the number of chars to compare
					unsigned short cmd = 0;
					for(  ; cmd < CMDS_SIZE; cmd++ )
					{
						struct command* c = &commands[cmd];
						if( strncmp( c->command, data , i ) == 0 )
						{
							buffer_seek( &telnet_receive_buffer, i );
							c->exec(telnet_handle);
							break;
						}
					}
					break;
				}
				i++; 
			}
			//not found. 
		printf("\necho: not_found seek %hd",i );
			buffer_seek( &telnet_receive_buffer, i );
		}
	}

}
