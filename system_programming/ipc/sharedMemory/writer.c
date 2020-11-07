#include <stdio.h> /* perror */
#include <stdlib.h> /* exit */
#include <string.h>	/* memcpy, strlen */
#include <sys/types.h> /* shared memory API */
#include <sys/ipc.h> /* shared memory API */
#include <sys/shm.h> /* shared memory API */

#define KEY_PATHNAME "/tmp/shrd_mem_key"
#define PROJECT_ID 'I'
#define PAGE_SIZE 4096
#define MESSAGE "This is the shared memory segment"

int main()
{
	key_t mem_key;
	int mem_id = 0, len = 0;
	void *shrd_mem_addr = NULL;

	/* creates tmp file for system v key */
	if (-1 == system("touch " KEY_PATHNAME))
	{
		perror("system");
		exit(EXIT_FAILURE);
	}

	/* genarates key with ftok*/
	if (-1 == (mem_key =  ftok(KEY_PATHNAME, PROJECT_ID)))
	{
		perror("ftok");
		exit(EXIT_FAILURE);
	}

	/* gets shared memory id */
	if (-1 == (mem_id = shmget(mem_key, PAGE_SIZE, IPC_CREAT | 0660)))
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}

	/* ataches shared memory to address */
	if ((void*)-1 == (shrd_mem_addr = shmat(mem_id, NULL, 0)))
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}

	/* writes a message */
	len = strlen(MESSAGE);
	memcpy(shrd_mem_addr, MESSAGE, len + 1);

	/* detaches from shared memory */
	if ( -1 == shmdt(shrd_mem_addr))
	{
		perror("shmdt");
		exit(EXIT_FAILURE);
	}

	return 0;
}

