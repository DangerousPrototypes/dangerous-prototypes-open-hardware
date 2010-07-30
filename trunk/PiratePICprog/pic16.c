
#include "pic16.h"


uint32_t PIC16_EnterICSP(struct picprog_t *p, enum icsp_t icsp_type) {
	return 1;
}

uint32_t PIC16_ExitICSP(struct picprog_t *p, enum icsp_t type) {
	return 1;
}

uint32_t PIC16_ReadID(struct picprog_t *p, uint16_t *id, uint16_t *rev) {
	return 1;
}

uint32_t PIC16_Read(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length) {
	return 1;
}

uint32_t PIC16_Write(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length) {
	return 1;
}

uint32_t PIC16_Erase(struct picprog_t *p) {
	return 1;
}

