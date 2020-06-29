/*
 UID creates unique IDs based on a timestamp ,counter and process
 ID.

APIs:
-	Create - creates a new UID. 
-	IsSame - checks if two UIDs are the same.
-	GetBadID - returns the bad ID.

UID API
-	24/06/20 16:42 Ver 1.0	API team discussion
-	25/06/20 08:50 Ver 1.1  include guard added
-   25/06/20 10:20 Ver 1.2  uid_t edited to unique_id_t 
                            file header sys/types.h added    
*/

#ifndef ILRD_UID_H
#define ILRD_UID_H

#include <sys/types.h> /* pid_t */ 
#include <unistd.h>    /* pid_t */
#include <time.h>      /* size_t, time_t */

typedef struct
{
    size_t counter;
    pid_t pid;
    time_t time;
} unique_id_t;

/*  UIDCreate:
* - Creates a new UID.
*
* Return value:
*   - if succeeded, returns a new UID 
*	- if failed, returns a bad UID
*
* Comments: 
*	- User should compare the return value to the bad ID to determine
*	  if function succeeded.
*/
unique_id_t UIDCreate(void);

/*---------------------------------------------------------------------------*/
/* UIDIsSame:
*   - compares two UIDs.
*
* Args:
*	- uid1 - first UID to compare
*	- uid2 - second uid to compare
*
* Return Value:
*   - 1 if the same (TRUE)
*	- 0 if not the same (FALSE)
*
*/
int UIDIsSame(unique_id_t uid1, unique_id_t uid2);

/*---------------------------------------------------------------------------*/
/* UidGetBadId:
* - returns the bad UID.
*
* Return value:
*   - returns the bad UID
*
* Comments: 
*	- Use this ID to compare to new created ID to validate a new created ID 
*/
unique_id_t UIDGetBadUID(void);

#endif /* ILRD_UID_H */
