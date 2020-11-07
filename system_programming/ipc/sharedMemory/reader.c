#include <stdio.h> /* perror */
#include <stdlib.h> /* exit */
#include <string.h> /* memcpy, strlen */
#include <unistd.h> /* write */
#include <sys/types.h> /* shared memory API */
#include <sys/ipc.h> /* shared memory API */
#include <sys/shm.h> /* shared memory API */

#define KEY_PATHNAME "/tmp/shrd_mem_key"
#define PROJECT_ID 'I'
#define PAGE_SIZE 4096
#define STD_OUTPUT 1

int main()
{
	key_t mem_key;
	int mem_id = 0, len = 0;
	void *shrd_mem_addr = NULL;

	if (-1 == system("touch " KEY_PATHNAME))
	{
		perror("system");
		exit(EXIT_FAILURE);
	}

	if (-1 == (mem_key =  ftok(KEY_PATHNAME, PROJECT_ID)))
	{
		perror("ftok");
		exit(EXIT_FAILURE);
	}

	if (-1 == (mem_id = shmget(mem_key, PAGE_SIZE, 0)))
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}

	if ((void*)-1 == (shrd_mem_addr = shmat(mem_id, NULL, SHM_RDONLY)))
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}

	len = strlen((char*)shrd_mem_addr);
	
	write(STD_OUTPUT, shrd_mem_addr, len);

	if ( -1 == shmdt(shrd_mem_addr))
	{
		perror("shmdt");
		exit(EXIT_FAILURE);
	}

	return 0;
}
