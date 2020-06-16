/*********************
File name: queue_test.c
Author: Ido Finkelstein
Reviewer: Rita Lempert
Date: 13/6/2020
**********************/

#include <stdio.h> /* printf */

#include "slist.h"
#include "queue.h"

void Scenario1Test(void);

int main()
{
	/* tests API */
	int x = 7;
	queue_t *queue = QCreate();	
	
	printf("size of Q = %ld\n", QSize(queue));

	printf("Emptiness = %d\n", QIsEmpty(queue));

	QEnqueue(queue, &x);
	QEnqueue(queue, &x);

	printf("size of Q = %ld\n", QSize(queue));

	printf("Emptiness = %d\n", QIsEmpty(queue));

	printf("first in line data = %d\n", *(int*)QPeek(queue));

	QDequeue(queue);

	QDestroy(queue);

/*********************************************************************/

	Scenario1Test();

	return 0;
}

/* tests append + enqueue */
void Scenario1Test(void)
{
	queue_t *dest = QCreate();
	queue_t *src = QCreate();
	
	QEnqueue(dest, "1");
	QEnqueue(dest, "2");
	QEnqueue(dest, "3");
	QEnqueue(src, "4");
	QEnqueue(src, "5");
	QEnqueue(src, "6");
	QEnqueue(src, "7");

	/* appends to not empty queue from not empty queue */
	QAppend(dest, src);

	while (!QIsEmpty(dest))
	{
		if (QPeek(dest))
		{
			printf("%s ", (char*)QPeek(dest));
		}

		QDequeue(dest);
	}

	puts("");

	printf("Emptiness = %d\n", QIsEmpty(dest));
	printf("Emptiness = %d\n", QIsEmpty(src));

	QEnqueue(src, "1");
	QEnqueue(src, "2");
	QEnqueue(src, "3");
	QEnqueue(src, "4");
	QEnqueue(src, "5");
	QEnqueue(src, "6");
	QEnqueue(src, "7");

	/* appends from not empty queue to empty queue */
	QAppend(dest, src);
	
	while (!QIsEmpty(dest))
	{
		if (QPeek(dest))
		{
			printf("%s ", (char*)QPeek(dest));
		}

		QDequeue(dest);
	}

	puts("");

	printf("Emptiness = %d\n", QIsEmpty(dest));
	printf("Emptiness = %d\n", QIsEmpty(src));

	QDestroy(dest);
	QDestroy(src);
}
