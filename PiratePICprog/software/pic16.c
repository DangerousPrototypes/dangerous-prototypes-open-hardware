
#include "pic16.h"


static uint32_t PIC16_EnterICSP(struct picprog_t *p, enum icsp_t icsp_type)
{
	return 1;
}

static uint32_t PIC16_ExitICSP(struct picprog_t *p, enum icsp_t type)
{
	return 1;
}

static uint32_t PIC16_ReadID(struct picprog_t *p, uint32_t *id, uint16_t *rev)
{
	return 1;
}

static uint32_t PIC16_Read(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length)
{
	return 1;
}

static uint32_t PIC16_Write(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length)
{
	return 1;
}

static uint32_t PIC16_Erase(struct picprog_t *p)
{
	return 1;
}


struct proto_ops_t pic16_proto = {
	.type = PROTO_PIC16,
	.EnterICSP = PIC16_EnterICSP,
	.ExitICSP = PIC16_ExitICSP,
	.ReadID = PIC16_ReadID,
	.Read = PIC16_Read,
	.Write = PIC16_Write,
	.Erase = PIC16_Erase
};
