
#include "uid.h"

#define ERROR -1

unique_id_t UIDCreate(void)
{
	unique_id_t uid = {0, 0, 0};
	static size_t counter = 0;

	uid.time = time(NULL);
	uid.pid = getpid();
	uid.counter = counter++;

	if (ERROR == uid.time)
	{
		return (UIDGetBadUID());
	}

	return (uid);
}

int UIDIsSame(unique_id_t uid1, unique_id_t uid2)
{
	return(uid1.time == uid2.time &&
		   uid1.pid == uid2.pid &&
		   uid1.counter == uid2.counter);
}

unique_id_t UIDGetBadUID(void)
{
	unique_id_t bad_uid = {0, ERROR, ERROR}; 

	return (bad_uid);
}
