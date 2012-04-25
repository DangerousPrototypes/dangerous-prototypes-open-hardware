#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include "debug.h"
#include "serial.h"
#include "buspirate.h"

#define BWCMD_PERSET_PWR 0b00001000
#define BWCMD_PERSET_PU  0b00000100
#define BWCMD_PERSET_AUX 0b00000010
#define BWCMD_PERSET_CS  0b00000001

extern int disable_comport;

struct BP_t *pBP;

static uint8_t BP_reversebyte(uint8_t c);
static uint32_t BP_Flush();

static void BP_BufferReset()
{
	pBP->buf[0] = '\xA7';
	pBP->buf[1] = 0;
	pBP->buf[2] = 0;
	pBP->bufcnt = 3;
}

//low lever send command, get reply function
static uint32_t BP_WriteToPirate(int fd, char * val)
{
	int res = -1;
	char ret = 0;

	dbg_verbose("val = %02x\n", ((uint8_t)*val));
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

static uint32_t BP_VccHigh()
{
	dbg_info("\n");
	pBP->per |= BWCMD_PERSET_PWR;
	return BP_WriteToPirate(pBP->fd, &pBP->per);
}

static uint32_t BP_VccLow()
{
	dbg_info("\n");
	pBP->per &= ~BWCMD_PERSET_PWR;
	return BP_WriteToPirate(pBP->fd, &pBP->per);
}

static uint32_t BP_MCLRLow()
{
	dbg_info("\n");
	pBP->per &= ~BWCMD_PERSET_CS;
	return BP_WriteToPirate(pBP->fd, &pBP->per);
}

static uint32_t BP_MCLRHigh()
{
	dbg_info("\n");
	pBP->per |= BWCMD_PERSET_CS;
	return BP_WriteToPirate(pBP->fd, &pBP->per);
}

static uint32_t BP_VPPHigh()
{
	dbg_info("\n");
	pBP->per |= BWCMD_PERSET_AUX;
	return BP_WriteToPirate(pBP->fd, &pBP->per);
}

static uint32_t BP_VPPLow()
{
	dbg_info("\n");
	pBP->per &= ~BWCMD_PERSET_AUX;
	return BP_WriteToPirate(pBP->fd, &pBP->per);
}

static uint32_t BP_Init(struct picprog_t *p, char *port, char *speed)
{
	int fd;

	printf("%s\n", speed);
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
		if (BP_WriteToPirate(fd, "\x40")){
			puts("ERROR");
			return -1;
		}
	}	else {
	  printf("bypassing port\n");
	}
	printf("(OK) \n");

	pBP = safe_malloc(sizeof(struct BP_t));
	pBP->fd = fd;
	pBP->per = 0x40; // peripheral command

	BP_BufferReset();
	p->iface_data = pBP;


	return 0;
}

static uint32_t BP_Deinit(struct picprog_t *p)
{
	struct BP_t *pBP = p->iface_data;
	int fd = pBP->fd;
	char tmp[6];
	int ret;

	dbg_info("\n");

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
	
	dbg_info("lsb = %02x\n", lsb);

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

	dbg_info("bwrite = %02x, val = %02x\n", bwrite, *val);
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

	dbg_info("bit_count = %02x, val = %02x\n", bit_count, val);
	opcode |= (bit_count - 1);

	BP_WriteToPirate(fd, &opcode);
	//serial_write(fd, &val, 1);
	BP_WriteToPirate(fd, &val);

	return 0;
}

static uint32_t BP_DataLow()
{
	int fd = pBP->fd;
	dbg_info("\n");
	return BP_WriteToPirate(fd, "\x0C");
}

static uint32_t BP_DataHigh()
{
	int fd = pBP->fd;
	dbg_info("\n");
	return BP_WriteToPirate(fd, "\x0D");
}

static uint32_t BP_ClockLow()
{
	int fd = pBP->fd;
	dbg_info("\n");
	return BP_WriteToPirate(fd, "\x0A");
}

