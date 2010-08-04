
#include "pic12.h"


uint32_t PIC12_EnterICSP(struct picprog_t *p, enum icsp_t icsp_type) {
	return 1;
}

uint32_t PIC12_ExitICSP(struct picprog_t *p, enum icsp_t type) {
	return 1;
}

uint32_t PIC12_ReadID(struct picprog_t *p, uint16_t *id, uint16_t *rev) {
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

//added as per video instruction  dated Aug 3, 2010
// modified pic12.h as well

int PIC12_WriteFlash(struct picprog_t *p, uint8_t *fw_data) {
return 1;
}

int PIC12_ReadFlash(struct picprog_t *p, uint8_t *fw_data) {
    return 1;
}
