/*****************************************************************************
 *  Serial UART and buffer functions
 *****************************************************************************
 * FileName:        serial.c
 * Processor:       dsPIC33
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Eric Walker			20101112	Initial File Creation
 *****************************************************************************/

/* includes */
#if 1

#include "../proc.h"
#include "serial.h" 
#include "serialconfig.h" 
#include "../console.h" 

#endif /* includes */

/* file scope */
#if 1

/* Serial bufferes betwen ISR and application code */
static volatile char rxbuff[RX_BUFF_SZ];
static volatile char txbuff[TX_BUFF_SZ];

static volatile unsigned char  rxptrISR = 0;
static volatile unsigned char  txptrISR = 0;

static unsigned char  rxptrApp = 0;
static unsigned char  txptrApp = 0;

#endif /* file scope */


/*********************************************************************
* Function Name     : SetupUART                                      *
* Description       : This function first disables the UART and      *
*                     clears the Interrupt flag and enable bits to   *
*                     ensure there are no UART interrupts durring    *
*                     configuration.  Then the UART mode, UART       *
*                     Interrupt modes and the Baud Rate are set.     *
* Arguments         : None                                           *
* Return Value      : None                                           *
*********************************************************************/
void SetupSerial(void)
{

/* Configure UART 1 */
#if UART_NUMBER == 1

	/* Reset UART */
	U1MODE = 0;

	/* Disable interupts */
    IEC0bits.U1TXIE = 0;
    IEC0bits.U1RXIE = 0;

	/* Clear interupts */
    IFS0bits.U1TXIF = 0;
    IFS0bits.U1RXIF = 0;

	/* Configure UART */
    U1BRG	= UART_BRG;
    U1MODE	= UART_MODE;
    U1STA	= UART_STATUS;

    /* Configure interupt priorities */
    IPC3bits.U1TXIP = UART_TX_INT_PR;
    IPC2bits.U1RXIP = UART_RX_INT_PR;

    /* Conditionally enable interupts */
    IEC0bits.U1RXIE = UART_RX_INT_EN;
    IEC0bits.U1TXIE = UART_TX_INT_EN;

#endif /**/

/* Configure UART 2 */
#if UART_NUMBER == 2
#endif /**/

	/*********************************************
	* It has been determined that it is best to 
	* not enable the UART Tx and potenially back
	* feed the FTDI USB to serial chip if there
	* is no USB connection.  The following code
	* checks to see if the Rx line is high which
	* would indicate an attached USB connection 
	* in an idle state and so it is ok to enable
	* the transmitter.  For now this check is 
	* only done once durring boot.  Eventually
	* this will hopefully be a dynamic change.
	*********************************************/

	/* First, ensure RB14 is a digital input    
	 * because it won't be after a reset.       */
	AD1PCFGL |= 0x0400;

	/* Per the data sheet: One instruction 
	 * cycle is required between a port 
	 * direction change and a read operation
	 * of the same port.                        */
	asm("NOP");

	if(PORTBbits.RB14){
		U1STAbits.UTXEN = 1;
	}	
}/* SetupSerial() */

/*********************************************************************
* Function Name     : SerialGetChar                                  *
* Description       : This function returns the next character in    *
*                     the circular receive buffer, if there are any  *
*                     new characters.  If there are none available   *
*                     the functions returns zero and does not block. *
* Arguments         : pointer to char to store character             *
* Return Value      : zero    - No new data.                         *
*                   : nonzero - New data available.                  *
*********************************************************************/
int SerialGetChar(char * data)
{

	if (rxptrApp == rxptrISR){
		/* If these pointers are equal then    *
		 * there is no new data in the buffer. */
		return 0;
	}

	*data = rxbuff[rxptrApp];

	/* this should give an atomic write to rxptrApp */
	rxptrApp = ( rxptrApp + 1 ) & (RX_BUFF_SZ - 1);
    
    return 1;
} /* SerialGetChar() */

