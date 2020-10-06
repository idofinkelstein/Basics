/*************************************
* 									 *			
* file name - bst_test.c			 *
* writer - Anna Poryadkov		 	 *
* reviewer - Ido Finkelstein		 *
* date -27.07.2020					 *
* topic - DS - BST					 *
*									 *
**************************************/

#include <stdio.h> /* printf, size_t */
#include <stdlib.h> /* calloc, free */

#include "bst.h"

#define UNUSED(x) (void)(x)

/* data struct */
typedef struct
{
	int id;
	int age;
	char *name;
}dog_data_t;

/* -------- Test functions Declaration -------- */

static void BSTCreateTest(void);
static void BSTIsEmptyTest(void);
static void BSTSizeTest(void);
static void BSTIterIsEqualTest(void);
static void BSTInsertTest(void);
static void BSTFindTest(void);
static void BSTForEachTest(void);

/*------------------------- Utility functions -------------------------------*/
static int CompId(const void *data1, const void *data2, void *param);
static dog_data_t *NewRecord(int id, int age, char *name);
static void PrintData(bst_t *bst_test);
static int AddAge(void *data, void *param);

/* ----------- main ----------- */
int main()
{
	/* unit testing */
	BSTCreateTest();
	printf("--------------------------------------------------\n");
	BSTIsEmptyTest();
	printf("--------------------------------------------------\n");	
	BSTInsertTest();
	printf("--------------------------------------------------\n");
	BSTSizeTest();
	printf("--------------------------------------------------\n");
	BSTIterIsEqualTest();
	printf("--------------------------------------------------\n");
	BSTFindTest();
	printf("--------------------------------------------------\n");
	BSTForEachTest();
	
	return(0);
} 

/* ----------- Test Functions ----------- */
static void BSTCreateTest(void)
{
	bst_t *bst_test = NULL;

	printf("\nBSTCreateTest: \n\n");

	bst_test = BSTCreate(CompId, NULL);

	if (NULL == bst_test)
	{
		printf ("creation of new bst failed!\n");
	}
	else
	{
		printf ("New bst created!\n");
	}

	BSTDestroy(bst_test);
}

static void BSTIsEmptyTest(void)
{
	bst_t *bst_test = NULL;

	printf("\nBSTIsEmptyTest: \n\n");

	bst_test = BSTCreate(CompId, NULL);

	if (NULL == bst_test)
	{
		printf ("creation of new bst failed!\n");
	}
	else
	{
		printf ("New bst created!\n");
	}

	printf("\n Result of IsEmpty: %d (0-not empty, 1-empty)\n", 
		  BSTIsEmpty(bst_test));

	BSTDestroy(bst_test);
}

static void BSTInsertTest(void)
{
	bst_t *bst_test = NULL;
	bst_iter_t test_iter = {0};
	bst_iter_t test_iter2 = {0};

	dog_data_t *data_test_1 = NewRecord(12, 2, "Toy");
	dog_data_t *data_test_2 = NewRecord(4, 10, "Pit");
	dog_data_t *data_test_3 = NewRecord(5, 4, "Rex");
	dog_data_t *data_test_4 = NewRecord(14, 8, "Huney");
	dog_data_t *data_test_5 = NewRecord(20, 3, "Mac");
	dog_data_t *data_test_6 = NewRecord(7, 15, "Shoko");

	printf("\nBSTInsertTest: \n\n");
	bst_test = BSTCreate(CompId, NULL);
		
	printf("New bst created.\n");
	test_iter = BSTInsert(bst_test, data_test_1);
	test_iter = BSTInsert(bst_test, data_test_2);
	test_iter = BSTInsert(bst_test, data_test_3);
	test_iter2 = BSTInsert(bst_test, data_test_4);
	test_iter = BSTInsert(bst_test, data_test_5);
	test_iter = BSTInsert(bst_test, data_test_6);

	printf("Six elements inserted\n");
	PrintData(bst_test);

	printf("one element removed\n");
	BSTRemove(test_iter);
	PrintData(bst_test);

	printf("one element removed\n");	
	BSTRemove(test_iter2);
	PrintData(bst_test);

	BSTDestroy(bst_test);
	free(data_test_1);
	free(data_test_2);
	free(data_test_3);
	free(data_test_4);
	free(data_test_5);
	free(data_test_6);
}

