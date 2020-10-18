#include <stdio.h>
#include <stdlib.h>

#include "string.h"
void foo(String *s);
void MyTest();
void bar(const char* arg, String *tmp_arg);

	


int main()
{
	printf("Line %d\n", __LINE__);
	String s1;
	StringCtor(&s1, "Hello", "");

	printf("Line %d\n", __LINE__);
	String s2;
	StringCCtor(&s2, &s1);


	printf("Line %d\n", __LINE__);
	String s3;
	String temp;
#ifdef NO_ELISION
	StringCtor(&temp, "Shalom", "");
	StringCCtor(&s3, &temp);
	StringDtor(&temp);
#else
	StringCtor(&s3, "Shalom", "");
#endif


	printf("Line %d\n", __LINE__);
	String *s4 = malloc(sizeof(String));
	StringCtor(s4, "", "");

	printf("Line %d\n", __LINE__);
	StringCCtor(&temp, &s3);
	s4 = OperatorAsignment(s4, &temp);
	StringDtor(&temp);

	printf("Line %d\n", __LINE__);
	StringCtor(&temp, "Shalom", "");
	if (OperatorComparison(&s3, &temp)) {}
	StringDtor(&temp);

	printf("Line %d\n", __LINE__);
	char c = *OperatorSubscript(&s3, 3);

	printf("Line %d\n", __LINE__);
	StringCCtor(&temp, &s3);
	foo(&s3);
	StringDtor(&temp);

	printf("Line %d\n", __LINE__);
	String cpy_tmp;
#ifdef NO_ELISION
	StringCtor(&temp, "RD90 are champions", "");
	StringCCtor(&cpy_tmp, &temp);
	foo(&cpy_tmp);
	StringDtor(&temp);
	StringDtor(&cpy_tmp);

#else
	StringCtor(&temp, "RD90 are champions", "");
	foo(&temp);
	StringDtor(&temp);
#endif

	printf("Line %d\n", __LINE__);
	bar("We love C++", &temp);
	c = *OperatorSubscript(&temp, 9);
	StringDtor(&temp);

	printf("Line %d\n", __LINE__);
	StringDtor(s4);
	free(s4);

	printf("Line %d\n", __LINE__);
	StringDtor(&s1);
	StringDtor(&s2);
	StringDtor(&s3);

	return c;
}

void foo(String *s)
{
	printf("Line %d\n", __LINE__);
	printf("foo got the arg:\n");
	printf("%s\n", OperatorSubscript(s, 0));
}

void bar(const char* arg, String *tmp_arg)
{
	String tmp1, tmp2;
	StringCtor(&tmp1, arg, "");
	StringCtor(&tmp2, "Really?", "");
	OperatorAdd(&tmp1, &tmp2, tmp_arg);

	StringDtor(&tmp1);
	StringDtor(&tmp2);
}









void MyTest()
{
	String s1, s2, s3, res;

	StringCtor(&s1, "hello ", "");
	puts("s1 created");
	StringCtor(&s2, "world", "");
	puts("s1 created");
	StringCCtor(&s3, &s1);
	puts("s1 created");
	OperatorCmpdAdd(&s1, &s2);
	puts("s1 += s2 ");
	OperatorAdd(&s3, &s2, &res);
	StringDtor(&res);
	puts("s3 + s2 ");

	puts(s1.m_str);
	puts(s2.m_str);
	puts(s3.m_str);
	puts(res.m_str);



	StringDtor(&s1);
	StringDtor(&s2);
	StringDtor(&s3);
}
