#include <stdio.h>	
#include <dlfcn.h>

int main(int argc, char **argv)
{
	char *lib_name = NULL;
	char *func_name = NULL;
	void *handler;
	void (*func)();

	if (argc < 3)
	{
		puts("not enough argument to execute properly");
		return 0;
	}

	lib_name = argv[1];
	func_name = argv[2];

	handler = dlopen(lib_name, RTLD_LAZY);
	if (NULL == handler)
	{
		puts("can't open library");
		return 1;
	}

	func = (void (*)())dlsym(handler, func_name);
	if (func == NULL)
	{
		puts("can't find symbol");
		return 0;
	}

	func();

	dlclose(handler);

	return 0;
}
