/*
* This is a simple round-robin co-operative multitasker.
* Each task is simply a function obeying two rules:
* 1. it will never return
* 2. it will call task_yield() at some point to allow other tasks to run
* The task list is initialised by calling task_init()
* The scheduler is started by calling task_schedule()
*/



/* The number of tasks in the list */
#define TASK_COUNT 3
/* The size of the stack for each task */
#define STACK_SIZE 500

/*
* Initialise a task with the address of the task entry
* point. Typical usage is:
* task_init( 0, &task_function_name );
* A "task" is just a function that:
* 1. will never return
* 2. will call task_yield at some point to allow other tasks to run
*/
void task_init( int task_id, void *entry_point );

/*
* Your task will call task_yield at some point to allow other
* tasks to run.
* Typically, while it is waiting for something to occur, eg:
*    while( timer_count < 1000 ) task_yield();
* The call to task_yield will return once the calling task's
* turn in the scheduler is reached (ie, after all other tasks
* have had an opportunity to run )
*/
void task_yield();

/*
* Call task_schedule() from your main code.
* This call will never return.
* task_schedule() will call each task in turn.
* The task will run until it calls task_yield()
* Then the next task in the list will be allowed to execute.
*/
void task_schedule();

/*
* Get the number of bytes used by the task from it's stack.
* Probably not that useful (depends when you call it)
*/
int task_stack_used(int);

/*
* Get the id of the task currently executing.
*/
int task_current_task_id();

