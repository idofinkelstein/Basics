#include <stdio.h>

void Foo(void)
{
	printf("hello world!\n");
}

int main()
{
	int x = 6;
	int *ptr_x = &x;

	float f = 4.2;
	float *ptr_f = &f;

	void *ptr = NULL;

	typedef void (*FP) (void);

	FP foo_ptr = &Foo;

	foo_ptr();

	printf("*&ptr_x = %p\n", (void*)ptr_x);
	printf("&x = %p\n", (void*)&x);

	printf("*&ptr_f = %p\n", (void*)ptr_f);
	printf("&f = %p\n", (void*)&f);

	printf("*(int*)&ptr = %d\n", *(int*)&ptr);
	printf("*(float*)&ptr = %f\n", *(float*)&ptr);

	printf("*(int*)&ptr_x = %d\n", *(int*)&ptr_x);
	printf("*(float*)&ptr_f = %f\n", *(float*)&ptr_f);

	*(int*)&ptr = 135;
	printf("*(int*)&ptr = %d\n", *(int*)&ptr);
	
	*(float*)&ptr = 121.76543;
	printf("*(int*)&ptr = %f\n", *(float*)&ptr);

	return 0;
}
