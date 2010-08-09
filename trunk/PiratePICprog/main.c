/*
 * PUMP flash loader
 *
 * 2010 - Michal Demin
 *
 * Loosely based on Pirate-Loader:
 * http://the-bus-pirate.googlecode.com/svn/trunk/bootloader-v4/pirate-loader/source/pirate-loader.c
 *
 */
//#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pic.h"
#include "proto_pic.h"
#include "data_file.h"
#include "iface.h"
#include "common.h"
#include "buspirate.h"

int verbose = 0;
int disable_comport = 0;   //1 to say yes, disable comport, any value to enable port default is 0 meaning port is enable.
enum {
	CMD_READ = 1,
	CMD_WRITE = 2,
	CMD_ERASE = 4,
	CMD_VERIFY = 8
};


void print_usage(char* name) {
        printf("Pirate Pic Programmer v0.2\n");
        printf("USAGE: \n");
        printf(" %s -p PROG -u PORT -s SPEED -c CHIP -t TYPE -w | -r FILE  -E | -W | -R | -V \n" ,name);

        printf(" %s -h \n\n" ,name);

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
		printf("-h  - this help usage\n");
		printf("\n\n");
		printf("Example usage: %s -p buspirate -u COM12 -s 115200 -c 18F2550 -t HEX  -r test.hex  -E\n",name);
        printf("               %s -p buspirate -u COM12 -s 115200 -c 18F2550 -V\n",name);
        printf("               %s -h\n",name);

}

int main(int argc, char** argv) {

	int opt;
//	int	res = -1;
	uint32_t i;
    uint16_t PICidver, PICrev, PICid;

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


	printf("(Bus) Pirate PIC Programer v0.2 \n\n");

#ifdef DEBUG
	cmd |= CMD_ERASE;
	cmd|=CMD_WRITE;
    cmd|=CMD_VERIFY;
    //cmd|=CMD_READ;
	param_chip=strdup("18F2550");
	param_port=strdup("COM12");
	param_prog=strdup("buspirate");
	param_speed=strdup("115200");
    param_read_file=strdup("dump-18F2550.hex");
	param_write_file=strdup("test-18F2550.hex");
	param_type=strdup("HEX");
#else
// added routine to trap no arguments
	if (argc <= 1)  {
	    printf("ERROR: Invalid argument(s).\n\n");
	    printf("Help Menu\n");
		print_usage(argv[0]);
		exit(-1);
	}
	#endif

	while ((opt = getopt(argc, argv, "ERWVr:w:evu:xp:s:c:t:")) != -1) {
       // printf("%c  \n",opt);
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
			//	printf("param_write_file: %s \n",param_write_file);
				break;
			case 'r':
				cmd |= CMD_READ;
				if (param_read_file != NULL) {
					printf("Multiple arguments !\n");
					exit(-1);
				}
				param_read_file = strdup(optarg);
			//	printf("param_read_file: %s\n", param_read_file);
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
			case 'x':      //disable comport
				disable_comport = 1;   //cheat so that I do not disturb the struct
				param_speed=strdup("115200"); //dummy
				param_port=strdup("COM12");    //dummy
				break;

			default:
				printf("Invalid argument %c", opt);
				print_usage(argv[0]);
				exit(-1);
				break;
		}
	}
/*   routine not needed.. error should be catch  before not after, moved to top
	if (opt == -1) {
	    printf("ERROR: Invalid argument(s).\n\n");
	    printf("Help Menu\n");
		print_usage(argv[0]);
		exit(-1);
	}
*/
 //   printf("param prog %s\n",param_prog);

	// catch content of param_prog, should not be null
	if (param_prog==NULL)
	{
	    printf("Name of Interface is required: eg.  -p buspirate\n");
	    exit(-1);

	}
	picprog.iface = Iface_GetByName(param_prog);

	if (picprog.iface == NULL) {
		printf("Unknown interface '%s' !\n", param_prog);
		return -1;
	}

	printf("Initializing interface \n");


    if (param_speed !=NULL && param_port !=NULL)     //added to check if port is null to avoid crash
    {
       if(picprog.iface->Init(&picprog, param_port, param_speed)){
            printf("ERROR: interface not responding \n");
            exit(-1);
       }
    }
    else {
        printf("ERROR: Port name or port speed not specified \n");
        printf("parameter -u and  -s must be specified: e.g -u com12 -s 115200\n");
        exit(-1);
    }
    if (param_chip==NULL)
    {
        printf("Chip type not specified: e.g -c 18F2550\n");
        exit(-1);
    }

	picprog.chip_idx = PIC_GetChipIdx(param_chip);
	if (picprog.chip_idx == -1) {
		printf("'%s' not in programming database :( \n", param_chip);
		return -1;
	}
	printf("Found '%s' in programming database :) index = %d\n", param_chip, picprog.chip_idx);

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


//check chip
    printf("Checking for %s attached to programmer... \n", param_chip);
    PICidver=picops->ReadID(&picprog, &PICid, &PICrev);
//determine device type
//if comport is disable make PICid=picchip->ID
if (disable_comport != 0)
{
    PICid=picchip->ID;
}

	if(PICid!=picchip->ID)
	{
	    printf("\nWrong device: %#X (ID: %#X REV: %#X) \n", PICidver, PICid, PICrev);
 	    return -1;
	}
    printf ("Found %s (%#X, ID: %#X REV: %#X) \n", picchip->name, PICidver, PICid, PICrev);


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
		//picops->Read(&picprog, 0x0000, buf_read, picchip->flash);
        picops->ReadFlash(&picprog, buf_read);
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
        printf("Erasing chip... ");
		picops->Erase(&picprog);
		printf("OK :) \n");
	}

	if (cmd & CMD_WRITE) {
		//picops->Write(&picprog, 0x0000, buf_write, picchip->flash);
		picops->WriteFlash(&picprog, buf_write);
	}

	if (cmd & CMD_VERIFY) {
		//if (cmd & CMD_READ == 0) { // read only when necessary
			picops->ReadFlash(&picprog, buf_read);
		//}
		if (memcmp(buf_read, buf_write, picchip->flash)) {
			printf("Verify ERROR :( \n");
		} else {
			printf("Verify OK :) !\n");
		}

        for(i=0; i<picchip->flash; i++){
            if(buf_read[i]!=buf_write[i]){
                printf("Verify ERROR %#X :%#X %#X \n",i, buf_read[i], buf_write[i]);
            }/*else{
                printf("Verify OK %#X :%#X %#X \n",i, buf_read[i], buf_write[i]);
            }*/
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

