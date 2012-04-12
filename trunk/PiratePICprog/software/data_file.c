
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#include "data_file.h"

static uint32_t HEX_ReadFile(const char *file, struct memory_t *mem);
static int HEX_WriteFile(const char *file, struct memory_t *mem);
static int HEX_CheckType(const char *);
static uint32_t BIN_ReadFile(const char *file, struct memory_t *mem);
static int BIN_WriteFile(const char *file, struct memory_t *mem);
static int BIN_CheckType(const char *);

#define FILE_OPS_CNT (sizeof(file_ops)/sizeof(struct file_ops_t))
const struct file_ops_t file_ops[] = {
	{
		.name = "HEX",
		.ReadFile = HEX_ReadFile,
		.WriteFile = HEX_WriteFile,
		.CheckType = HEX_CheckType,
	},
	{
		.name = "BIN",
		.ReadFile = BIN_ReadFile,
		.WriteFile = BIN_WriteFile,
		.CheckType = BIN_CheckType,
	}
};

struct file_ops_t *GetFileOps(char *name)
{
	int i;

	for (i = 0; i < FILE_OPS_CNT; i++) {
		if (strcasecmp(name, file_ops[i].name) == 0) {
			return (struct file_ops_t *)&file_ops[i];
		}
	}

	return NULL;
}

/*
 * returns checksum of input buffer
 */
uint8_t Data_Checksum(uint8_t *buf, uint16_t size)
{
	uint16_t i;
	uint8_t sum = 0;

	for (i=0; i<size; i++) {
		sum -= buf[i];
	}
	return sum;
}

/*
 * reads hex file
 * file - name of hexfile
 * buf - buffer where the data should be written to
 * size - size of buffer
 */
#define MAX_LINE_SIZE 256
static uint32_t HEX_ReadFile(const char *file, struct memory_t *mem)
{
	char raw_line[MAX_LINE_SIZE];
	int line = 0;
	uint32_t base_addr;
	FILE *fp;
	uint32_t addr_max=0;
	uint8_t *tmp;
	uint16_t tmp_len;
	uint8_t chksum;
	uint16_t i;
	unsigned int b;

	fp = fopen(file, "r");

	if (fp == NULL) {
		return 0;
	}

	tmp = safe_malloc(sizeof(raw_line)+1);


	while(fgets(raw_line, sizeof(raw_line), fp) != 0) {
		// read line header
		uint8_t byte_count;
		uint32_t addr;
		uint8_t rec_type;
		const char *p;

		if (raw_line[0] != ':') {
			printf("File '%s' is not a hex file !\n", file);
			return 0;
		}

		line ++;
		p = raw_line + 1;

		tmp_len = 0;
		// read byte count (1byte), address (2byte), record type (1byte)
		for (i = 0; i < 4; i ++) {
			sscanf(p, "%2x", &b);
			p += 2;
			tmp[tmp_len] = b;
			tmp_len ++;
		}

		byte_count = tmp[0];
		addr = (tmp[1] << 8) | tmp[2];
		rec_type = tmp[3];

		if (rec_type == 0x00) {
			// data record
			uint16_t i;
			addr = base_addr | addr;

			for (i = 0; i < byte_count; i++) {
				sscanf(p, "%2x", &b);
				p += 2;

				tmp[tmp_len] = b;

				tmp_len++;

				if (addr_max < addr + i) {
					addr_max = addr + i;
				}

				//MEM_Write(mem, addr + i, &tmp[tmp_len-1], 1);
			}
			MEM_Write(mem, addr, &tmp[tmp_len-byte_count], byte_count);
		} else if (rec_type == 0x04) {
			// extended linear: base addr
			base_addr = 0;
			for (i = 0; i < byte_count; i++) {
				sscanf(p, "%2x", &b);
				p += 2;

				tmp[tmp_len] = b;
				tmp_len ++;
				base_addr = (base_addr << 8) | (b & 0xff);
			}

			base_addr <<= 16;
#ifdef DEBUG
			fprintf(stderr, "new (linear) base addr = %08x\n", base_addr);
#endif
		} else if (rec_type == 0x01) {
			// end record
			break;
		} else {
			fprintf(stderr, "Unknown record type on line %d\n", line);
			return 0;
		}

		sscanf(p, "%2x", &b);
		chksum = b;

		// calculate checksum after line was parsed
		if (Data_Checksum(tmp, tmp_len) != chksum) {
			fprintf(stderr, "Checksum error on line %d\n", line);
			return 0;
		}
	}

	free(tmp);
	fclose(fp);
	return addr_max + 1;
}

/*
 * writes hex file
 * file - name of hexfile
 * buf - buffer where data is stored
 * size - size of buffer
 */
