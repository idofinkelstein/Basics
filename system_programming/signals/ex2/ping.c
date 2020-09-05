#define _POSIX_SOURCE
/******************************************************************************
* Project name:					 	Pingpong_ex2
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

void Sigusr2Handler(int signal_num);
void Sigusr1Handler(int signal_num);
void SendSigToChild(int child_pid);

/********************************  MAIN  *************************************/

int main(void)
{
    int child_pid;
    int child_status;

    child_pid = fork();

    if (child_pid < 0)
    {
        perror("Error: fork");
        return (-1);
    }

    /* inside child */
    else if (0 == child_pid)
    {
        execl("./pong.out", "./pong.out", (char *)NULL);
        perror("Error: evecl");
        abort();
    }
    
    /* inside parent 
    else
    {*/
    signal(SIGUSR2, Sigusr2Handler);
    sleep(1);
    SendSigToChild(child_pid);
    waitpid(child_pid, &child_status, 1);
    /*}*/

    printf("Parent process terminating\n");  
    return (0);
}

/*---------------------------------------------------------------------------*/

void SendSigToChild(int child_pid)
{
    printf("ping\n");
    kill(child_pid, SIGUSR1);
}

/*---------------------------------------------------------------------------*/

void Sigusr2Handler(int signal_num)
{
    (void)signal_num;
    printf("ping\n");
}

/*****************************************************************************/
