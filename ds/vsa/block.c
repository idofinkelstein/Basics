
#include "vsa.h"
#include "block.h"

size_t BlockCapacity(block_t *block)
{
	return (block->capacity);
}

size_t BlockAvailableBytes(block_t *block)
{
	return (block->available_bytes);
}

block_t *BlockNext(block_t *block)
{
	return ((block_t*)((char*)block + actual_block_size));
}
