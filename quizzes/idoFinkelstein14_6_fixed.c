int IsBalanced(char *str)
{
	size_t size = 0;
	size_t len = strlen(str);
	stact_t stack = StackCreate(len);

	while (*str)
	{
		if ((']' == *str && NULL; == StackPeep(stack)) ||
		    (')' == *str && NULL == StackPeep(stack)) ||
		    ('}' == *str && NULL == StackPeep(stack)))
		{
			return 0;
		}

		if ('[' == *str || '{' == *str || '(' == *str)
		{
			StackPush(stack , *str);
			++str;
		}

		if ((']' == *str && '[' == StackPeep(stack)) ||
		    (')' == *str && '(' == StackPeep(stack)) ||
		    ('}' == *str && '{' == StackPeep(stack)))
		{
			StackPop(stack);
			++str;
		}
		else
		{
			++str;
		}
	}

	size = StackSize(stack);

	DestroyStack(stack);

	return (0 == size);
		
}
