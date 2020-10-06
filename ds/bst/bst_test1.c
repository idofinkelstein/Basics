#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */
#include <assert.h>
#include "bst.h"

typedef struct person
{
    int id;
    char *name;
} person_t;

void TestBSTCreate(void);
void TestBSTIsEmpty(void);
void TestBSTEnd(void);
void TestBSTGetData(void);
void TestBSTDestroy(void);
void TestCase(void);
void TestCase2(void);
int cmp(const void *data1, const void *data2, void *param);
int DoAction(void *data, void *param);



int main()
{
    TestCase2();
    /*TestCase();*/
    TestBSTCreate();
    TestBSTIsEmpty();
    TestBSTEnd();
    TestBSTGetData();
    TestBSTDestroy();
    return (0);
}

void TestBSTCreate(void)
{
    bst_t * tree = NULL;

    tree = BSTtCreate(&cmp, NULL);
    printf("new tree handle address: %p \n", (void*)tree);
    BSTDestroy(tree);
}

void TestBSTIsEmpty(void)
{
    bst_t * tree = NULL;

    tree = BSTtCreate(&cmp, NULL);
    printf("Is new tree empty? (should by 1 for yes): %d \n", BSTIsEmpty(tree));
    BSTDestroy(tree);
}

void TestBSTEnd(void)
{
    bst_t * tree = NULL;
    bst_iter_t iter;

    tree = BSTtCreate(&cmp, NULL);
    iter = BSTEnd(tree);
    printf("end address in new empty list: %p \n", (void*)iter.node);
    BSTDestroy(tree);
}

void TestBSTGetData(void)
{
    bst_t * tree = NULL;
    bst_iter_t iter;

    tree = BSTtCreate(&cmp, NULL);
    iter = BSTEnd(tree);
    printf("end data in new empty list: %p \n", (void*)BSTGetData(iter));
    BSTDestroy(tree);
}

void TestBSTDestroy(void)
{
    bst_t *tree = NULL;
    tree = BSTtCreate(&cmp, NULL);
    BSTDestroy(tree); 
}

void TestCase(void)
{
    person_t person1;
    person_t person2;
    person_t person3; /*temp person for printing etc. */
    person_t person4;
    person_t person5;
    person_t person6;
    bst_t *bst = NULL;
    bst_iter_t iter1;
    bst_iter_t iter2;

    person1.id = 123;
    person1.name = "bob";

    person2.id = 234;
    person2.name = "kiki";

    bst = BSTtCreate(cmp, NULL);
    printf("new empty tree size is: %ld \n", BSTSize(bst));
    iter1 = BSTInsert(bst, &person1);
    printf("size should be 1: %ld \n", BSTSize(bst));

    iter2 = BSTInsert(bst, &person2);
    printf("size should be 2: %ld \n", BSTSize(bst));

    person3 = *(person_t*)BSTGetData(iter2);
    printf("person3 after getdata id: %d, name: %s\n", person3.id, person3.name);
    person3 = *(person_t*)BSTGetData(BSTBegin(bst));
    printf("person3 after getdata and begin id: %d, name: %s\n", person3.id, person3.name);
    
    iter1 = BSTBegin(bst);
    iter2 = BSTBegin(bst);
    printf("is iter1 equal to iter2? (should be yes = 1): %d\n", 
    BSTIterIsEqual(iter1, iter2));

    printf("is tree empty? (should be no = 0): %d\n", 
    BSTIsEmpty(bst));

    iter1 = BSTEnd(bst);
    iter2 = BSTPrev(iter1);
    person3 = *(person_t*)BSTGetData(iter2);
    printf("person3 after getdata from end->prev id: %d, name: %s\n", person3.id, person3.name);

    printf("tree size after 2 elements inserted is: %ld \n", BSTSize(bst));

    person4.name = "lulu";
    person4.id = 789;
    person5.id = 111;
    person5.name = "nili";
    person6.name = "abraham";
    person6.id = 999;
    BSTInsert(bst, &person4);
    BSTInsert(bst, &person5);
    BSTInsert(bst, &person6);
    printf("tree size after 3 more elements inserted is: %ld \n", BSTSize(bst));

    iter1 = BSTEnd(bst);
    iter1 = BSTPrev(iter1);
    while(!BSTIterIsEqual(iter1, BSTEnd(bst)))
    {
        person3 = *(person_t*)BSTGetData(iter1);
        printf("person data from end to top: %d, name: %s\n", person3.id, person3.name);
        iter1 = BSTPrev(iter1);
    }

    iter1 = BSTBegin(bst);
    while(!BSTIterIsEqual(iter1, BSTEnd(bst)))
    {
        person3 = *(person_t*)BSTGetData(iter1);
        printf("person data from root to end: %d, name: %s\n", person3.id, person3.name);
        iter1 = BSTNext(iter1);
    }

    iter2 = BSTFind(bst, &person4);
    person3 = *(person_t*)BSTGetData(iter2);
    printf("person data after find function: %d, name: %s\n", person3.id, person3.name);

    BSTForEach(BSTBegin(bst), BSTEnd(bst), DoAction, NULL);

    iter1 = BSTEnd(bst);
    iter1 = BSTPrev(iter1);
    while(!BSTIterIsEqual(iter1, BSTEnd(bst)))
    {
        person3 = *(person_t*)BSTGetData(iter1);
        printf("person data from end to top after FOREACH function: %d, name: %s\n", person3.id, person3.name);
        iter1 = BSTPrev(iter1);
    }
    
    iter1 = BSTBegin(bst);
    BSTRemove(iter1);
    printf("size should be 4: %ld \n", BSTSize(bst));

    iter1 = BSTEnd(bst);
    iter1 = BSTPrev(iter1);
    while(!BSTIterIsEqual(iter1, BSTEnd(bst)))
    {
        person3 = *(person_t*)BSTGetData(iter1);
        printf("person data from end to top after REMOVE function: %d, name: %s\n", person3.id, person3.name);
        iter1 = BSTPrev(iter1);
    }
    
    BSTDestroy(bst);
}

void TestCase2(void)
{
    person_t person1;
    person_t person2;
    person_t person3;
    person_t person4;

    bst_t *bst = NULL;
    bst_iter_t iter1;
    bst_iter_t iter2;

    person1.id = 123;
    person1.name = "bob";
    person2.id = 456;
    person2.name = "tilda";
    person3.id = 444;
    person3.name = "lili";
    person4.id = 20;
    person4.name = "mike";

    bst = BSTtCreate(cmp, NULL);
    printf("new empty tree size is: %ld \n", BSTSize(bst));
    iter1 = BSTInsert(bst, &person1);
    printf("size should be 1: %ld \n", BSTSize(bst));

    iter1 = BSTInsert(bst, &person2);
    iter1 = BSTInsert(bst, &person3);
    iter1 = BSTInsert(bst, &person4);
    iter1 = BSTFind(bst, &person4);
    BSTRemove(iter1);
    iter1 = BSTFind(bst, &person3);
    BSTRemove(iter1);

    BSTDestroy(bst);
}

int cmp(const void *data1, const void *data2, void *param)
{
    person_t person1;
    person_t person2;
    param = param;

    person1 = *(person_t*)data1;
    person2 = *(person_t*)data2;

    if(person1.id > person2.id)
    {
        return (1);
    }
    else if (person1.id == person2.id)
    {
        return (0);
    }
    return (-1);
}

int DoAction(void *data, void *param)
{
    person_t *person = NULL;
    param = param;

    assert(data);

    person = (person_t*)data;
    ++person->id;
    return (0);
}
