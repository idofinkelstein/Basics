#define ODD 1
#define EVEN 2

int ListEvenOrOdd(list_node_t *head)
{
	while(head)
	{
		if (head->next == NULL)
		{
			return (ODD);
		}

		head = head->next->next;
	}

	return (EVEN);
}
