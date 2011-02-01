
#ifndef _OS_H_
#define _OS_H_

void osInit(void);
void osBegin(void);
void osExit(void);
int osTaskCreate(void (*taskPtr)(void));
void osTaskExit(void);
void osTaskPreempt(void);

#endif


