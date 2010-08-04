#ifndef PIC24_h_
#define PIC24_h_

#include <stdint.h>
#include "proto_pic.h"
#include "common.h"

uint32_t PIC24_EnterICSP(struct picprog_t *, enum icsp_t);
uint32_t PIC24_ExitICSP(struct picprog_t *, enum icsp_t);
uint32_t PIC24_ReadID(struct picprog_t *, uint16_t *id, uint16_t *rev);
uint32_t PIC24_Read(struct picprog_t *, uint32_t, void *, uint32_t);
uint32_t PIC24_Write(struct picprog_t *, uint32_t, void *, uint32_t);
uint32_t PIC24_Erase(struct picprog_t *);

//added as per video instruction  dated Aug 3, 2010
// modified pic24.c as well
uint32_t PIC24_WriteFlash(struct picprog_t *, uint8_t *);
uint32_t PIC24_ReadFlash(struct picprog_t *, uint8_t *);

#endif

