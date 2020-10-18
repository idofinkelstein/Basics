#pragma once

#include <stddef.h>

typedef struct 
{
	char *m_str;
}String;

void StringCtor(String * const this, const char *str1, const char *str2);
void StringCCtor(String * const this, const String *str);
void StringDtor(String * const this);

void OperatorAdd(const String *s1, const String *s2, String *temp);

String *OperatorCmpdAdd(String * const this, const String *other);
String *OperatorAsignment(String * const this,const String *other);
int OperatorComparison(String * const this, const String *other);

char *OperatorSubscript(String * const this, size_t idx);
const char *OperatorSubscriptCnst(const String * const this, size_t idx);

void swap(String *a, String *b);

void Cleanup(String * const this);

char *ConcatIMP(String * const this, const char *s1, const char *s2);