/*********************************************************************
* Function Name     : SerialPutCharNoBlock                           *
* Description       : This function puts the character in to the     *
*                     circular transmit buffer if there is space.    *
*                     If there is no space available the function    *
*                     returns zero and does not block.               *
* Arguments         : char to send                                   *
* Return Value      : zero    - No buffer space available.           *
*                   : nonzero - Character added to transmit buffer.  *
*********************************************************************/
int SerialPutCharNoBlock(char data)
{
	unsigned char ptr;
	unsigned char sta = 0;

	/* Check if room in the buffer */
	ptr = txptrApp;
	ptr = (ptr + 1) & (TX_BUFF_SZ - 1); 

	/* If room then add char */
	if (ptr != txptrISR){
		txbuff[txptrApp] = data;
        txptrApp = ptr;

		/* Check if HW buffer is full. */
		if (!U1STAbits.UTXBF){
			/* If not force an interupt because  *
			 * the HW buffer could be completely *
			 * empty and the interupt flag might *
			 * also be cleard.                   */
			IFS0bits.U1TXIF = 1;
		}	

		/* Ensure UART Tx interupt is enabled */
		IEC0bits.U1TXIE = 1;
				
		sta = 1;
	} 
    return sta;
} /* SerialPutCharNoBlock() */

/*********************************************************************
* Function Name     : SerialPutChar                                  *
* Description       : This function puts the character in to the     *
*                     circular transmit buffer.  This function will  *
*                     block until there is space.                    *
* Arguments         : char to send                                   *
* Return Value      : None                                           *
*********************************************************************/
void SerialPutChar(char data)
{
	while(!SerialPutCharNoBlock(data))
		;
} /* SerialPutChar() */

/*********************************************************************
* Function Name     : SerialPutStringNoBlock                         *
* Description       : This function puts a null terminated character *
*                     string in to the circular transmit buffer.  As *
                      much of the string as will fit will be copied. *
*                     If there is not enough space available the     *
*                     function returns zero and does not block.      *
* Arguments         : pointer to char (null terminated) string       *
* Return Value      : zero    - Not enough buffer space available.   *
*                   : nonzero - All Characters added to buffer.      *
*********************************************************************/
int SerialPutStringNoBlock(char * data)
{
	unsigned char sta;

	while(*data++)
		sta = SerialPutCharNoBlock(*data);

	return sta;
} /* SerialPutStringNoBlock() */

/*********************************************************************
* Function Name     : SerialPutString                                *
* Description       : This function puts a null terminated           *
*                     character string in to the circular transmit   *
*                     buffer.  This function will block until the    *
*                     whole string has been copied to the buffer.    *
* Arguments         : pointer to char (null terminated) string       *
* Return Value      : None                                           *
*********************************************************************/
void SerialPutString(char * data)
{
	while(*data)
		SerialPutChar(*data++);

} /* SerialPutString() */

/* UART 1 Interups */
#if UART_NUMBER == 1
/*********************************************************************
* Function Name     : _U1RXInterrupt                                 *
* Description       : This function is the interupt handler for      *
*                     UART 1 receive interupts.  It reads the        *
*                     hardware recieve buffer and copies the         *
*                     character to a circular receive buffer if      *
*                     there is room.                                 *
* Arguments         : None                                           *
* Return Value      : None                                           *
*********************************************************************/
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
	char data;
	unsigned char ptr;
  
	while( U1STAbits.URXDA ){
		data = U1RXREG;
		ptr = (rxptrISR + 1) & (RX_BUFF_SZ - 1);
		if (ptr != rxptrApp){
			rxbuff[rxptrISR] = data;
			rxptrISR = ptr;
		} else {
			/* TODO: add error handling for full buffer */
		}
	}
	
	IFS0bits.U1RXIF = 0;
	
	ResumeConsoleTaskFromISR();
} /* _U1RXInterrupt() */

/*********************************************************************
* Function Name     : _U1TXInterrupt                                 *
* Description       : This function is the interupt handler for      *
*                     UART 1 transmit interupts.  It reads the       *
*                     circular transmit buffer and copies characters *
*                     to the hardware transmit buffer till it is     *
*                     full then returns.  Once the circular buffer   *
*                     is completely empty the transmit interupt will *
*                     be dissabled.                                  *
* Arguments         : None                                           *
* Return Value      : None                                           *
*********************************************************************/
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{
	char data;
	unsigned char ptr;

	ptr = txptrISR;

	do {
		data = txbuff[ptr];
		U1TXREG = data;
		ptr = (ptr + 1) & (TX_BUFF_SZ - 1);
	} while ((txptrApp != ptr) && !U1STAbits.UTXBF);
	
	txptrISR = ptr;
	
	/* If last char sent disable interupts */
	if (txptrISR == txptrApp){
		IEC0bits.U1TXIE = 0;
	}
	
	IFS0bits.U1TXIF = 0;
} /* _U1TXInterrupt */
#endif /* UART 1 Interups */

/* UART 2 Interups */
#if UART_NUMBER == 2
#endif /* UART 2 Interups */

/*EOF*/
