#ifndef COMMON_h_
#define COMMON_h_

#include <stdint.h>

struct picprog_t {
	struct iface_t *iface;
	void *iface_data;

	uint16_t chip_idx; // this ID is not the silicon ID !!! it is the index in the chip table

	uint8_t debug;
};


uint8_t hexdec(const char* pc);
void dumpHex(uint8_t *buf, uint32_t len);

#endif

