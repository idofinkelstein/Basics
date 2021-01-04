#define _POSIX_C_SOURCE (200809L)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <linux/nbd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "bio_access.h"

#define DEV_OPN_FAILURE -1

/* Utility functions declaration */
u_int64_t Ntohll(u_int64_t a);
static int WriteAll(int fd, char* buf, size_t count);

typedef struct 
{
    BioRequest 		 request;
    int 			 nbd_socket;
    struct nbd_reply reply;
    char 			 buffer[1];
} nbd_message;


/*----------------------------------------------------------------------------*/
int BioDevOpen(const char* dev_file, uint64_t size)
{
	int sp[2];
	int nbd, err;

	if (-1 == (err = socketpair(AF_UNIX, SOCK_STREAM, 0, sp)))
	{
		puts("can't create socket pair");
		return (DEV_OPN_FAILURE);
	}
	

	/* achieving file descriptor for /dev/nbd0 */
	if (-1 == (nbd = open(dev_file, O_RDWR)))
	{
		puts("can't open");
		close(sp[1]);
		close(sp[0]);
		return (DEV_OPN_FAILURE);
	}
		
	if (-1 == (err = ioctl(nbd, NBD_SET_SIZE, size)))
	{
		return (DEV_OPN_FAILURE);
	}
	
		
	ioctl(nbd, NBD_CLEAR_QUE);
	if (-1 == (err = ioctl(nbd, NBD_CLEAR_SOCK)))
	{
		return (DEV_OPN_FAILURE);
	}


	if(ioctl(nbd, NBD_SET_SOCK, sp[1]))
	{
		return (DEV_OPN_FAILURE);
	}

	if (ioctl(nbd, NBD_SET_TIMEOUT, 1))
	{
		puts("ioctl NBD_SET_TIMEOUT");
		return (DEV_OPN_FAILURE);
	}

	pid_t pid = fork();
	if (-1 == pid)
	{
		return (DEV_OPN_FAILURE);
	}

	if (0 == pid) /* child process */
	{
		close(sp[0]);
		puts("before do it");
		
		ioctl(nbd, NBD_DO_IT);

		puts("after do it");
		exit(EXIT_SUCCESS);
	}
	else /* parent process */
	{
		close(sp[1]);

		if (-1 == (waitpid(pid, 0, WNOHANG)))
        {
            return (DEV_OPN_FAILURE);
        }
	}

	close(sp[1]);

	return (sp[0]);
}
/*----------------------------------------------------------------------------*/
BioRequest* BioRequestRead(int bioDesc)
{
	nbd_message* message = NULL;
	struct nbd_request request;
	struct nbd_reply reply;
	size_t data_len = 0;

	/* reads request message */
	ReadAll(bioDesc, (char*)&request, sizeof(struct nbd_request));
	
	/* handles only read and write request */
	data_len = (ntohl(request.type) == NBD_CMD_READ || ntohl(request.type) == NBD_CMD_WRITE) * 
				ntohl(request.len);
		
	 /* alloc new nbd_message */
    message = (nbd_message *)malloc(offsetof(nbd_message, buffer) + data_len);
    
    if (NULL == message)
    {
        return (NULL);
    }
    
    /* init reply members */
    reply.magic = htonl(NBD_REPLY_MAGIC);
    reply.error = htonl(0);
    memcpy(reply.handle, request.handle, sizeof(reply.handle));

    /* init message */
    message->request.reqType = ntohl(request.type);
    message->request.dataLen = data_len;
    message->request.offset = Ntohll(request.from);
    message->request.dataBuf = message->buffer;

    /* init reply in message */
    memcpy(&message->reply, &reply, sizeof(struct nbd_reply));
    /* init socket in message */
    message->nbd_socket = bioDesc;

		
	if(message->request.reqType == NBD_CMD_WRITE)
    {
       ReadAll(bioDesc, message->request.dataBuf, message->request.dataLen);
    }
	
                          
    return ((BioRequest*)message);
	
}
/*----------------------------------------------------------------------------*/
void BioRequestDone(BioRequest *req, int error)
{
	nbd_message *message = (nbd_message*)req;
	message->reply.error = htonl(error); 

	switch (req->reqType)
	{
		case (NBD_CMD_WRITE):

	        WriteAll(message->nbd_socket, (char*)&(message->reply),
	                 sizeof(struct nbd_reply));
		break;

    	case (NBD_CMD_READ):
    
        	WriteAll(message->nbd_socket, (char*)&(message->reply),
                 sizeof(struct nbd_reply) + message->request.dataLen);
    		break;

		default:
			break;
	}
    
    free(req);

}

/*----------------------------------------------------------------------------*/
#ifdef WORDS_BIGENDIAN
u_int64_t Ntohll(u_int64_t a) {
  return a;
}
#else
u_int64_t Ntohll(u_int64_t a) 
{
  u_int32_t lo = a & 0xffffffff;
  u_int32_t hi = a >> 32U;
  lo = ntohl(lo);
  hi = ntohl(hi);
  return ((u_int64_t) lo) << 32U | hi;
}
#endif
#define htonll Ntohll
/*----------------------------------------------------------------------------*/
/* reads from fd to buf */
int ReadAll(int fd, char* buf, size_t count)
{
  int bytes_read;

  while (count > 0) 
  {
    bytes_read = read(fd, buf, count);
    buf += bytes_read;
    count -= bytes_read;
  }

  return 0;
}
/*----------------------------------------------------------------------------*/
/* writes to fd from buf */
static int WriteAll(int fd, char* buf, size_t count)
{
  int bytes_written;

  while (count > 0) 
  {
    bytes_written = write(fd, buf, count);
    buf += bytes_written;
    count -= bytes_written;
  }

  return 0;
}
