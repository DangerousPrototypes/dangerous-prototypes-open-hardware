#ifndef PIC_h_
#define PIC_h_

#include <stdint.h>

#include "common.h"
#include "memory.h"
#include "proto_pic.h"

#define PIC_EMPTY  0xff

enum pic_mem_t {
	PIC_MEM_FUSE,
	PIC_MEM_FLASH,
	PIC_MEM_EEPROM,
	PIC_MEM_LAST
};

struct pic_memmap_t {
	uint32_t base;
	uint32_t size;
};

struct pic_chip_t {
	const char *name;
	uint32_t ID;
	uint16_t family;

	struct pic_memmap_t memmap[PIC_MEM_LAST];
};

struct pic_family_t {
	enum proto_t proto;
	uint32_t ID_addr;
	uint8_t word_size;
	uint16_t page_size;

	enum icsp_t icsp_type;
	uint32_t icsp_key; 
	uint16_t erase_key[4];

	uint32_t write_delay;
	uint32_t erase_delay;
};

typedef uint32_t (*pic_rw_func)(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length);

int16_t PIC_GetChipIdx(char *name);
int16_t PIC_GetFamilyIdx(uint16_t chip_idx);
struct pic_chip_t *PIC_GetChip(uint16_t i);
struct pic_family_t *PIC_GetFamily(uint16_t i);
struct proto_ops_t *PIC_GetProtoOps(uint16_t i);
extern const struct pic_chip_t pic_chip[];

void PIC_PreserveConfig(struct picprog_t *p, struct memory_t *mem);
int PIC_WriteMemory(struct picprog_t *p, struct memory_t *mem);
int PIC_ReadMemory(struct picprog_t *p, struct memory_t *mem);

#endif

