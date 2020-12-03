#include <argp.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/nbd.h>
#include <netinet/in.h>
#include <assert.h>
#include <unistd.h>

#include "bio_access.h"

#include <argp.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <assert.h>
#include <unistd.h>

#include "bio_access.h"

#ifndef BUSE_DEBUG
  #define BUSE_DEBUG (0)
#endif

/* function declarations */
static void *data;
int ReadAll(int fd, char* buf, size_t count);

static int HandleRead(void *buf, u_int32_t len, u_int64_t offset)
{
  fprintf(stderr, "R - %lu, %u\n", offset, len);
    
  memcpy(buf, (char *)data + offset, len);

  return (0);
}

static int HandleWrite(const void *buf, u_int32_t len, u_int64_t offset)
{
  fprintf(stderr, "W - %lu, %u\n", offset, len);
    
  memcpy((char *)data + offset, buf, len);

  return (0);
}

/* argument parsing using argp */
static struct argp_option options[] = 
{
  {"verbose", 'v', 0, 0, "Produce verbose output", 0},
  {0},
};

struct arguments {
  unsigned long long size;
  char *device;
  int verbose;
};

static unsigned long long strtoull_with_prefix(const char * str, char * * end) 
{
  unsigned long long v = strtoull(str, end, 0);
  
  switch (**end) 
  {
    case 'K':
      v *= 1024;
      *end += 1;
      break;

    case 'M':
      v *= 1024 * 1024;
      *end += 1;
      break;

    case 'G':
      v *= 1024 * 1024 * 1024;
      *end += 1;
      break;
  }

  return (v);
}

/* Parse a single option. */
static error_t ParseOpt(int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;
  char *endptr;

  switch (key)
  {

    case 'v':
      arguments->verbose = 1;
      break;

    case ARGP_KEY_ARG:
      switch (state->arg_num) 
      {

        case 0:
          arguments->size = strtoull_with_prefix(arg, &endptr);

          if (*endptr != '\0') 
          {
            /* failed to parse integer */
            errx(EXIT_FAILURE, "SIZE must be an integer");
          }

          break;

        case 1:
          arguments->device = arg;
          break;

        default:
          /* Too many arguments. */
          return (ARGP_ERR_UNKNOWN);
      }

      break;

    case ARGP_KEY_END:
      if (state->arg_num < 2) 
      {
        warnx("not enough arguments");
        argp_usage(state);
      }

      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }

  return (0);
}

static struct argp argp = 
{
  .options = options,
  .parser = ParseOpt,
  .args_doc = "SIZE DEVICE",
  .doc = "BUSE virtual block device that stores its content in memory.\n"
         "`SIZE` accepts suffixes K, M, G. `DEVICE` is path to block device, for example \"/dev/nbd0\".",
};


int main(int argc, char *argv[]) 
{
  BioRequest* next_request = NULL;
	uint32_t error = 0;

  struct arguments arguments = 
  {
    .verbose = 0,
  };

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  data = malloc(arguments.size);

  if (data == NULL) 
  {
    err(EXIT_FAILURE, "failed to alloc space for data");
  }

  //int nbd_socket = buse_main(arguments.device, &aop, (void *)&arguments.verbose);
  int nbd_socket = BioDevOpen(arguments.device, arguments.size);

  while (1)
  {
    /* serve NBD socket */
     next_request = BioRequestRead(nbd_socket);
		if (NULL == next_request)
		{
			fprintf(stderr, "request read failed\n");
			close(nbd_socket);
      
			return(EXIT_FAILURE);
		}
		
		switch(next_request->reqType)
		{

		case NBD_CMD_READ:
					
			error = HandleRead(next_request->dataBuf, 
							next_request->dataLen, 
							next_request->offset);
			break;

		case NBD_CMD_WRITE:
	
			ReadAll(nbd_socket, next_request->dataBuf, next_request->dataLen);

			error = HandleWrite(next_request->dataBuf, 
							 next_request->dataLen, 
							 next_request->offset);
			break;
		}

		BioRequestDone(next_request, error);
  }

  return (0);
}