typedef struct node
{
	void *data;
	struct node *next;
} node_t;


void SListDestroy(node_t *head);
node_t *CreateNode(node_t *node);
int Fibonacci(int element_index);
int Fibonacci2(int element_index);
node_t *Flip(node_t *head);
node_t *Flip2(node_t *head);
size_t StrLen(const char *str);
int StrCmp(const char *str1, const char *str2);
char *StrCpy(char *dest, const char *src);
char *StrCat(char *dest, const char *src);

