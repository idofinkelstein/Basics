
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


	SchTimerStart(sched, 3, task3, NULL);
	
	SchTimerStart(sched, 2, task2, NULL);
	
	SchTimerStart(sched, 1, task1 , NULL);
	
	SchRun(sched);

	SchDestroy(sched);

	return 0;
}

int task1(sch_t *sch, unique_id_t uid, void *param)
{
	printf("hello!\n");

	(void)uid;
	(void)param;
	(void)sch;

	return 1;
}

int task2(sch_t *sch, unique_id_t uid, void *param)
{
	(void)uid;
	(void)param;
	(void)sch;

	printf("hi!\n");

	return 1;
}

int task3(sch_t *sch, unique_id_t uid, void *param)
{
	
(	void)uid;
	(void)param;
	(void)sch;

	printf("hello to you\n");

	return 1;
}


