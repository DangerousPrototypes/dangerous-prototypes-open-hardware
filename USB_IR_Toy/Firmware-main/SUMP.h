/*
*
*	USB infrared remote control receiver transmitter firmware v1.0
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
#ifndef SUMP_H
#define SUMP_H

unsigned char irSUMPservice(void); //pass this command SUMP

#define SUMP_SAMPLE_PKT_CNT 0x40  //( * 64 byte packets)

#endif
