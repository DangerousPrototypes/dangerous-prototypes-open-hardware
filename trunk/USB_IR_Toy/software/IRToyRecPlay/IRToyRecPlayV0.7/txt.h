#ifndef BIN_H_INCLUDED
#define TXT_H_INCLUDED

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
#include "kbhit.h"
#endif

#include "serial.h"

void IRtxtrecord(char * );
void IRtxtplay(	char *,int,char *);

#endif // TXT_H_INCLUDED
