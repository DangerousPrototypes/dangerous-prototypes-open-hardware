/*
* Implementations of the stdlib functions required
* for using stdlib with the Dangerous Prototypes Web Server Platform
*/

#include "HardwareProfile.h"
/*
_mon_putc - required for puts(), printf() and friends
Outputs to UART1 ( USB Serial port )
NOTE: Nothing is output until the sync char "U" is received on UART1
for the auto-baud rate detection.
*/
void _mon_putc(char c){
	if( U1MODEbits.ABAUD == 1) return; //still waiting for auto baud. Don't transmit
	U1STAbits.UTXEN = 1; //enable UART TX
	while(U1STAbits.UTXBF == 1); //if buffer is full, wait
    U1TXREG = c;
}


int __attribute__((__section__(".libc"))) read(int handle, void *buffer, unsigned int len){
	
 	if( U1STAbits.OERR ) U1STAbits.OERR = 0; //clear any overrun
	int readCount = 0;
	char* p = (char*) buffer;
	for( ; readCount < len ; readCount ++ )
	{	
		if( U1STAbits.URXDA == 0) break;
		*p = U1RXREG;
		p++;
	}
	return readCount;
}

/*
_mon_getc - required for getchar() , gets() etc
Reads from UART1 (USB Serial port )
*/
int _mon_getc(){
	char buf;
	int count = read(1,(void*)&buf,1);
	if(count == 0) return -1;
	return (int)buf;
}



