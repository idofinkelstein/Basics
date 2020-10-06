#include <stdio.h>

int main()
{
	char *str1 = "hello world";
	char str2[] = "hello world";
	char str3[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
	int x = *(int*)str1;

	int size1 = sizeof(str1);
	int size2 = sizeof(str2);
	int size3 = sizeof(str3);
	

	printf("%d %d %d\n", size1, size2, size3);

	return 0;
}
