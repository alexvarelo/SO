#include "sched.h"

static task_t* pick_next_task_prio(runqueue_t* rq,int cpu)
{
    task_t* t=head_slist(&rq->tasks);

	if (t) 
		remove_slist(&rq->tasks,t);

	return t;
}


static int compare_tasks_priority(void *t1,void *t2)
{
	task_t* tsk1=(task_t*)t1;
	task_t* tsk2=(task_t*)t2;
	return tsk1->prio-tsk2->prio;
}

static void enqueue_task_prio(task_t* t,int cpu, int runnable)
{
    /*
    Completar codigo
    */
    runqueue_t* rq=get_runqueue_cpu(cpu);
    
        if (t->on_rq || is_idle_task(t))
            return;
        
        sorted_insert_slist(&rq->tasks, t, 1, compare_tasks_priority);  //Push task
    
        /* If the task was not runnable before, update the number of runnable tasks in the rq*/
        if (!runnable) {
            task_t* current=rq->cur_task;
    
            /* Trigger a preemption if this task has a shorter CPU burst than current */
            if (preemptive_scheduler && !is_idle_task(current) && t->prio<current->prio) {
                rq->need_resched=TRUE;
            }
        } 
}

static task_t* steal_task_prio(runqueue_t* rq,int cpu)
{
	task_t* t=tail_slist(&rq->tasks);
    
        if (t) {
            remove_slist(&rq->tasks,t);
            t->on_rq=FALSE;
            rq->nr_runnable--;
        }
        return t;
}


sched_class_t prio_sched= {
	.pick_next_task=pick_next_task_prio,
	.enqueue_task=enqueue_task_prio,
	.steal_task=steal_task_prio
};
