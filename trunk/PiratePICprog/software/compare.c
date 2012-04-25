/*
 * memory comparation program
 *
 * one argument
 * ./compare file.bin
 * loads file.bin and prints the content
 *
 * one argument with specified file type
 * ./compare hex:file.hex
 * loads file.hex in intel-hex format and prints content
 *
 * two arguments (with or without file type)
 * ./compare file.bin hex:file.hex
 * loads file.bin and file.hex, prints content, and compares files content wise.
 *
 * 0xFF is "blank" (applies to most flash devices) and it is trimmed from all
 * loaded buffers
 *
 * All files loaded are split into 128byte chunks
 * (unless first argument is Cxxx, where xxx is the size of chunks)
 */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "memory.h"
#include "data_file.h"


static void parse_file(char *input, struct file_ops_t **op, char **file)
{
	char *pos;

	*op = GetFileOps("bin");

	pos = strchr(input, ':');

	if (pos != NULL) {
		pos[0] = '\0';
		*op = GetFileOps(input);
		*file = &pos[1];
	} else {
		*file = input;
	}
}

int main(int argc, char** argv)
{
	struct file_ops_t *fo1;
	struct file_ops_t *fo2;
	struct memory_t *mem1;
	struct memory_t *mem2;

	uint16_t chunk = 128;

	char *filename;

	uint32_t max;

	if (argc < 2) {
		printf("too few arguments\n");
		printf("%s [type:]filename [[type:]filename]\n", argv[0]);
		printf(" type is either HEX or BIN, case insensitive\n\n");
		printf(" If second file is present both files are printed and compared\n");
		printf("  else only first file is printed\n");
		exit(-1);
	}

	if (argc > 1) {
		if (argv[1][0] == 'C') {
			chunk = atoi(&argv[1][1]);

			/* hack */
			argc--;
			argv++;
		}
	}

	if (argc > 1) {
		mem1 = MEM_Init(chunk, 1);

		parse_file(argv[1], &fo1, &filename);
		max = fo1->ReadFile(filename, mem1);

		printf("Filename: %s\n", filename);
		MEM_Print(mem1);
	}

	if (argc > 2) {
		mem2 = MEM_Init(chunk, 1);

		parse_file(argv[2], &fo2, &filename);
		max = fo2->ReadFile(filename, mem2);

		printf("\n\nFilename: %s\n", filename);
		MEM_Print(mem2);

		printf("\nComparing files...\n");
		if (MEM_Compare(mem1, mem2)) {
			// mem_compare is verbose enough ;)
			//printf("Differ\n");
		} else {
			printf("Same\n");
		}

		MEM_Destroy(mem2);
	}

	MEM_Destroy(mem1);
}
