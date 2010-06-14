#include "telnettask.h"
#include "lib/socket.h"
#include "lib/multitasker.h"
#include "lib/uip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hardware/rtcc.h"

#define SEND_BUF_SIZE 100
#define REC_BUF_SIZE 100

#define CHAR_BACKSPACE 8

//telnet option values
#define TELNET_IAC 	255
#define TELNET_WILL	251
#define TELNET_WONT	252
#define TELNET_DO	253
#define TELNET_DONT 254
#define TELNET_SB	250
#define TELNET_SE	240
#define TELNET_EC	247
#define TELNET_ECHO 1
#define TELNET_SUPPRESS_GO_AHEAD	3
#define TELNET_LINEMODE 34
#define TELNET_LINEMODE_SB_MODE 1
#define TELNET_LINEMODE_SB_EDIT 1

//telnet operating mode word bit assignments
#define MODE_ECHO 	1

const char* CRLF ="\r\n";

struct command
{
	char * command;
	void(* exec)(file_handle_t, char**, unsigned int );		
};



char send_buf[SEND_BUF_SIZE];
char receive_buf[REC_BUF_SIZE];
file_handle_t telnet_handle;
struct buffer_t telnet_receive_buffer;
struct buffer_t telnet_send_buffer;
struct file_event_query_t connection_event;
unsigned char telnet_mode = 0;
unsigned char optneg_mode = 0;

//returns the number of parameters found in [line] up to [count] many
//the start of each param is set in the [params] array, which must be at least [count] big
//Each param is \0 terminated on return
int tokenise_line( char* line, const char* line_end, char** params, const int count)
{
	int found = 0;
	while( line < line_end )
	{
		if( isprint(*line) && ' ' != (*line) )
		{
			if( found < count) params[found] = line;
			found++;
			while( line < line_end && isprint(*line) && ' '!=(*line) ) line++;
			*line='\0';
		}
		line++;
	}
	return found;
}





void telnet_time( file_handle_t handle, char** argv, unsigned int argc )
{
	file_puts( "RTCC Date/Time: ", handle );
	struct tm time;
	rtcc_get_tm( &time );
	char* timestr = malloc( 32 );
	sprintf(timestr,"%u-%02u-%02u %02u:%02u:%02u", time.tm_year+1900, time.tm_mon+1, time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec );
	file_puts(timestr, handle);
	free( timestr );
	file_puts(CRLF, handle);
}


void telnet_quit( file_handle_t handle, char** argv, unsigned int argc )
{
	file_close( handle );
	telnet_handle = FILE_INVALID_HANDLE;
}


void telnet_echo( file_handle_t handle, char** argv, unsigned int argc )
{	
	int i;
	for( i=1; i < argc; )
	{
		file_puts(argv[i], handle);
		if( ++i < argc ) file_putchar(' ',handle);		
	} 
	file_puts(CRLF, handle);
	return;
}

void telnet_memdump( file_handle_t handle, char** argv, unsigned int argc )
{
	int i = 1;
	char* memstart = NULL;
	char* parseend;
	unsigned int len = 0;
	char* line = malloc(64);
	if( argc != 3)
	{
		file_puts("memdump [address] [count]\r\n", telnet_handle);
		return;
	} 
	memstart = (char*)(unsigned short) strtoul( argv[1], &parseend, 0);
	len = (unsigned int) strtoul( argv[2], &parseend, 0);
	parseend = memstart + len;
	char *tmp;
	while( memstart < parseend )
	{
		tmp = line;
		tmp += sprintf(tmp,"%p\t", memstart);
		for( i = 0 ; i < 8; i++ )
		{
			unsigned char b = memstart[i];
			tmp+=sprintf(tmp, "%02hhx ", b);
		}
		*tmp = '\t';
		for( i = 0 ; i < 8; i++ )
		{
			if( *memstart >= ' ' && *memstart <= '~' ) *tmp++ = *memstart;
			else *tmp++ = '.';
			memstart++;
		}
		*tmp = '\0';	
		file_puts( line , telnet_handle);
		file_puts( CRLF , telnet_handle);
	}
	free(line);
	return;
}

void telnet_help( file_handle_t handle, char** argv, unsigned int argc );

/*
* To add more commands, define them above and add to this array initialisation.
*/
const struct command const commands[]={
	{"help",&telnet_help},
	{"echo",&telnet_echo},
	{"time",&telnet_time},
	{"quit",&telnet_quit},
	{"memdump",&telnet_memdump}
};	
#define CMDS_SIZE  ( sizeof(commands) / sizeof(struct command) )

void telnet_help( file_handle_t handle, char** argv, unsigned int argc )
{
	file_puts(  "Configured commands:\r\n" , handle);
	int i = 0;
	for( ; i < CMDS_SIZE ; i++ )
	{
		file_puts(  commands[i].command , handle);
		file_puts( CRLF , handle );
	}
}


void exec_line( char* line, char* end )
{
	int token_count = tokenise_line( line, end, NULL, 0 );
	if( token_count >  0 )
	{
		char** argv = malloc( sizeof(char*) * token_count );
		tokenise_line( line, end, argv, token_count );
		//match command against cmd list
		unsigned short i = 0;
		for( ; i < CMDS_SIZE; i++ )
		{
			if( strcmp( commands[i].command, argv[0] ) == 0)
			{
				commands[i].exec( telnet_handle, argv, token_count);
				break;
			}
		}
		if(  i == CMDS_SIZE ) //fell out of loop without a match
		{
			file_puts("Unknown command: ", telnet_handle);
			file_puts(argv[0], telnet_handle );
			file_puts(CRLF, telnet_handle );
		}
		free( argv );
	}
}



