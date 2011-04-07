/*****************************************************************************
 * C Standard Library write() function Replacement
 *****************************************************************************
 * FileName:        write.c
 * Processor:       dsPIC33
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Eric Walker			20101112	Initial File Creation
 *****************************************************************************/

#include "serial.h"

int __attribute__((__weak__, __section__(".libc")))
write(int handle, void *buffer, unsigned int len) 
{
//	int i;

	switch (handle){
		case 0:
		case 1:
		case 2:
//			for (i = len; i; --i){
//				while (!SerialPutCharNoBlock(*(char*)buffer++))
//					;
//			}
		/* Using unbuffered stdio so only ever get one byte */
			if(*(char*)buffer == '\n')	/* do \n to CRLF conversion */
				while(!SerialPutCharNoBlock('\r'))
					;
			while(!SerialPutCharNoBlock(*(char*)buffer))
				;
			break;
		default:
			break; 
	}
	return(len);
}/**/

/*EOF*/
