/* 
*  scheduler is a tool used for creating schedulered tasks recurring or
*   non-recurring.
*
*  Tasks can create other tasks, cancel them or add conditional-cancel rules 
*
*   
*  Attributes:
* -	Grows by demand.
* -	User has a pointer to the scheduler.
*
* Main operations on scheduler:
* -   SchCreate - Creates an empty scheduler
* -   SchDestroy - Destroys asch given scheduler
* -   SchRun - Hands control over to the app and timers start running, 
*     until scheduler is empty.
* -   SchStop - Stops a running scheduler
*
* -   Timer Start - Starts a new timer in the scheduler
* -   Timer Cancel - Cancels an existing task in the scheduler 
*
*  
*
* Scheduler API
* -   29/06/20 18:20 - Ver:  1.0  API team proposal
* -   30/06/20 13:11 - Ver:  1.1  API team proposal :
*                                 -1- in define ILRD change sch to SCH.
*                                 -2- Sop function rename.
*                                 -3- adding more discription to schtimerstart.
*                                                         
*
*/

#ifndef ILRD_SCH_H
#define ILRD_SCH_H

#include "uid.h" /* unique_id_t */


typedef struct scheduler sch_t;


/* Task function return values:
* -1 : task failed.
*  0 : task is finished.
*  1 : re-run task.
*/
typedef int (*sch_task_func_t)(sch_t *sch, unique_id_t uid, void *param);


/* sample task function  example 

int taskFunction1(sch_t *sched, uit_t uid, void *param)
{
    if ((size_t)param == 1)
    {
        schTimerCancel(sched, uid);
    }

    return 0;
}

int main()
{
    schTimerStart(sched, 3, taskFunction1, 1);
    schTimerStart(sched, 4, taskFunction1, 2);
}

*/

/*---------------------------------------------------------------------------*/

/* SchCreate:
*   - Creates an empty scheduler.
*
* Return Value:
*   - if succeeded, return a pointer to a scheduler.
*   - if failed, return NULL.
*/
sch_t *SchCreate(void);

/*---------------------------------------------------------------------------*/

/* SchDestroy:
*   - Destroys a given scheduler.
*
* Args:
*   - sch - pointer to sch given by a user.
*
* Comments: 
*   - in case of invalid scheduler - undefined behavior.
*
*/

void SchDestroy(sch_t *sch);

/*---------------------------------------------------------------------------*/

/* SchStop:
*	- Stops a running scheduler - exits.
*
* Args:
*	- sched - pointer to a scheduler given by a user.
*
* Return Value - boolean:
*	- 1 - scheduler has been stopped (TRUE).
*	- 0 - scheduler was not stopped (FALSE).
*/

int SchStop(sch_t *sch);

/*---------------------------------------------------------------------------*/

/* SchTimerRun:
*   - Inversion of control, all timers will start running by the app.
*
* Args:
*   - sch - pointer to a sch given by a user.
*
* Return Value - boolean:
*	- 1 - scheduler stopped due to task failure (FAILURE).
*	- 0 - scheduler finished successfuly (SUCCESS).
*
* Comments: 
*   - in case of failure - run stops.
*   - if schedular is emptied - function will be stopped.
*   - in case of invalid scheduler - undefined behavior.
*/

int SchRun(sch_t *sch);

/*---------------------------------------------------------------------------*/

/* SchTimerStart:
*   - Inserts a new timer to a given scheduler, according to scheduler's 
* pre-defined priority.
*
* Args:
*   - sch - pointer to a sch given by a user.
*   - interval_in_sec - time span in seconds, between repetitions of task.
*   - task - task function.
*   - param - dynamic parameter provided by user.
*  
* Return Value - uid of the timer.
*   
* Comments: 
*   - in case of invalid scheduler - undefined behavior.
*   - user should compare return value to BadUID for success or failure check.
*  
*/
unique_id_t SchTimerStart(sch_t *sch, 
						  size_t interval_in_sec,
						  sch_task_func_t task,
						  void* param);

/*---------------------------------------------------------------------------*/

/* SchTimerCancel:
*   - Removes a timer from a given scheduler.
*
* Args:
*   - sch - pointer to a scheduler given by a user.
*   - uid - id of the timer to be canceled.
*
* Comments: 
*   - in case of invalid scheduler- undefined behavior.
*   - in case of empty scheduler - undefined behaviour.
*/
void SchTimerCancel(sch_t *sch, unique_id_t uid);

#endif /* ILRD_sch_H */ 
