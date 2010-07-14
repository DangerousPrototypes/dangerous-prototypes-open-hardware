/*
 * PUMP flash loader
 *
 * 2010 - Michal Demin
 *
 * Loosely based on Pirate-Loader:
 * http://the-bus-pirate.googlecode.com/svn/trunk/bootloader-v4/pirate-loader/source/pirate-loader.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pic.h"
#include "proto_pic.h"
#include "data_file.h"
#include "iface.h"
#include "common.h"

int verbose = 0;

enum {
	CMD_READ = 1,
	CMD_WRITE = 2,
	CMD_ERASE = 4,
	CMD_VERIFY = 8
};


void print_usage(char* name) {
		printf("parameters:\n");
		printf("-p PROG  - name of interface\n");
		printf("-u PORT  - interface port\n");
		printf("-s SPEED - interface speed\n");
		printf("-c CHIP  - chip type\n");
		printf("\n");
		printf("-t TYPE - input/output file type HEX, BIN\n");
		printf("-w FILE - file to be uploaded to PIC\n");
		printf("-r FILE - file to be downloaded from PIC\n");
//		printf("-v      - be noisy\n");
		printf("commands:\n");
		printf("-E  - erases Flash\n");
		printf("-W  - writes data to Flash\n");
		printf("-R  - reads data from Flash\n");
		printf("-V  - verifies content of flash\n");
		printf("-I  - get the chip ID\n");
		printf("\n\n");
}

int main(int argc, char** argv) {
	int opt;
//	int	res = -1;
//	uint32_t i;

	uint32_t read_size;

	uint8_t *buf_read, *buf_write;
	char *param_write_file = NULL;
	char *param_read_file = NULL;
	char *param_prog = NULL;
	char *param_port = NULL;
	char *param_speed = NULL;
	char *param_type = NULL;
	char *param_chip = NULL;
	uint16_t cmd = 0;

	struct picprog_t picprog;
	struct proto_ops_t *picops;
	struct pic_chip_t *picchip;
	struct pic_family_t *picfamily;


	printf("Pirate PIC Programer\n\n");

	cmd |= CMD_ERASE;
	param_chip=strdup("18F24J50");
	param_port=strdup("COM12");
	param_prog=strdup("buspirate");
	param_speed=strdup("115200");


	while ((opt = getopt(argc, argv, "ERWVr:w:evu:p:s:c:t:")) != -1) {
		switch (opt) {
			case 'R':
				cmd |= CMD_READ;
				break;
			case 'W':
				cmd |= CMD_WRITE;
				break;
			case 'E':
				cmd |= CMD_ERASE;
				break;
			case 'V':
				cmd |= CMD_VERIFY;
				break;
			case 'w':
				cmd |= CMD_WRITE;
				if (param_write_file != NULL) {
					printf("Multiple arguments !\n");
					exit(-1);
				}
				param_write_file = strdup(optarg);
				break;
			case 'r':
				cmd |= CMD_READ;
				if (param_read_file != NULL) {
					printf("Multiple arguments !\n");
					exit(-1);
				}
				param_read_file = strdup(optarg);
				//printf("%s\n", param_read_file);
				break;
			case 't':
				if (param_type != NULL) {
					printf("Multiple arguments !\n");
					exit(-1);
				}
				param_type = strdup(optarg);
				break;
			case 'c':
				if (param_chip != NULL) {
					printf("Multiple arguments !\n");
					exit(-1);
				}
				param_chip = strdup(optarg);
				break;
			case 'u':
				if (param_port != NULL) {
					printf("Multiple arguments !\n");
					exit(-1);
				}
				param_port = strdup(optarg);
				break;
			case 'p':
				if (param_prog != NULL) {
					printf("Multiple arguments !\n");
					exit(-1);
				}
				param_prog = strdup(optarg);
				//printf("interface: %s\n", param_prog);
				break;
			case 's':
				if (param_speed != NULL) {
					printf("Multiple arguments !\n");
					exit(-1);
				}
				param_speed = strdup(optarg);
				break;
			default:
				printf("Invalid argument %c", opt);
				print_usage(argv[0]);
				exit(-1);
				break;
		}
	}

/*	if (optind >= argc) {
		print_usage(argv[0]);
		exit(-1);
	}
*/
	picprog.iface = Iface_GetByName(param_prog);

	if (picprog.iface == NULL) {
		printf("Unknown interface '%s' !\n", param_prog);
		return -1;
	}

	printf("Initializing interface \n");

	picprog.iface->Init(&picprog, param_port, param_speed);
    picprog.iface->MCLRLow(&picprog);

	picprog.chip_idx = PIC_GetChipIdx(param_chip);
	if (picprog.chip_idx == -1) {
		printf("Unknown chip '%s' !\n", param_chip);
		return -1;
	}
	printf("Found chip ! index = %d\n", picprog.chip_idx);

	picops = PIC_GetProtoOps(picprog.chip_idx);
	picchip = PIC_GetChip(picprog.chip_idx);
	picfamily = PIC_GetFamily(picchip->family);



	buf_read = (uint8_t*)malloc(picchip->flash);
	buf_write = (uint8_t*)malloc(picchip->flash);

	if ((buf_read == NULL) || (buf_write == NULL)) {
		printf("Error allocating %ld bytes of memory\n", (long)picchip->flash);
		return -1;
	}

	memset(buf_read, PIC_EMPTY, picchip->flash);
	memset(buf_write, PIC_EMPTY, picchip->flash);

