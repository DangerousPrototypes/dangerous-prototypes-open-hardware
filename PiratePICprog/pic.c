
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
	FAMILY_24FJxxGAxxx,
	FAMILY_18Fx5xx,
};

#define CHIP_CNT (sizeof(pic_chip)/sizeof(struct pic_chip_t))
#define FAMILY_CNT (sizeof(pic_family)/sizeof(struct pic_family_t))

const struct pic_chip_t pic_chip[] = {
    {
		.name = "18F2550",
		.ID = 0x92,
		.flash = 0x8000,
		.eeprom = 256,
		.family = FAMILY_18Fx5xx,
	},
	{
		.name = "18F24J50",
		.ID = 0x260,
		.flash = 16*1024,
		.eeprom = 0,
		.family = FAMILY_18F2xJxx,
	},
    {
		.name = "24FJ64GA002",
		.ID = 0x447,
		.flash = 344*256,
		.eeprom = 0,
		.family = FAMILY_24FJxxGAxxx,
	},

};

const struct pic_family_t pic_family[] = {
	{
		.family = FAMILY_18F2xJxx,
		.proto = PROTO_PIC18,
		.ID_addr = 0x3ffffe,
		.word_size = 2, //bytes
		.page_size = 64, //bytes (32 words)
		.icsp_type = ICSP_LVPP,
		.icsp_key = 0x4d434850,
		.erase_key = { 0x3f3f, 0x8f8f },
		.write_delay = 1,
		.erase_delay = 524,
	},
    {
		.family = FAMILY_24FJxxGAxxx,
		.proto = PROTO_PIC24,
		.ID_addr = 0x00FF0000,
		.word_size = 2,
		.page_size = 256,
		.icsp_type = ICSP_LVPP,
		.icsp_key = 0x4D434851,
		.erase_key = { 0x3f3f, 0x8f8f },
		.write_delay = 1, //polled in 24FJ
		.erase_delay = 524,
	},
    {
		.family = FAMILY_18Fx5xx,
		.proto = PROTO_PIC18,
		.ID_addr = 0x3ffffe,
		.word_size = 2, //bytes
		.page_size = 32, //bytes (32 words)
		.icsp_type = ICSP_HVPP,
		.icsp_key = 0x00000000,
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


