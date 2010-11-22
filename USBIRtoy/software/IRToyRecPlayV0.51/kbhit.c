#ifndef _WIN32
#include "kbhit.h"
#include <termios.h>
#include <unistd.h>

//return a character key pressed
int kbhit()
{
    int ch;
    ch=getch();
    return ch;


}

#endif
