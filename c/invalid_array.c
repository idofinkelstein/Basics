
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *arr = (int*)malloc(sizeof(int) * 10);
	char *c = (char*)malloc(sizeof(char));
	int i;
	int *ptr = NULL;
	
	*ptr = 4;	

	free(c);
	*c = 't'; 

	if (arr[5] == 10)
		puts("can't be");

	printf("c = %s\n", c);

	for (i = 0; i <= 14; i++)
	{
		arr[i] = i;
	}
	
	for (i = 0; i <= 14; i++)
	{
		printf("arr[%d] = %d\n", i, arr[i]);
	}

	return 0;
}
