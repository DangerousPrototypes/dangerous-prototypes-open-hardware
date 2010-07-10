#ifndef PIC18_h_
#define PIC18_h_

#include <stdint.h>

#include "proto_pic.h"
#include "common.h"

uint32_t PIC18_EnterICSP(struct picprog_t *, enum icsp_t);
uint32_t PIC18_ExitICSP(struct picprog_t *);
uint32_t PIC18_ReadID(struct picprog_t *);
uint32_t PIC18_Read(struct picprog_t *, uint32_t, void *, uint32_t);
uint32_t PIC18_Write(struct picprog_t *, uint32_t, void *, uint32_t);
uint32_t PIC18_Erase(struct picprog_t *);


#endif

