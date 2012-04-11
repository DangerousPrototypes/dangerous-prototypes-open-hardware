#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include "serial.h"
#include "buspirate.h"

extern int disable_comport;

struct BP_t *pBP;

static uint8_t BP_reversebyte(uint8_t c);
static uint32_t BP_Flush();

//low lever send command, get reply function
static uint32_t BP_WriteToPirate(int fd, char * val)
{
	int res = -1;
	char ret = 0;

	if (disable_comport== 1)
		return 0;

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
	char tmp[21] = { [0 ... 20] = 0x00 };
	int done = 0;
	int cmd_sent = 0;
	
	printf("Entering binary mode");
	serial_write(fd, tmp, 20);
	usleep(10000);
	
	/* reads 1 to n "BBIO1"s and one "OCD1" */
	while (!done) {
		ret = serial_read(fd, tmp, 4);
		if (ret != 4) {
			fprintf(stderr, "Buspirate did not respond correctly :(");
			exit(-1);
		}
		if (strncmp(tmp, "BBIO", 4) == 0) {
			ret = serial_read(fd, tmp, 1);
			if (ret != 1) {
				fprintf(stderr, "Buspirate did not respond well :( restart everything");
				exit(-1);
			}
			if (tmp[0] != '1') {
				fprintf(stderr, "Unsupported binary protocol ");
				exit(-1);
			}
			if (cmd_sent == 0) {
				cmd_sent = 1;
				tmp[0] = '\x05';
				ret = serial_write(fd, tmp, 1);
			}
		} else if (strncmp(tmp, "RAW1", 4) == 0) {
			done = 1;
		} else {
			fprintf(stderr, "Buspirate did not respond correctly :((");
			exit(-1);
		}
	}
}

static uint32_t BP_MCLRLow()
{
	int fd = pBP->fd;
	return BP_WriteToPirate(fd, "\x04");
}

static uint32_t BP_VPPHigh()
{
	int fd = pBP->fd;
	return BP_WriteToPirate(fd, "\x4B");
}

static uint32_t BP_VPPLow()
{
	int fd = pBP->fd;
	return BP_WriteToPirate(fd, "\x49");
}

