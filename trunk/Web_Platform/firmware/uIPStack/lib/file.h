#ifndef _FILE_H_
#define _FILE_H_

#include "buffer.h"
#include "../stdlib/stdbool.h"

//file states states
enum file_state_t{
	Free = 0,		//initial, and after file_close is processed by uip()
	NotFree,		//when allocated from the pool
	OpenPending,	//after association with a connection, but before it's established. May never go to Open
	Open,			//connection established or file open; you may read/write only in this state
	Aborted,		//connection aborted by other end
	TimedOut,		//connection timed out
	Closed,			//connection closed by other end
	ClosePending    //after file_close() is called. uip will (at some point) close the connection and return it to Free
};

struct file_t
{
	struct buffer_t *read_buffer;
	struct buffer_t *write_buffer;
	enum file_state_t state;
};


enum file_event_t
{
	Readable = 1,  //file has bytes to read
	Writeable = 2,	//file will accept bytes to write
	ReadOrWriteable = 3,
	Exception = 4,  //file has an error
	ReadableOrException = 5,
	NotWritable = 5,
	WriteableOrException = 6,
	NotReadable = 6,
	All = 7,
	
};


typedef unsigned char file_handle_t;

//invalid file_handle_t value. If file_handle_t is defined as unsigned char, then we can have at most 255 handles. (0->254)
#define FILE_INVALID_HANDLE 255 
#define FILE_HANDLE_MAX 10

//Allocate a file handle, associating it with read_buffer and write_buffer
//Both these buffers must have already been initialised with buffer_init before passing into here
//Returns FILE_INVALID_HANDLE if a file handle cannot be allocated. It's the caller responsibility to 
//free the read and write buffers, if necessary.
file_handle_t file_handle_create( struct buffer_t *read_buffer, struct buffer_t *write_buffer );

struct file_t * file_get_by_handle( file_handle_t handle);

void file_close( file_handle_t handle );


struct file_event_query_t
{
	file_handle_t handle; //output - the handle of the file with the event
	enum file_event_t event; //output - the event(s) on the file
	enum file_event_t event_mask; //a file_event_mask value. Event must match one of these to be reported
	unsigned char last_index; //the last one inspected; state for file_get_next_event()
};

//Pass in a list of handles you care about (handle_list) and it's length
//and a ptr to a file_event struct you're going to keep
//You'll get back in that struct the handle of the file that is operable 
//and what the state is (readable, writable or is in exception)
//If no handles in the list are operable, you get FILE_INVALID_HANDLE for the handle value - 
// you'll probably want to task_yield().
bool file_get_next_event( file_handle_t *handle_list , int file_handle_count, struct file_event_query_t *event );


void file_init();
void file_free( file_handle_t handle );


/*
* file stdio like functions. These will all task_yield() if the 
* buffer they are writing to is full, so don't call from
* anywhere but in a task!
*/
int file_puts(const char*, file_handle_t );
int file_putchar(const char, file_handle_t);
#endif
