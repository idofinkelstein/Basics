
/*********************    PREPROCESSOR DIRECTIVES    *************************/
#include <assert.h>
#include <errno.h>
#include <err.h>
#include <linux/nbd.h>
#include <fcntl.h>
#include <linux/nbd.h>
#include <netinet/in.h>
#include <stdint.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>

#include "bio_access.h"

/******************************************************************************/
typedef struct nbd_message
{
    BioRequest req;
    int nbd_socket;
    struct nbd_reply reply;
    char buffer[1];  
}nbd_message_t;


/* TO DO - CLEANUP */

/************************* Function Declarations *******************************/
static int write_all(int fd, char* buf, size_t count);
static void CopyRequest(nbd_message_t *nbd_meesage, struct nbd_request *request, 
                                                                int bioDesc);
u_int64_t ntohll(u_int64_t a);
int ReadAll(int fd, char* buf, size_t count);
static void KernelSide(int fd);
/******************************************************************************/

int BioDevOpen(const char* dev_file, uint64_t size)
{
    int sp[2] = {0};
    int nbd = 0, err = 0;

    err = socketpair(AF_UNIX, SOCK_STREAM, 0, sp);
    if(err)
    {
        return(-1);
    }

    /* Opening nbd socket */
    nbd = open(dev_file, O_RDWR);
    if ((-1) == nbd)
    {
        fprintf(stderr, "Failed to open `%s': %s\n"
                "Is kernel module `nbd' loaded and you have permissions "
                "to access the device?\n", dev_file, strerror(errno));
        return (1);
    }

    /* Setting message size */
    err += ioctl(nbd, NBD_SET_SIZE, size);
    err += ioctl(nbd, NBD_CLEAR_QUE);
    err += ioctl(nbd, NBD_CLEAR_SOCK);
    err += ioctl(nbd, NBD_SET_SOCK, sp[1]);

    if(err)
    {
        return(-1);
    }

    pid_t pid = fork();

    /* Inside child */
    if (0 == pid)
    {
        close(sp[0]);
        KernelSide(nbd);

        exit(0);
    }

    /* Inside parent */
    close(sp[1]);

    return (sp[0]);
}


BioRequest* BioRequestRead(int bioDesc)
{
    nbd_message_t* ndb_message = NULL;
    struct nbd_request request;
    size_t len = 0;
    size_t data_len = ntohl(request.len);
    /* read request from sk to nbd_request */
    ReadAll(bioDesc, (char *)&request, sizeof(struct nbd_request));
    
    len = (request.type == NBD_CMD_READ || request.type == NBD_CMD_WRITE) * data_len;

    /* alloc new nbd_message */
    ndb_message = (nbd_message_t *)malloc(offsetof(nbd_message_t, buffer) + 
                                                                data_len);
    if (!ndb_message)
    {
        return(NULL);
    }

    CopyRequest(ndb_message, &request, bioDesc);

    /* To do */
    if(request.type == NBD_CMD_WRITE)
    {
        write(bioDesc, &ndb_message->buffer, data_len);
    }

    return ((BioRequest *)ndb_message);
}

void BioRequestDone(BioRequest* req, int error)
{
    nbd_message_t *message = (nbd_message_t *)req;
    size_t size_to_write = 0;

    message->reply.error = htonl(error);

    if (NBD_CMD_READ == req->reqType)
    {
        size_to_write = message->req.dataLen + sizeof(struct nbd_reply);
    }
    else
    {
        size_to_write = sizeof(struct nbd_reply);
    }

    write(message->nbd_socket, (char *)&(message->reply), size_to_write);

    free(req);
}

static void CopyRequest(nbd_message_t *nbd_meesage, struct nbd_request *request, 
                                                                int bioDesc)
{
    struct nbd_reply reply;
    size_t reply_len = sizeof(struct nbd_reply);

    /* init reply members */
    reply.magic = htonl(NBD_REPLY_MAGIC);
    reply.error = htonl(0);
    memcpy(reply.handle, request->handle, sizeof(reply.handle));

    /* init next_message */
    nbd_meesage->req.reqType = ntohl(request->type);
    nbd_meesage->req.dataLen = ntohl(request->len);
    nbd_meesage->req.offset = ntohll(request->from);
    nbd_meesage->req.dataBuf = nbd_meesage->buffer;

    /* init reply in next_message */
    memcpy(&nbd_meesage->reply, &reply, reply_len);
    /* init socket in next_message */
    nbd_meesage->nbd_socket = bioDesc;
} 

static int write_all(int fd, char* buf, size_t count)
{
  int bytes_written;

  while (count > 0) {
    bytes_written = write(fd, buf, count);
    assert(bytes_written > 0);
    buf += bytes_written;
    count -= bytes_written;
  }
  assert(count == 0);

  return 0;
}

int ReadAll(int fd, char* buf, size_t count)
{
  int bytes_read;

  while (count > 0) {
    bytes_read = read(fd, buf, count);
    assert(bytes_read > 0);
    buf += bytes_read;
    count -= bytes_read;
  }
  assert(count == 0);

  return 0;
}

u_int64_t ntohll(u_int64_t a) {
  u_int32_t lo = a & 0xffffffff;
  u_int32_t hi = a >> 32U;
  lo = ntohl(lo);
  hi = ntohl(hi);
  return ((u_int64_t) lo) << 32U | hi;
}

static void KernelSide(int fd)
{
    int err = 0;
    err = ioctl(fd, NBD_DO_IT);
    if (err == -1)
        {
        warn("NBD_DO_IT terminated with error");
        exit(EXIT_FAILURE);
    } 
}
