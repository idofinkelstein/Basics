#include <dlfcn.h>
#include <stdio.h>
#include "l1.h"

int main()
{
	void *handle;
	void (*f)(void);

	handle = dlopen("./libl1.so", RTLD_LAZY);
	if (!handle)
	{
		puts("error open library");
		return 0;
	}

	f = (void (*)(void))dlsym(handle, "_Z3foov");
	if (!f)
	{
		puts("error - no symbol found");
		return 0;
	}

	f();
	return 0;
}

