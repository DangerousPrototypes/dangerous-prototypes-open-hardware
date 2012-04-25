
#include <unistd.h>
#include <stdio.h>
#include "pic.h"
#include "iface.h"

#include "pic16.h"
#include "debug.h"

static uint32_t pic16_pc = 0;

static uint32_t PIC16_Read(struct picprog_t *p, uint32_t addr, uint16_t *data, uint32_t length);

static uint32_t PIC16_EnterICSP(struct picprog_t *p, enum icsp_t icsp_type)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;

	if (icsp_type != ICSP_HVPP) {
		dbg_err("LVPP not supported yet\n");
		exit(-1);
	}

	iface->VCCHigh();

	iface->ClockLow();
	iface->DataLow();
	iface->VPPLow();
	iface->MCLRHigh(); // neg in HVPP mode

	// VCC-first entry
	iface->VPPHigh(); //AUX high to apply 13V (CS=1)
	iface->MCLRLow(); //MCLR low to bring MCLR to 13volts

	pic16_pc = 0;

	return 0;
}

static uint32_t PIC16_ExitICSP(struct picprog_t *p, enum icsp_t type)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;

	iface->ClockLow();
	iface->DataLow();
	iface->VPPLow();
	iface->MCLRHigh();

	iface->VCCLow();

	return 0;
}

static void PIC16_SetPC(struct picprog_t *p, uint32_t addr)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;

	if (addr >= 0x2000 && pic16_pc < 0x2000) {
		iface->PIC614Write(0, 0); // load configuration
		pic16_pc = 0x2000;
	} else if (pic16_pc >= 0x2000 && addr < 0x2000) {
		// only way to reset PC is to reset the CPU
		PIC16_ExitICSP(p, f->icsp_type);
		PIC16_EnterICSP(p, f->icsp_type);
		pic16_pc = 0;
	}

	dbg_info("addr= %04x pc= %04x\n", addr, pic16_pc);
	while (addr > pic16_pc) {
		iface->PIC614Write(0x80 | 0x06, 0); // inc pc (0x80 = command without data)
		pic16_pc++;
	}
}

// read number of words into data
static uint32_t PIC16_ReadRaw(struct picprog_t *p, uint32_t addr, uint16_t *data, uint32_t length)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	uint32_t i;

	dbg_info("addr = %04x len=%d \n", addr, length);
	PIC16_SetPC(p, addr);
	
	for (i = 0; i < length; i++) {
		iface->PIC614Read(0x04, 0, 1); // read program data
		iface->PIC614Write(0x80 | 0x06, 0); // inc pc (0x80 = command without data)
		pic16_pc++;
	}

	iface->GetData((uint8_t *)data, length * 2);

	// unpack data
	for (i = 0; i < length; i++) {
		data[i] = (data[i] >> 1) & 0x3FFF;
	}
	
	return 0;
}

static uint32_t PIC16_ReadID(struct picprog_t *p, uint32_t *id, uint16_t *rev)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;

	uint16_t buf;

	PIC16_EnterICSP(p, f->icsp_type);

	PIC16_ReadRaw(p, f->ID_addr, &buf, 1);

	PIC16_ExitICSP(p, f->icsp_type);

	dbg_info("raw id = %04x \n", buf);

	*id = buf >> 5;
	*rev = buf & 0x1F;

	return *id;
}

static uint32_t PIC16_Read(struct picprog_t *p, uint32_t addr, uint16_t *data, uint32_t length)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	uint32_t i;

	dbg_info("addr = %04x len=%d \n", addr, length);
	return PIC16_ReadRaw(p, addr/2, data, length/2);
}

static uint32_t PIC16_Write(struct picprog_t *p, uint32_t addr, uint16_t *data, uint32_t length)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	uint32_t i;

	dbg_info("addr = %04x length = %02x\n", addr, length);
	dbg_buf_info((uint8_t*)data, length);

	if (length % 2) {
		dbg_err("size not word aligned");
		return 1;
	}

	length /= 1;
	addr /= 2;
	PIC16_SetPC(p, addr);

	for (i = 0; i < length/2; i++) { // TODO: read after write ?
		dbg_info("Writing pc=%04x\n", pic16_pc);
		if (pic16_pc < 0x2000 || pic16_pc == 0x2007 || pic16_pc == 0x2008) {
			iface->PIC614Write(0x02, (data[i] << 1) & 0x7FFE); // bulk erase program memory
			iface->PIC614Write(0x80 | 0x08, 0); // begin programming internaly timed
			iface->flush();
			usleep(f->write_delay * 1000);
		}

		iface->PIC614Write(0x80 | 0x06, 0); // inc pc (0x80 = command without data)
		pic16_pc++;
	}

	return 0;
}

static uint32_t PIC16_Erase(struct picprog_t *p)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;

	PIC16_EnterICSP(p, f->icsp_type);

	iface->PIC614Write(0x80 | 0x09, 0); // bulk erase program memory
	iface->flush();
	usleep(f->erase_delay * 1000);

	iface->PIC614Write(0, 0); // load configuration

	iface->PIC614Write(0x80 | 0x09, 0); // bulk erase program memory
	iface->flush();
	usleep(f->erase_delay * 1000);

	iface->PIC614Write(0x80 | 0x0B, 0); // bulk erase data memory
	iface->flush();
	usleep(f->erase_delay * 1000);

	PIC16_ExitICSP(p, f->icsp_type);

	return 0;
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
