/*******************************************
* File Name: scheduler_test.c			   *
* Name: Matan Yankovich				       *
* Date: 30.6.2020						   *
* Reviewed by: Oriel					   *
* Topic: scheduler						   *
********************************************/
#include <stddef.h> 	/* size_t */
#include <assert.h> 	/* assert */
#include <sys/types.h>  /* ssize_t */
#include <stdlib.h>		/* malloc, free */

#include "utils.h"

#include "scheduler.h"
/*#include "pqueue_heap.h"*/

#define CANCEL_TIMER 2


/* Utils functions decleretions */
int TaskSimple1(sch_t *sch, unique_id_t uid, void *param);
int TaskSimple2(sch_t *sch, unique_id_t uid, void *param);
int TaskCancelTimer(sch_t *sch, unique_id_t uid, void *param);
static void PrintUID(unique_id_t uid);


#if 0
/* User functions */

/* functions for the operitions itself */

/* task that cancel its timer */
TaskLogger(sch, uid, param)
{
	/* check if param is request for 'schTimerCancel' */
	switch ((int)param)


 (CANCEL_TIMER == (int)param)
	{
		schTimerCancel(sch, uid);
	}
}
#endif
/*  */
int main(void)
{
	sch_t *scheduler = NULL;
	size_t interval_in_sec1 = 3;
	size_t interval_in_sec2 = 1;
	size_t interval_in_sec3 = 6;
/*	sch_task_func_t task = TaskSimple; */
	unique_id_t uid1 = UIDGetBadUID();
	unique_id_t uid2 = UIDGetBadUID();
	unique_id_t uid3 = UIDGetBadUID();

	scheduler = SchCreate();
	if (NULL != scheduler)
	{
		printf("'SchCreate' succeed\n");
	}

	uid1 = SchTimerStart(scheduler, interval_in_sec1, TaskSimple1, NULL);
	uid2 = SchTimerStart(scheduler, interval_in_sec2, TaskSimple2, NULL);
	uid3 = SchTimerStart(scheduler, interval_in_sec3, TaskCancelTimer, &uid1);
	PrintUID(uid1);

	SchRun(scheduler);

	SchDestroy(scheduler);
	printf("'SchDestroy' succeed\n");

	return (SUCCESS);
}

/* Utils functions definitions */
int TaskSimple1(sch_t *sch, unique_id_t uid, void *param)
{
	static size_t counter = ZERO;

	UNUSED(sch);
	UNUSED(param);

	printf("Task1 + run worked\n");
	PrintUID(uid);
	++counter;

	if (counter > 4)
	{
		return (0);
	}

	return (1);
}

int TaskSimple2(sch_t *sch, unique_id_t uid, void *param)
{
	static size_t counter = ZERO;

	UNUSED(sch);
	UNUSED(param);

	printf("Task2 + run worked\n");
	PrintUID(uid);
	++counter;

	if (counter > 4)
	{
		return (0);
	}

	return (1);
}

int TaskCancelTimer(sch_t *sch, unique_id_t uid, void *param)
{
	static size_t counter = ZERO;

	UNUSED(sch);
	UNUSED(param);

	SchTimerCancel(sch, *(unique_id_t *)param);

	printf("Cancel Timer 1\n");
}

static void PrintUID(unique_id_t uid)
{
	printf("\nThe UID is:\n");
	printf("%ld-%d-%ld\n\n", uid.time, uid.pid, uid.counter);
}
