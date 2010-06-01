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
		buffer->write_ptr = buffer->buffer;
		while( buffer->read_ptr < buf_end )
		{
			*(buffer->write_ptr++)=*(buffer->read_ptr++);
		}
	}
	unsigned short written = can_write;
	while( can_write > 0 )
	{
		*(buffer->write_ptr++) = *(local++);
		can_write--;
	}

	return written; //number of bytes written

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


const char* buffer_read_const_ptr( register const struct buffer_t * buffer)
{
	return buffer->buffer;
}
