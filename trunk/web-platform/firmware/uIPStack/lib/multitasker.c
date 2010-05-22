
#include <p33Fxxxx.h>
#include "multitasker.h"

struct task{
	short sp;
	short fp;
	short stack[STACK_SIZE];
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

struct task tasks[TASK_COUNT];
void * schedule_return;
short original_stack;
short original_frame;
short original_splim;
struct task *current_task;


void task_init( int task_id, void *entry_point )
{
	struct task *t = &tasks[task_id];
	union DWORD ep;
	ep.value = entry_point;
	short *stack_ptr = t->stack;
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
		unsigned int t = 0 ;
		schedule_return = &&sch_ret;
		while(1)
		{
			current_task = &(tasks[t]);
			SPLIM = (unsigned int) (current_task->stack + (STACK_SIZE ));
			asm volatile ( " \
				disi #0x06	\n \
				mov %0,w15 	\n \
				mov %1,w14 	\n \
				ulnk		\n \
				return " 
				: 
				: "m"(current_task->sp), "m"(current_task->fp) );
			
sch_ret:	t++;
			if( t >= TASK_COUNT ) t=0;
			
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



