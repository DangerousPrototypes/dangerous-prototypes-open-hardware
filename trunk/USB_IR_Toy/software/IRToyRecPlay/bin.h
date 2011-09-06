/*
    Written and maintained by the IR TOY Project and http://dangerousprototypes.com
    WIKI page:    http://dangerousprototypes.com/usb-ir-toy-manual/
    Forum page:   http://dangerousprototypes.com/forum/viewforum.php?f=29&sid=cdcf3a3177044bc1382305a921585bca
********************************************************************************************************************

Copyright (C) 2011 Where Labs, LLC (DangerousPrototypes.com/Ian Lesnet)

This work is free: you can redistribute it and/or modify it under the terms of Creative Commons Attribution ShareAlike license v3.0

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the License for more details. You should have received a copy of the License along with this program. If not, see <http://creativecommons.org/licenses/by-sa/3.0/>.

Contact Details: http://www.DangerousPrototypes.com
Where Labs, LLC, 208 Pine Street, Muscatine, IA 52761,USA

********************************************************************************************************************* */

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


int IRrecord(	char *,int,float,char *);
void IRplay(	char *,int,char *,char *);

#endif // BIN_H_INCLUDED
