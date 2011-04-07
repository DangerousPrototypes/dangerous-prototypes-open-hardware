/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
#ifndef USBBUF_H
#define USBBUF_H

void usbbufservice(void);
unsigned char usbbufgetbyte(unsigned char *c);
void usbbufflush(void);


#endif
