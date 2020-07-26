#include <stdio.h>
#include <string.h>


#include "recursion.h"

void TesTStrLen(void);
void FlipTest(void);
void TestStrCmp(void);
void TestStrCpy(void);
void TestStrCat(void);

int main()
{
	int n = 3;

	printf("%d\n", Fibonacci(n));
	printf("%d\n", Fibonacci2(n));
	/*FlipTest();*/
	TesTStrLen();
	TestStrCmp();
	TestStrCpy();
	TestStrCat();

	return 0;
}

void TesTStrLen(void)
{
	printf("%ld\n", StrLen("12345"));
	printf("%ld\n", StrLen("12"));
	printf("%ld\n", StrLen(""));
}

void TestStrCmp(void)
{
	puts("*** test strcmp & StrCmp ***");
	
	printf("StrCmp: %d\n", StrCmp("hello", "hello"));
	printf("strcmp: %d\n", strcmp("hello", "hello"));
	printf("StrCmp: %d\n", StrCmp("heklo", "hello"));
	printf("strcmp: %d\n", strcmp("heklo", "hello"));
	printf("StrCmp: %d\n", StrCmp("hello", "hell"));
	printf("strcmp: %d\n", strcmp("hello", "hell"));
	printf("StrCmp: %d\n", StrCmp("aello", "hello"));
	printf("strcmp: %d\n", strcmp("aello", "hello"));
}

void TestStrCpy(void)
{
	char str[] = "                   ";

	puts("*** test strcpy & StrCpy ***");

	printf("StrCpy: %s\n", StrCpy(str, "h"));
	printf("strcpy: %s\n", strcpy(str, "h"));
	printf("StrCpy: %s\n", StrCpy(str, "world"));
	printf("strcpy: %s\n", strcpy(str, "world"));
	printf("StrCpy: %s\n", StrCpy(str, ""));
	printf("strcpy: %s\n", strcpy(str, ""));
	printf("StrCpy: %s\n", StrCpy(str, "123456789"));
	printf("strcpy: %s\n", strcpy(str, "123456789"));
}

void TestStrCat(void)
{
	char str1[30] = "ABS\0";
	char str2[30] = "ABS\0";
	char str3[30] = "ABS\0";
	char str4[30] = "ABS\0";
	char str5[30] = "ABS\0";
	char str6[30] = "ABS\0";
	char str7[30] = "ABS\0";
	char str8[30] = "ABS\0";

	puts("*** test strcat & StrCat ***");

	printf("StrCat: %s\n", StrCat(str1, "h"));
	printf("strcat: %s\n", strcat(str2, "h"));
	printf("StrCat: %s\n", StrCat(str3, "world"));
	printf("strcat: %s\n", strcat(str4, "world"));
	printf("StrCat: %s\n", StrCat(str5, ""));
	printf("strcat: %s\n", strcat(str6, ""));
	printf("StrCat: %s\n", StrCat(str7, "123456789"));
	printf("strcat: %s\n", strcat(str8, "123456789"));
}

void FlipTest(void)
{
	node_t *node1 = NULL;
	node_t *node2 = NULL;
	node_t *node3 = NULL;
	node_t *node4 = NULL;
	node_t *node5 = NULL;
	node_t *node6 = NULL;
	node_t *node7 = NULL;
	node_t *node8 = NULL;
	node_t *curr = NULL;
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	int x4 = 4;
	int x5 = 5;
	int x6 = 6;
	int x7 = 7;
	int x8 = 8;

	node1 = CreateNode(node1);
	node2 = CreateNode(node2);
	node3 = CreateNode(node3);
	node4 = CreateNode(node4);
	node5 = CreateNode(node5);
	node6 = CreateNode(node6);
	node7 = CreateNode(node7);
	node8 = CreateNode(node8);

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = node7;
	node7->next = node8;
	node8->next = NULL;
	curr = node1;
	node1->data = &x1;
	node2->data = &x2;
	node3->data = &x3;
	node4->data = &x4;
	node5->data = &x5;
	node6->data = &x6;
	node7->data = &x7;
	node8->data = &x8;
	
	while (curr)
	{
		printf("%d ", *(int*)curr->data);
		curr = curr->next;
	}
	puts("");

	node1 = Flip2(node1);

	while (node1)
	{
		printf("%d ", *(int*)node1->data);
		node1 = node1->next;
	}
	puts("");

	SListDestroy(node8);
}

