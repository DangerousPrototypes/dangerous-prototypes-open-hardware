#ifndef KBHIT_H_INCLUDED
#define KBHIT_H_INCLUDED
#ifndef _WIN32
#include <stdio.h>
void   init_keyboard(void);
void   close_keyboard(void);
int    kbhit(void);
int    readch(void);

#endif
#endif // KBHIT_H_INCLUDED
