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
	uint8_t per; // peripheral
	int bufcnt;
};

extern struct iface_t buspirate_iface;

#endif

