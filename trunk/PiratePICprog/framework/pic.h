#ifndef PIC_h_
#define PIC_h_

#include <stdint.h>

struct pic_chip_t {
	const char *name;
	uint16_t ID;
	uint32_t flash;
	uint32_t eeprom;
	uint16_t family;
};

struct pic_family_t {
	uint32_t family;

	proto_t proto;
	uint32_t ID_addr;
	uint8_t word_size;
	uint16_t page_size;

	icsp_t icsp_type;
	uint32_t icsp_key; 
	uint16_t erase_key[4];

	uint32_t write_delay;
	uint32_t erase_delay;
};

int16_t PIC_GetChipIdx(char *name);
int16_t PIC_GetFamilyIdx(uint16_t chip_idx);
struct pic_chip_t *PIC_GetChip(uint16_t i);
struct pic_family_t *PIC_GetFamily(uint16_t i);

#endif

