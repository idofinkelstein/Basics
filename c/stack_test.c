

#include <stdio.h>

#include "f_stack.h"
#include "c_stack.h"

int main()
{
	float arr[] = {3.4, 43.3, 32.4, 11.4};
	size_t size_f = sizeof(arr) / sizeof(float);
	char c[] = {'a', 'b', 'c', 'd'};
	size_t size_c = sizeof(c);
	size_t i = 0;
	c_stack_t *cstack = CStackCreate(size_c);
	f_stack_t *fstack = FStackCreate(size_f);

	for (i = 0; i < size_f; ++i)
	{
		FStackPush(fstack, arr[i]);
	}

	for (i = 0; i < size_f; ++i)
	{
		printf("%f\n", FStackPeek(fstack));
		FStackPop(fstack);
	}

	for (i = 0; i < size_c; ++i)
	{
		CStackPush(cstack, c[i]);
	}

	for (i = 0; i < size_c; ++i)
	{
		printf("%c\n", CStackPeek(cstack));
		CStackPop(cstack);
	}

	FStackDestroy(fstack);
	CStackDestroy(cstack);


	return 0;
}
