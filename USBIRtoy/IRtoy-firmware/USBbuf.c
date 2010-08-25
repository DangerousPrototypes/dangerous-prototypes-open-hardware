/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
/*
Functions to consolidate all USB read access into a single management system
The Microchip code doesn't seem to like byte reads
*/

#include "globals.h"

static struct _irtoyusbbuffer{
	unsigned char inBuf[30];
	unsigned char cnt;
	unsigned char rdptr;
} usbbuf;

void usbbufservice(void){
	
	if(usbbuf.cnt==0){//if the buffer is empty, get more data
		usbbuf.cnt = getsUSBUSART(usbbuf.inBuf,30);
		usbbuf.rdptr=0;
	}

}

//puts a byte from the buffer in the byte, returns 1 if byte
unsigned char usbbufgetbyte(unsigned char* c){
	if(usbbuf.cnt>0){
		*c=usbbuf.inBuf[usbbuf.rdptr];
		usbbuf.cnt--;
		usbbuf.rdptr++;
		return 1;
	}
	return 0;
}

void usbbufflush(void){
	usbbuf.cnt = 0;
	usbbuf.rdptr=0;
}
