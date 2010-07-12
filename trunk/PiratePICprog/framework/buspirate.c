#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
//#include "common.h"
#include "serial.h"
#include "buspirate.h"

//low lever send command, get reply function
static uint32_t BP_WriteToPirate(int fd, uint8_t* val) {
	int res = -1;
	uint8_t ret = 0;
	
	serial_write(fd, val, 1);
	res = serial_read(fd, &ret, 1);

	if( ret != '\x01') {
		printf("ERROR");
		return -1;
	} 
	return 0;
}

static void BP_EnableRaw2Wire(int fd)
{
	int ret;
	char tmp[100] = { [0 ... 20] = 0x00 };
	int done = 0;
	int cmd_sent = 0;
	int tries=0;
	
	printf("Entering binary mode\n");

	/* reads 1 to n "BBIO1"s and one "OCD1" */
	while (!done) {
		tmp[0]=0x00;
		serial_write(fd, tmp, 1);
		tries++;
		usleep(10);
		ret = serial_read(fd, tmp, 5);
		if (ret != 5 && tries>20) {
			fprintf(stderr, "Buspirate did not respond correctly :( %i \n", ret );
			exit(-1);
		}else if (strncmp(tmp, "BBIO1", 5) == 0) {
			done=1;
		}
	}

	done=0;
	tmp[0] = '\x05';
	serial_write(fd, tmp, 1);
	tries++;
	usleep(10);
	ret = serial_read(fd, tmp, 4);

	if ( (ret==4) && (strncmp(tmp, "RAW1", 4) == 0)) {

	}else{
		fprintf(stderr, "Buspirate did not respond correctly :( %i \n", ret );
		exit(-1);
	}

}

static int BP_SetPicMode(int fd, enum BP_picmode_t mode) {
	uint8_t m = mode;
	serial_write(fd, "\xA0", 1);
	
	if(BP_WriteToPirate(fd, &m)){
		puts("ERROR");
		return -1;
	}
	return 0;
}

uint32_t BP_Init(void *pBP, char *port, char *speed) {
	int fd;

	fd = serial_open(port);
	if (fd < 0) {
		fprintf(stderr, "BP: Error openning serial port\n");
		return -1;
	}

	serial_setup(fd, B115200);
	BP_EnableRaw2Wire(fd);

	//setup output pin type (normal)
	printf("BP: Setup mode...\n");
	if (BP_WriteToPirate(fd, "\x8A")){
		fprintf(stderr, "ERROR");
		return -1;
	} 

	//high speed mode
	if (BP_WriteToPirate(fd, "\x63")) {
		fprintf(stderr, "ERROR");
		return -1;
	} 

	//setup power supply, AUX pin, pullups
	printf("Setup peripherals...\n");
	if (BP_WriteToPirate(fd, "\x4F")){
		puts("ERROR");
		return -1;
	} 
	printf("(OK) \n");

	((struct BP_t *)pBP)->fd = fd;
	return 0;
}

uint32_t BP_SetBitOrder(void *pBP, uint8_t lsb) {
	int fd = ((struct BP_t *)pBP)->fd;
	if(BP_WriteToPirate(fd, (lsb==1)?"\x8A":"\x88")){
		printf("Set bit order (%s)...ERROR", (lsb==1)?"LSB":"MSB");
		return -1;
	} 
	return 0;
}

//binmode: bulk write bytes to bus command
uint32_t BP_BulkByteWrite(void *pBP, uint8_t bwrite, uint8_t* val) {
	int fd = ((struct BP_t *)pBP)->fd;
	int i;
	uint8_t opcode = 0x10;
	opcode |= (bwrite - 1);

	BP_WriteToPirate(fd, &opcode);
	for (i = 0; i < bwrite; i++){
		BP_WriteToPirate(fd, &val[i]);	
	}
}

uint32_t BP_BulkBitWrite(void *pBP, uint8_t bit_count, uint8_t val) {
	int fd = ((struct BP_t *)pBP)->fd;
	int i;
	uint8_t opcode = 0x30;

	opcode |= (bit_count - 1);

	BP_WriteToPirate(fd, &opcode);
	serial_write(fd, &val, 1);
	return 0;
}

