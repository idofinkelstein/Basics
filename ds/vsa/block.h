typedef struct block block_t;

struct block
{
	block_t *next;
	size_t available_bytes; /* how many bytes available */
	size_t capacity; 		/* volume of block */
};

