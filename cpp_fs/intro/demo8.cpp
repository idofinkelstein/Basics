#include <stdio.h>
#include <dlfcn.h>

int main()
{
	void *handle;
	void (*f)(void);

	handle = dlopen("./libmylib.so", RTLD_LAZY);
	if (handle == NULL)
	{
		puts("error - 11");
		return 0;
	}

	f = (void (*)(void))dlsym(handle, "foo");
	if (f == NULL)
	{
		puts("error - 18");
		return 0;
	}

	f();
	dlclose(handle);

	return 0;
}
