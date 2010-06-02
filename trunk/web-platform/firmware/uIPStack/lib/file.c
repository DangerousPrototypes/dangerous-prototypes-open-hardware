#include "file.h"                                                                     
#include <stdio.h>
#include "multitasker.h"

struct file_t file_handles[ FILE_HANDLE_MAX ];

void file_debug()
{
	unsigned char i = 0;
	printf("\nid\tstate\tavail\tfree\n");
	for( ; i < FILE_HANDLE_MAX ; i++ )
	{
		struct file_t * file = &file_handles[i];
		int av = 0;
		int free = 0;
		if( file->read_buffer != NULL ) av = buffer_available( file->read_buffer );
		if( file->write_buffer != NULL ) free = buffer_free( file->write_buffer );

		printf("\n%03hhd\t  %02hhx \t%5d\%5d",i,file->state,av,free);
	}
	puts("\n");
}

void file_init()
{
	int i = 0;
	for( ; i < FILE_HANDLE_MAX ; i++ )
	{
		file_handles[i].state = Free;
	}

}

//
//Allocate a file handle, associating it with read_buffer and write_buffer
//Both these buffers must have already been initialised with buffer_init before passing into here
//Returns FILE_INVALID_HANDLE if a file handle cannot be allocated. It's the caller responsibility to 
//free the read and write buffers, if necessary.
file_handle_t file_handle_create( struct buffer_t *read_buffer, struct buffer_t *write_buffer)
{
	file_handle_t i = 0;
	for( ; i < FILE_HANDLE_MAX ; i++ )
	{
		if( Free == file_handles[i].state ) goto handle_found;
	}
	return FILE_INVALID_HANDLE;
handle_found:
	file_handles[i].state = NotFree;
	file_handles[i].read_buffer = read_buffer;
	file_handles[i].write_buffer = write_buffer;
	return i;
}


struct file_t * file_get_by_handle( file_handle_t handle)
{
	if( handle >= FILE_INVALID_HANDLE ) return NULL;
	return &file_handles[handle];
}
void file_close( file_handle_t handle )
{
	struct file_t * file = &file_handles[handle];
	//file->read_buffer=NULL;
	//file->write_buffer=NULL;
	file->state=ClosePending;
}

void file_free( file_handle_t handle )
{
	struct file_t * file = &file_handles[handle];
	file->read_buffer=NULL;
	file->write_buffer=NULL;
	file->state=Free;
}


//Pass in a list of handles you care about (handle_list) and it's length
//and a ptr to a file_event struct you're going to keep
//You'll get back in that struct the handle of the file that is operable 
//and what the state is (readable, writable or is in exception)
//If no handles in the list are operable, you get FILE_INVALID_HANDLE for the handle value - 
// you'll probably want to task_yield().
bool file_get_next_event( file_handle_t *handle_list , int file_handle_count, struct file_event_query_t *event )
{
//	assert( file_handle_count >= 1 );
	unsigned char start = event->last_index;
	//ensure start is within bounds of array
	start = ++start >= file_handle_count ? 0 : start;
	event->last_index = start;

	//do one loop through to find a file of interest
	event->handle = FILE_INVALID_HANDLE;
	int i = start;
	do{
		file_handle_t handle = handle_list[i];
		if( handle != FILE_INVALID_HANDLE )
		{
			struct file_t *f = &file_handles[handle];
			register unsigned char evt = 0;
			register unsigned char mask = event->event_mask;
			//check for readable
			if( mask & Readable)
			{
				evt |= buffer_available( f->read_buffer ) > 0 ? Readable : 0;
			}
			//check for writeable
			if( mask & Writeable)
			{
				evt |= buffer_free( f->write_buffer ) > 0 ? Writeable : 0;
			}
			//check for errors
			if( mask & Exception)
			{
				evt |= ( f->state > Open && f->state < ClosePending)  ? Exception : 0;
			}
			//do the events match the mask?
			if( evt & mask )
			{
				event->handle = handle;
				event->event = evt;
				return true;
			}
		}
		//check next file
		i = ++i >= file_handle_count ? 0 : i;
	}while( i!=start );

	return false;
}


//only call this function from a TASK (it will yield if the buffer is full)
int file_puts(const char* string, file_handle_t handle)
{
	struct file_t* f = file_get_by_handle(handle);
	if( f == NULL || f->write_buffer == NULL ) return EOF;
	struct buffer_t* w =  f->write_buffer;
	const char* t = string;
	while( *t != 0 )
	{
		int free = buffer_free( w );
		if( free == 0 ) task_yield();
		else
		{
			while( free > 0 && *t != 0 ) 
			{
				buffer_write( w, t, 1 );
				t++;
				free--;
			}
		}	 
	}
	return 1;
}

int file_putchar(const char c, file_handle_t handle){
	struct file_t* f = file_get_by_handle(handle);
	if( f == NULL || f->write_buffer == NULL ) return EOF;
	struct buffer_t* w =  f->write_buffer;
	while( buffer_write( w, &c , 1 ) != 1 ) task_yield();
	return 1;
}


