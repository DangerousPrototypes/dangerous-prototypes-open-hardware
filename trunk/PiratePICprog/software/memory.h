/* 
 * Part of ols-fwloader - data file parsing/generaion
 *
 * Copyright (C) 2011 Michal Demin <michal.demin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdint.h>

#define MEM_EMPTY 0xFF

struct mem_empty_t {
	uint8_t len;
	uint8_t *pattern;
};

struct mem_page_t {
	/* base address of page */
	uint32_t base;

	/* size of usable data */
	uint32_t size;

	/* data buffer */
	uint8_t *data;

	/* pointer to next page */
	struct mem_page_t *next;
};

struct memory_t {
	/* size of pages in memory */
	uint32_t page_size;

	uint8_t word_size;

	struct mem_page_t *page;
	struct mem_empty_t *empty;
};

struct memory_t *MEM_Init(uint32_t page_size, uint8_t word_size);
int MEM_Write(struct memory_t *mem, uint32_t addr, uint8_t *data, uint32_t len);
int MEM_Read(struct memory_t *mem, uint32_t addr, uint8_t **data, uint32_t len);
int MEM_PageExists(struct memory_t *mem, uint32_t addr);
struct mem_page_t *MEM_GetPage(struct memory_t *mem, uint32_t base);
struct mem_page_t *MEM_GetFirstPage(struct memory_t *mem);
struct mem_page_t *MEM_GetNextPage(struct mem_page_t *page);

int MEM_Compare(struct memory_t *mem_a, struct memory_t *mem_b);
int MEM_PageEmpty(struct memory_t *mem, struct mem_page_t *page);
void MEM_Optimize(struct memory_t *mem);
void MEM_Print(struct memory_t *mem);
int MEM_Destroy(struct memory_t *);

#endif


