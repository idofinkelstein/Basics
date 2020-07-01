
#include <stdlib.h>
#include <assert.h>

#include "pqueue.h"
#include "scheduler.h"

#define FAILURE 1
#define CONTINUE 1
#define STOP 0
#define ERROR -1

int Compare(const void *data1, const void *data2, void *param);
int IsMatch(const void *data, void *param);


typedef struct timer
{
	unique_id_t uid;
	sch_task_func_t task_func;
	time_t interval;
	time_t abs_time;
	void *param;

}t_t;

struct scheduler
{
	pqueue_t *pqueue;
	int stop_signal;
};


sch_t *SchCreate(void)
{
	sch_t *scheduler = (sch_t*)malloc(sizeof(sch_t));
	pqueue_cmp_func_t cmp = Compare;
	
	
	if (NULL == scheduler)
	{
		return (NULL);
	}

	scheduler->pqueue = PQCreate(cmp, NULL);
	scheduler->stop_signal = 0;

	if (NULL == scheduler->pqueue)
	{
		free(scheduler);

		return (NULL);
	}

	return (scheduler);
}

void SchDestroy(sch_t *sch)
{
	while (!PQIsEmpty(sch->pqueue))
	{
		free(PQDequeue(sch->pqueue));
	}

	PQDestroy(sch->pqueue);

	free(sch);

	sch = NULL;
}

unique_id_t SchTimerStart(sch_t *sch, 
						  size_t interval_in_sec,
						  sch_task_func_t task,
						  void* param)
{
	t_t *timer = malloc(sizeof(t_t));

	if (NULL == timer)
	{
		return(UIDGetBadUID());
	}
	
	timer->uid = UIDCreate();

	if(UIDIsSame(timer->uid, UIDGetBadUID()))
	{
		free(timer);

		return(UIDGetBadUID());
	}

	timer->interval = interval_in_sec;

	timer->task_func = task;

	timer->param = param;

	timer->abs_time = interval_in_sec + time(NULL);

	PQEnqueue(sch->pqueue, timer);
	
	return (timer->uid);
}

int SchRun(sch_t *sch)
{
	t_t *timer = NULL;
	int task_result = 0;

	while (!PQIsEmpty(sch->pqueue) && ERROR != task_result)
	{
		timer = PQPeek(sch->pqueue);
		
		if (timer->abs_time - time(NULL) >= 0)
		{
			sleep(timer->abs_time - time(NULL));
		}

		task_result = timer->task_func(sch, timer->uid, timer->param);
		
		if (CONTINUE == task_result && !sch->stop_signal)
		{
			SchTimerStart(sch,
						  timer->interval,
						  timer->task_func,
						  timer->param);

			free(PQDequeue(sch->pqueue));			
		}
		else if (STOP == task_result)
		{
			free(PQDequeue(sch->pqueue));
		}
	}
			
	return (ERROR == task_result);
}

void SchTimerCancel(sch_t *sch, unique_id_t uid)
{
	pqueue_is_match_func_t is_match = &IsMatch;

	free(PQErase(sch->pqueue, is_match, &uid));
}

int SchStop(sch_t *sch)
{
	sch->stop_signal = 1;

	return (sch->stop_signal);
}

/* function to pass to Create */
int Compare(const void *data1, const void *data2, void *param)
{
	/* data2 is the new data */

	t_t *timer1 = (t_t*)data1;
	t_t *timer2 = (t_t*)data2;

	(void)param;

	if (timer1->abs_time < timer2->abs_time)
	{
		return -1;
	}
	else if (timer1->abs_time == timer2->abs_time)
	{
		return 0;
	}
	
	return 1;
}

int IsMatch(const void *data, void *param)
{
	t_t *timer = (t_t*)data;
	unique_id_t *to_match = param;

	return (UIDIsSame(timer->uid, *to_match));
}