static uint32_t BP_Init(struct picprog_t *p, char *port, char *speed)
{
	int fd;
	printf("%s\n",speed);
	fd = serial_open(port);

	if (disable_comport !=1)
	{

		if (fd < 0) {
			fprintf(stderr, "BP: Error openning serial port\n");
			return -1;
		}

		serial_setup(fd, B115200);
		BP_EnableRaw2Wire(fd);

		//setup output pin type (normal)
		printf("BP: Setup mode...\n");
		if (BP_WriteToPirate(fd, "\x88")){
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
	}	else {
	  printf("bypassing port\n");
	}
	printf("(OK) \n");

	pBP = safe_malloc(sizeof(struct BP_t));
	pBP->fd = fd;
	pBP->bufcnt=2; //start the buffer at position 2, after the command and length
	p->iface_data = pBP;


	return 0;
}

static uint32_t BP_Deinit(struct picprog_t *p)
{
	struct BP_t *pBP = p->iface_data;
	int fd = pBP->fd;
	char tmp[6];
	int ret;

	tmp[0] = 0x00;
	serial_write(fd, tmp, 1);

	ret = serial_read(fd, tmp, 5);
	if (strncmp(tmp, "BBIO1", 5) == 0) {
		tmp[0] = 0x0F; /*  reset BP */
		serial_write(fd, tmp, 1);
	} else
		printf("Bad reply :( Please restart manually");

	serial_close(fd);

	free(pBP);
	p->iface_data = NULL;

	return 0;
}

static uint32_t BP_SetBitOrder(uint8_t lsb)
{
	int fd = pBP->fd;
	if (BP_WriteToPirate(fd, (lsb==1)?"\x8A":"\x88")) {
		printf("Set bit order (%s)...ERROR", (lsb==1)?"LSB":"MSB");
		return -1;
	}
	return 0;
}

//binmode: bulk write bytes to bus command
static uint32_t BP_BulkByteWrite(uint8_t bwrite, char* val)
{
	int fd = pBP->fd;
	int i;
	char opcode = 0x10;
	opcode |= (bwrite - 1);

	BP_WriteToPirate(fd, &opcode);
	for (i = 0; i < bwrite; i++) {
		BP_WriteToPirate(fd, &val[i]);
	}

	return 0;
}

static uint32_t BP_BulkBitWrite(uint8_t bit_count, char val)
{
	int fd = pBP->fd;
	char opcode = 0x30;

	opcode |= (bit_count - 1);

	BP_WriteToPirate(fd, &opcode);
	//serial_write(fd, &val, 1);
	BP_WriteToPirate(fd, &val);
	return 0;
}

static uint32_t BP_DataLow()
{
	int fd = pBP->fd;
	return BP_WriteToPirate(fd, "\x0C");
}

static uint32_t BP_DataHigh()
{
	int fd = pBP->fd;
	return BP_WriteToPirate(fd, "\x0D");
}

static uint32_t BP_ClockLow()
{
	int fd = pBP->fd;
	return BP_WriteToPirate(fd, "\x0A");
}

static uint32_t BP_ClockHigh()
{
	int fd = pBP->fd;
	return BP_WriteToPirate(fd, "\x0B");
}

static uint32_t BP_MCLRHigh()
{
	int fd = pBP->fd;
	return BP_WriteToPirate(fd, "\x05");
}

static uint8_t BP_reversebyte(uint8_t c)
{
	uint8_t r, i;

	for (i = 0x1; i != 0; i = i << 1) {
		r = r << 1;
		if (c & i)
			r |= 0x1;
	}
	return r;
}

static int BP_SetPicMode(enum BP_picmode_t mode)
{
	int fd = pBP->fd;
	char m = mode;

	if (pBP->picmode == mode) {
		return 0;
	}

	serial_write(fd, "\xA0", 1);

	if (BP_WriteToPirate(fd, &m)) {
		puts("ERROR");
		return -1;
	}
	return 0;
}

static uint32_t BP_PIC416Write(uint8_t cmd, uint16_t data)
{
	int fd = pBP->fd;
	//uint8_t buffer[4] = {0};
	//int res = -1;

	BP_SetPicMode(BP_PIC416);

//	buffer[0] = '\xA4';
//	buffer[1] = cmd;
//	buffer[2] = BP_reversebyte((uint8_t)(data));
//	buffer[3] = BP_reversebyte((uint8_t)(data >> 8));

	pBP->buf[0] = '\xA4';
	pBP->buf[pBP->bufcnt] = cmd;
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = BP_reversebyte((uint8_t)(data));
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = BP_reversebyte((uint8_t)(data >> 8));
	pBP->bufcnt++;

	pBP->buf[1]=((pBP->bufcnt-2)/3);

	if (pBP->bufcnt>(3*100)) {
		return BP_Flush(pBP);
	}

/*	serial_write(fd, buffer, 4);
	res = serial_read(fd, buffer, 1);
	if (buffer[0] != '\x01') {
		puts("ERROR");
		return -1;
	}
	*/
	return 0;
}

static void BPdr(char *Data, uint32_t length)
{
	uint32_t i;
	//swap bit order
	for (i=0; i<length; i++) {
		Data[i]=BP_reversebyte((uint8_t)(Data[i]));
	}

}

static uint32_t BP_PIC416Read(uint8_t cmd, void *Data, uint32_t length)
{
	int fd = pBP->fd;
	char buffer[3] = {0};
	int res = -1;

	BP_SetPicMode(BP_PIC416);

	buffer[0] = '\xA5';
	buffer[1] = length;
	buffer[2] = cmd;

	serial_write(fd,  buffer, 3);
	res = serial_read(fd, Data, length);

	//swap bit order
	BPdr(Data, length);

	//return BP_reversebyte(buffer[0]);
	return 0;
}

static uint32_t BP_PIC424Read(uint32_t cmd, void *Data, uint32_t length)
{
	int fd = pBP->fd;
	char buffer[5] = {0};
	int res = -1;

	BP_SetPicMode(BP_PIC424);


	buffer[0]='\xA5';
	buffer[1]=length; //2;
	/*buffer[2]= BP_reversebyte((uint8_t)(cmd));
	buffer[3]= BP_reversebyte((uint8_t)(cmd >> 8));
	buffer[4]= BP_reversebyte((uint8_t)(cmd >> 16));*/
	serial_write(fd, buffer, 2);
	res = serial_read(fd, Data, (length*6));
	//res = serial_read(fd, buffer, 2);

	//swap bit order
	BPdr(Data, (length*6));

	return 0; //BP_reversebyte(buffer[0]) | BP_reversebyte(buffer[1]) << 8;	//upper 8 bits
}

static uint32_t BP_PIC424Write(uint32_t data, uint8_t prenop, uint8_t postnop)
{
	int fd = pBP->fd;
	//uint8_t buffer[5] = {0};
	//int res = -1;

	BP_SetPicMode(BP_PIC424);

//	buffer[0] = '\xA4';
//	buffer[1] = (uint8_t)(data);
//	buffer[2] = data >> 8;
//	buffer[3] = data >> 16;
//	buffer[4] = ((prenop << 4) | (postnop & 0x0F));

	pBP->buf[0] = '\xA4';
	pBP->buf[pBP->bufcnt] = BP_reversebyte((uint8_t)(data));
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = BP_reversebyte((uint8_t)(data >> 8));
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = BP_reversebyte((uint8_t)(data >> 16));
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = ((prenop << 4) | (postnop & 0x0F));
	pBP->bufcnt++;

	pBP->buf[1]=((pBP->bufcnt-2)/4);

	if (pBP->bufcnt>(4*100)) {
		return BP_Flush(pBP);
	}

//	serial_write(fd, buffer, 5);
//	res = serial_read(fd, buffer, 1);
//	if (buffer[0] != '\x01') {
//		puts("ERROR");
//		return -1;
//	}
	return 0;
}

static uint32_t BP_Flush()
{
	int fd = pBP->fd;
	char buffer[1] = {0};
	int res = -1;

	serial_write(fd, pBP->buf, pBP->bufcnt);
	res = serial_read(fd, buffer, 1);
	if (buffer[0] != '\x01') {
		printf("ERROR: %#X",buffer[0]);
		return -1;
	}
	pBP->bufcnt=2;//reset counter to data area

	return 0;
}

struct iface_t buspirate_iface = 
{
	.name = "buspirate",
	.Init = BP_Init,
	.Deinit = BP_Deinit,
	.DataLow = BP_DataLow,
	.DataHigh = BP_DataHigh,
	.ClockLow = BP_ClockLow,
	.ClockHigh = BP_ClockHigh,
	.MCLRLow = BP_MCLRLow,
	.MCLRHigh = BP_MCLRHigh,
	.SetBitOrder = BP_SetBitOrder,
	.SendBytes = BP_BulkByteWrite,
	.SendBits = BP_BulkBitWrite,
	.PIC416Read = BP_PIC416Read,
	.PIC416Write = BP_PIC416Write,
	.PIC424Read = BP_PIC424Read,
	.PIC424Write = BP_PIC424Write,
	.flush=BP_Flush,
	.VPPHigh = BP_VPPHigh,
	.VPPLow = BP_VPPLow,
};
