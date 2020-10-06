
#ifndef ILRD_RADIX_SORT_H
#define ILRD_RADIX_SORT_H

#include <stddef.h>	/* size_t */

typedef unsigned uint;

int CountingSort(uint *arr, size_t size, uint min, uint max);

int RadixBitsSort(uint *arr, size_t size, size_t num_of_bits);

#endif /* ILRD_RADIX_SORT_H */ 


