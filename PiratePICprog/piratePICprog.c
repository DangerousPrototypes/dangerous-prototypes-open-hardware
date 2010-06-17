/*
 
 Pirate-Loader for Bootloader v4
 
 Version  : 1.0.2
 
 Changelog:
 
  + 2010-02-04 - Changed polling interval to 10ms on Windows select wrapper, suggested by Michal (robots)
  
  + 2010-02-04 - Added sleep(0) between write instructions, patch submitted by kbulgrien
 
  + 2010-01-22 - Added loader version number to the console output and source code
 
  + 2010-01-19 - Fixed BigEndian incompatibility
			   - Added programming simulate switch ( --simulate ) for data verification 
 
  + 2010-01-18 - Initial release
 
 
 Building:
 
  UNIX family systems:
	
	gcc pirate-loader.c -o pirate-loader
 
  WINDOWS:
    
	cl pirate-loader.c /DWIN32=1
 
 
 Usage:
	
	Run ./pirate-loader --help for more information on usage and possible switches
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <errno.h>

#define PIRATE_LOADER_VERSION "1.0.2"

#define STR_EXPAND(tok) #tok
#define OS_NAME(tok) STR_EXPAND(tok)


#ifdef WIN32
	#include <windows.h>
	#include <time.h>

	#define O_NOCTTY 0
	#define O_NDELAY 0
	#define B115200 115200

	#define OS WINDOWS
	
	int write(int fd, const void* buf, int len)
	{
		HANDLE hCom = (HANDLE)fd;
		int res = 0;
		unsigned long bwritten = 0;


		res = WriteFile(hCom, buf, len, &bwritten, NULL);

		if( res == FALSE ) {
			return -1;
		} else {
			return bwritten;
		}
	}

	int read(int fd, void* buf, int len)
	{
		HANDLE hCom = (HANDLE)fd;
		int res = 0;
		unsigned long bread = 0;

		res = ReadFile(hCom, buf, len, &bread, NULL);

		if( res == FALSE ) {
			return -1;
		} else {
			return bread;
		}
	}

	int close(int fd)
	{
		HANDLE hCom = (HANDLE)fd;

		CloseHandle(hCom);
		return 0;
	}

	int open(const char* path, unsigned long flags)
	{
		static char full_path[32] = {0};

		HANDLE hCom = NULL;
		
		if( path[0] != '\\' ) {
			_snprintf(full_path, sizeof(full_path) - 1, "\\\\.\\%s", path);
			path = full_path;
		}

		hCom = CreateFileA(path, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if( !hCom || hCom == INVALID_HANDLE_VALUE ) {
			return -1;
		} else {
			return (int)hCom;
		}
	}

	int __stdcall select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfs, const struct timeval* timeout)
	{
		time_t maxtc = time(0) + (timeout->tv_sec);
		COMSTAT cs = {0};
		unsigned long dwErrors = 0;

		if( readfds->fd_count != 1 ) {
			return -1;
		}

		while( time(0) <= maxtc )
		{ //only one file supported
			if( ClearCommError( (HANDLE)readfds->fd_array[0], 0, &cs) != TRUE ){
				return -1;
			}

			if( cs.cbInQue > 0 ) {
				return 1;
			}

			Sleep(10);
		}
		return 0;
	}

	unsigned int sleep(unsigned int sec)
	{
		Sleep(sec * 1000);
		
		return 0;
	}

#else
	#include <unistd.h>
	#include <termios.h>
	#include <sys/select.h>
	#include <sys/types.h>
	#include <sys/time.h>
#endif

/* macro definitions */

#if !defined OS
#define OS UNKNOWN
#endif

#define BOOTLOADER_HELLO_STR "\xC1"
#define BOOTLOADER_OK 0x4B
#define BOOTLOADER_PLACEMENT 1

#define PIC_FLASHSIZE 0xAC00

#define PIC_NUM_PAGES 512
#define PIC_NUM_ROWS_IN_PAGE  8
#define PIC_NUM_WORDS_IN_ROW 64

#define PIC_WORD_SIZE  (3)
#define PIC_ROW_SIZE  (PIC_NUM_WORDS_IN_ROW * PIC_WORD_SIZE)
#define PIC_PAGE_SIZE (PIC_NUM_ROWS_IN_PAGE  * PIC_ROW_SIZE)


