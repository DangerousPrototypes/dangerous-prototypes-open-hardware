#ifndef PROTO_PIC_h_
#define PROTO_PIC_h_

#include <stdint.h>

#include "common.h"

enum icsp_t {
	ICSP_LVPP,
	ICSP_HVPP
};

enum proto_t {
	PROTO_PIC12,
	PROTO_PIC16,
	PROTO_PIC18,
	PROTO_PIC24,
	PROTO_LAST
};

struct proto_ops_t {
	enum proto_t type;
	uint32_t (*EnterICSP)(struct picprog_t *, enum icsp_t);
	uint32_t (*ExitICSP)(struct picprog_t *, enum icsp_t);
	uint32_t (*ReadID)(struct picprog_t*, uint16_t *id, uint16_t *rev);
	uint32_t (*Read)(struct picprog_t *, uint32_t addr, void *buf, uint32_t len);
	uint32_t (*Write)(struct picprog_t *, uint32_t addr, void *buf, uint32_t len);
	uint32_t (*Erase)(struct picprog_t *);
	uint32_t (*WriteFlash)(struct picprog_t *, uint8_t *);
	uint32_t (*ReadFlash) (struct picprog_t *, uint8_t *);
};

struct proto_ops_t *Proto_GetOps(enum proto_t protocol);

#endif
