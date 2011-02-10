
#include <stdio.h>
#include <stdlib.h>

#include <setjmp.h>

#include "osp.h"




#define TASKS_SIZE 4
#define TASK_STACK_SIZE 256


typedef enum { 
    Clear = 0x0000, Running = 0x0001, Ready = 0x0002, Block = 0x0004, 
}os_tstate;

typedef struct {
    int state;
    int sem;
    jmp_buf regs;
    unsigned short stack[TASK_STACK_SIZE];
} taskType;

taskType tasks[TASKS_SIZE];
int tasksSize;
int taskIndex;


typedef enum { 
	os_init = 0, os_exit, task_schedule, task_exit 
}os_enum;

jmp_buf osRegs;



#define SEM_SIZE 3

typedef struct {
    int value;
} semType;
semType sems[SEM_SIZE];

void osSemInit(int s, int v)
{
   sems[s].value = v; 
}

void osSemP(int s)
{    
    --sems[s].value;    
    if (sems[s].value < 0) {  
        tasks[taskIndex].sem = s; 
        tasks[taskIndex].state = Block;
        if (!setjmp( tasks[taskIndex].regs)) {
            longjmp(osRegs, task_schedule);
        }
    }
}

void osSemV(int s)
{
    int i;
    
    ++sems[s].value; 
    if (sems[s].value <= 0) {
        i = taskIndex; 
        do {
            i = (i + 1) % TASKS_SIZE;
        } while ( tasks[i].sem != s); 
        tasks[i].sem = -1;
        tasks[i].state = Ready;
    }
}


void osInit(void)
{
    int i;

    tasksSize = 0; 
    for(i = 0; i < TASKS_SIZE; i++) {
        tasks[i].state = Clear;
        tasks[i].sem = -1; 
    }
    
    for(i = 0; i < SEM_SIZE; i++) { 
        sems[i].value = 1;
    }
}

void osBegin(void)
{
    switch (setjmp(osRegs)) {
        case task_schedule:         
            do {
                taskIndex = (taskIndex + 1) % TASKS_SIZE;
            } while ( tasks[taskIndex].state != Ready); 
            
            tasks[taskIndex].state = Running;
            longjmp(tasks[taskIndex].regs, task_schedule);
            break;
        case task_exit:
            tasks[taskIndex].state = Clear;
            tasks[taskIndex].sem = -1;
            if (--tasksSize) {
                longjmp(osRegs, task_schedule);
            }
            break;
        case os_init:
            if (tasksSize) {
                taskIndex = -1;
                longjmp(osRegs, task_schedule);
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
    int i = 0;

    if (tasksSize < TASKS_SIZE) {       
        for ( i = 0; tasks[i].state != Clear; i++ );
        ++tasksSize;
        tasks[taskIndex].sem = -1;
        tasks[i].state = Ready;
        
        setjmp( tasks[i].regs );
        tasks[i].regs[14] = (unsigned int)&tasks[i].stack[0];
        tasks[i].regs[15] = (unsigned int)&tasks[i].stack[0];  
 		tasks[i].regs[16] = (unsigned int)taskPtr;
		tasks[i].regs[17] = 0;        
    }
    return( i );
}

void osTaskExit(void)
{
    longjmp(osRegs, task_exit);
}

void osTaskPreempt(void)
{
    if (!setjmp( tasks[taskIndex].regs)) {
        tasks[taskIndex].state = Ready;
        longjmp(osRegs, task_schedule);
    }
}


