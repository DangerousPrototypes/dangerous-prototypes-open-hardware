/*
 * OS independent serial interface
 *
 * Heavily based on Pirate-Loader:
 * http://the-bus-pirate.googlecode.com/svn/trunk/bootloader-v4/pirate-loader/source/pirate-loader.c
 *
 */
#ifndef MYSERIAL_H_
#define MYSERIAL_H_

#include <stdint.h>

#ifdef WIN32
#include <windows.h>
#include <time.h>

#define B115200 115200
#define B921600 921600

typedef long speed_t;
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

