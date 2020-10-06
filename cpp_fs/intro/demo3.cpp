typedef struct List List_t;
typedef struct Person Person_t;

struct List 
{
	List_t *node;
	int key;
};

struct Person
{
	char *name;
	int age;
};

Person_t *ll_find(List_t *ll, int key);

void foo(List_t *ll, int key, int age)
{
	void *vv = ll_find(ll, key);
	
//	Person_t *p = (Person_t*)ll;
//	Person_t *p = static_cast<Person_t*>(ll);
	Person_t *p = static_cast<Person_t*>(vv);

	

	p->age = age;
}

void foo()
{
	char *str = "aaa";

	strlen(str);
}
