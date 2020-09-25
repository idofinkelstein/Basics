#include "sort.h"

/*
	ShuffleAndSort:
		this function reads the dictionary, blends the words and sorts it again
		according sorting_alghorithm and num_of_threads parameters.

		sorting_alghorithm:
		1 - merge sort.
		2 - bubble sort.
		3 - insertion sort.
		4 - selection sort.

		* any other value - qsort is chosen
*/
void *ShuffleAndSort(size_t num_of_threads, int sorting_alghorithm);


