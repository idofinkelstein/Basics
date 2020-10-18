#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.h"

void StringCtor(String * const this, const char *str1, const char *str2)
{
	puts("\tString ctor");
	this->m_str = ConcatIMP(this, str1, str2);

}

void StringCCtor(String * const this, const String *str)
{
	puts("\tString cctor");
	this->m_str = ConcatIMP(this, str->m_str, "");

}

void StringDtor(String * const this)
{
	Cleanup(this);
}

String *OperatorAsignment(String * const this,const String *other) /* = */
{
	puts("\tString oper=");	
	if (this != other)
	{
		char *temp_str = ConcatIMP(this, other->m_str, "");
		free(this->m_str);
		this->m_str = temp_str;
	}
	return (this);	
}

String *OperatorCmpdAdd(String * const this, const String *other) /* += */
{
	/* s1 += s2 */
	String temp;
	puts("\tString oper+=");		
	StringCtor(&temp, this->m_str, other->m_str);
	OperatorAsignment(this, &temp);
	StringDtor(&temp);

	return (this);
}

void OperatorAdd(const String *s1, const String *s2, String *res) /* + */
{
	/* s1 = s2 + s3 */
	puts("\tString oper+");	
	StringCCtor(res, s1);
	OperatorCmpdAdd(res, s2);

}

int OperatorComparison(String * const this, const String *other)
{
	puts("\tString oper==");	
	return (!strcmp(this->m_str, other->m_str));
}

const char *OperatorSubscriptCnst(const String * const this, size_t idx)
{
		puts("\tString oper[] const");	
		return (&this->m_str[idx]);
}

char *OperatorSubscript(String * const this, size_t idx)
{
	puts("\tString oper[]");	
	return ((char*)OperatorSubscriptCnst(this, idx));
}

char *ConcatIMP(String * const this, const char *s1, const char *s2)
{
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2) + 1;

	char* str = malloc((len1 + len2) * sizeof(char));
	(void)this;

	memcpy(str, s1, len1);
	memcpy(str + len1, s2, len2);

	return str;
}

void Cleanup(String * const this)
{
	puts("\tString dtor");
	free(this->m_str);
}
