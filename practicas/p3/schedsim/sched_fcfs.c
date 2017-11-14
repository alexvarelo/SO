#include "sched.h"

static task_t* pick_next_task_fcfs(runqueue_t* rq,int cpu)
{
    /*
    Completar codigo
    */
    task_t* t=head_slist(&rq->tasks);

	/* Current is not on the rq -> let's remove it */
	if (t) 
		remove_slist(&rq->tasks,t);

	return t;
}

static void enqueue_task_fcfs(task_t* t,int cpu, int runnable)
{
    /*
    Completar codigo
    */
    runqueue_t* rq=get_runqueue_cpu(cpu);

    if (t->on_rq || is_idle_task(t))
		return;

    insert_slist(&rq->tasks, t);

    /* If the task was not runnable before, update the number of runnable tasks in the rq*/
	if (!runnable) {
		task_t* current=rq->cur_task;

		/* Trigger a preemption if this task has a shorter CPU burst than current */
		if (preemptive_scheduler && !is_idle_task(current) && t->runnable_ticks_left<current->runnable_ticks_left) {
			rq->need_resched=TRUE;
			current->flags|=TF_INSERT_FRONT; /* To avoid unfair situations in the event
                                                another task with the same length wakes up as well*/
		}
	}
}

static task_t* steal_task_fcfs(runqueue_t* rq,int cpu)
{
    /*
    Completar codigo
    */
	task_t* t=tail_slist(&rq->tasks);

	if (t) {
		remove_slist(&rq->tasks,t);
		t->on_rq=FALSE;
		rq->nr_runnable--;
	}
	return t;
}


sched_class_t fcfs_sched= {
	.pick_next_task=pick_next_task_fcfs,
	.enqueue_task=enqueue_task_fcfs,
	.steal_task=steal_task_fcfs
};
