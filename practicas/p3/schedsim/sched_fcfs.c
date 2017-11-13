#include "sched.h"

static task_t* pick_next_task_fcfs(runqueue_t* rq,int cpu)
{
	task_t* t;
    /*
    Completar codigo
    */
	return t;
}

static void enqueue_task_fcfs(task_t* t,int cpu, int runnable)
{
    /*
    Completar codigo
    */
}

static task_t* steal_task_fcfs(runqueue_t* rq,int cpu)
{
	task_t* t;
    /*
    Completar codigo
    */
	return t;
}


sched_class_t fcfs_sched= {
	.pick_next_task=pick_next_task_fcfs,
	.enqueue_task=enqueue_task_fcfs,
	.steal_task=steal_task_fcfs
};
