#ifndef PIC12_h_
#define PIC12_h_

#include <stdint.h>
#include "proto_pic.h"
#include "common.h"

uint32_t PIC12_EnterICSP(struct picprog_t *, enum icsp_t);
uint32_t PIC12_ExitICSP(struct picprog_t *, enum icsp_t);
uint32_t PIC12_ReadID(struct picprog_t *, uint16_t *id, uint16_t *rev);
uint32_t PIC12_Read(struct picprog_t *, uint32_t, uint8_t *, uint32_t);
uint32_t PIC12_Write(struct picprog_t *, uint32_t, uint8_t *, uint32_t);
uint32_t PIC12_Erase(struct picprog_t *);

//added as per video instruction  dated Aug 3, 2010
// modified pic12.c as well
int PIC12_WriteFlash(struct picprog_t *, uint8_t *);
int PIC12_ReadFlash(struct picprog_t *, uint8_t *);

#endif


