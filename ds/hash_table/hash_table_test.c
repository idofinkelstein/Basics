/* #include <stdlib.h> */ /* malloc */
#include <stdio.h> /* printf */
#include <assert.h>
#include <stdlib.h> /* rand */
#include <string.h> /* strcmp */
#include <math.h> /* pow */

#include "hash_table.h"
/*---------------------------------------------------------------------------*/
#define	UNUSED(x) (void)(x)
/*---------------------------------------------------------------------------*/
/* Utils functions declarations */
/*---------------------------------------------------------------------------*/
void TestHashCreateAndDestroy(void);
void TestHashInsert(void);
void TestHashSizeFunctions(void);
void TestHashRemove(void);
void TestHashFind(void);
size_t HashFunc(const void *data1, void *hash_param);
int IsMatch(void *data, void *param);
int Print(void *data, void *param);
void TestCase1(void);
/*---------------------------------------------------------------------------*/
int main()
{
	TestHashCreateAndDestroy();
	TestHashInsert();
	TestHashSizeFunctions();
	TestHashRemove();
	TestHashFind();
	TestCase1();

	return (0);
}
/*---------------------------------------------------------------------------*/
/* Utils functions definitions */
/*---------------------------------------------------------------------------*/
void TestHashCreateAndDestroy(void)
{
	hash_t *hash = HashCreate(&HashFunc, NULL, &IsMatch, 10000);

	HashDestroy(hash);
}
/*---------------------------------------------------------------------------*/
void TestHashInsert(void)
{
	hash_t *hash = HashCreate(&HashFunc, NULL, &IsMatch, 10000);

	printf("Is 'HashInsert' worked ?\t(should be 0)\n%d\n",
	HashInsert(hash, "hello"));

	HashDestroy(hash);
}
/*---------------------------------------------------------------------------*/
void TestHashSizeFunctions(void)
{
	hash_t *hash = HashCreate(&HashFunc, NULL, &IsMatch, 10000);

	HashInsert(hash, "hello");
	HashInsert(hash, "hello");
	HashInsert(hash, "hello");

	printf("Is 'HashSize' worked ?\t(should be 3)\n%lu\n",
	HashSize(hash));

	printf("Is 'HashTableSize' worked ?\t(should be ?)\n%lu\n",
	HashTableSize(hash));

	printf("Is 'HashBucketSize' worked ?\t(should be ?)\n%lu\n",
	HashBucketSize(0, hash));

	printf("Is 'HashBucketSize' worked ?\t(should be ?)\n%lu\n",
	HashBucketSize(6, hash));

	printf("Is 'HashBucketSize' worked ?\t(should be ?)\n%lu\n",
	HashBucketSize(7, hash));

	HashDestroy(hash);
}
/*---------------------------------------------------------------------------*/
void TestHashRemove(void)
{
	hash_t *hash = HashCreate(&HashFunc, NULL, &IsMatch, 10000);

	HashInsert(hash, "123");
	HashInsert(hash, "234");
	HashInsert(hash, "345");

	printf("Before remove 'HashBucketSize' of 234 is ?\t(should be 1)\n%lu\n",
	HashBucketSize(150, hash));

	HashRemove(hash, "234");

	printf("After remove 'HashBucketSize' of 234 is ?\t(should be 0)\n%lu\n",
	HashBucketSize(150, hash));	

	HashDestroy(hash);	
}

/*---------------------------------------------------------------------------*/
void TestHashFind(void)
{
	hash_t *hash = HashCreate(&HashFunc, NULL, &IsMatch, 10000);

	char *str1 = "123";
	char *str2 = "12";
	char *find_result = NULL;

	HashInsert(hash, str1);
	HashInsert(hash, "234");
	HashInsert(hash, "345");

	find_result = (char *)HashFind(hash, str1);

	if (NULL == find_result)
	{
		puts("not found!");
	}
	else
	{
		printf("found it! -> %s\n", find_result);
	}
	
	find_result = (char *)HashFind(hash, str2);

	HashForEach(hash, Print, NULL);

	if (NULL == find_result)
	{
		puts("not found!");
	}
	else
	{
		printf("found it! -> %s\n",find_result);
	}

	HashDestroy(hash);	
}

void TestCase1(void)
{
	char *file_name = "/usr/share/dict/american-english";
	FILE *file_ptr = fopen(file_name, "r");
	hash_t *hash = HashCreate(&HashFunc, NULL, &IsMatch, 10000);
	char *s = malloc(100);
	char **dict = NULL;
	size_t len = 0;
	char c = '\0';
	size_t cnt = 0;
	size_t i = 0;
	char **start = NULL;

	/* checks if successeded to open file */
	if(NULL != file_ptr)
	{
		puts("SECCESS");
	}
	else
	{
		puts("failed");
		return;
	}
	
	/* gets number of words in dictionary */
	while((c = fgetc(file_ptr)) && c != EOF)
	{
		if ('\n' == c)
		{ 
			++cnt; 
		}
	}	

	fclose(file_ptr);
	file_ptr = fopen(file_name, "r");


	dict = (char**)malloc(sizeof(char*) * cnt);	
	start = dict;

	for (i = 0; i < cnt; ++i)
	{
		fgets(s, 30 , file_ptr);
		len = strlen(s);
		*(s + len - 1) = '\0'; /* removes new line character */
		dict[i] =(char*) malloc(len + 1);
		strcpy(dict[i], s);
		HashInsert(hash, dict[i]);
	}

	HashForEach(hash, Print, NULL);

	dict = start;

	fclose(file_ptr);
	

	for (i = 0; i < cnt; ++i)
	{
		free(dict[i]);	
	}
	
	free(dict);
	HashDestroy(hash);	
	free(s);
}

/*---------------------------------------------------------------------------*/
size_t HashFunc(const void *data1, void *hash_param)
{
	size_t hash_value = 0;
	size_t i = 0;
	size_t p = 17;
	size_t m = (size_t)pow(10, 2);

	UNUSED(hash_param);

	/* hash value = data[0] * p^0 + data[1] * p^1 + data[2] * p^2 + ... + data[i] * p^i */
	for (i = 0; '\0' != *((char *)data1 + i); ++i)
	{
		hash_value += *(char *)data1 * pow(p, i);
	}

	return (hash_value / m);
}
/*---------------------------------------------------------------------------*/
int IsMatch(void *data, void *param)
{
	return (0 == strcmp((char *)data, (char *)param));
}

int Print(void *data, void *param)
{
	(void)param;

	printf("%s\n", (char*)data);

	return 0;
}
