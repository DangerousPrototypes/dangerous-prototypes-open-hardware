#include "buffer.h"

unsigned short buffer_peek( register struct buffer_t * buffer, char * local, const unsigned short count)
{
	unsigned short available = buffer_available( buffer );
	unsigned short can_read = count < available ? count : available ;

	char * last = buffer->read_ptr + can_read;
	char * ptr = buffer->read_ptr;

	while( ptr != last )
	{
		*(local++) = *(ptr++);
	}
	
	return can_read; //number of bytes read

}

void buffer_seek( register struct buffer_t * buffer, const unsigned short count){
	unsigned short available = buffer_available( buffer );
	unsigned short can_seek = count < available ? count : available ;
	
	buffer->read_ptr += can_seek;
	
	//whenever the read and write ptrs are equal, pounsigned short them all back to the start
	if(buffer->read_ptr == buffer->write_ptr )
	{
		buffer->read_ptr = buffer->write_ptr = buffer->buffer;	
	}
}


unsigned short buffer_read( register struct buffer_t * buffer, register char * local, const unsigned short count)
{
	//read_ptr moves by number of bytes read
	unsigned short did_read = buffer_peek( buffer, local, count );
	buffer->read_ptr += did_read;
	
	//whenever the read and write ptrs are equal, pounsigned short them all back to the start
	if(buffer->read_ptr == buffer->write_ptr )
	{
		buffer->read_ptr = buffer->write_ptr = buffer->buffer;	
	}

	return did_read; //number of bytes read
}

unsigned short buffer_write( register struct buffer_t * buffer, register const char * local, const unsigned short count )
{
	//write_ptr moves by number of bytes read
	unsigned short free = buffer_free( buffer );
	unsigned short can_write = count < free ? count : free ;
	char * buf_end = buffer->buffer + buffer->size;
	if( buffer->write_ptr + can_write > buf_end )
	{
		//will overflow. move existing data to start of buffer
		unsigned short need_move = buffer_available( buffer );
		buffer->write_ptr = buffer->buffer;
		while( need_move > 0 )
		{
			*(buffer->write_ptr++)=*(buffer->read_ptr++);
			need_move --;
		}
		//read ptr is now at the start of the buffer
		buffer->read_ptr  = buffer->buffer;
	}
	unsigned short written = can_write;
	while( can_write > 0 )
	{
		*(buffer->write_ptr++) = *(local++);
		can_write--;
	}

	return written; //number of bytes written

}

// RaaxxPbbbW --> RaaPbbbW  when count < 0 (remove X prior items)
// RaaaaPxxbW --> RaaaaPbW  when count > 0 (remove next X items)
void buffer_unwrite( register struct buffer_t * buffer, char* ptr, signed short count )
{
	if(count == 0 ) return; //nothing to do
	if( ptr < buffer->read_ptr  ) return;
	if( ptr > buffer->write_ptr ) return;
	
	char* ptr2 = ptr + count;
	if( ptr2 >= buffer->write_ptr )
	{
		//the best case scenario
		//The bytes between ptr and write_ptr are to be deleted.
		//just move write_ptr back to ptr
		buffer->write_ptr = ptr; //all done!
		return;
	}
	if( ptr2 < buffer->read_ptr  ) ptr2 = buffer->read_ptr;
	
	//all other cases require moving data in the buffer :(
	if( count < 0 )
	{
		buffer->write_ptr += count; //move left X positions (count is negative)
		while( ptr2 != buffer->write_ptr )
		{
			*ptr2++ = *ptr++; //ptr is to the right of ptr2
		}
	}
	else
	{
		buffer->write_ptr -= count; //move left X positions (count is positive)
		while( ptr != buffer->write_ptr )
		{
			*ptr++ = *ptr2++; //ptr2 is to the right of ptr
		}
	}
}


//number of bytes available to read
unsigned short __attribute__((always_inline)) buffer_available( register const struct buffer_t * buffer)  
{
	return buffer->write_ptr - buffer->read_ptr;
}

//number of bytes we can write
unsigned short __attribute__((always_inline)) buffer_free( register const struct buffer_t * buffer) 
{
	return buffer->size - ( buffer->write_ptr - buffer->read_ptr );
}


void buffer_init( register struct buffer_t *buffer, register char * data, const unsigned short size )
{
	buffer->buffer = data;
	buffer->read_ptr = data;
	buffer->write_ptr = data;
	buffer->size = size;
}


char* __attribute__((always_inline)) buffer_read_ptr( register const struct buffer_t * buffer)
{
	return buffer->read_ptr;
}