static void HEX_WriteRec(FILE *fp, uint8_t rec_id, uint8_t byte_count, uint16_t addr, uint8_t *data)
{
	int res;
	uint8_t bin_line[128];
	char raw_line[256];
	uint8_t i=0;
	uint8_t j;

	// fill header
	bin_line[0] = byte_count;
	bin_line[1] = (addr >> 8) & 0xff;
	bin_line[2] = addr & 0xff;
	bin_line[3] = rec_id;

	// copy data
	for (i=0; i<byte_count; i++) {
		bin_line[4 + i] = data[i];
	}

	// add checksum
	bin_line[4 + i] = Data_Checksum(bin_line, 4+i);

	// rewrite bin data to hex
	res = sprintf(raw_line, ":");
	for (j = 0; j < 4 + i + 1; j++) {
		res += sprintf(raw_line + res, "%02X", bin_line[j]);
	}
	res += sprintf(raw_line + res, "\n");

#ifdef DEBUG
	printf(raw_line);
#endif

	// output to file
	res = fwrite(raw_line, sizeof(char), res, fp);
}

/*
 * writes hex file
 * file - name of hexfile
 * buf - buffer which contains the data
 * size - size of buffer
 */
static int HEX_WriteFile(const char *file, struct memory_t *mem)
{
	struct mem_page_t *page;
	uint32_t written = 0;
	uint16_t base = 0x0000;
	uint16_t oldbase = 0xFFFF;
	uint8_t base_bytes[2];
	uint32_t addr = 0x0000;
	FILE *fp;

	if (mem == NULL) {
		return -2;
	}


	fp = fopen(file, "w");

	if (fp == NULL) {
		return -1;
	}

	page = MEM_GetFirstPage(mem);
	while (page != NULL) {
		written = 0;

		if (MEM_PageEmpty(page)) {
			page = MEM_GetNextPage(page);
			continue;
		}

		// ext address record
		base = page->base >> 16;
		if (oldbase != base) {
			base_bytes[0] = (base & 0xff00) >> 8;
			base_bytes[1] = base & 0x00ff;
			HEX_WriteRec(fp, 0x04, 2, 0x0000, base_bytes);
			oldbase = base;
		}

		while (written < page->size) {
			uint8_t byte_count;
			uint32_t offset;

			if ((page->size - written) > 0x10) {
				byte_count = 0x10;
			} else {
				byte_count = page->size - written;
			}

			addr = (page->base + written) & 0xffff;

			// write data record
			HEX_WriteRec(fp, 0x00, byte_count, addr, &page->data[written]);

			written += byte_count;
		}

		page = MEM_GetNextPage(page);
	}

	// end record
	HEX_WriteRec(fp, 0x01, 0x00, 0x0000, NULL);

	fclose(fp);
	return 0;
}

static int HEX_CheckType(const char *dummy)
{
	return 0; //TODO: finish
}

/*
 * reads bin file
 * file - name of hexfile
 * buf - buffer where the data should be written to
 * size - size of buffer, returns actual size read
 */
static uint32_t BIN_ReadFile(const char *file, struct memory_t *mem)
{
	int res;
	long fsize;
	FILE *fp;

	uint8_t *data;
	uint8_t *empty;
	uint32_t addr = 0;

	data = safe_malloc(mem->page_size);
	empty = safe_malloc(mem->page_size);

	memset(empty, MEM_EMPTY, mem->page_size);

	fp = fopen(file, "rb");
	if (fp == NULL) {
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	addr = 0;

	while ((res = fread(data, sizeof(uint8_t), mem->page_size, fp)) > 0) {
		if (memcmp(data, empty, mem->page_size) != 0) {
			MEM_Write(mem, addr, data, res);
		}
		addr += res;
	}

	free(data);
	fclose(fp);
	return addr;
}

/*
 * writes bin file
 * file - name of hexfile
 * buf - buffer which contains the data
 * size - size of buffer
 */
static int BIN_WriteFile(const char *file, struct memory_t *mem)
{
	struct mem_page_t *page;
	uint32_t addr;
	FILE *fp;
	int res;

	fp = fopen(file, "wb");
	if (fp == NULL) {
		return -1;
	}

	page = MEM_GetFirstPage(mem);
	addr = 0;
	while (page != NULL) {
		if (MEM_PageEmpty(page)) {
			page = MEM_GetNextPage(page);
			continue;
		}

#ifdef DEBUG
		printf("pagebase %08x addr %08x size %02x\n", page->base, addr, page->size);
#endif

		// fill difference with MEM_EMPTYs
		if (page->base > addr) {
			uint32_t i;
			uint8_t tmp = MEM_EMPTY;

#ifdef DEBUG
			printf("adding empty (%ld)\n", page->base -addr);
#endif
			for (i = 0; i < page->base - addr; i++) {
				fwrite(&tmp, sizeof(uint8_t), 1, fp);
			}

			addr = page->base;
		}

		res = fwrite(page->data, sizeof(uint8_t), page->size, fp);
		addr += page->size;

		page = MEM_GetNextPage(page);
	}

	fclose(fp);

	return 0;
}

static int BIN_CheckType(const char *dummy)
{
	/* always binary */
	return 1;
}