static void BSTSizeTest(void)
{
	bst_t *bst_test = NULL;


	dog_data_t *data_test_1 = NewRecord(12, 2, "Toy");
	dog_data_t *data_test_2 = NewRecord(23, 10, "Pit");

	printf("\nBSTSizeTest: \n\n");

	bst_test = BSTCreate(CompId, NULL);

	if (NULL == bst_test)
	{
		printf ("creation of new bst failed!\n");
	}
	else
	{
		printf ("New bst created!\n");
	}

	printf("Size of bst: %lu\n", BSTSize(bst_test));

	BSTInsert(bst_test, data_test_2);
	BSTInsert(bst_test, data_test_1);

	printf("Two elements added to bst. Size of bst: %lu\n", BSTSize(bst_test));
	
	BSTDestroy(bst_test);

	free(data_test_1);
	free(data_test_2);
}

static void BSTIterIsEqualTest(void)
{

	bst_t *bst_test = NULL;
	bst_iter_t test_iter = {0};

	dog_data_t *data_test_1 = NewRecord(14, 4, "Rex");

	printf("\nBSTIterIsEqualTest: \n\n");

	bst_test = BSTCreate(CompId, NULL);

	if (NULL == bst_test)
	{
		printf ("creation of new bst failed!\n");
	}
	else
	{
		printf ("New bst created!\n");
	}

	printf("Beginning of bst equal to end: %d (0-not equal, 1-equal)\n",
			BSTIterIsEqual(BSTBegin(bst_test), BSTEnd(bst_test)));

	test_iter = BSTInsert(bst_test, data_test_1);
	if (BSTIterIsEqual(test_iter, BSTEnd(bst_test)))
	{
		printf ("element insertion failed!\n");
	}
	else
	{
		printf ("One element inserted successfully!\n");
	}

	printf("After insertion one element, beginning of bst equal to end: "
			"%d (0-not equal, 1-equal) \n",
			BSTIterIsEqual(BSTBegin(bst_test), BSTEnd(bst_test)));

	BSTDestroy(bst_test);

	free(data_test_1);
}

static void BSTFindTest(void)
{
	bst_t *bst_test = NULL;
	bst_iter_t test_iter = {0};
	dog_data_t *result_data = NULL;
	int id = 14;

	dog_data_t *data_test_1 = NewRecord(12, 2, "Toy");
	dog_data_t *data_test_2 = NewRecord(4, 10, "Pit");
	dog_data_t *data_test_3 = NewRecord(5, 4, "Rex");
	dog_data_t *data_test_4 = NewRecord(14, 8, "Huney");
	dog_data_t *data_test_5 = NewRecord(20, 3, "Mac");
	dog_data_t *data_test_6 = NewRecord(7, 15, "Shoko");

	bst_test = BSTCreate(CompId, NULL);

	printf("\nBSTFindTest: \n\n");
	
	test_iter = BSTInsert(bst_test, data_test_1);
	test_iter = BSTInsert(bst_test, data_test_2);
	test_iter = BSTInsert(bst_test, data_test_3);
	test_iter = BSTInsert(bst_test, data_test_4);
	test_iter = BSTInsert(bst_test, data_test_5);
	test_iter = BSTInsert(bst_test, data_test_6);

	test_iter = BSTBegin(bst_test);
	PrintData(bst_test);

	test_iter = BSTFind(bst_test, &id);
	
	printf("test_iter equal to end: %d (0-not equal, 1-equal)\n",
		  BSTIterIsEqual(test_iter, BSTEnd(bst_test)));
	result_data = BSTGetData(test_iter);
	printf("the data id to find: %d, data stored in test_iter: %d\n",
		  id, result_data->id);

	id = 150;
	test_iter = BSTFind(bst_test, &id);
	printf("test_iter equal to end: %d (0-not equal, 1-equal). "
	"the data id %d not found\n", 
	BSTIterIsEqual(test_iter, BSTEnd(bst_test)), id);
	
	BSTDestroy(bst_test);
	free(data_test_1);
	free(data_test_2);
	free(data_test_3);
	free(data_test_4);
	free(data_test_5);
	free(data_test_6);
}

