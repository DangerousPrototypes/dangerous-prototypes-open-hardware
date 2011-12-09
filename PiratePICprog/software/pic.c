
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include "proto_pic.h"
#include "pic.h"
#include "iface.h"
#include "memory.h"
#include "common.h"

enum {
	FAMILY_18F2xJxx, // also 18F4xJxx
	FAMILY_24FJxxGAxxx,
	FAMILY_24FJxxGBxxx,
	FAMILY_18Fx5xx,
	FAMILY_LAST
};

#define CHIP_CNT (sizeof(pic_chip)/sizeof(struct pic_chip_t))

const struct pic_chip_t pic_chip[] = {
	{
		.name = "18F2550",
		.ID = 0x92,
		.family = FAMILY_18Fx5xx,
		.memmap = {
			[PIC_MEM_FLASH] = {
				.base = 0x0000,
				.size = 32*1024
			},
			[PIC_MEM_FUSE] = {
				.base = 0x300000,
				.size = 14
			},
			/* TODO
			[PIC_MEM_EEPROM] = {
				.base = 
			}*/
		}
	},
	{
		.name = "18F2553",
		.ID = 0x152,
		.family = FAMILY_18Fx5xx,
		.memmap = {
			[PIC_MEM_FLASH] = {
				.base = 0x0000,
				.size = 32*1024
			},
			[PIC_MEM_FUSE] = {
				.base = 0x300000,
				.size = 14
			},
/* TODO
			[PIC_MEM_EEPROM] = {
				.base =
			}*/
		}
	},
	{
		.name = "18F4550",
		.ID = 0x90,
		.family = FAMILY_18Fx5xx,
		.memmap = {
			[PIC_MEM_FLASH] = {
				.base = 0x0000,
				.size = 32*1024
			},
			[PIC_MEM_FUSE] = {
				.base = 0x300000,
				.size = 14
			}
		}
	},
	{
		.name = "18F24J50",
		.ID = 0x260,
		.family = FAMILY_18F2xJxx,
		.memmap = {
			[PIC_MEM_FLASH] = {
				.base = 0x0000,
				.size = 16*1024
			},
			[PIC_MEM_FUSE] = {
				.base = 0x3FF8,
				.size = 8
			}
		}
	},
	{
		.name = "24FJ64GA002",
		.ID = 0x447,
		.family = FAMILY_24FJxxGAxxx,
		.memmap = {
			[PIC_MEM_FLASH] = {
				.base = 0x0000,
				.size = 64*1024,
			},
			[PIC_MEM_EEPROM] = {
				.base = 0xABFE,
				.size = 2
			}
		}
	},
	{
		.name = "24FJ256GB106",
		.ID = 0x1019,
		.family = FAMILY_24FJxxGBxxx,
		.memmap = {
			[PIC_MEM_FLASH] = {
				.base = 0x0000,
				.size = 256*1024,
			},
			[PIC_MEM_EEPROM] = {
				.base = 0x2ABFE,
				.size = 3
			}
		}
	},

};

