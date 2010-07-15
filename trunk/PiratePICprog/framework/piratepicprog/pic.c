
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#include "proto_pic.h"
#include "pic.h"
#include "iface.h"
#include "common.h"

enum {
	FAMILY_18F2xJxx, // also 18F4xJxx
};

#define CHIP_CNT (sizeof(pic_chip)/sizeof(struct pic_chip_t))
#define FAMILY_CNT (sizeof(pic_family)/sizeof(struct pic_family_t))

const struct pic_chip_t pic_chip[] = {
	{
		.name = "18F24J50",
		.ID = 0x260,
		.flash = 16*1024,
		.eeprom = 0,
		.family = FAMILY_18F2xJxx,
	},
};

const struct pic_family_t pic_family[] = {
	{
		.family = FAMILY_18F2xJxx,
		.proto = PROTO_PIC18,
		.ID_addr = 0x3ffffe,
		.word_size = 2,
		.page_size = 64,
		.icsp_type = ICSP_LVPP,
		.icsp_key = 0x4d434850,
		.erase_key = { 0x3f3f, 0x8f8f },
		.write_delay = 1,
		.erase_delay = 524,
	},

};

int16_t PIC_GetChipIdx(char *name) {
	int16_t i;

	for (i = 0; i < CHIP_CNT; i++) {
		if (strcmp(name, pic_chip[i].name) == 0) {
			return i;
		}
	}

	return -1;
}

int16_t PIC_GetFamilyIdx(uint16_t chip_idx) {
	int16_t idx;

	if (chip_idx > CHIP_CNT)
		return -1;

	idx = pic_chip[chip_idx].family;

	if (idx > FAMILY_CNT) {
		printf("Fatal error: Family index out of bounds !\n");
	}

	// The enum should have the same order as family array
	if (pic_family[idx].family == idx) {
		return idx;
	}

	/*  this is not necessary
	for (i = 0; i < FAMILY_CNT; i++) {
		if (pic_family[i].family == idx) {
			return i;
		}
	}
	*/

	// This ensures that the table is written in correct order :)
	printf("Fatal error: Fix family table !\n");

	return -1;
}

struct pic_chip_t *PIC_GetChip(uint16_t i) {

	if (i > CHIP_CNT)
		return NULL;

	return (struct pic_chip_t *)&pic_chip[i];
}

struct pic_family_t *PIC_GetFamily(uint16_t i) {

	if (i > FAMILY_CNT)
		return NULL;

	return (struct pic_family_t *)&pic_family[i];
}

struct proto_ops_t *PIC_GetProtoOps(uint16_t i) {
	struct pic_chip_t *c = PIC_GetChip(i);
	struct pic_family_t *f = PIC_GetFamily(c->family);

	return Proto_GetOps(f->proto);
}

int PIC_WriteFlash(struct picprog_t *p, uint8_t *fw_data)
{
	struct pic_family_t *fam = PIC_GetFamily(p->chip_idx);
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct proto_ops_t *proto = Proto_GetOps(fam->proto);
    struct iface_t *iface = p->iface;

	uint32_t u_addr;
	uint32_t page  = 0;
	uint32_t done  = 0;
	uint8_t used = 0, t;
	uint16_t i = 0;

    proto->EnterICSP(p, fam->icsp_type);

	for (page = 0; page < pic->flash / fam->page_size; page++)
	{
		u_addr = page * fam->page_size;
		//( PIC_NUM_WORDS_IN_ROW * 2 * PIC_NUM_ROWS_IN_PAGE );
		//u_addr = page * ( 2 * 32 );

		// check used page
		used = 0;
		for (i = 0; i < fam->page_size; i++) {
		    t=fw_data[u_addr+i];
			if (fw_data[u_addr+i] != PIC_EMPTY) {
				used = 1;
				break;
			}
		}

		// skip unused
		if (used == 0 ) {
			if (u_addr < pic->flash) {
				fprintf(stdout, "Skipping page %ld [ 0x%06lx ], not used\n", (unsigned long)page, (unsigned long)u_addr);
			}
			continue;
		}

		if (u_addr >= pic->flash) {
			fprintf(stderr, "Address out of flash\n");
			continue;
		}

		printf("Writing page %ld, %04lx... \n", (unsigned long)page, (unsigned long)u_addr);

		if (p->debug) {
			dumpHex(&fw_data[page * fam->page_size], fam->page_size);
		}

		proto->Write(p, u_addr, &fw_data[page * fam->page_size], fam->page_size);

		//usleep(fam->write_delay * 1000);

		done += fam->page_size;
	}

    proto->ExitICSP(p);

	return done;
}

int PIC_ReadFlash(struct picprog_t *p, uint8_t *fw_data)
{
	struct pic_family_t *fam = PIC_GetFamily(p->chip_idx);
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct proto_ops_t *proto = Proto_GetOps(fam->proto);

	uint32_t u_addr;
	uint32_t page  = 0;
	uint32_t done  = 0;

	for (page = 0; page < pic->flash / fam->page_size; page++)
	{
		u_addr = page * fam->page_size;
		//( PIC_NUM_WORDS_IN_ROW * 2 * PIC_NUM_ROWS_IN_PAGE );
		//u_addr = page * ( 2 * 32 );

		if (u_addr >= pic->flash) {
			fprintf(stderr, "Address out of flash\n");
			continue;
		}

		printf("Reading page %ld, %04lx... \n", (unsigned long)page, (unsigned long)u_addr);

		proto->Read(p, u_addr, &fw_data[page * fam->page_size], fam->page_size);

		if (p->debug) {
			dumpHex(&fw_data[page * fam->page_size], fam->page_size);
		}

		usleep(fam->write_delay * 1000);

		done += fam->page_size;
	}

	return done;
}


