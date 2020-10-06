#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma pack(2)

typedef struct log
{
	void *data;	
}log_t;

union numbers
{
	int i;
	float f;
	double d;
};

struct crd
{
	unsigned int s : 2;
	int a;
	unsigned int t : 4;
};

struct crdl
{
	unsigned int s : 2;
	int a;
	unsigned int t : 4;
	long l;
};

struct abc
{
	int a;
	char b;
	char c;
};/* guessed size: 8byte */

struct bca
{
	char b;
	char c;
	int a;
}; /* guessed size: 8byte */

struct bac
{
	char b;
	int a;
	char c;
}; /* guessed size: 12byte */

int add(void **data, void *num)
{
	*(int*)data += *(int*)&num;

	return 0;
}

int addstring(void **data, void *str)
{
	strcat(*data,str);

	return 0;
}

int main()
{
	log_t arr[2];
	void *num = (int*)5;
	char str[] = "world";
	
	
	arr[0].data = malloc(15);	
	strcpy((char*)arr[0].data, "hello "); 

	*(int*)&arr[1].data = 11;

	add(&arr[1].data, num);

	addstring(&arr[0].data, str);

	printf("%d\n", *(int*)&arr[1].data);
	printf("%s\n", (char*)arr[0].data);

	printf("size of abc: %ld\n", sizeof(struct abc));
	printf("size of abc: %ld\n", sizeof(struct bca));
	printf("size of abc: %ld\n", sizeof(struct bac));
	printf("size of crd: %ld\n", sizeof(struct crd));
	printf("size of crdl: %ld\n", sizeof(struct crdl));

	free(arr[0].data);
		

	return 0;
}
