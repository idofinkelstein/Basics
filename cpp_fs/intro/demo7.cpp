#include <dlfcn.h>
#include <stdio.h>

int main()
{
	void *handle;
	void (*f)(void);

	handle = dlopen("./libmyshared.so", RTLD_LAZY);
	if(handle == NULL)
	{
		puts("can't open library");
		return 0;
	}


	f = reinterpret_cast<void (*)(void)>(dlsym(handle, "_Z3bari"));

	if (f == NULL)
	{
		puts("can't find symbol");
		return 0;
	}

	f();
	dlclose(handle);


	return 0;
}