static void BSTForEachTest(void)
{
	bst_t *bst_test = NULL;
	bst_iter_t test_iter = {0};
	int add = 1;

	dog_data_t *data_test_1 = NewRecord(11, 2, "Toy");
	dog_data_t *data_test_2 = NewRecord(10, 10, "Pit");
	dog_data_t *data_test_3 = NewRecord(4, 4, "Rex");
	dog_data_t *data_test_4 = NewRecord(13, 8, "Huney");
	dog_data_t *data_test_5 = NewRecord(5, 3, "Mac");
	dog_data_t *data_test_6 = NewRecord(9, 15, "Shoko");

	bst_test = BSTCreate(CompId, NULL);

	printf("\nBSTForEachTest: \n\n");
	
	test_iter = BSTInsert(bst_test, data_test_1);
	test_iter = BSTInsert(bst_test, data_test_2);
	test_iter = BSTInsert(bst_test, data_test_3);
	test_iter = BSTInsert(bst_test, data_test_4);
	test_iter = BSTInsert(bst_test, data_test_5);
	test_iter = BSTInsert(bst_test, data_test_6);

	test_iter = BSTBegin(bst_test);
	PrintData(bst_test);

	printf("Add 1 to data age. status for ForEach func: %d"
		   " (0 - success, 1 - fail)\n",
		   BSTForEach(test_iter, BSTEnd(bst_test), AddAge, &add));

	test_iter = BSTBegin(bst_test);
	PrintData(bst_test);

	BSTDestroy(bst_test);
	free(data_test_1);
	free(data_test_2);
	free(data_test_3);
	free(data_test_4);
	free(data_test_5);
	free(data_test_6);
}

/*-------------------------- Utility functions ------------------------------*/
/* create new data */
static dog_data_t *NewRecord(int id, int age, char *name)
{
	dog_data_t *new_data = (dog_data_t *) calloc (1, sizeof(dog_data_t));
	if (NULL == new_data)
	{
		return (NULL);
	}

	new_data->id = id;
	new_data->age = age;
	new_data->name = name;

	return (new_data);
}
/*---------------------------------------------------------------------------*/
/* return value is boolean - 1 for match, 0 if not matched */
/* return value is boolean - TRUE if data1 is before data2, FALSE if not */
/* function should be implemented considering stable sorted policy */
static int CompId(const void *data1, const void *data2, void *param)
{
	UNUSED(param);

	return (((dog_data_t *)data1)->id - ((dog_data_t *)data2)->id);
}
/*---------------------------------------------------------------------------*/
static void PrintData(bst_t *bst_test)
{
	bst_iter_t test_iter = BSTBegin(bst_test);
	dog_data_t *result_data = NULL;

	printf("the data in bst:\n");

	while (!BSTIterIsEqual(BSTEnd(bst_test), test_iter))
	{
		result_data = BSTGetData(test_iter);
		printf("id: %d, age: %d, name: %s\n", 
			   result_data->id, result_data->age, result_data->name);
		test_iter = BSTNext(test_iter);
	}
}
/*---------------------------------------------------------------------------*/
/* add param to data . return value - 0 for success, 1 for fail */
static int AddAge(void *data, void *param)
{
	dog_data_t *new_data = (dog_data_t *)data;

	new_data->age += *(int *)param;

	return (new_data->age > 100);
}
