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

//added as per video instruction  dated Aug 3, 2010
// modified pic16.c as well
int PIC16_WriteFlash(struct picprog_t *, uint8_t *);
int PIC16_ReadFlash(struct picprog_t *, uint8_t *);

#endif