uint32_t BP_DataLow(void *pBP) {
	int fd = ((struct BP_t *)pBP)->fd;
	return BP_WriteToPirate(fd, "\x0C");
}

uint32_t BP_DataHigh(void *pBP) {
	int fd = ((struct BP_t *)pBP)->fd;
	return BP_WriteToPirate(fd, "\x0D");
}

uint32_t BP_ClockLow(void *pBP) {
	int fd = ((struct BP_t *)pBP)->fd;
	return BP_WriteToPirate(fd, "\x0A");
}

uint32_t BP_ClockHigh(void *pBP) {
	int fd = ((struct BP_t *)pBP)->fd;
	return BP_WriteToPirate(fd, "\x0B");
}

uint32_t BP_MCLRLow(void *pBP) {
	int fd = ((struct BP_t *)pBP)->fd;
	return BP_WriteToPirate(fd, "\x04");
}

uint32_t BP_MCLRHigh(void *pBP) {
	int fd = ((struct BP_t *)pBP)->fd;
	return BP_WriteToPirate(fd, "\x05");
}

uint32_t BP_PIC416Write(void *pBP, uint8_t cmd, uint16_t data) {
	int fd = ((struct BP_t *)pBP)->fd;
	enum BP_picmode_t mode = ((struct BP_t*)pBP)->picmode;
	uint8_t buffer[4] = {0};
	int res = -1;

	if (mode != BP_PIC416)
		BP_SetPicMode(fd, BP_PIC416);

	buffer[0] = '\xA4';
	buffer[1] = cmd;
	buffer[2] = (uint8_t)(data);
	buffer[3] = data >> 8;

	
	serial_write(fd, buffer, 4);
	res = serial_read(fd, buffer, 1);
	if (buffer[0] != '\x01') {
		puts("ERROR");
		return -1;
	} 
	return 0;
}

uint32_t BP_PIC416Read(void *pBP, uint8_t cmd) {
	int fd = ((struct BP_t *)pBP)->fd;
	enum BP_picmode_t mode = ((struct BP_t*)pBP)->picmode;
	uint8_t buffer[2] = {0};
	int res = -1;
	
	if (mode != BP_PIC416)
		BP_SetPicMode(fd, BP_PIC416);

	buffer[0] = '\xA5';
	buffer[1] = cmd;

	serial_write(fd, buffer, 2);
	res = serial_read(fd, buffer, 1);
	
	return buffer[0];
}

uint32_t BP_PIC424Read(void *pBP) {
	int fd = ((struct BP_t *)pBP)->fd;
	enum BP_picmode_t mode = ((struct BP_t*)pBP)->picmode;
	uint8_t buffer[4] = {0};
	int res = -1;
	
	if (mode != BP_PIC424)
		BP_SetPicMode(fd, BP_PIC424);

	serial_write(fd, "\xA5", 1);
	res = serial_read(fd, buffer, 2);
	
	//read device ID, two bytes takes 2 read operations, each gets a byte
	return buffer[0] | buffer[1] << 8;	//upper 8 bits
}

uint32_t BP_PIC424Write(void *pBP, uint32_t data, uint8_t prenop, uint8_t postnop) {
	int fd = ((struct BP_t *)pBP)->fd;
	enum BP_picmode_t mode = ((struct BP_t*)pBP)->picmode;
	uint8_t buffer[5] = {0};
	int res = -1;
				printf("\n here!!! \n");
	if (mode != BP_PIC424)
		BP_SetPicMode(fd, BP_PIC424);

	buffer[0] = '\xA4';
	buffer[1] = (uint8_t)(data);
	buffer[2] = data >> 8;
	buffer[3] = data >> 16;
	buffer[4] = ((prenop << 4) | (postnop & 0x0F));

	
	serial_write(fd, buffer, 5);
	res = serial_read(fd, buffer, 1);
	if (buffer[0] != '\x01') {
		puts("ERROR");
		return -1;
	} 
	return 0;
}

