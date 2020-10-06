#include <stdio.h>
#include <stdlib.h>

#define SIZEOF_TYPE(TYPE) ((long)(1 + (TYPE*)0))

#define SIZEOF_VAR(A) ((char*)(&(A) + 1) - (char*)&(A)) 

struct abc
{
	int a;
	char b;
	char c;
	int *arr;
};

int main()
{

	/*struct abc *s;*/
	struct abc *ptr = malloc(sizeof(struct abc));
	size_t size = 0;

	/*size = (struct abc*)&(ptr->c) - (struct abc*)0 ;*/

	size = (size_t)(&((struct abc *)0)->arr);


	printf("%ld\n", size);

	free(ptr);

	return 0;
}
