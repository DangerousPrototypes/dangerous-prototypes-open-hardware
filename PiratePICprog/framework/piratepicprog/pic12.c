
#include "pic12.h"


uint32_t PIC12_EnterICSP(struct picprog_t *p, enum icsp_t icsp_type) {
	return 1;
}

uint32_t PIC12_ExitICSP(struct picprog_t *p) {
	return 1;
}

uint32_t PIC12_ReadID(struct picprog_t *p) {
	return 1;
}

uint32_t PIC12_Read(struct picprog_t *p, uint32_t tblptr, uint8_t *Data, uint32_t length) {
	return 1;
}

uint32_t PIC12_Write(struct picprog_t *p, uint32_t tblptr, uint8_t* Data, uint32_t length) {
	return 1;
}

uint32_t PIC12_Erase(struct picprog_t *p) {
	return 1;
}

