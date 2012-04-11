#ifndef COMMON_h_
#define COMMON_h_

#include <stdint.h>
#include <stdlib.h>
#include "iface.h"

#ifdef VERSION
#define PICPROG_VER VERSION
#else
#define PICPROG_VER "v0.3"
#endif

struct picprog_t {
	struct iface_t *iface;
	void *iface_data;

	int16_t chip_idx; // this ID is not the silicon ID !!! it is the index in the chip table

	uint8_t debug;
};


uint8_t hexdec(const char* pc);
void *safe_malloc(size_t size);
void dumpHex(uint8_t *buf, uint32_t len);

#endif

