
#include "pic16.h"


uint32_t PIC16_EnterICSP(struct picprog_t *) {
	return 1;
}

uint32_t PIC16_ExitICSP(struct picprog_t *) {
	return 1;
}

uint32_t PIC16_ReadID(struct picprog_t *) {
	return 1;
}

uint32_t PIC16_Read(uint32 tblptr, uint8* Data, int length) {
	return 1;
}

uint32_t PIC16_Write(struct picprog_t *, uint32 tblptr, uint8* Data, int length) {
	return 1;
}

uint32_t PIC16_Erase(struct picprog_t *) {
	return 1;
}

