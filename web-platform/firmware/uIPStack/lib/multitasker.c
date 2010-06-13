
#include <p33Fxxxx.h>
#include "multitasker.h"


//state of a task
struct task{
	short sp;	//stack pointer
	short fp;	//frame pointer
	short stack[STACK_SIZE];	//the task's stack
};

union DWORD
{
	struct
	{
		unsigned short low;
		unsigned short high;
	} word;
	unsigned long value;
};

#define STACK_FILL 0x55AA

//pointer for jumping back into the scheduler
void * schedule_return;
//scheduler's stack pointer
short original_stack;
//scheduler's frame pointer
short original_frame;
//scheduler's stack limit pointer
short original_splim;

//pointer to the currently executing task
//Not valid when the scheduler function is running
struct task *current_task;

//the id of the current task
unsigned int current_task_id;

struct task tasks[TASK_COUNT];

void task_init( int task_id, void *entry_point )
{
	struct task *t = &tasks[task_id];
	union DWORD ep;
	ep.value = (unsigned short)entry_point;
	short* stack_ptr = t->stack;

	//fill stack with known value so we can report usage later
	short* stack_end = stack_ptr + STACK_SIZE;
	while( stack_ptr < stack_end ) *stack_ptr++ = STACK_FILL;
	stack_ptr = t->stack;

	//put the entry point of the function onto this stack
	//we'll be jumping to the function later by switching to
	//this stack then "return"-ing
	*stack_ptr++ = ep.word.low;
	*stack_ptr++ = ep.word.high;
	*stack_ptr++ = (short)t->stack;
	t->sp = (short) stack_ptr;
	t->fp = t->sp;

}


void task_schedule()
{
	asm volatile ( " \
		mov w15,_original_stack		\n \
		mov w14,_original_frame		\n \
		");
	original_splim = SPLIM;

	while(1)
	{
		current_task_id = 0;
		schedule_return = &&sch_ret;
		while(1)
		{
			current_task = &(tasks[current_task_id]);
			SPLIM = (unsigned int) (current_task->stack + (STACK_SIZE ));
			asm volatile ( " \
				disi #0x06	\n \
				mov %0,w15 	\n \
				mov %1,w14 	\n \
				ulnk		\n \
				return " 
				: 
				: "m"(current_task->sp), "m"(current_task->fp) );
			
sch_ret:	current_task_id++;
			if( current_task_id >= TASK_COUNT ) current_task_id=0;
			
		}
	}

}

void task_yield()
{
	asm volatile ( " \
		disi	#0x30	\n \
		mov w15, %0 	\n \
		mov w14, %1		\n " 
		: 
		: "m"(current_task->sp), "m"(current_task->fp) );

	SPLIM = original_splim;
	asm volatile ( " \
		mov _original_stack, w15	\n \
		mov _original_frame, w14	\n ");

	goto *schedule_return;
}

int task_stack_high_water_mark(int task_id){
	struct task *ptr = &tasks[task_id];
	short* stack_end = ptr->stack + STACK_SIZE - 1;
	while( stack_end > ptr->stack && (*stack_end) == STACK_FILL ) stack_end--;

	return (int)(stack_end) - (int)(ptr->stack);
}

int __attribute__((always_inline)) task_current_task_id(){ return current_task_id; }
