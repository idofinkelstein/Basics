/***********************
File name: scheduler_test.c
Author: Ido Finkelstein
Reviewer: Rita Lampert 
Date: 1/7/2020
************************/

#include <stdio.h>   /* printf       */
#include <stdbool.h> /* true, false  */

#include "scheduler.h"

/* task function declarations */
int task1(sch_t *sch, unique_id_t uid, void *param);
int task2(sch_t *sch, unique_id_t uid, void *param);
int task3(sch_t *sch, unique_id_t uid, void *param);

int main()
{
	sch_t *sched = SchCreate();
	sch_task_func_t task_func = task1;
	unique_id_t uid1 = SchTimerStart(sched, 1, task_func , NULL);
	unique_id_t bad_uid = {0, -1, -1};
	unique_id_t uid2;
	int stop = true;
	int run = false;

	SchTimerStart(sched, 3, task3, &run);
	printf("%ld-%d-%ld\n", uid1.time, uid1.pid, uid1.counter);
	uid2 = SchTimerStart(sched, 2, task2, NULL);
	
	printf("%ld-%d-%ld\n", uid2.time, uid2.pid, uid2.counter);
	uid1 = SchTimerStart(sched,3, task_func , NULL);
	
	printf("%ld-%d-%ld\n", uid1.time, uid1.pid, uid1.counter);

	SchTimerStart(sched, 2, task3, &stop);

	uid2 = SchTimerStart(sched, 4, task2, NULL);

	SchRun(sched);

	SchDestroy(sched);

	return 0;
}

int task1(sch_t *sch, unique_id_t uid, void *param)
{
	static size_t count = 0;
	printf("hello!\n");

	(void)uid;
	(void)param;
	(void)sch;

	++count;

	if (count < 3)
	{
		return 1;
	}

	return 0;
}

int task2(sch_t *sch, unique_id_t uid, void *param)
{
	(void)uid;
	(void)param;
	(void)sch;

	printf("hi!\n");

	return 0;
}

int task3(sch_t *sch, unique_id_t uid, void *param)
{
	int signal = *(int*)param;
	(void)uid;

	if (true == signal)
	{
		SchStop(sch);
	}
	else
	{
		puts("continue!");
	}

	printf("%d\n", signal);

	return 0;
}