// prepare data file
	if ((cmd & CMD_WRITE) || (cmd & CMD_VERIFY)) {

		if (param_write_file == NULL) {
			printf("No write file specified\n");
			return -1;
		}
		if (strcasecmp(param_type, "HEX")==0) {
			printf("Reading HEX file '%s' ... ", param_write_file);
			read_size = HEX_ReadFile(param_write_file, buf_write, picchip->flash);
		} else if (strcasecmp(param_type, "BIN")==0) {
			printf("Reading BIN file '%s' ... ", param_write_file);
			read_size = BIN_ReadFile(param_write_file, buf_write, picchip->flash);
		} else {
			printf("You need to specify file type! \n");
			return -1;
		}

		if (read_size == 0) {
			printf("Error!\n");
			return -1;
		}
		printf("Read binary size = %ld\n", (long int)read_size);
	}

// execute commands
	if (cmd & CMD_READ) {
		picops->Read(&picprog, 0x0000, buf_read, picchip->flash);

		if (param_read_file == NULL) {
			printf("No read file specified\n");
			return -1;
		}
		if (strcasecmp(param_type, "HEX")==0) {
			printf("Writing HEX file '%s' ... ", param_read_file);
			HEX_WriteFile(param_read_file, buf_read, picchip->flash);
			printf("done!\n");
		} else if (strcasecmp(param_type, "BIN")==0) {
			printf("Writing BIN file '%s' ... ", param_read_file);
			BIN_WriteFile(param_read_file, buf_read, picchip->flash);
			printf("done!\n");
		} else {
			printf("No output filetype specified\n");
			return -1;
		}
	}

	if (cmd & CMD_ERASE) {
		picops->Erase(&picprog);
	}

	if (cmd & CMD_WRITE) {
		picops->Write(&picprog, 0x0000, buf_write, picchip->flash);
	}

	if (cmd & CMD_VERIFY) {
		if (cmd & CMD_READ == 0) { // read only when necessary
			picops->Read(&picprog, 0x0000, buf_read, picchip->flash);
		}
		if (memcmp(buf_read, buf_write, picchip->flash)) {
			printf("Verify ERROR :( \n");
		} else {
			printf("Verify OK :) !\n");
		}
	}

	free(buf_write);
	free(buf_read);

#define FREE(x) if(x) free(x);
	FREE(param_write_file);
	FREE(param_read_file);
	FREE(param_prog);
	FREE(param_port);
	FREE(param_speed);
	FREE(param_type);
	FREE(param_chip);

	return 0;
}

