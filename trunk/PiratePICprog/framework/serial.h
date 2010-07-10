/*
 * OS independent serial interface
 *
 * Heavily based on Pirate-Loader:
 * http://the-bus-pirate.googlecode.com/svn/trunk/bootloader-v4/pirate-loader/source/pirate-loader.c
 *
 */
#ifndef MYSERIAL_H_
#define MYSERIAL_H_
/*
#ifdef WIN32
	#include <windows.h>
	#include <time.h>

	#define O_NOCTTY 0
	#define O_NDELAY 0
	#define B115200 115200
	#define B921600 921600

	#define OS WINDOWS

    int write(int fd, const void* buf, int len);
    int read(int fd, void* buf, int len);
    int close(int fd);
    int open(const char* path, unsigned long flags);
    int __stdcall select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfs, const struct timeval* timeout);

#else
	#include <unistd.h>
	#include <termios.h>
	#include <sys/select.h>
	#include <sys/types.h>
	#include <sys/time.h>

	#ifdef MACOSX
		#include <IOKit/serial/ioss.h>
		#include <sys/ioctl.h> 

		#define B1500000 1500000
		#define B1000000 1000000
		#define B921600  921600
	#endif

#endif
*/

#include <stdint.h>

#ifdef WIN32
#include <windows.h>
#include <time.h>

#define B115200 115200
#define B921600 921600

#else

#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>

#endif

int serial_setup(int fd, speed_t speed);
int serial_write(int fd, char *buf, int size);
int serial_read(int fd, char *buf, int size);
int serial_open(char *port);
int serial_close(int fd);


#endif

