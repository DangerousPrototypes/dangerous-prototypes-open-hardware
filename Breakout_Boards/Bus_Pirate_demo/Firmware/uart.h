/* header */

#define BRGVAL          25      // should be 9600 baud@4mhz (BRGH=1)
#define RINGBUFFSIZE    8       // ringbuffer size (should be power of 2!)
#define RINGBUFFMASK    (RINGBUFFSIZE-1)


// forward declarations
void initUART(void);
void UARTworker(void);
void UARTwrite(unsigned char c);
unsigned char UARTread(void);

extern unsigned ringbuff[RINGBUFFSIZE];
extern volatile char rhead, rtail;

// spi interrupt service routine
#define UARTisr	do {				\
	if(RCIF)						\
	{	LED2ON;						\
		if(!(RCSTA&0b00000110))		\
		{	rhead++;				\
			rhead&=RINGBUFFMASK;	\
			ringbuff[rhead]=RCREG;	\
		}							\
		RCIF=0;						\
		LED2OFF;					\
	}								\
	if(TXIF)						\
	{	TXIF=0;						\
	}								\
} while(0);

