#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include "serial.h"
#include "buspirate.h"

static struct BP_t pBP;
static
uint8_t BP_reversebyte(uint8_t c);
static char bpbuf[4096];
static int bpbufcnt;
extern disable_comport;
//low lever send command, get reply function
static uint32_t BP_WriteToPirate(int fd, uint8_t* val) {
	int res = -1;
	uint8_t ret = 0;

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
	char tmp[100] = { [0 ... 20] = 0x00 };
	int done = 0;
	int cmd_sent = 0;
	int tries=0;

	printf("Entering binary mode\n");
    if (disable_comport==1) return;        //added to disable comport
	/* reads 1 to n "BBIO1"s and one "OCD1" */

	if (fd==-1)   //added because the fd has already returned null
	{
	    printf("Port does not exist!");
	    return;

	}
	while (!done) {
		tmp[0]=0x00;
		serial_write(fd, tmp, 1);
		tries++;
	//	printf("tries: %i Ret %i\n",tries,ret);
		usleep(10);
		ret = serial_read(fd, tmp, 5);
		if (ret != 5 && tries>20) {
			fprintf(stderr, "Buspirate did not respond correctly :( %i \n", ret );
			exit(-1);
		}else if (strncmp(tmp, "BBIO1", 5) == 0) {
			done=1;
		}
		if (tries>25){
		printf("Buspirate:Too many tries in serial read! -exiting \n - chip not detected, or not readable/writable\n");
		exit(-1);
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

uint32_t BP_MCLRLow(void *pBP) {
	int fd = ((struct BP_t *)pBP)->fd;
	return BP_WriteToPirate(fd, "\x04");
}

uint32_t BP_VPPHigh(void *pBP) {
	int fd = ((struct BP_t *)pBP)->fd;
	return BP_WriteToPirate(fd, "\x4B");
}

uint32_t BP_VPPLow(void *pBP) {
	int fd = ((struct BP_t *)pBP)->fd;
	return BP_WriteToPirate(fd, "\x49");
}

uint32_t BP_Init(void *p, char *port, char *speed) {
	int fd;
    printf("%s\n",speed);
	fd = serial_open(port);
	if (disable_comport !=1)
	{

	if (fd < 0) {
		fprintf(stderr, "BP: Error openning serial port\n");
		exit(-1);
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
}
	else
	{
	    printf("bypassing port\n");

	}
	printf("(OK) \n");
    pBP.fd=fd;
	((struct picprog_t *)p)->iface_data = &pBP;

	bpbufcnt=2; //start the buffer at position 2, after the command and length

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

	return 0;
}

uint32_t BP_BulkBitWrite(void *pBP, uint8_t bit_count, uint8_t val) {
	int fd = ((struct BP_t *)pBP)->fd;
	int i;
	uint8_t opcode = 0x30;

	opcode |= (bit_count - 1);

	BP_WriteToPirate(fd, &opcode);
	//serial_write(fd, &val, 1);
	BP_WriteToPirate(fd, &val);
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

uint32_t BP_MCLRHigh(void *pBP) {
	int fd = ((struct BP_t *)pBP)->fd;
	return BP_WriteToPirate(fd, "\x05");
}
uint8_t BP_reversebyte(uint8_t c){
        uint8_t r, i;

        for(i=0x1; i!=0; i=i<<1){
            r=r<<1;
            if(c&i)r|=0x1;
        }
        return r;
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
uint32_t BP_PIC416Write(void *pBP, uint8_t cmd, uint16_t data) {
	int fd = ((struct BP_t *)pBP)->fd;
	enum BP_picmode_t mode = ((struct BP_t*)pBP)->picmode;
	uint8_t buffer[4] = {0};
	int res = -1;

	if (mode != BP_PIC416){
        BP_SetPicMode(fd, BP_PIC416);
		((struct BP_t*)pBP)->picmode = BP_PIC416;
	}


//	buffer[0] = '\xA4';
//	buffer[1] = cmd;
//	buffer[2] = BP_reversebyte((uint8_t)(data));
//	buffer[3] = BP_reversebyte((uint8_t)(data >> 8));

	bpbuf[0] = '\xA4';
	bpbuf[bpbufcnt] = cmd;
	bpbufcnt++;
	bpbuf[bpbufcnt] = BP_reversebyte((uint8_t)(data));
	bpbufcnt++;
	bpbuf[bpbufcnt] = BP_reversebyte((uint8_t)(data >> 8));
	bpbufcnt++;

	bpbuf[1]=((bpbufcnt-2)/3);

	if(bpbufcnt>(3*100)){
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

void BPdr(char *Data, uint32_t length){
    uint32_t i;
	//swap bit order
	for(i=0; i<length; i++){
        Data[i]=BP_reversebyte((uint8_t)(Data[i]));
	}

}

uint32_t BP_PIC416Read(void *pBP, uint8_t cmd, void *Data, uint32_t length) {
	int fd = ((struct BP_t *)pBP)->fd;
	enum BP_picmode_t mode = ((struct BP_t*)pBP)->picmode;
	uint8_t buffer[3] = {0};
	int res = -1;

	if (mode != BP_PIC416){
        BP_SetPicMode(fd, BP_PIC416);
		((struct BP_t*)pBP)->picmode = BP_PIC416;
	}

	buffer[0] = '\xA5';
	buffer[1] = length;
	buffer[2] = cmd;

	serial_write(fd, buffer, 3);
	res = serial_read(fd, Data, length);

	//swap bit order
    BPdr(Data, length);

	//return BP_reversebyte(buffer[0]);
	return 0;
}



uint32_t BP_PIC424Read(void *pBP, uint32_t cmd, void *Data, uint32_t length) {
	int fd = ((struct BP_t *)pBP)->fd;
	enum BP_picmode_t mode = ((struct BP_t*)pBP)->picmode;
	uint8_t buffer[5] = {0};
	int res = -1;

	if (mode != BP_PIC424){
        BP_SetPicMode(fd, BP_PIC424);
		((struct BP_t*)pBP)->picmode = BP_PIC424;
	}


	buffer[0]='\xA5';
	buffer[1]=length/2;
	buffer[2]= BP_reversebyte((uint8_t)(cmd));
	buffer[3]= BP_reversebyte((uint8_t)(cmd >> 8));
    buffer[4]= BP_reversebyte((uint8_t)(cmd >> 16));
    serial_write(fd, buffer, 5);
    res = serial_read(fd, Data, length);
	//res = serial_read(fd, buffer, 2);

    //swap bit order
    BPdr(Data, length);

	return 0; //BP_reversebyte(buffer[0]) | BP_reversebyte(buffer[1]) << 8;	//upper 8 bits
}

uint32_t BP_PIC424Write(void *pBP, uint32_t data, uint8_t prenop, uint8_t postnop) {
	int fd = ((struct BP_t *)pBP)->fd;
	enum BP_picmode_t mode = ((struct BP_t*)pBP)->picmode;
	uint8_t buffer[5] = {0};
	int res = -1;

	if (mode != BP_PIC424){
        BP_SetPicMode(fd, BP_PIC424);
		((struct BP_t*)pBP)->picmode = BP_PIC424;
	}

//	buffer[0] = '\xA4';
//	buffer[1] = (uint8_t)(data);
//	buffer[2] = data >> 8;
//	buffer[3] = data >> 16;
//	buffer[4] = ((prenop << 4) | (postnop & 0x0F));

	bpbuf[0] = '\xA4';
	bpbuf[bpbufcnt] = BP_reversebyte((uint8_t)(data));
	bpbufcnt++;
	bpbuf[bpbufcnt] = BP_reversebyte((uint8_t)(data >> 8));
	bpbufcnt++;
    bpbuf[bpbufcnt] = BP_reversebyte((uint8_t)(data >> 16));
	bpbufcnt++;
    bpbuf[bpbufcnt] = ((prenop << 4) | (postnop & 0x0F));
	bpbufcnt++;

	bpbuf[1]=((bpbufcnt-2)/4);

	if(bpbufcnt>(4*100)){
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

uint32_t BP_Flush(void *pBP) {
	int fd = ((struct BP_t *)pBP)->fd;
	uint8_t buffer[1] = {0};
	int res = -1;

	serial_write(fd, bpbuf, bpbufcnt);
	res = serial_read(fd, buffer, 1);
	if (buffer[0] != '\x01') {
		printf("ERROR: %#X",buffer[0]);
		return -1;
	}
	bpbufcnt=2;//reset counter to data area

	return 0;
}
