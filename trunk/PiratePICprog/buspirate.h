#ifndef BUSPIRATE_h_
#define BUSPIRATE_h_

#include <stdint.h>
#include "common.h"

enum BP_picmode_t {
	BP_PICUNK=0,
	BP_PIC416,
	BP_PIC424,
	BP_PIC614
};

struct BP_t {
	int fd;
	enum BP_picmode_t picmode;
	char buf[4096];
	int bufcnt;
};

uint32_t BP_Init(struct picprog_t *, char *port, char *speed);
uint32_t BP_Deinit(struct picprog_t *);
uint32_t BP_SetBitOrder(struct BP_t *, uint8_t);
uint32_t BP_BulkByteWrite(struct BP_t *, uint8_t, char *);
uint32_t BP_BulkBitWrite(struct BP_t *, uint8_t, char);
uint32_t BP_DataLow(struct BP_t *);
uint32_t BP_DataHigh(struct BP_t *);
uint32_t BP_ClockLow(struct BP_t *);
uint32_t BP_ClockHigh(struct BP_t *);
uint32_t BP_MCLRLow(struct BP_t *);
uint32_t BP_MCLRHigh(struct BP_t *);
uint32_t BP_PIC416Write(struct BP_t *, uint8_t cmd, uint16_t data);
uint32_t BP_PIC416Read(struct BP_t *pBP, uint8_t cmd, void *Data, uint32_t length);
uint32_t BP_PIC424Read(struct BP_t *, uint32_t cmd, void *Data, uint32_t length);
uint32_t BP_PIC424Write(struct BP_t *, uint32_t , uint8_t, uint8_t);
uint32_t BP_Flush(struct BP_t *pBP);
uint32_t BP_VPPHigh(struct BP_t *pBP);
uint32_t BP_VPPLow(struct BP_t *pBP);

#endif

