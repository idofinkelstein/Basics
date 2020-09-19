#define _DEFAULT_SOURCE
#include <stdio.h>  	/* printf, perror		  */
#include <stdlib.h> 	/* sleep 				  */
#include <string.h>		/* strcmp				  */
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

static const char *process_files[] = {"./main_app.Debug.out", "./watch_dog.Debug.out"};

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
int CreateProcess(keep_alive_info_t *thread_info);

static sig_atomic_t are_u_there_g = false;

int MMI(char **argv)
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
			
			if (NULL == thread_info)
			{
				perror("error: init thread_info failed");
				return 1;
			}

		/*	pthread_create(&t, NULL, KeepAlive, thread_info); to communicate with WD */
			/*pthread_join(t, NULL);*/			
		}
	} 	
	/*else
	{
 		puts("env exist");
		thread_info = InitThreadInfo(argv, getppid(), 0);
		if (NULL == thread_info)
		{
			perror("error: init thread_info failed");
			return 1;
		}

		puts("child was born");
		
		pthread_join(t, NULL);
	}*/
	thread_info = InitThreadInfo(argv, pid, creator);
	pthread_create(&t, NULL, KeepAlive, thread_info);
	/*SchDestroy(thread_info->sched);
	sem_unlink("/sem");
	free(thread_info);*/

	return 0;
}

void Sigusr1Handler(int signal_num, siginfo_t *info, void *context)
{
	(void)signal_num;
	(void)info;
	(void)context;	

	are_u_there_g = true;
	__atomic_store_n(&are_u_there_g, 1, __ATOMIC_SEQ_CST);
	puts("flag was raised");
}

int SendPulse(sch_t *sch, unique_id_t uid, void *param) /* task 1 */
{
	keep_alive_info_t *thread_info = (keep_alive_info_t*)param;
	pid_t partner_pid = thread_info->pid;

	(void)sch;
	(void)uid;
	
	kill(partner_pid, SIGUSR1);
	printf("massage was sent to process %d\n", (int)partner_pid);

	return 1;
}
int CheckPulse(sch_t *sch, unique_id_t uid, void *param) /* task 2 */
{
	keep_alive_info_t *thread_info = (keep_alive_info_t*)param;

	(void)sch;
	(void)uid;
	

	puts("in task2");

	if (are_u_there_g == true)
	{
		are_u_there_g = false;
		 __atomic_store_n(&are_u_there_g, 0, __ATOMIC_SEQ_CST);
		puts("got the massage");
	}
	else
	{
		/* resurrect the dead process */
		puts("the process is dead");
		/*
		fork + exec
		sem_wait
		
		*/
		CreateProcess(thread_info);
		sem_wait(thread_info->sem);
	}

	return 1;
}

void *KeepAlive(void *arg)
{
	keep_alive_info_t *thread_info = (keep_alive_info_t*)arg;

	

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

	SchTimerStart(thread_info->sched, 2, SendPulse, thread_info);
	SchTimerStart(thread_info->sched, 2, CheckPulse, thread_info);

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

int CreateProcess(keep_alive_info_t *thread_info)
{
    pid_t child_pid = 0;
    int is_user_app = 0;
	char **argv = thread_info->argv;

    /* create watchdog process */
    child_pid = fork();

    if(-1 == child_pid)
    {
        return(1);
    }
    if(0 == child_pid)
    {
		puts("creating new process");
        /* check if argv is equal to user app file - "./app.Debug.out" */
       is_user_app = !strcmp(process_files[0], argv[0]);

        /* exec process to the right program - if the process is user app - run 
        watchdog. if the process is watchdog - run user app */
       if (-1 == execlp(process_files[is_user_app], process_files[is_user_app], NULL))
       {
			puts("failed to create process");
            return(1);
       }
		puts("failed to create process");
    }

   thread_info->pid = child_pid;

    return(0);
}
