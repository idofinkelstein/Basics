
#include <stdio.h>
#include <string.h>
#include "stack.h"

int IsBalanced(char *str)
{
	size_t size = 0;
	size_t len = strlen(str);
	stack_t *stack = StackCreate(len);

	while (*str)
	{
		if ((']' == *str && NULL == StackPeek(stack)) ||
		    (')' == *str && NULL == StackPeek(stack)) ||
		    ('}' == *str && NULL == StackPeek(stack)))
		{
			return 0;
		}
		else if ('[' == *str || '{' == *str || '(' == *str)
		{
			StackPush(stack , str);
			++str;
		}
		else if ((']' == *str && '[' == *(char*)StackPeek(stack)) ||
		   		(')' == *str && '(' == *(char*)StackPeek(stack)) ||
		    	('}' == *str && '{' == *(char*)StackPeek(stack)))
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

	StackDestroy(stack);

	return (0 == size);
		
}

int main()
{
	char str[] = "fdd{53}45{}}{$}";	
	printf("is balanced? %d\n", IsBalanced(str));
	printf("is balanced? %d\n", IsBalanced("{dfgd()fgj}FG((GFH)fgh){(1)}"));
	printf("is balanced? %d\n", IsBalanced("([{fff(())}{}])[]"));

	printf("is balanced? %d\n", IsBalanced("{{{}}}"));
	printf("is balanced? %d\n", IsBalanced("{df[]gd(gfj)fgj}FG((GFH)[fgh){()}"));

	return 0;
}

