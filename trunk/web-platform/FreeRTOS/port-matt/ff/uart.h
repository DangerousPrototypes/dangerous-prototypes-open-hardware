#ifndef _COMMFUNC
#define _COMMFUNC

#include "integer.h"

void uart_init (void);
int uart_test (void);
void uart_put (BYTE);
BYTE uart_get (void);

#endif

