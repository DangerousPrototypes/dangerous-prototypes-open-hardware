/*
This work is licensed under the Creative Commons Attribution 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/
or send a letter to
        Creative Commons,
        171 Second Street,
        Suite 300,
        San Francisco,
        California,
        94105,
        USA.
*/
#ifndef __CDC_H__
#define __CDC_H__

// JTR v0.1a

/* Is the CDC transmitting? */
char BusyCDC( void );
/* Configure the USART. */
void OpenCDC(unsigned char config, unsigned int spbrg);
/* Disable the CDC. */
void CloseCDC( void );
/* Is data available in the CDC read buffer? */
char DataRdyCDC( void );
/* Read a byte from the CDC. */
char getcCDC( void );
/* Read an array from the USBART. */
unsigned char getaCDC( char *buffer, unsigned char len );
/* Read a string from the USART. */
void getsCDC( char *buffer, unsigned char len);
/* Write a byte to the USART. */
void putcCDC( char c );
/* Write a string from data memory to the USART. */
void putsCDC( const char *str );
/* Write an array from data memory to the USBART */
void putaCDC( const char *array, unsigned int len );
/* Write a string from program memory to the USART. */
void putrsCDC( ROM const char *str );
/* Set the baud rate configuration bits for enhanced USART. */
void baudCDC( unsigned char baudconfig );

#endif

