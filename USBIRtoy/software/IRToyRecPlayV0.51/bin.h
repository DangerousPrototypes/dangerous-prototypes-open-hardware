#ifndef BIN_H_INCLUDED
#define BIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#ifdef _WIN32
#include <conio.h>
#include <windef.h>
#include <windows.h>
#else
#include <sys/select.h>
#include <curses.h>
#include <stdbool.h>
#include <unistd.h>
#endif

#ifndef _WIN32
#ifndef _BOOL_
#define _BOOL_
typedef int BOOL;
#include "kbhit.h"
#endif
#endif

#include "serial.h"

int IRrecord(	char *,int );
void IRplay(	char *,int,char *);

#endif // BIN_H_INCLUDED
