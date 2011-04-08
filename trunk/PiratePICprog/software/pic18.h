#ifndef PIC18_h_
#define PIC18_h_

#include <stdint.h>
#include "proto_pic.h"
#include "common.h"

uint32_t PIC18_EnterICSP(struct picprog_t *, enum icsp_t);
uint32_t PIC18_ExitICSP(struct picprog_t *, enum icsp_t);
uint32_t PIC18_ReadID(struct picprog_t *, uint16_t *id, uint16_t *rev);
uint32_t PIC18_Read(struct picprog_t *, uint32_t, void *, uint32_t);
uint32_t PIC18_Write(struct picprog_t *, uint32_t, void *, uint32_t);
uint32_t PIC18_Erase(struct picprog_t *);

//added as per video instruction  dated Aug 3, 2010
// modified pic18.c as well
uint32_t PIC18_WriteFlash(struct picprog_t *, uint8_t *);
uint32_t PIC18_ReadFlash(struct picprog_t *, uint8_t *);

#endif

