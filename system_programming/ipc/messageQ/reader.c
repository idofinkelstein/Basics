#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_KEY_PATHNAME "/tmp/mqueue_server_key"
#define PROJECT_ID 'M'
#define QUEUE_PERMISSIONS 0660

struct message 
{
    long message_type;
    char buf [200];
};

int main()
{
    key_t msg_queue_key;
    int qid;
    struct message message;

	/* gets unique key */
    if ((msg_queue_key = ftok (SERVER_KEY_PATHNAME, PROJECT_ID)) == -1)
	{
        perror ("ftok");
        exit (1);
    }

	/* gets message queue ID */
    if ((qid = msgget (msg_queue_key, 0)) == -1) 
	{
        perror ("msgget");
        exit (1);
    }

    /* read an incoming message */
    if (-1 == msgrcv (qid, &message, sizeof(message.buf), 0, 0)) 
	{
        perror ("msgrcv");
        exit (1);
    }

    printf ("Server: message received.\n");

    /* process message */
	puts(message.buf);

	return 0;
}
