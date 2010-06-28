
#include "pic16.h"


uint32_t PIC12_EnterICSP(struct picprog_t *) {
	return 1;
}

uint32_t PIC12_ExitICSP(struct picprog_t *) {
	return 1;
}

uint32_t PIC12_ReadID(struct picprog_t *) {
	return 1;
}

uint32_t PIC12_Read(uint32 tblptr, uint8* Data, int length) {
	return 1;
}

uint32_t PIC12_Write(struct picprog_t *, uint32 tblptr, uint8* Data, int length) {
	return 1;
}

uint32_t PIC12_Erase(struct picprog_t *) {
	return 1;
}

