
#include "pic12.h"


static uint32_t PIC12_EnterICSP(struct picprog_t *p, enum icsp_t icsp_type)
{
	return 1;
}

static uint32_t PIC12_ExitICSP(struct picprog_t *p, enum icsp_t type)
{
	return 1;
}

static uint32_t PIC12_ReadID(struct picprog_t *p, uint16_t *id, uint16_t *rev)
{
	return 1;
}

static uint32_t PIC12_Read(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length)
{
	return 1;
}

static uint32_t PIC12_Write(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length)
{
	return 1;
}

static uint32_t PIC12_Erase(struct picprog_t *p)
{
	return 1;
}


struct proto_ops_t pic12_proto = {
	.type = PROTO_PIC12,
	.EnterICSP = PIC12_EnterICSP,
	.ExitICSP = PIC12_ExitICSP,
	.ReadID = PIC12_ReadID,
	.Read = PIC12_Read,
	.Write = PIC12_Write,
	.Erase = PIC12_Erase
};