static uint32_t BP_ClockHigh()
{
	int fd = pBP->fd;
	dbg_info("\n");
	return BP_WriteToPirate(fd, "\x0B");
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

	dbg_info("mode = %02x\n", mode);

	serial_write(fd, "\xA0", 1);

	if (BP_WriteToPirate(fd, &m)) {
		puts("ERROR");
		return -1;
	}

	pBP->picmode = mode;

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

static uint32_t BP_PIC614Read(uint8_t cmd, void *Data, uint32_t length)
{
	int fd = pBP->fd;
	uint32_t i;

	BP_SetPicMode(BP_PIC614);

	for (i = 0; i < length; i++) {
		pBP->buf[2]++; // increase read command counter
		pBP->buf[pBP->bufcnt] = 2; // read command
		pBP->bufcnt++;
		pBP->buf[pBP->bufcnt] = cmd;
		pBP->bufcnt++;
	}

	dbg_info("read cmd = 0x%02x length = 0x%08x\n", cmd, length);

	return 0;
}

static uint32_t BP_PIC614Write(uint8_t cmd, uint16_t data)
{
	int fd = pBP->fd;

	BP_SetPicMode(BP_PIC614);

	dbg_info("cmd = 0x%02x, data = 0x%04x\n", cmd, data);

	pBP->buf[1] ++; // increase write command counter
	pBP->buf[pBP->bufcnt] = 1; // write command
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = cmd;
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = BP_reversebyte((uint8_t)(data));
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = BP_reversebyte((uint8_t)(data >> 8));
	pBP->bufcnt++;

	return 0;
}

static uint32_t BP_PIC416Read(uint8_t cmd, void *Data, uint32_t length)
{
	int fd = pBP->fd;
	uint32_t i;

	BP_SetPicMode(BP_PIC416);

	for (i = 0; i < length; i++) {
		pBP->buf[2]++; // increase read command counter
		pBP->buf[pBP->bufcnt] = 2; // read command
		pBP->bufcnt++;
		pBP->buf[pBP->bufcnt] = cmd;
		pBP->bufcnt++;
	}

	dbg_info("read cmd = 0x%02x length = 0x%08x\n", cmd, length);

	return 0;
}

static uint32_t BP_PIC416Write(uint8_t cmd, uint16_t data)
{
	int fd = pBP->fd;

	BP_SetPicMode(BP_PIC416);

	dbg_info("cmd = 0x%02x, data = 0x%04x\n", cmd, data);

	pBP->buf[1] ++; // increase write command counter
	pBP->buf[pBP->bufcnt] = 1; // write command
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = cmd;
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = BP_reversebyte((uint8_t)(data));
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = BP_reversebyte((uint8_t)(data >> 8));
	pBP->bufcnt++;

	return 0;
}

static uint32_t BP_PIC424Read(uint32_t cmd, void *Data, uint32_t length)
{
	int fd = pBP->fd;
	uint32_t i;

	BP_SetPicMode(BP_PIC424);

	dbg_info("\n");

	for (i = 0; i < length; i++) {
		pBP->buf[2]++; // increase read command counter
		pBP->buf[pBP->bufcnt] = 2; // read command
		pBP->bufcnt++;
	}

	return 0;
}

static uint32_t BP_PIC424Write(uint32_t data, uint8_t prenop, uint8_t postnop)
{
	int fd = pBP->fd;

	BP_SetPicMode(BP_PIC424);

	dbg_info("data = 0x%08x, prenop = 0x%02x, postnop = 0x%02x\n", data, prenop, postnop);

	pBP->buf[1] ++; // increase write command counter
	pBP->buf[pBP->bufcnt] = 1; // write command
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = BP_reversebyte((uint8_t)(data));
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = BP_reversebyte((uint8_t)(data >> 8));
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = BP_reversebyte((uint8_t)(data >> 16));
	pBP->bufcnt++;
	pBP->buf[pBP->bufcnt] = ((prenop << 4) | (postnop & 0x0F));
	pBP->bufcnt++;

	return 0;
}

static uint32_t BP_GetData(uint8_t *data, uint32_t len)
{
	int fd = pBP->fd;
	int res = -1;

	if (pBP->picmode == BP_PIC424) {
		if (pBP->buf[2] * 2 != len) {
			dbg_info("len != expected len\n");
		}
	} else if (pBP->picmode == BP_PIC416) {
		if (pBP->buf[2] != len) {
			dbg_info("len != expected len\n");
		}
	} else if (pBP->picmode == BP_PIC614) {
		if (pBP->buf[2] * 2 != len) {
			dbg_info("len != expected len\n");
		}
	}

	dbg_info("length = 0x%08x\n", len);

	BP_Flush();
	res = serial_read(fd, data, len);

	//swap bit order
	BPdr(data, len);

	dbg_buf_info(data, len);
}

static uint32_t BP_Flush()
{
	int fd = pBP->fd;
	char buffer[1] = {0x0f};
	int res = -1;

	dbg_info("bufcnt = %d\n", pBP->bufcnt);

	if (pBP->bufcnt <= 3) {
		return 0;
	}

	dbg_info("Flushing...\n");
	serial_write(fd, pBP->buf, pBP->bufcnt);
	res = serial_read(fd, buffer, 1);
	if (buffer[0] != '\x01') {
		printf("ERROR: 0x%02X\n", buffer[0]);
		return -1;
	}

	BP_BufferReset();

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
	.PIC614Read = BP_PIC614Read,
	.PIC614Write = BP_PIC614Write,
	.PIC416Read = BP_PIC416Read,
	.PIC416Write = BP_PIC416Write,
	.PIC424Read = BP_PIC424Read,
	.PIC424Write = BP_PIC424Write,
	.GetData = BP_GetData,
	.flush=BP_Flush,
	.VPPHigh = BP_VPPHigh,
	.VPPLow = BP_VPPLow,
	.VCCHigh = BP_VccHigh,
	.VCCLow = BP_VccLow,
};
