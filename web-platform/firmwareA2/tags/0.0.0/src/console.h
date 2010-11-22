/*****************************************************************************
 *  Console interface task
 *****************************************************************************
 * FileName:        console.h
 * Processor:       dsPIC33
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Eric Walker			20101113	Initial File Creation
 *****************************************************************************/

#define CMDBUFLEN	256
#define CMDLENMSK	(CMDBUFLEN-1)

/* Prototypes */
#if 1

int CreateConsoleTask( void );
void ResumeConsoleTaskFromISR( void );

#endif /* Prototypes */


/*EOF*/
