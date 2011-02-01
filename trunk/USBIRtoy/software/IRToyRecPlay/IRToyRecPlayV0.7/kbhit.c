#ifndef _WIN32
#include "kbhit.h"

#include <termios.h>
#include <unistd.h>

static struct termios init_settings, new_settings;
static int peek_char = -1;

void init_keyboard()
{
    tcgetattr(0,&init_settings);
    new_settings = init_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard()
{
    tcsetattr(0, TCSANOW, &init_settings);
}

int kbhit()
{
    unsigned char ch;
    int nread;

    if (peek_char != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1)
    {
        peek_char = ch;
        return ch;
    }

    return 0;
}

int getch()
{
    char ch;

    if(peek_char != -1)
    {
        ch = peek_char;
        peek_char = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}

#endif

