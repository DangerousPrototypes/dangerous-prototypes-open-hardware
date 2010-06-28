

#include "serial.h"
#include "buspirate.h"

//low lever send command, get reply function
static uint32_t BP_writetopirate(int fd, uint8_t* val) {
	int res = -1;
	uint8_t ret = 0;
	
	serial_write(fd, 1, val);
	res = serial_read(fd, &ret, 1);

	if( ret != "\x01") {
		puts("ERROR");
		return -1;
	} 
	return 0;
}

uint32_t BP_SetBitOrder(void *data, uint8_t lsb) {
	int fd = &(int*) data;
	if(writetopirate(fd, (lsb==1)?"\x8A":"\x88")){
		puts("Set bit order (%s)...ERROR", (lsb==1)?"LSB":"MSB");
		return -1;
	} 
	return 0;
}

//binmode: bulk write bytes to bus command
uint32_t BP_BulkByteWrite(void *data, uint8_t bwrite, uint8_t* val) {
	int fd = &(int*) data;
	int i;
	uint8_t opcode = 0x10;
	opcode |= (bwrite - 1);

	writetopirate(fd, &opcode);
	for (i = 0; i < bwrite; i++){
		writetopirate(fd, &val[i]);	
	}
}

uint32_t BP_BulkBitWrite(void *data, uint8_t bit_count, uint8_t val) {
	int fd = &(int*) data;
	int i;
	uint8_t opcode = 0x30;
	opcode |= (bit_count - 1);

	writetopirate(fd, &opcode);
	serial_write(fd, 1, &val);
	return 0;
}

uint32_t BP_DataLow(void *data) {
	int fd = &(int*) data;
	return writetopirate("\x0C");
}

uint32_t BP_DataHigh(void *data) {
	int fd = &(int*) data;
	return writetopirate("\x0D");
}

uint32_t BP_ClockLow(void *data) {
	int fd = &(int*) data;
	return writetopirate("\x0A");
}

uint32_t BP_ClockHigh(void *data) {
	int fd = &(int*) data;
	return writetopirate("\x0B");
}

uint32_t BP_MCLRLow(void *data) {
	int fd = &(int*) data;
	return writetopirate("\x04");
}

uint32_t BP_MCLRHigh(void *data) {
	int fd = &(int*) data;
	return writetopirate("\x05");
}

uint32_t BP_PIC416Write(void *pdf, uint8_t cmd, uint16_t data) {
	int fd = &(int*) pdf;
	uint8_t buffer[4]={0};
	int res = -1;
	
	buffer[0]='\xA4';
	buffer[1]=cmd;
	buffer[2]=(uint8)(data);
	buffer[3]=(data>>8);

	
	serial_write(fd, 4, buffer);
	res = serial_read(fd, buffer, 1);
	if (buffer[0] != "\x01") {
		puts("ERROR");
		return -1;
	} 
	return 0;
}

uint32_t BP_PIC416Read(void *data, uint8_t cmd) {
	int fd = &(int*) data;
	uint8_t buffer[2]={0};
	int res = -1;
	
	buffer[0]='\xA5';
	buffer[1]=cmd;

	serial_write(fd, 2, buffer);
	res = serial_read(fd, buffer, 1);
	
	return buffer[0];
}

uint32_t BP_PIC424Read(void *data) {
	int fd = &(int*) data;
	uint8_t buffer[4]={0};
	int res = -1;
	
	serial_write(fd, 1, "\xA5");
	res = serial_read(fd, buffer, 2);
	
	//read device ID, two bytes takes 2 read operations, each gets a byte
	return buffer[0] | buffer[1]<<8;	//upper 8 bits
}

uint32_t BP_PIC424Write(void *pfd, uint32_t data, uint8_t prenop, uint8_t postnop) {
	int fd = &(int*) pdf;
	uint8 buffer[5]={0};
	int res = -1;
	
	buffer[0]='\xA4';
	buffer[1]=(uint8)(data);
	buffer[2]=(data>>8);
	buffer[3]=(data>>16);
	buffer[4]=((prenop<<4)|(postnop&0x0F));

	
	serial_write(fd, 5, buffer);
	res = serial_read(fd, buffer, 1);
	if (buffer[0] != "\x01") {
		puts("ERROR");
		return -1;
	} 
	return 0;
}

