int main()
{
	int *segv =(void*)0;

	*segv = 5;

	return 0;
}