#define PIC_ROW_ADDR(p,r)		(((p) * PIC_PAGE_SIZE) + ((r) * PIC_ROW_SIZE))
#define PIC_WORD_ADDR(p,r,w)	(PIC_ROW_ADDR(p,r) + ((w) * PIC_WORD_SIZE))
#define PIC_PAGE_ADDR(p)		(PIC_PAGE_SIZE * (p))

#define PAYLOAD_OFFSET 5
#define HEADER_LENGTH PAYLOAD_OFFSET
#define LENGTH_OFFSET 4
#define COMMAND_OFFSET 3

/* type definitions */

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned long  uint32;

/* global settings, command line arguments */

uint8		g_verbose = 0;
uint8		g_hello_only = 0;
uint8		g_simulate = 0;
const char* g_device_path  = NULL;
const char* g_hexfile_path = NULL;
int		dev_fd = -1;

/* functions */

int readWithTimeout(int fd, uint8* out, int length, int timeout)
{
	fd_set fds;
	struct timeval tv = {timeout, 0};
	int res = -1;
	int got = 0;
	
	do {
	
		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		
		res = select(fd + 1, &fds, NULL, NULL, &tv);
		
		if( res > 0 ) {
			res = read(fd, out, length);
			if( res > 0 ) {
				length -= res;
				got    += res;
				out    += res;
			} else {
				break;
			}
		} else { 
			return res;
		}
	} while( length > 0);
	
	return got;
}

unsigned char hexdec(const char* pc)
{
	return (((pc[0] >= 'A') ? ( pc[0] - 'A' + 10 ) : ( pc[0] - '0' ) ) << 4 | 
			((pc[1] >= 'A') ? ( pc[1] - 'A' + 10 ) : ( pc[1] - '0' ) )) & 0x0FF;
	
}

void dumpHex(uint8* buf, uint32 len)
{
	uint32 i=0;
	
	for(i=0; i<len; i++){
		printf("%02X ", buf[i]);
	}
	putchar('\n');
}

int readHEX(const char* file, uint8* bout, unsigned long max_length, uint8* pages_used)
{
	static const uint32 HEX_DATA_OFFSET = 4;
	uint8  linebin[256] = {0};
	uint8* data = (linebin + HEX_DATA_OFFSET);
	uint8  hex_crc, hex_type, hex_len;
	uint32 hex_addr;
	uint32 hex_base_addr = 0;
	uint32 hex_words     = 0;
	
	uint32 f_addr = 0;
	uint32 o_addr = 0;
	
	uint32 num_words = 0;
	
	char  line[512] = {0};
	char  *pc;
	char  *pline = line + 1;
	int   res = 0;
	int	  binlen = 0;
	int   line_no = 0;
	int   i = 0;
	
	FILE* fp = fopen(file, "rb");
	
	if( !fp ) {
		return -1;
	}
	
	while( !feof(fp) && fgets(line, sizeof(line) - 1, fp) )
	{
		line_no++;
		
		if( line[0] != ':' ) {
			break;
		}
		
		res = strlen(pline);
		pc  = pline + res - 1;
		
		while( pc > pline && *pc <= ' ' ) {
			*pc-- = 0;
			res--;
		}
		
		if( res & 0x01 || res > 512 || res < 10) {
			fprintf(stderr, "Incorrect number of characters on line %d:%d\n", line_no, res);
			return -1;
		}
		
		hex_crc = 0;
		
		for( pc = pline, i = 0; i<res; i+=2, pc+=2 ) {
			linebin[i >> 1] = hexdec(pc);
			hex_crc += linebin[i >> 1];
		}
		
		binlen = res / 2;
		
		if( hex_crc != 0 ) {
			fprintf(stderr, "Checksum does not match, line %d\n", line_no);
			return -1;
		}
		
		hex_addr = (linebin[1] << 8) | linebin[2];
		hex_len  = linebin[0];
		hex_type = linebin[3];
		
		if( binlen - (1 + 2 + 1 + hex_len + 1) != 0 ) {
			fprintf(stderr, "Incorrect number of bytes, line %d\n", line_no);
			return -1;
		}
		
		if( hex_type == 0x00 )
		{
			f_addr  = (hex_base_addr | (hex_addr)) / 2; //PCU
			
			if( hex_len % 4 ) {
				fprintf(stderr, "Misaligned data, line %d\n", line_no);
				return -1;
			} else if( f_addr >= PIC_FLASHSIZE ) {
				fprintf(stderr, "Current record address is higher than maximum allowed, line %d\n", line_no);
				return -1;
			}
			
			hex_words = hex_len  / 4;
			o_addr  = (f_addr / 2) * PIC_WORD_SIZE; //BYTES
			
			for( i=0; i<hex_words; i++)
			{
				bout[o_addr + 0] = data[(i*4) + 2];
				bout[o_addr + 1] = data[(i*4) + 0];
				bout[o_addr + 2] = data[(i*4) + 1];
				
				pages_used[ (o_addr / PIC_PAGE_SIZE) ] = 1;
				
				o_addr    += PIC_WORD_SIZE;
				num_words ++;
			}

		} else if ( hex_type == 0x04 && hex_len == 2) {
			hex_base_addr = (linebin[4] << 24) | (linebin[5] << 16);
		} else if ( hex_type == 0x01 ) {
			break; //EOF
		} else {
			fprintf(stderr, "Unsupported record type %02x, line %d\n", hex_type, line_no);
			return -1;
		}
		
	}
	
	fclose(fp);
	return num_words;
}

