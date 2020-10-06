/*******************************************
* File Name: scheduler.c				   *
* Name: Matan Yankovich				       *
* Date: 30.6.2020						   *
* Reviewed by: Oriel					   *
* Topic: scheduler						   *
********************************************/
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <sys/types.h> /* ssize_t */
#include <stdlib.h> /* malloc, free */
/* matan - should incluse time.h also */
#include "utils.h"

#include "scheduler.h"
#include "pqueue.h"


#define RUNNING 1
#define STOP_RUNNING 0
#define TASK_FAILED -1
#define RE_RUN_TASK 1
#define RUN_TASK_ONE_TIME_ONLY 0


struct scheduler
{
	pqueue_t *pqueue; /* for the 'timer's */
	int run_status;
};

typedef struct timer
{
	unique_id_t uid;
	sch_task_func_t task;
	size_t interval_in_sec;
	time_t abs_next_time;
	void *param;
}sch_timer_t;


/* Utils functions decleretions */
static int TimerComper();
static int IsMatch(const void *data1, const void *data2, void *param);

/* API functions */

sch_t *SchCreate(void)
{
	sch_t *scheduler = NULL;
	pqueue_cmp_func_t timer_cmpare = TimerComper;
	
	scheduler = (sch_t *)malloc(sizeof(sch_t));
	if(NULL == scheduler)
	{
		return (NULL);
	}

	scheduler->pqueue = PQCreate(timer_cmpare, NULL);
	if(NULL == scheduler->pqueue)
	{
		free(scheduler);
		scheduler = NULL;

		return (NULL);
	}

	scheduler->run_status = RUNNING;

	return (scheduler);
}

void SchDestroy(sch_t *sch)
{
	sch_timer_t *timer = NULL;

/* matan - assert missing */

	/* destroy each timer */
	while (!PQIsEmpty(sch->pqueue))
	{
		timer = (sch_timer_t *)PQDequeue(sch->pqueue);
		free(timer);
		timer = NULL;
	}

	/* destroy the pq */
	PQDestroy(sch->pqueue);

	/* destroy the administrative struct */
	free(sch);
	sch = NULL;	
}

unique_id_t SchTimerStart(sch_t *sch, 
                                size_t interval_in_sec,
                                sch_task_func_t task,
                                void* param)
{
	sch_timer_t *timer = NULL;
	int enqueue_status = SUCCESS;

	assert(sch);

	timer = (sch_timer_t *)malloc(sizeof(sch_timer_t));
	if (NULL == timer)
	{
		return (UIDGetBadUID());
	}

	/* create uid and handle fail of 'UIDCreate' */
	timer->uid = UIDCreate();	
	if (UIDIsSame(UIDGetBadUID(), timer->uid))
	{
		free(timer);
		timer = NULL;

		return (UIDGetBadUID());
	}

	timer->task = task;
	timer->interval_in_sec = interval_in_sec;
	timer->param = param;

	timer->abs_next_time = time(NULL) + interval_in_sec;

	enqueue_status = PQEnqueue(sch->pqueue, timer);
	if (enqueue_status)
	{
		free(timer);
		timer = NULL;

		return (UIDGetBadUID());
	}

	return (timer->uid);
}

int SchRun(sch_t *sch)
{
	sch_timer_t *timer = NULL;
	int task_status = RE_RUN_TASK;
	int pq_enqueue_status = SUCCESS;
	time_t curr_time = 0;
	time_t sleep_time = 0;

	assert(sch);

	/* run until no timers or until task failure */
	while(!PQIsEmpty(sch->pqueue) && task_status != TASK_FAILED)
	{
		/* get timer */
		timer = (sch_timer_t *)PQPeek(sch->pqueue);

		/* get current time and check if failed to use to set sleep time */
		curr_time = time(NULL);
		if (-1 == curr_time)
		{
			return (1);
		}

		/* check if next task should be allready, if no send run to sleep */
		sleep_time = timer->abs_next_time - curr_time;
		if (sleep_time > 0)
		{
			sleep(sleep_time);
		}

		timer = (sch_timer_t *)PQDequeue(sch->pqueue);

		task_status = timer->task(sch, timer->uid, timer->param);
		if (RE_RUN_TASK == task_status && sch->run_status != STOP_RUNNING)
		{
			/* get current time and check if failed */
			curr_time = time(NULL);
			if (-1 == curr_time)
			{
				return (1);
			}

			/* adjust next wake up time*/
			timer->abs_next_time = curr_time + timer->interval_in_sec;

			pq_enqueue_status = PQEnqueue(sch->pqueue, timer);
			if (pq_enqueue_status != SUCCESS)
			{
				/* will be change to ernno */
				printf("re-run task setting failed\n");
			}
		}
		else /* if (RUN_TASK_ONE_TIME_ONLY == task_status) */
		{
			free(timer);
			timer = NULL;
		}
	}

	return (task_status != TASK_FAILED);
}

void SchTimerCancel(sch_t *sch, unique_id_t uid)
{
	sch_timer_t *timer = NULL;
	pqueue_is_match_func_t is_match = &IsMatch;

	timer = PQErase(sch->pqueue, &uid, is_match, NULL);
	free(timer);
	timer = NULL;
}


int SchStop(sch_t *sch)
{
	sch->run_status = STOP_RUNNING;

	return (ONE);
}



/* Utils functions */
static int TimerComper(const void *data1, const void *data2, void *param)
{
	UNUSED(param);

	if ((*(sch_timer_t **)data1)->abs_next_time <
		(*(sch_timer_t **)data2)->abs_next_time)
	{
		return (1);
	}
	else if ((*(sch_timer_t **)data1)->abs_next_time >
			 (*(sch_timer_t **)data2)->abs_next_time)
	{
		return (-1);
	}
	else
	{
		return (0);
	}
}

static int IsMatch(const void *data1, const void *data2, void *param)
{
	sch_timer_t *timer = (sch_timer_t*)data1;
	unique_id_t *to_match = (unique_id_t *)data2;

	return (UIDIsSame(timer->uid, *to_match));
}










