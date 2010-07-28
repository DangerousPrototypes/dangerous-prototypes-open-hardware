#ifndef IFACE_h_
#define IFACE_h_

#include <stdint.h>

enum bitorder_t {
	BIT_MSB,
	BIT_LSB
};

struct iface_t {
	char *name;

	uint32_t (*Init)(void *, char *, char *);
	uint32_t (*DataLow)(void *);
	uint32_t (*DataHigh)(void *);

	uint32_t (*ClockLow)(void *);
	uint32_t (*ClockHigh)(void *);

	uint32_t (*MCLRLow)(void *);
	uint32_t (*MCLRHigh)(void *);

	uint32_t (*SetBitOrder)(void *, uint8_t);
	uint32_t (*SendBytes)(void *, uint8_t, uint8_t *);
	uint32_t (*SendBits)(void *, uint8_t, uint8_t);

	uint32_t (*PIC614Read)(void *, uint8_t);
	uint32_t (*PIC614Write)(void *, uint8_t, uint16_t);

	uint32_t (*PIC416Read)(void *, uint8_t, void *, uint32_t);
	uint32_t (*PIC416Write)(void *, uint8_t, uint16_t);

	uint32_t (*PIC424Read)(void *);
	uint32_t (*PIC424Write)(void *, uint32_t, uint8_t, uint8_t);

	uint32_t (*flush)(void *pBP);

};


struct iface_t *Iface_GetByName(char *name);

#endif

