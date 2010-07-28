#ifndef BUSPIRATE_h_
#define BUSPIRATE_h_

#include <stdint.h>

enum BP_picmode_t {
	BP_PICUNK=0,
	BP_PIC416,
	BP_PIC424,
	BP_PIC614
};

struct BP_t {
	int fd;
	enum BP_picmode_t picmode;
};

uint32_t BP_Init(void *, char *port, char *speed);
uint32_t BP_SetBitOrder(void *, uint8_t);
uint32_t BP_BulkByteWrite(void *, uint8_t, uint8_t *);
uint32_t BP_BulkBitWrite(void *, uint8_t, uint8_t);
uint32_t BP_DataLow(void *);
uint32_t BP_DataHigh(void *);
uint32_t BP_ClockLow(void *);
uint32_t BP_ClockHigh(void *);
uint32_t BP_MCLRLow(void *);
uint32_t BP_MCLRHigh(void *);
uint32_t BP_PIC416Write(void *, uint8_t cmd, uint16_t data);
uint32_t BP_PIC416Read(void *pBP, uint8_t cmd, void *Data, uint32_t length);
uint32_t BP_PIC424Read(void *);
uint32_t BP_PIC424Write(void *, uint32_t , uint8_t, uint8_t);
uint32_t BP_Flush(void *pBP);

#endif

