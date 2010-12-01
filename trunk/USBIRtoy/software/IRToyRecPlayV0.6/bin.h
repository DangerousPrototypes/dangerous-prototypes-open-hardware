#ifndef BIN_H_INCLUDED
#define BIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <time.h>
#ifdef _WIN32
#include <conio.h>
#include <windef.h>
#include <windows.h>
#else
#include <sys/select.h>
#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include "kbhit.h"
#endif

#include "serial.h"

int IRrecord(	char *,int,float );
void IRplay(	char *,int,char *);

#endif // BIN_H_INCLUDED
