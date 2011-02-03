
#include <stdio.h>
#include <stdlib.h>

#include <setjmp.h>
/*
#ifndef	_SETJMP_H_
#define	_SETJMP_H_

#ifdef __C30__
typedef unsigned int jmp_buf[18];
#else
typedef unsigned int jmp_buf[4];
#endif
extern	int	setjmp(jmp_buf);
extern void	longjmp(jmp_buf, int);
#endif	

*/


#define TASKS_SIZE 4
#define TASK_STACK_SIZE 256


typedef enum { 
	os_init = 0, os_exit, task_preempt, task_exit 
}os_enum;

typedef struct {
    int id;
    jmp_buf regs;
    unsigned stack[TASK_STACK_SIZE];
} taskType;


taskType tasks[TASKS_SIZE];
int tasksSize;
int taskCurr;
jmp_buf osRegs;


void osInit(void)
{
    int i;

    tasksSize = 0; 
    taskCurr = -1;
    for(i = 0; i < TASKS_SIZE; i++) tasks[i].id = 0;
}

void osBegin(void)
{
    switch (setjmp(osRegs)) {
        case task_preempt:
            for ( ; !tasks[ (taskCurr = ++taskCurr % TASKS_SIZE) ].id; );
            longjmp(tasks[taskCurr].regs, task_preempt);
            break;
        case task_exit:
            tasks[taskCurr].id = 0;
            if (--tasksSize) {
                longjmp(osRegs, task_preempt);
            }
            break;
        case os_init:
            if (tasksSize) {
                longjmp(osRegs, task_preempt);
            }
            break;
        case os_exit:
            break;
    }
}

void osExit(void)
{
    longjmp(osRegs, os_exit);
}

int osTaskCreate(void (*taskPtr)(void))
{
    int i;

    if (tasksSize < TASKS_SIZE) {
        
        for ( i = 0; tasks[i].id > 0; i++ );
        tasks[i].id = i+1;
        ++tasksSize;
        setjmp( tasks[i].regs );
       
        //stack frame pointer
        tasks[i].regs[14] = (unsigned int)&tasks[i].stack[0];
        //stack pointer
        tasks[i].regs[15] = (unsigned int)&tasks[i].stack[0]; 
        //pc low
        tasks[i].regs[16] = (unsigned int)taskPtr;
        //pc high
        tasks[i].regs[17] = 0;
        
        return(i+1);
    }
    return( 0 );
}

void osTaskExit(void)
{
    longjmp(osRegs, task_exit);
}

void osTaskPreempt(void)
{
    if (!setjmp(tasks[taskCurr].regs)) {
        longjmp(osRegs, task_preempt);
    }
}



