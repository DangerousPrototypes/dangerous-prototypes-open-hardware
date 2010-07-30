#ifndef PIC12_h_
#define PIC12_h_

#include <stdint.h>

#include "proto_pic.h"
#include "common.h"

uint32_t PIC12_EnterICSP(struct picprog_t *, enum icsp_t);
uint32_t PIC12_ExitICSP(struct picprog_t *,enum icsp_t );
uint32_t PIC12_ReadID(struct picprog_t *, uint16_t *id, uint16_t *rev);
uint32_t PIC12_Read(struct picprog_t *, uint32_t, uint8_t *, uint32_t);
uint32_t PIC12_Write(struct picprog_t *, uint32_t, uint8_t *, uint32_t);
uint32_t PIC12_Erase(struct picprog_t *);



#endif


