#define _DEFAULT_SOURCE
#include <stdio.h>  	/* printf, perror		  */
#include <stdlib.h> 	/* sleep 				  */
#include <signal.h> 	/* sigaction, sigemptyset */
#include <errno.h>		/* errno, perror		  */
#include <unistd.h> 	/* pause 				  */
#include <semaphore.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/types.h>  /* getpid, kill			  */
#include <sys/wait.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

#include "scheduler.h" /* scheduler API */
#include "uid.h"

typedef struct keep_alive_info
{
	sem_t *sem;
	sch_t *sched;
	char **argv;
	pid_t pid;
	int creator;

}keep_alive_info_t;

void Sigusr1Handler(int signal_num, siginfo_t *info, void *context);
void *KeepAlive(void *arg);
keep_alive_info_t *InitThreadInfo(char **argv, pid_t pid, int creator);

int are_u_there_g = false;

void MMI(char **argv)
{
	struct sigaction sigusr2action;
	pid_t pid = 0;
	keep_alive_info_t *thread_info = NULL;
	int creator = 0;
	pthread_t t;

	/* initializing signal handler */
	sigusr2action.sa_sigaction = Sigusr1Handler;
	sigusr2action.sa_flags = SA_SIGINFO; 
	sigemptyset(&sigusr2action.sa_mask);
	sigaction(SIGUSR1, &sigusr2action, NULL);

	/* checks if the user's env  not exists, if so fork and exec WD process */
	if(!getenv("VAR"))
	{
	 	putenv("VAR=1");
		pid = fork();

	
		if (-1 == pid)
		{
			exit(1);
		}
		else if(pid == 0) /* in child process */
		{
			execlp("watch.Debug.out", "watch.Debug.out", NULL);
			puts("exec failed");
			exit(1);
		}
		else if (pid > 0) /* in parent process */
		{
			creator = 1;
			thread_info = InitThreadInfo(argv, pid, creator);
			if (NULL == thread_info)
			{
				perror("error: init thread_info failed");
				return;
			}

			pthread_create(&t, NULL, KeepAlive, thread_info); /*to communicate with WD */
			pthread_join(t, NULL);			
		}
	} 	
	else
	{
 		puts("env exist");
		thread_info = InitThreadInfo(argv, getppid(), 0);
		if (NULL == thread_info)
		{
			perror("error: init thread_info failed");
			return;
		}

		pthread_create(&t, NULL, KeepAlive, thread_info);
		pthread_join(t, NULL);
	}


	

	
	
	
	
	
#if 0
	
		
#endif
}

void Sigusr1Handler(int signal_num, siginfo_t *info, void *context)
{
	are_u_there_g = true;
	puts("flag was raised");
}

int SendPulse(sch_t *sch, unique_id_t uid, void *param) /* task 1 */
{
	keep_alive_info_t *thread_info = (keep_alive_info_t*)param;
	pid_t partner_pid = thread_info->pid;
	
	kill(partner_pid, SIGUSR1);
	printf("massage was sent to process %d\n", (int)partner_pid);

	/*SchTimerStart(thread_info->sched, 1, SendPulse, thread_info);*/

	return 0;
}
int CheckPulse(sch_t *sch, unique_id_t uid, void *param) /* task 2 */
{
	keep_alive_info_t *thread_info = (keep_alive_info_t*)param;

	if (are_u_there_g == true)
	{
		are_u_there_g  = false;
		puts("got the massage");
	}
	else
	{
		/* resurrect the dead process */
		puts("the process is dead");
		
	}

	/*SchTimerStart(thread_info->sched, 1, CheckPulse, thread_info);*/

	return 0;
}

void *KeepAlive(void *arg)
{
	keep_alive_info_t *thread_info = (keep_alive_info_t*)arg;

	SchTimerStart(thread_info->sched, 1, SendPulse, thread_info);
	SchTimerStart(thread_info->sched, 1, CheckPulse, thread_info);

	if (thread_info->creator == 1)
	{
		sem_wait(thread_info->sem);
	}
	else
	{
		sem_post(thread_info->sem);
	}

	SchRun(thread_info->sched);
	

	return (NULL);
}

keep_alive_info_t *InitThreadInfo(char **argv, pid_t pid, int creator)
{
	keep_alive_info_t *thread_info = NULL;

	thread_info = (keep_alive_info_t*)malloc(sizeof(keep_alive_info_t));

	if (NULL == thread_info)
	{
		return (NULL);
	}

	thread_info->sched = SchCreate();

	if (NULL == thread_info->sched)
	{
		free(thread_info);
		return (NULL);
	}

	thread_info->sem = sem_open("/sem", O_CREAT, 0664, 0);

	if (NULL == thread_info->sem)
	{
		free(thread_info->sched);
		free(thread_info);
		return (NULL);
	}

	thread_info->argv = argv;
	thread_info->pid = pid;
	thread_info->creator = creator;

	return (thread_info);
}

void DNR()
{

}
