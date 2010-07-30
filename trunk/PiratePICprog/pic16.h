#ifndef PIC16_h_
#define PIC16_h_

#include <stdint.h>
#include "proto_pic.h"

#include "common.h"

uint32_t PIC16_EnterICSP(struct picprog_t *, enum icsp_t);
uint32_t PIC16_ExitICSP(struct picprog_t *, enum icsp_t);
uint32_t PIC16_ReadID(struct picprog_t *, uint16_t *id, uint16_t *rev);
uint32_t PIC16_Read(struct picprog_t *, uint32_t, void *, uint32_t);
uint32_t PIC16_Write(struct picprog_t *, uint32_t, void *, uint32_t);
uint32_t PIC16_Erase(struct picprog_t *);



#endif


