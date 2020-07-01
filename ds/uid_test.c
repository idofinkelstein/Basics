/***********************
File name: uid_test.c
Author: Ido Finkelstein
Reviewer: Hilla Pilo
Date: 26/6/2020
************************/

#include <stdio.h> /* printf */

#include "uid.h"

int main()
{
	unique_id_t uid1;
	unique_id_t uid2 = UIDCreate();
	int i = 0;

	for (i = 0; i < 10; ++i)
	{
		uid1 = UIDCreate();

		printf("%ld-%d-%ld\n", uid1.time, uid1.pid, uid1.counter);
	}

	printf("%d\n", UIDIsSame(uid1, uid2));
	printf("%d\n", UIDIsSame(uid1, uid1));

	return 0;
}
