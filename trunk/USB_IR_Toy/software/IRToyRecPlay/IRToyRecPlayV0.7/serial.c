/*
 * Part of ols-fwloader - Serial port routines
 * Inspired by pirate-loader, written by Piotr Pawluczuk
 * http://the-bus-pirate.googlecode.com/svn/trunk/bootloader-v4/pirate-loader/source/pirate-loader.c
 *
 * Copyright (C) 2010 Piotr Pawluczuk
 * Copyright (C) 2011 Michal Demin <michal.demin@gmail.com>
 *
 ********************************************************************************************************************************
 *  Released into the public domain, 2011 Where Labs, LLC (DangerousPrototypes.com/Ian Lesnet)
 *
 *  This work is free: you can redistribute it and/or modify it under the terms of Creative Commons Zero license v1.0
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the License for more details. You should have received a copy of the License along with this program. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 *
 *  Contact Details: http://www.DangerousPrototypes.com
 *  Where Labs, LLC, 208 Pine Street, Muscatine, IA 52761,USA

*/



#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <string.h>

#include "serial.h"

int serial_setup(int fd, unsigned long speed)
{
#if IS_WIN32
	COMMTIMEOUTS timeouts;
	DCB dcb = {0};
	HANDLE hCom = (HANDLE)fd;

	dcb.DCBlength = sizeof(dcb);

	dcb.BaudRate = speed;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;

	if( !SetCommState(hCom, &dcb) ){
		return -1;
	}

	timeouts.ReadIntervalTimeout = 100;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 100;

	if (!SetCommTimeouts(hCom, &timeouts)) {
		return -1;
	}

	return 0;
#else
	struct termios t_opt;
	speed_t baud;

	switch (speed) {
		case 921600:
			baud = B921600;
			break;
		case 115200:
			baud = B115200;
			break;
		case 1000000:
			baud = B1000000;
			break;
		case 1500000:
			baud = B1500000;
			break;
		default:
			printf("unknown speed setting \n");
			return -1;
			break;
	}

	/* set the serial port parameters */
	fcntl(fd, F_SETFL, 0);
	tcgetattr(fd, &t_opt);
	cfsetispeed(&t_opt, baud);
	cfsetospeed(&t_opt, baud);
	t_opt.c_cflag |= (CLOCAL | CREAD);
	t_opt.c_cflag &= ~PARENB;
	t_opt.c_cflag &= ~CSTOPB;
	t_opt.c_cflag &= ~CSIZE;
	t_opt.c_cflag |= CS8;
	t_opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	t_opt.c_iflag &= ~(IXON | IXOFF | IXANY);
	t_opt.c_iflag &= ~(ICRNL | INLCR);
	t_opt.c_oflag &= ~(OCRNL | ONLCR);
	t_opt.c_oflag &= ~OPOST;
	t_opt.c_cc[VMIN] = 0;
	t_opt.c_cc[VTIME] = 10;

#if IS_DARWIN
	if( tcsetattr(fd, TCSANOW, &t_opt) < 0 ) {
		return -1;
	}

	return ioctl( fd, IOSSIOSPEED, &baud );
#else
	tcflush(fd, TCIOFLUSH);

	return tcsetattr(fd, TCSANOW, &t_opt);
#endif
#endif
}

int serial_write(int fd, const char *buf, int size)
{
	int ret = 0;
#if IS_WIN32
	HANDLE hCom = (HANDLE)fd;
	int res = 0;
	unsigned long bwritten = 0;

	res = WriteFile(hCom, buf, size, &bwritten, NULL);

	if( res == FALSE ) {
		ret = -1;
	} else {
		ret = bwritten;
	}
#else
	ret = write(fd, buf, size);
#endif

#if DEBUG
	if (ret != size)
		fprintf(stderr, "Error sending data (written %d should have written %d)\n", ret, size);
#endif

	return ret;
}

int serial_read(int fd, char *buf, int size)
{
	int len = 0;
	int ret = 0;
	int timeout = 0;
#if IS_WIN32
	HANDLE hCom = (HANDLE)fd;
	unsigned long bread = 0;

	ret = ReadFile(hCom, buf, size, &bread, NULL);

	if( ret == FALSE || ret==-1 ) {
		len = -1;
	} else {
		len = bread;
	}

#else
	while (len < size) {
		ret = read(fd, buf+len, size-len);
		if (ret == -1){
			//printf("ret -1");
			return -1;
		}

		if (ret == 0) {
			timeout++;

			if (timeout >= 10)
				break;

			continue;
		}

		len += ret;
	}
#endif

#if DEBUG
	if (len != size)
		fprintf(stderr, "Error receiving data (read %d should have read %d)\n", len, size);
#endif

	return len;
}

int serial_open(const char *port)
{
	int fd;
#if IS_WIN32
	static char full_path[32] = {0};

	HANDLE hCom = NULL;

	if( port[0] != '\\' ) {
		_snprintf(full_path, sizeof(full_path) - 1, "\\\\.\\%s", port);
		port = full_path;
	}

	hCom = CreateFileA(port, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if( !hCom || hCom == INVALID_HANDLE_VALUE ) {
		fd = -1;
	} else {
		fd = (int)hCom;
	}
#else
	fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) {
		//fprintf(stderr, "Could not open serial port.\n");
		return -1;
	}
#endif
	return fd;
}

int serial_close(int fd)
{
#if IS_WIN32
	HANDLE hCom = (HANDLE)fd;

	CloseHandle(hCom);
#else
	close(fd);
#endif
	return 0;
}

