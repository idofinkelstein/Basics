#include <stdio.h>

#include "avl.h"

int Compare(const void *data1, const void *data2, void *param);

void TestCase1(void);

int main()
{
	TestCase1();

	return 0;
}

void TestCase1(void)
{
	avl_t *avl = AVLCreate(Compare, NULL);
			  /* 0   1  2  3  4  5   6   7   8   9  10 */
	int arr[] = {0, 1, 2, 3, 0, 66, 43, 36, 37, 3, 7, 38};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;
	int x = 23;

	for (i = 0; i < size; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	printf("size = %ld\n", AVLSize(avl));

	if (AVLFind(avl, &arr[5]))
	{
		puts("found!");
	}
	else
	{
		puts("not found!");	
	}

	AVLInsert(avl, &x);
	if (AVLFind(avl, &x))
	{
		puts("found!");
	}
	else
	{
		puts("not found!");	
	}

	AVLFind(avl, &arr[1]);

	AVLDestroy(avl);
}

int Compare(const void *data1, const void *data2, void *param)
{
	(void)param;

	return (*(int*)data1 - *(int*)data2);
}
