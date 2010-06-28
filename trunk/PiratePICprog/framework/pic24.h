#ifndef PIC24_h_
#define PIC24_h_

#include <stdint.h>

#include "common.h"

uint32_t PIC24_EnterICSP(struct picprog_t *);
uint32_t PIC24_ExitICSP(struct picprog_t *);
uint32_t PIC24_ReadID(struct picprog_t *);
uint32_t PIC24_Read(struct picprog_t *, uint32 addr, uint16* Data, int length);
uint32_t PIC24_Write(struct picprog_t *, uint32_t tblptr, uint16* Data, int length);
uint32_t PIC24_Erase(struct picprog_t *);

#endif

