#if !defined _BUFFER_H_
#define _BUFFER_H_

struct buffer_t
{
	char *buffer;
	unsigned short size;		//size of buffer
	char *read_ptr; //points at next byte to read
	char *write_ptr;//points at next byte to write; initially, both this and read_ptr point at buffer
};

//initialise a [buffer] to use [data] as the storage of [size] bytes
void buffer_init( struct buffer_t *buffer, char * data, unsigned short size );


//return number of bytes we may read from [buffer] right now
unsigned short buffer_available( const struct buffer_t * buffer);

//Read data of [count] bytes from [buffer] into [local]
//returns number of bytes written. May be lower than [count] if [buffer] is emptyish
unsigned short buffer_read( struct buffer_t * buffer, char * local, unsigned short count);

//read, but don't advance read pointer or free/available counts
unsigned short buffer_peek( struct buffer_t * buffer, char * local, unsigned short count);

//seek the read buffer forward by count bytes (as if a read had occurred )
void buffer_seek( struct buffer_t * buffer, unsigned short count);

//get a pointer to the data that we could read from this buffer
//The pointer is only valid for the next [buffer_available()] bytes
char* buffer_read_ptr( const struct buffer_t * buffer);

//return the number of bytes we may write to [buffer] right now
unsigned short buffer_free( const struct buffer_t * buffer);

//Write data of [count] bytes from [local] into [buffer]
//returns number of bytes written. May be lower than [count] if [buffer] is full
unsigned short buffer_write( struct buffer_t * buffer, const char * local, unsigned short count );


#endif


