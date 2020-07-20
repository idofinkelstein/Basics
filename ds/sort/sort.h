#ifndef ILRD_SORT_H
#define ILRD_SORT_H

#include <stddef.h>	/* size_t */


/*int Cmp(const void *data1, const void *data2, void *param);*/

typedef int (*sort_cmp_func_t)(const void *data1, const void *data2, void *param);

/* stable sort */
void BubbleSort(void *base, size_t nmemb, size_t size,
                  sort_cmp_func_t cmp,
                  void *arg);

void SelectionSort(void *base, size_t nmemb, size_t size,
                  sort_cmp_func_t cmp,
                  void *arg);

/* stable sort */
void InsertionSort(void *base, size_t nmemb, size_t size,
                  sort_cmp_func_t cmp,
                  void *arg);

int CountingSort(int *arr, size_t size, int min, int max, int *result);

#endif /* ILRD_SORT_H */ 
