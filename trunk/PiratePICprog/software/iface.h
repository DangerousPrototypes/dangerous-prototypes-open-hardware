#ifndef IFACE_h_
#define IFACE_h_

#include <stdint.h>

struct picprog_t;

enum bitorder_t {
	BIT_MSB,
	BIT_LSB
};

struct iface_t {
	char *name;

	uint32_t (*Init)(struct picprog_t *, char *, char *);
	uint32_t (*Deinit)(struct picprog_t *);
	uint32_t (*DataLow)();
	uint32_t (*DataHigh)();

	uint32_t (*ClockLow)();
	uint32_t (*ClockHigh)();

	uint32_t (*MCLRLow)();
	uint32_t (*MCLRHigh)();

	uint32_t (*SetBitOrder)(uint8_t);
	uint32_t (*SendBytes)(uint8_t, char *);
	uint32_t (*SendBits)(uint8_t, char);

	uint32_t (*PIC614Read)(uint8_t, void *, uint32_t);
	uint32_t (*PIC614Write)(uint8_t, uint16_t);

	uint32_t (*PIC416Read)(uint8_t, void *, uint32_t);
	uint32_t (*PIC416Write)(uint8_t, uint16_t);

	uint32_t (*PIC424Read)(uint32_t, void *, uint32_t);
	uint32_t (*PIC424Write)(uint32_t, uint8_t, uint8_t);

	uint32_t (*GetData)(uint8_t *, uint32_t);

	uint32_t (*flush)();

	uint32_t (*VPPHigh)();
	uint32_t (*VPPLow)();

	uint32_t (*VCCHigh)();
	uint32_t (*VCCLow)();

};


struct iface_t *Iface_GetByName(char *name);

#endif

