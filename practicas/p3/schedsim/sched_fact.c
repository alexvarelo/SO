#include "sched.h"

static task_t* pick_next_task_fact(runqueue_t* rq,int cpu)
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

static int factor(task_t* t){
    return (t->sys_time!=0)?((t->last_time_enqueued-t->real_time) / t->sys_time):(t->last_time_enqueued-t->real_time);
}

static int compare_tasks_factor(void *t1,void *t2)
{
	return factor((task_t*)t1)-factor((task_t*)t2);
}

static void enqueue_task_fact(task_t* t,int cpu, int runnable)
{
    runqueue_t* rq=get_runqueue_cpu(cpu);

    if (t->on_rq || is_idle_task(t))
		return;

    sorted_insert_slist(&rq->tasks, t, 1, compare_tasks_factor); 

}

static task_t* steal_task_fact(runqueue_t* rq,int cpu)
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


sched_class_t fact_sched= {
	.pick_next_task=pick_next_task_fact,
	.enqueue_task=enqueue_task_fact,
	.steal_task=steal_task_fact
};
