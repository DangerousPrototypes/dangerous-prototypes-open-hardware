#ifndef OLS_H_INCLUDED
#define OLS_H_INCLUDED

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
#endif
#endif

void create_ols(char *);

#endif // OLS_H_INCLUDED