int sendString(int fd, int length, uint8* dat)
{
	int res=0;
	
	res = write(fd, dat, length);
	
	if( res <= 0 ) {
		puts("ERROR");
		return -1;
	}
}

int sendFirmware(int fd, uint8* data, uint8* pages_used)
{
	uint32 u_addr;
	
	
	uint32 page  = 0;
	uint32 done  = 0;
	uint32 row   = 0;
	uint8  command[256] = {0};
	
	
	for( page=0; page<PIC_NUM_PAGES; page++)
	{
		
		u_addr = page * ( PIC_NUM_WORDS_IN_ROW * 2 * PIC_NUM_ROWS_IN_PAGE );
		
		if( pages_used[page] != 1 ) {
			if( g_verbose && u_addr < PIC_FLASHSIZE) {
				fprintf(stdout, "Skipping page %ld [ %06lx ], not used\n", page, u_addr);
			}
			continue;
		}
		
		if( u_addr >= PIC_FLASHSIZE ) {
			fprintf(stderr, "Address out of flash\n");
			return -1;
		}
		
		//write 64 bytes
		for( row = 0; row < PIC_NUM_ROWS_IN_PAGE; row ++, u_addr += (PIC_NUM_WORDS_IN_ROW * 2))
		{
			command[0] = (u_addr & 0x00FF0000) >> 16;
			command[1] = (u_addr & 0x0000FF00) >>  8;
			command[2] = (u_addr & 0x000000FF) >>  0;
			command[COMMAND_OFFSET] = 0x02; //write command
			command[LENGTH_OFFSET ] = PIC_ROW_SIZE + 0x01; //DATA_LENGTH + CRC
			
			memcpy(&command[PAYLOAD_OFFSET], &data[PIC_ROW_ADDR(page, row)], PIC_ROW_SIZE);
			
			printf("Writing page %ld row %ld, %04lx...", page, row + page*PIC_NUM_ROWS_IN_PAGE, u_addr);
			
			
			sleep(0);
			
			done += PIC_ROW_SIZE;
		}
	}
	
	return done;
}

/* non-firmware functions */

int configurePort(int fd, unsigned long baudrate)
{
#ifdef WIN32
	DCB dcb = {0};
	HANDLE hCom = (HANDLE)fd;

	dcb.DCBlength = sizeof(dcb);

	dcb.BaudRate = baudrate;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;

	if( !SetCommState(hCom, &dcb) ){
		return -1;
	}

	return (int)hCom;
#else
	struct termios g_new_tio;
	
	memset(&g_new_tio, 0x00 , sizeof(g_new_tio));
	cfmakeraw(&g_new_tio);
	
	g_new_tio.c_cflag |=  (CS8 | CLOCAL | CREAD);
	g_new_tio.c_cflag &= ~(PARENB | CSTOPB | CSIZE);
	g_new_tio.c_oflag = 0;
	g_new_tio.c_lflag = 0;
	
	
	g_new_tio.c_cc[VTIME] = 0;
	g_new_tio.c_cc[VMIN] = 1;
	
	cfsetispeed (&g_new_tio, baudrate);
	cfsetospeed (&g_new_tio, baudrate);
	
	tcflush(fd, TCIOFLUSH);
	
	return tcsetattr(fd, TCSANOW, &g_new_tio);
#endif
}

int openPort(const char* dev, unsigned long flags)
{
	return open(dev, O_RDWR | O_NOCTTY | O_NDELAY | flags);
}

