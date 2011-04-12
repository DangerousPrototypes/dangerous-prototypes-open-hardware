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

#ifndef MYSERIAL_H_
#define MYSERIAL_H_

#include <config.h>
#include <stdint.h>

#if IS_WIN32
#include <windows.h>
#include <time.h>

#define B115200 115200
#define B921600 921600

typedef long speed_t;
#else // WIN32

#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>

#endif

#if IS_DARWIN
#include <IOKit/serial/ioss.h>
#include <sys/ioctl.h>

#define B1500000 1500000
#define B1000000 1000000
#define B921600  921600
#endif

int serial_setup(int fd, unsigned long speed);
int serial_write(int fd, const char *buf, int size);
int serial_read(int fd, char *buf, int size);
int serial_open(const char *port);
int serial_close(int fd);


#endif

