#ifndef PIC12_h_
#define PIC12_h_

#include <stdint.h>

#include "common.h"

uint32_t PIC12_EnterICSP(struct picprog_t *);
uint32_t PIC12_ExitICSP(struct picprog_t *);
uint32_t PIC12_ReadID(struct picprog_t *);
uint32_t PIC12_Read(uint32 tblptr, uint8* Data, int length);
uint32_t PIC12_Write(struct picprog_t *, uint32 tblptr, uint8* Data, int length);
uint32_t PIC12_Erase(struct picprog_t *);



#endif