const struct pic_family_t pic_family[] = {
	[FAMILY_18F2xJxx] = {
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

	[FAMILY_24FJxxGAxxx] = {
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

	[FAMILY_24FJxxGBxxx] = {
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

	[FAMILY_18Fx5xx] = {
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

int PIC_ReadMemory(struct picprog_t *p, struct memory_t *mem)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *fam = PIC_GetFamily(pic->family);
	struct proto_ops_t *proto = PIC_GetProtoOps(p->chip_idx);

	uint8_t *data;
	uint32_t page;
	uint32_t size;
	uint32_t addr;

	data = safe_malloc(fam->page_size);

	proto->EnterICSP(p, fam->icsp_type); 
	
	for (page = 0; page < pic->memmap[PIC_MEM_FLASH].size / fam->page_size; page++) {
		addr = page * fam->page_size;
		size = fam->page_size;

		printf("Reading page %ld, %04lx... \n", (unsigned long)page, (unsigned long)addr);

		proto->Read(p, addr, data, size);
		MEM_Write(mem, addr, data, size);
	}

	// TODO: check fuses already read by last page read
	addr = pic->memmap[PIC_MEM_FUSE].base;
	size = pic->memmap[PIC_MEM_FUSE].size;

	if (size > 0) {
		printf("Reading config words %04lx size %02x... \n", (unsigned long)addr, size);
		proto->Read(p, addr, data, size);
		MEM_Write(mem, addr, data, size);
	}

	// TODO: read EEPROM once ready
/*
	addr = pic->memmap[PIC_MEM_EEPROM].base;
	size = pic->memmap[PIC_MEM_EEPROM].size;
	if (size > 0) {
	}
*/

	proto->ExitICSP(p, fam->icsp_type); 

	free(data);

	return 0;
}

int PIC_WriteMemory(struct picprog_t *p, struct memory_t *mem)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *fam = PIC_GetFamily(pic->family);
	struct proto_ops_t *proto = PIC_GetProtoOps(p->chip_idx);

	struct mem_page_t * page;

	proto->EnterICSP(p, fam->icsp_type); 

	page = MEM_GetFirstPage(mem);
	while (page != NULL) {
		printf("Writing page %04lx... \n", (unsigned long)page->base);

		// TODO: check address against pic memory map! EEPROM and Fuses might need separate handling
		proto->Write(p, page->base, page->data, page->size);
		page = MEM_GetNextPage(page);
	}

	proto->ExitICSP(p, fam->icsp_type); 

	return 0;
}

// TODO: this code assumes that config lies in single page!
void PIC_PreserveConfig(struct picprog_t *p, struct memory_t *mem)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *fam = PIC_GetFamily(pic->family);
	struct proto_ops_t *proto = PIC_GetProtoOps(p->chip_idx);

	uint32_t size;
	uint32_t addr;
	uint8_t *data;
	uint8_t *tmp;
	int ret;
	int i;

	addr = pic->memmap[PIC_MEM_FUSE].base;
	size = pic->memmap[PIC_MEM_FUSE].size;


	printf("Checking fuses \n");
	if (MEM_PageExists(mem, addr)) {
		ret = MEM_Read(mem, addr, &data, size);
		if (ret < 0) {
			printf("error reading config ... \n");
			exit(-1);
		} else if (ret > 0) {

			// check valid fuses in memory
			// TODO: more robust solution needed (mask?)
			for (i = 0; i < size; i++) {
				if (data[i] != PIC_EMPTY) {
					break;
				}
			}

			if (i != size) {
				printf("fuses found in loaded file\n");
				return;
			}
		} else {
			printf("no fuses found\n");
		}
	}


	tmp = safe_malloc(size);

	printf("Loading fuses from PIC\n");

	// read fuses into memory
	proto->EnterICSP(p, fam->icsp_type); 
	proto->Read(p, addr, tmp, size);
	MEM_Write(mem, addr, tmp, size);
	proto->ExitICSP(p, fam->icsp_type); 

	free(tmp);
}

int16_t PIC_GetChipIdx(char *name) {
	int16_t i;

	for (i = 0; i < CHIP_CNT; i++) {
		if (strcasecmp(name, pic_chip[i].name) == 0) {
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

	return idx;
}

struct pic_chip_t *PIC_GetChip(uint16_t i) {

	if (i > CHIP_CNT)
		return NULL;

	return (struct pic_chip_t *)&pic_chip[i];
}

struct pic_family_t *PIC_GetFamily(uint16_t i) {
	if (i >= FAMILY_LAST)
		return NULL;

	return (struct pic_family_t *)&pic_family[i];
}

struct proto_ops_t *PIC_GetProtoOps(uint16_t i) {
	struct pic_chip_t *c = PIC_GetChip(i);
	struct pic_family_t *f = PIC_GetFamily(c->family);

	return Proto_GetOps(f->proto);
}

