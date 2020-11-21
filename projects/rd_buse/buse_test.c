#include <argp.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bio_access.h"

#define DEV_OPN_FAILURE -1

/* BUSE callbacks */
static void *data; /* represent the device */

static error_t ParseOpt(int key, char *arg, struct argp_state *state);
static void UserRead(void *buf, u_int32_t len, u_int64_t offset);
static void UserWrite(const void *buf, u_int32_t len, u_int64_t offset);
static unsigned long long StrToUllWithPrefix(const char *str, char **end);

struct arguments 
{
	unsigned long long size;
	char 			   *device;
	int 			   verbose;
};


/* argument parsing using argp */

static struct argp_option options[] = 
{
  {"verbose", 'v', 0, 0, "Produce verbose output", 0},
  {0},
};


static struct argp argp = 
{
  .options = options,
  .parser = ParseOpt,
  .args_doc = "SIZE DEVICE",
  .doc = "BUSE virtual block device that stores its content in memory.\n"
         "`SIZE` accepts suffixes K, M, G. `DEVICE` is path to block device,"
		 " for example \"/dev/nbd0\".",
};

int main(int argc, char *argv[]) 
{
	int nbd_socket = 0;
    int error = 0;
    BioRequest *bioRequest = NULL;

	struct arguments arguments = 
	{
		.verbose = 0,
	};

	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	data = malloc(arguments.size);
	if (NULL == data)
	{
		perror("malloc failed");
		return (EXIT_FAILURE);
	}

	nbd_socket = BioDevOpen(arguments.device, arguments.size);
	if (DEV_OPN_FAILURE == nbd_socket)
	{
		perror("BioDevOpen failed");
		puts(arguments.device);
		free(data);
		return (EXIT_FAILURE);
	}

	while (1)
	{
		
		bioRequest = BioRequestRead(nbd_socket);
		if (NULL == bioRequest)
		{
			free(data);
			return (EXIT_FAILURE);
		}

		switch (bioRequest->reqType)
		{
			case (NBD_CMD_READ):

				UserRead(bioRequest->dataBuf, bioRequest->dataLen, bioRequest->offset);
				break;

			case (NBD_CMD_WRITE):

				UserWrite(bioRequest->dataBuf, bioRequest->dataLen, bioRequest->offset);
				break;

			default:
				break;
		}

	BioRequestDone(bioRequest, error);
	}


	return 0;
}

static void UserRead(void *buf, u_int32_t len, u_int64_t offset)
{
	memcpy(buf, (char *)data + offset, len);
}

static void UserWrite(const void *buf, u_int32_t len, u_int64_t offset)
{
	memcpy((char *)data + offset, buf, len);
}




static unsigned long long StrToUllWithPrefix(const char *str, char **end) 
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
	return v;
}

/* Parse a single option. */
static error_t ParseOpt(int key, char *arg, struct argp_state *state) 
{
  struct arguments *arguments = state->input;
  char * endptr;

  switch (key) 
  {

    case 'v':
      arguments->verbose = 1;
      break;

    case ARGP_KEY_ARG:
      switch (state->arg_num) 
      {

        case 0:
          arguments->size = StrToUllWithPrefix(arg, &endptr);
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
          return ARGP_ERR_UNKNOWN;
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

  return 0;
}




