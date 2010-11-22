/*****************************************************************************
 *  Serial UART and buffer functions
 *****************************************************************************
 * FileName:        serial.h
 * Processor:       dsPIC33
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Eric Walker			20101112	Initial File Creation
 *****************************************************************************/
#ifndef _serial_h
#define _serial_h

/* defines */
#if 1

/* These define and set the size of the serial buffers. *
 * The bound checking code requires a power of two.     *
 *    !!! They must be set to a power of two. !!!       *
 * If these are made larger than 256 then the size of   *
 * the variables used as pointers must also be changed. */
#define RX_BUFF_SZ     8
#define TX_BUFF_SZ     64
/* The receive buffer can be small because the serial   *
 * port is relatively slow compared to the PIC and so   *
 * will get serviced relatively often.  The transmit    *
 * buffer should be big enough to hold a few lines.     *
 * Most functions, and all those using stdio output to  *
 * stdout or stderr such as printf(), will block if the *
 * Tx buffer is full which could affect performance.    */

#endif /* defines */

/* Prototypes */
#if 1

void SetupSerial(void);
int SerialGetChar(char *);
void SerialPutChar(char);
int SerialPutCharNoBlock(char);
void SerialPutString(char *);
int SerialPutStringNoBlock(char *);

#endif /* Prototypes */

#endif /* _serial_h */

/*EOF*/
