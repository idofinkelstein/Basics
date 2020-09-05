#define _DEFAULT_SOURCE
/******************************************************************************
* Project name:					 	Pingpong_ex3
* Developer: 						Matan Yankovich
* Project Lauch: 					Aug 31, 2020
* Submitted for review:				02/09/2020
* Reviewer:
******************************************************************************/

/**********************   PREPROCESSOR DIRECTIVES   **************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/****************************   DECLARATIONS   *******************************/

void Sigusr2Handler(int signal_num, siginfo_t *info, void *context);

/********************************  MAIN  *************************************/

int main(void)
{  
    struct sigaction sigusr2action;
    sigusr2action.sa_sigaction = Sigusr2Handler;
    sigusr2action.sa_flags = SA_SIGINFO;
    sigemptyset(&sigusr2action.sa_mask);
    sigaction(SIGUSR2, &sigusr2action, 0);
    
    printf("my pid (ping) is: %d\n", getpid());
    sleep(15);

    while (1)
    {
        sleep(1);
        pause();
        printf("ping\n");
    }
    
    return (0);
}

/*---------------------------------------------------------------------------*/

void Sigusr2Handler(int signal_num, siginfo_t *info, void *context)
{
    (void)signal_num;
    (void)context;

    if (0 != kill(info->si_pid, SIGUSR1))
    {
        perror("Error: kill sigusr1 failed");
    }
}

/*****************************************************************************/