//A pointer to this function is passed into the socket_listen call
//It will be called whenever an incoming connection is setup on the listening port
file_handle_t telnet_connect_accept(u16_t local_port, u16_t *remote_address, u16_t remote_port)
{
#ifdef __DEBUG
	unsigned char* raddr = (unsigned char*) remote_address;
	printf("\nTelnet: Connect from %hhd.%hhd.%hhd.%hhd port %d", raddr[1],raddr[0],raddr[3],raddr[2], remote_port  );
#endif
	if( telnet_handle != FILE_INVALID_HANDLE ) return FILE_INVALID_HANDLE;
	buffer_init( &telnet_send_buffer, send_buf, SEND_BUF_SIZE );
	buffer_init( &telnet_receive_buffer, receive_buf, REC_BUF_SIZE );
	telnet_handle = file_handle_create( &telnet_receive_buffer, &telnet_send_buffer );
	optneg_mode = 0;

	//we will do the echoing from this end. 
	//It's just easier than to try and do full option negotiation
	telnet_mode = 0 | MODE_ECHO;
	file_putchar(TELNET_IAC, telnet_handle);
	file_putchar(TELNET_WILL, telnet_handle);
	file_putchar(TELNET_ECHO, telnet_handle);
	file_putchar(TELNET_IAC, telnet_handle);
	file_putchar(TELNET_WILL, telnet_handle);
	file_putchar(TELNET_SUPPRESS_GO_AHEAD, telnet_handle);
	file_puts("\r\nWeb platform telnet. Enter help for commands.\r\n>", telnet_handle);
	return telnet_handle;
}

//The main telnet task
void telnet_task_main(void)
{
/*
	commands[0].command="help";
	commands[0].exec = &telnet_help;

	commands[1].command="echo";
	commands[1].exec = &telnet_echo;

	commands[2].command="time";
	commands[2].exec = &telnet_time;

	commands[3].command="quit";
	commands[3].exec = &telnet_quit;

	commands[4].command="memdump";
	commands[4].exec = &telnet_memdump;
*/
	connection_event.event_mask = ReadableOrException;
	telnet_handle = FILE_INVALID_HANDLE;
	socket_listen(HTONS(23), &telnet_connect_accept );

	unsigned short pos = 0;
	while(1)
	{
restart:
		while( ! file_get_next_event( &telnet_handle, 1, &connection_event) )
		{
			task_yield();
		}
		if( connection_event.event & Exception )
		{
//#ifdef __DEBUG
			puts("\r\nTelnet: Closing connection");
//#endif
			file_close( telnet_handle );
			telnet_handle = FILE_INVALID_HANDLE;
			pos = 0;
			optneg_mode = 0;
			goto restart;
		}

		unsigned short avail = buffer_available(&telnet_receive_buffer);
		char* rd_buf = buffer_read_ptr(&telnet_receive_buffer);
		while( pos < avail)//if avail == 1, rd_buf[0] is the last char we can read
		{
			unsigned char c = rd_buf[pos];
			if( pos == REC_BUF_SIZE-1 )
			{
				//buffer is full, but no CR/LF seen yet... what to do?
				//either discard line, or pretend the last char was \r ??
				c = '\r';
			}

			switch(c)
			{
				case TELNET_IAC:
					if( avail - pos > 2 )
					{
						//buf[pos+1] = will/wont/do/dont
						//buf[pos+2] = option
						switch( (unsigned char) rd_buf[pos+2] )
						{
							case TELNET_ECHO:
								switch( (unsigned char) rd_buf[pos+1] )
								{
									case TELNET_DO:
										//other end wants us to echo
										telnet_mode |= MODE_ECHO;
										break;
									case TELNET_DONT:
										//other end demands we don't echo
										telnet_mode &= ~MODE_ECHO;
										break;
								}
								break;
						}
						//remove 3 chars from buffer
						buffer_unwrite(&telnet_receive_buffer, &rd_buf[pos], 3 );
						avail -= 3;
					}
					else
					{
						task_yield();
					}
					break;
				case '\r': // could be \r\n , \r\0 or just \r on its own
					pos++;
					if( telnet_mode & MODE_ECHO)
					{
						file_puts(CRLF, telnet_handle);
					}
					//if there's a following character, and it's \n or \0, chomp it too.
					if( pos < avail && (rd_buf[pos+1] == '\n' || rd_buf[pos+1] == '\0')) pos++; 
					exec_line( rd_buf, rd_buf+pos ); //if read rd_buf[0], pos == 1 -> end = (rd_ptr + 1)

					buffer_seek( &telnet_receive_buffer, pos ); //free buffer
					rd_buf = buffer_read_ptr(&telnet_receive_buffer);

					pos = 0;
					avail = buffer_available(&telnet_receive_buffer);
					file_putchar('>', telnet_handle);
					break;
				case '\b':
				case 0x7f:
					puts("\r\ntel:backspace");
					if( pos > 0 ) //not the first character
					{
						if( telnet_mode & MODE_ECHO)
						{
							file_putchar('\b', telnet_handle);
							file_putchar(' ', telnet_handle);
							file_putchar('\b', telnet_handle);
						}
						buffer_unwrite(&telnet_receive_buffer, &rd_buf[pos-1], 2 );
						avail-=2;
						pos--;
					}
					else
					{
						buffer_unwrite(&telnet_receive_buffer, &rd_buf[pos], 1 );
						avail--;
					}
					break;
				default:
					if( c >= ' ' && c <='~' )
					{
						if( telnet_mode & MODE_ECHO)
						{
							file_putchar(c, telnet_handle);
							pos++;
						}
					}
					else
					{
						buffer_unwrite(&telnet_receive_buffer, &rd_buf[pos], 1 );
						avail--;
					}
			}//end switch
		}//end while loop

		task_yield();
	}//end outer while
}



