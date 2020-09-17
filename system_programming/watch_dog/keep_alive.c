#define _DEFAULT_SOURCE
#include <stdio.h>  	/* printf, perror		  */
#include <stdlib.h> 	/* sleep 				  */
#include <string.h>		/* strcmp				  */
#include <signal.h> 	/* sigaction, sigemptyset */
#include <errno.h>		/* errno, perror		  */
#include <unistd.h> 	/* pause 				  */
#include <semaphore.h>	/* semaphore API		  */
#include <stdbool.h>	/* true, false			  */
#include <pthread.h>	/* pthread API			  */
#include <sys/types.h>  /* getpid, kill			  */
#include <sys/wait.h>
#include <fcntl.h>      /* For O_* constants */
#include <sys/stat.h>   /* For mode constants */

#include "scheduler.h" /* scheduler API */
#include "uid.h"

static const char *process_files[] = {"./main_app.Debug.out", "./watch.Debug.out"};

typedef struct keep_alive_info
{
	sem_t *sem;
	sch_t *sched;
	char **argv;
	pid_t pid;
	int creator;

}keep_alive_info_t;

void Sigusr1Handler(int signal_num, siginfo_t *info, void *context);
void Sigusr2Handler(int signal_num, siginfo_t *info, void *context);
void *KeepAlive(void *arg);
keep_alive_info_t *InitThreadInfo(char **argv, pid_t pid, int creator);
int CreateProcess(keep_alive_info_t *thread_info);

static sig_atomic_t shut_down_g = false;
static sig_atomic_t are_u_there_g = false;
static sig_atomic_t partner_pid_g = 0;

int MMI(char **argv)
{
	struct sigaction sigusr1action;
	struct sigaction sigusr2action;
	pid_t pid = 0;
	keep_alive_info_t *thread_info = NULL;
	int creator = 0;
	pthread_t t;

	/* initializing signal handler 1 */
	sigusr1action.sa_sigaction = Sigusr1Handler;
	sigusr1action.sa_flags = SA_SIGINFO; 
	sigemptyset(&sigusr1action.sa_mask);
	sigaction(SIGUSR1, &sigusr1action, NULL);

	/* initializing signal handler 2 */
	sigusr2action.sa_sigaction = Sigusr2Handler;
	sigusr2action.sa_flags = SA_SIGINFO;
	sigemptyset(&sigusr2action.sa_mask);
	sigaction(SIGUSR2, &sigusr2action, NULL);

	/* checks if the user's env  not exists, if so fork and exec WD process */
	if(!getenv("VAR"))
	{
	 	if (0 != putenv("VAR=1"))
		{
			return(1);
		}
		pid = fork();
		creator = 1;

	
		if (-1 == pid)
		{
			exit(1);
		}
		else if(pid == 0) /* in child process */
		{
			if (-1 == execlp("./watch.Debug.out", "./watch.Debug.out", NULL))
			{
				perror("execlp: execlp failed");
				exit(1);
			}
		}
		
	}

	if (pid == 0)
	{
		pid = getppid();
	}

	partner_pid_g = pid;
	thread_info = InitThreadInfo(argv, partner_pid_g, creator);
	if (NULL == thread_info)
	{
		exit(1);
	}

	if (0 != pthread_create(&t, NULL, KeepAlive, thread_info))
	{
		SchDestroy(thread_info->sched);
		free(thread_info);
		perror("pthread_create: pthread_create failed");
		exit(1);
	}

	return 0;
}

void Sigusr1Handler(int signal_num, siginfo_t *info, void *context)
{
	(void)signal_num;
	(void)info;
	(void)context;	

	are_u_there_g = true;
	puts("pulse cheked");
}

int SendPulse(sch_t *sch, unique_id_t uid, void *param) /* task 1 */
{
	keep_alive_info_t *thread_info = (keep_alive_info_t*)param;
	pid_t partner_pid = thread_info->pid;

	(void)sch;
	(void)uid;
	
	if (-1 == kill(partner_pid, SIGUSR1))
	{
		perror("kill: failed to send signal");
		exit(1);
	}

	return 1;
}
int CheckPulse(sch_t *sch, unique_id_t uid, void *param) /* task 2 */
{
	keep_alive_info_t *thread_info = (keep_alive_info_t*)param;
	pid_t partner_pid = thread_info->pid;

	(void)sch;
	(void)uid;

	/* printf("in task2, the pid is: %d\n", (int)getpid()); */

	if (shut_down_g == true)
	{
		/* free everything */
		SchDestroy(thread_info->sched);
		free(thread_info);
		thread_info = NULL;
		sem_post(thread_info->sem);
		kill(partner_pid, SIGUSR2);
		/* pthread_exit(NULL);
		puts("passed 'pthread_exit'"); */
		exit(0);
	}

	if (are_u_there_g == true)
	{
		are_u_there_g = false;
		puts("got the massage");
	}
	else
	{
		/* resurrect the dead process */
		puts("the process is dead");
		
		CreateProcess(thread_info);
		if (-1 == sem_wait(thread_info->sem))
		{
			exit(1);
		}
	}

	return 1;
}

void *KeepAlive(void *arg)
{
	keep_alive_info_t *thread_info = (keep_alive_info_t*)arg;

	SchTimerStart(thread_info->sched, 1, SendPulse, thread_info);
	SchTimerStart(thread_info->sched, 3, CheckPulse, thread_info);

	

	if (thread_info->creator == 1)
	{
		printf("pid in thread (wait): %d\n", (int)getpid());
		if (-1 == sem_wait(thread_info->sem))
		{
			exit(1);
		}
		
	}
	else
	{
		if (-1 == sem_post(thread_info->sem))
		{
			exit(1);
		}
		printf("pid in thread (post): %d\n", (int)getpid());
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

void Sigusr2Handler(int signal_num, siginfo_t *info, void *context)
{
	(void)signal_num;
	(void)info;
	(void)context;	

	shut_down_g = true;
	puts("shut_down flag raised");
}

void DNR()
{
	sem_t *sem = sem_open("/sem", O_CREAT, 0664, 0);

	kill(partner_pid_g, SIGUSR2);
	sem_wait(sem);
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
        /* checks if argv is equal to user app file - "./app.Debug.out" */
       is_user_app = !strcmp(process_files[0], argv[0]);

        /* exec process to the right program - if the process is user app - run 
        watchdog. if the process is watchdog - run user app */
       if (-1 == execlp(process_files[is_user_app], process_files[is_user_app], NULL))
       {
			perror("failed to create process");
            return(1);
       }	
    }

   thread_info->pid = child_pid;

    return(0);
}