int parseCommandLine(int argc, const char** argv)
{
	int i = 0;
	
	for(i=1; i<argc; i++)
	{
		
		if( !strncmp(argv[i], "--hex=", 6) ) {
			g_hexfile_path = argv[i] + 6;
		} else if ( !strncmp(argv[i], "--dev=", 6) ) {
			g_device_path = argv[i] + 6;
		} else if ( !strcmp(argv[i], "--verbose") ) {
			g_verbose = 1;
		} else if ( !strcmp(argv[i], "--hello") ) {
			g_hello_only = 1;
		} else if ( !strcmp(argv[i], "--simulate") ) {
			g_simulate = 1;
		} else if ( !strcmp(argv[i], "--help") ) {
			argc = 1; //that's not pretty, but it works :)
			break;
		} else {
			fprintf(stderr, "Unknown parameter %s, please use pirate-loader --help for usage\n", argv[i]);
			return -1;
		}
	}
	
	if( argc == 1 )
	{
		//print usage
		puts("pirate-loader usage:\n");
		puts(" ./pirate-loader --dev=/path/to/device --hello");
		puts(" ./pirate-loader --dev=/path/to/device --hex=/path/to/hexfile.hex [ --verbose");
		puts(" ./pirate-loader --simulate --hex=/path/to/hexfile.hex [ --verbose");
		puts("");
		
		return 0;
	}
	
	return 1;
}

int BulkByteWrite(int bwrite, uint8* val){
	int i;
	uint8 opcode=0x10;
	opcode=opcode|(bwrite-1);

	writetopirate(&opcode);	
	for(i=0;i<bwrite;i++){
		writetopirate(&val[i]);	
	}
}

int PIC416Write(uint8 cmd, uint16 data){
	uint8 buffer[4]={0};
	int res = -1;
	
	buffer[0]='\xA4';
	buffer[1]=cmd;
	buffer[2]=(uint8)(data);
	buffer[3]=(data>>8);

	
	sendString(dev_fd, 4, buffer);
	res = readWithTimeout(dev_fd, buffer, 1, 1);
	if( memcmp(buffer, "\x01", 1) ) {
		puts("ERROR");
		return -1;
	} 
	return 0;
}

int PIC416WriteLongData(uint8 cmd, uint16 data){
	uint8 buffer[4]={0};
	int res = -1;
	
	buffer[0]='\xA4';
	buffer[1]=cmd;
	buffer[2]=(uint8)(data);
	buffer[3]=(data>>8);

	
	sendString(dev_fd, 4, buffer);
	res = readWithTimeout(dev_fd, buffer, 1, 1);
	if( memcmp(buffer, "\x01", 1) ) {
		puts("ERROR");
		return -1;
	} 
	return 0;
}

uint16 PIC416Read(uint8 cmd){
	uint16 PICread;
	uint8 buffer[2]={0};
	int res = -1;
	
	
	buffer[0]='\xA5';
	buffer[1]=cmd;

	sendString(dev_fd, 2, buffer);
	res = readWithTimeout(dev_fd, buffer, 1, 1);
	PICread=buffer[0];
	
	return PICread;
}

int writetopirate(uint8* val){
	int res = -1;
	uint8	buffer[2] = {0};
	
	sendString(dev_fd, 1, val);
	res = readWithTimeout(dev_fd, buffer, 1, 1);
	if( memcmp(buffer, "\x01", 1) ) {
		puts("ERROR");
		return -1;
	} 
	return 0;
}

void DataLow(){
	writetopirate("\x0C");
}
void DataHigh(){
	writetopirate("\x0D");
}

void ClockLow(){
	writetopirate("\x0A");
}
void ClockHigh(){
	writetopirate("\x0B");
}
void MCLRLow(){
	writetopirate("\x04");
}
void MCLRHigh(){
	writetopirate("\x05");
}

//enter ICSP on PICs with low voltage ICSP mode
//pulls MCLR low, sends programming mode entry key, releases MCLR
void enterLowVPPICSP(uint32 icspkey){
	uint8	buffer[4];
	
	//all programming operations are LSB first, but the ICSP entry key is MSB first. 
	// Reconfigure the mode for LSB order
	printf("Set mode for MCLR (MSB)...");
	if(writetopirate("\x88")){
		puts("ERROR");
		//goto Error;
	} 
	puts("(OK)");
	
	ClockLow();
    DataLow();
    MCLRLow();
    MCLRHigh();
    MCLRLow();
   //send ICSP key 0x4D434850
	buffer[0]=icspkey>>24;
	buffer[1]=icspkey>>16;
	buffer[2]=icspkey>>8;
	buffer[3]=icspkey;	
    BulkByteWrite(4,buffer);
    DataLow();
    MCLRHigh();
	
	//all programming operations are LSB first, but the ICSP entry key is MSB first. 
	// Reconfigure the mode for LSB order
	printf("Set mode for PIC programming (LSB)...");
	if(writetopirate("\x8A")){
		puts("ERROR");
		//goto Error;
	} 
	puts("(OK)");
}

