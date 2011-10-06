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

extern struct iface_t buspirate_iface;

//uint32_t BP_Init(struct picprog_t *, char *port, char *speed);
//uint32_t BP_Deinit(struct picprog_t *);
//uint32_t BP_SetBitOrder(uint8_t);
//uint32_t BP_BulkByteWrite(uint8_t, char *);
//uint32_t BP_BulkBitWrite(uint8_t, char);
//uint32_t BP_DataLow();
//uint32_t BP_DataHigh();
//uint32_t BP_ClockLow();
//uint32_t BP_ClockHigh();
//uint32_t BP_MCLRLow();
//uint32_t BP_MCLRHigh();
//uint32_t BP_PIC416Write(uint8_t cmd, uint16_t data);
//uint32_t BP_PIC416Read(uint8_t cmd, void *Data, uint32_t length);
//uint32_t BP_PIC424Read(uint32_t cmd, void *Data, uint32_t length);
//uint32_t BP_PIC424Write(uint32_t , uint8_t, uint8_t);
//uint32_t BP_Flush();
//uint32_t BP_VPPHigh();
//uint32_t BP_VPPLow();

#endif

