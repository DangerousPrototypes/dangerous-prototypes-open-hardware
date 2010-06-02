#include "telnettask.h"
#include "lib/socket.h"
#include "lib/multitasker.h"
#include "lib/uip.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "hardware/rtcc.h"

#define CMDS_SIZE 4
#define SEND_BUF_SIZE 200
#define REC_BUF_SIZE 100

const char* CRLF ="\r\n";

struct command
{
	char * command;
	void(* exec)(file_handle_t, char*, char* );		
};

struct command commands[CMDS_SIZE];

char send_buf[SEND_BUF_SIZE];
char receive_buf[REC_BUF_SIZE];
file_handle_t telnet_handle;
struct buffer_t telnet_receive_buffer;
struct buffer_t telnet_send_buffer;
struct file_event_query_t connection_event;


//position ptr to start of first non-whitespace between ptr and end
void find_nonspace( char** ptr, char* end )
{
	while( (*ptr) < end && isspace( *(*ptr) )  )
	{
		(*ptr)++;
	}
}



//returns the count of chars contained in the next token starting at [ptr].
//-1 if no whitespace found before [end]
//will return 0 if [ptr] is pointing at whitespace
int next_token( char* ptr , char* end )
{
	char* start = ptr;
	while( ptr < end )
	{
		if( isspace( *ptr ) )
		{ 
			return ptr - start;
		}
		ptr++;
	}
	return -1;
}

void exec_line( char* line, char* end )
{
	int cmd_size = next_token( line, end );
	if( cmd_size > 0 )
	{
		line[cmd_size] = '\0' ;	//we can do this because line[cmd_size] MUST be pointing at an isspace() char
								//that will help with string comps and reporting, etc

		//match command against cmd list
		unsigned short i = 0;
		for( ; i < CMDS_SIZE; i++ )
		{
			if( strcmp( commands[i].command, line ) == 0)
			{
				commands[i].exec( telnet_handle, line + cmd_size + 1, end );
				break;
			}
		}
		if(  i == CMDS_SIZE ) //fell out of loop without a match
		{
			file_puts("Unknown command: ", telnet_handle);
			file_puts(line, telnet_handle );
			file_puts(CRLF, telnet_handle );
		}
	}
	else
	{
		//if cmd_size == 0, line started with space
		//if < 0, no token found in line
		//Both are errors
		file_puts("Bad input.\r\n", telnet_handle);			
	}
}


void telnet_help( file_handle_t handle, char* start, char* end )
{
	file_puts(  "Configured commands:\r\n" , handle);
	int i = 0;
	for( ; i < CMDS_SIZE ; i++ )
	{
		file_puts(  commands[i].command , handle);
		file_puts( CRLF , handle );
	}
}


void telnet_time( file_handle_t handle, char* start, char* end )
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
	file_puts(CRLF, handle);
}


void telnet_quit( file_handle_t handle, char* start, char* end )
{
	file_close( handle );
	telnet_handle = FILE_INVALID_HANDLE;
}


void telnet_paramcheck( file_handle_t handle, char* start, char* end )
{
	int i = 1;
	while( start < end )
	{
printf("\r\npc: start/end: %p/%p", start, end );
		find_nonspace( &start, end );
printf("\r\npc: start/end: %p/%p", start, end );
		if( start < end )
		{
			int token_size = next_token( start, end );
printf("\r\npc: size: %d", token_size );
			if( token_size < 1 ) return; //no more tokens
			start[token_size] = '\0'; //null terminate the param

			file_puts("Parameter ", handle);
			file_putchar('0'+i, handle);
			file_puts(": ", handle);
			file_puts(start, handle);
			file_puts(CRLF, handle);

			start+= (++token_size);
			i++;
		}
	}
	return;
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

	commands[1].command="paramcheck";
	commands[1].exec = &telnet_paramcheck;

	commands[2].command="time";
	commands[2].exec = &telnet_time;

	commands[3].command="quit";
	commands[3].exec = &telnet_quit;


	connection_event.event_mask = ReadableOrException;
	telnet_handle = FILE_INVALID_HANDLE;
	socket_listen(HTONS(23), &telnet_connect_accept );

	unsigned short pos = 0;
	while(1)
	{
		while( ! file_get_next_event( &telnet_handle, 1, &connection_event) )
		{
			task_yield();
		}

		//Wikipedia says that you'll get either:
		//LF	\n 
		//or
		//CR+LF	\r\n
		//If we just drop the \r, it should be fine?
				
		unsigned short avail = buffer_available(&telnet_receive_buffer);
		char* rd_buf = buffer_read_ptr(&telnet_receive_buffer);
		while( pos < avail)//if avail == 1, rd_buf[0] is the last char we can read
		{
printf("\r\ntel: pos/avail:%d/%d @ %p", pos, avail, rd_buf );
			char c = rd_buf[pos];
			if( c & 0x80 ){
printf("\r\ntel: ctrl code %02x", c );
				c=' ';
			}
			file_putchar(c, telnet_handle);
			pos++;
			if( pos == REC_BUF_SIZE )
			{
				//buffer is full, but no CR/LF seen yet... what to do?
				//either discard line, or pretend the last char was \n ??
				c = '\n';
			}
			if( c == '\n' )
			{
printf("\r\ntel: exec");
				exec_line( rd_buf, rd_buf+pos ); //if read rd_buf[0], pos == 1 -> end = (rd_ptr + 1)
				buffer_seek( &telnet_receive_buffer, pos ); //free buffer
				pos = 0;
				break;
			}
		}
		task_yield();

	}
}