void exitICSP(void){
	//exit programming mode
	MCLRLow();
	MCLRHigh();
}

uint16 readID(void){
	uint16 PICid;
	
	//setup read from device ID bits
	PIC416Write(0,0x0E3F);
	PIC416Write(0,0x6EF8);	
	PIC416Write(0,0x0EFF);
	PIC416Write(0,0x6EF7);
	PIC416Write(0,0x0EFE);
	PIC416Write(0,0x6EF6);
	//read device ID, two bytes takes 2 read operations, each gets a byte
	PICid=PIC416Read(0x09);	//lower 8 bits
	PICid|=PIC416Read(0x09)<<8;	//upper 8 bits
	return PICid;
}

void erasePIC(void){

        PIC416Write(0,0x0E3C);
        PIC416Write(0,0x6EF8);
        PIC416Write(0,0x0E00);
        PIC416Write(0,0x6EF7);
        PIC416Write(0,0x0E05);
        PIC416Write(0,0x6EF6);
        PIC416Write(0x0C,0x0101);
        PIC416Write(0,0x0E3C);
        PIC416Write(0,0x6EF8);
        PIC416Write(0,0x0E00);
        PIC416Write(0,0x6EF7);
        PIC416Write(0,0x0E04);
        PIC416Write(0,0x6EF6);
        PIC416Write(0x0C,0x8080);
        PIC416Write(0,0);
        PIC416Write(0,0);
        sleep(1);//Thread.Sleep(1000); (524ms worst case)
}

        /// <summary>
        /// Up to 64 bytes Write
        /// </summary>
        /// <param name="hexAddData"></param>
        /// <param name="offset"></param>
        /// <returns></returns>
void writePIC(uint32 tblptr, uint8* Data, int length)
        {
        uint16 DataByte;//, buffer[2]={0x00,0x00};
		int ctr;
		uint8	buffer[2] = {0};
        
        PIC416Write(0x00,0x8EA6);
        PIC416Write(0x00,0x9CA6);
        PIC416Write(0x00,0x84A6);
        
        // set TBLPTR
        PIC416Write(0x00,0x0E00 | (tblptr>>16));
        PIC416Write(0x00,0x6EF8);
        PIC416Write(0x00,0x0E00 | (tblptr>>8));
        PIC416Write(0x00,0x6EF7);
        PIC416Write(0x00,0x0E00 | (tblptr));
        PIC416Write(0x00,0x6EF6);

        PIC416Write(0x00,0x6AA6);
        PIC416Write(0x00,0x88A6);

        for(ctr=0;ctr<length-2;ctr+=2)
            {
            DataByte=Data[ctr+1];
            DataByte=DataByte<<8;
            DataByte|=Data[ctr];
            PIC416Write(0x0D,DataByte);
            }
        DataByte=Data[length-1];
        DataByte=DataByte<<8;
        DataByte|=Data[length-2];
        PIC416Write(0x0F,DataByte);

		//delay the 4th clock bit of the 20bit command to allow programming....
		DataLow();
		for(ctr=0; ctr<3; ctr++){
			ClockHigh();
			ClockLow();
		}

        ClockHigh();
        sleep(1);
        ClockLow();

		BulkByteWrite(2, buffer);
        }

/* entry point */

int main (int argc, const char** argv)
{
	int		res = -1;
	uint8	buffer[256] = {0};
	uint8	pages_used[PIC_NUM_PAGES] = {0};
	uint8*	bin_buff = NULL;
	uint8 i=0, PICrev;
	uint16 PICid;
	char PICname[]="UNKNOWN/INVALID PIC ID";
	uint8 test[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
	
	puts("+++++++++++++++++++++++++++++++++++++++++++");
	puts("  piratePICprog for the Bus Pirate         ");
	puts("  Loader version: " PIRATE_LOADER_VERSION "  OS: " OS_NAME(OS));
	puts("+++++++++++++++++++++++++++++++++++++++++++\n");
	
	if( (res = parseCommandLine(argc, argv)) < 0 ) {
		return -1;
	} else if( res == 0 ) {
		return 0;
	}
	
	if( !g_hello_only ) {
		
		if( !g_hexfile_path ) {
			fprintf(stderr, "Please specify hexfile path --hex=/path/to/hexfile.hex\n");
			return -1;
		}
	
		bin_buff = (uint8*)malloc(256 << 10); //256kB
		if( !bin_buff ) {
			fprintf(stderr, "Could not allocate 256kB buffer\n");
			goto Error;
		}
		
		//fill the buffer with 0xFF
		memset(bin_buff, 0xFFFFFFFF, (256 << 10));
		
		printf("Parsing HEX file [%s]\n", g_hexfile_path);
		
		res = readHEX(g_hexfile_path, bin_buff, (256 << 8), pages_used);
		if( res <= 0 || res > PIC_FLASHSIZE ) {
			fprintf(stderr, "Could not load HEX file, result=%d\n", res);
			goto Error;
		}
		
		printf("Found %d words (%d bytes)\n", res, res * 3);
	
	}

	if( !g_device_path ) {
		fprintf(stderr, "Please specify serial device path --dev=/dev/...\n");
		return -1;
	}
	
	printf("Opening serial device %s...", g_device_path);
	
	dev_fd = openPort(g_device_path, 0);
	
	if( dev_fd < 0 ) {
		puts("ERROR");
		fprintf(stderr, "Could not open %s\n", g_device_path);
		goto Error;
	}
	puts("OK");
	
	printf("Configuring serial port settings...");
	
	if( configurePort(dev_fd, B115200) < 0 ) {
		puts("ERROR");
		fprintf(stderr, "Could not configure device, errno=%d\n", errno);
		goto Error;
	}
	puts("OK");
	
	
	//enter BBIO mode 
	
	printf("Entering binary mode...");
	sendString(dev_fd, 1, "\x00");
	res = readWithTimeout(dev_fd, buffer, 5, 1);
	if( memcmp(buffer, "BBIO1", 5) ) {
		for(i=0; i<20; i++){
			buffer[i]=0x00;
		}
		sendString(dev_fd, 19, buffer);
		
		res = readWithTimeout(dev_fd, buffer, 5, 1);
		if( memcmp(buffer, "BBIO1", 5) ) {
			puts("ERROR");
			goto Error;
		} 	
		//puts("(OK)");
	} 	
	printf(buffer);
	puts("(OK)");
	
	//enter raw-wire mode

	printf("Entering rawwire mode...");
	sendString(dev_fd, 1, "\x05");
	res = readWithTimeout(dev_fd, buffer, 4, 1);
	buffer[4]=0x00;
	printf(buffer);
	if( memcmp(buffer, "RAW1", 4) ) {
		puts("ERROR");
		goto Error;
	} 
	puts("(OK)");
	
	//setup output pin type (normal)
	printf("Setup mode...");
	if(writetopirate("\x8A")){
		puts("ERROR");
		goto Error;
	} 
	puts("(OK)");
	
	//setup power supply, AUX pin, pullups
	printf("Setup peripherals...");
	if(writetopirate("\x4F")){
		puts("ERROR");
		goto Error;
	} 
	puts("(OK)");
	
	puts("Entering ICSP...");
	enterLowVPPICSP(0x4D434850);
	
	//now we're in ICSP mode, can do programming stuff with the PIC
 	//read ID
	//determine device type
	PICid=readID();
	PICrev=(PICid&(~0xFFE0)); //find PIC ID (lower 5 bits)
	PICid=(PICid>>5); //isolate PIC device ID (upper 11 bits)
	//could this be an array and we lookup that value?
	switch(PICid){
		case 0x260:
			strcpy(PICname,"18F24J50"); 
			break;
	}	
	printf ("PIC ID: %#X (%s) REV: %#X \n", PICid, PICname, PICrev);
	
	//erase device
	printf("Erasing the PIC (please wait)...");
	erasePIC();
	puts("(OK)");
	
	//exit programming mode
	puts("Exit ICSP...");
	exitICSP();
	
	puts("Entering ICSP...");	
	enterLowVPPICSP(0x4D434850);
	puts("Writing the PIC (please wait)...");	
	writePIC(0x00000000, test, 64);
	//exit programming mode
	puts("Exit ICSP...");
	exitICSP();
	

	
Finished:
	puts("Done!");
	if( bin_buff ) { 
		free( bin_buff );
	}
	close(dev_fd);
    return 0;
	
Error:
	if( bin_buff ) {
		free( bin_buff );
	}
	if( dev_fd >= 0 ) {
		close(dev_fd);
	}
	return -1;
}
