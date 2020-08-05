/*
A hash table is an unordered collection of key-value pairs, 
where each key is unique.
Hash tables offer a combination of efficient lookup, 
insert and delete operations.
*/

#ifndef ILRD_HASH_TABLE_H
#define ILRD_HASH_TABLE_H

#include <stddef.h>	/* size_t */

/*version 1.0  mentor approval */

typedef struct hash hash_t;

/* typedefs of functions to be implemented by the user */

/* hash table function returns numaric value of the mapped data1 */
typedef size_t (*hash_table_func_t)(const void *data1, void *param);
/* return value is status - 0 for success, 1 for fail */
typedef int (*hash_do_action_func_t)(void *data, void *param);
/* return value is boolean - 1 for match, 0 if not matched */
typedef int (*hash_is_match_func_t)(void *data, void *param);

/*---------------------------------------------------------------------------*/
/* HashCreate:
*   - creates an empty hash table.
*
* Args:
*	- hash_func - pointer to hash function.
*   - match_func - pointer to match function.
*	- param - parameters given by user to be sent into hash function.
*   - table_size - size of hash table requesed by the user.
*
* Return Value:
*   - pointer to the hash table.
*
*/
hash_t *HashCreate(hash_table_func_t hash_func, void *hash_param, 
				   hash_is_match_func_t match_func,
				   size_t table_size);

/*---------------------------------------------------------------------------*/
/* HashDestroy:
*   - destroys the hash table.
*
* Args:
*   - hash - pointer to the hash table to be destroyed
*
*/
void HashDestroy(hash_t *hash);

/*---------------------------------------------------------------------------*/
/* HashSize:
*   - returns the number of elements in hash table buckets.
* 
* Args:
*   - hash - pointer to the hash table
*  
* Return Value:
*   - number of elements in hash table buckets.
*
*/
size_t HashSize(const hash_t *hash);

/*---------------------------------------------------------------------------*/
/* HashTableSize:
*   - returns the number of buckets whithin the hash table.
* 
* Args:
*   - hash - pointer to the hash table
*  
* Return Value:
*   - number of buckets in the hash table
*
*/
size_t HashTableSize(const hash_t *hash);

/*---------------------------------------------------------------------------*/
/* HashBucketsSize:
*   - returns the number of elements in a specific bucket.
* 
* Args:
*   - index - index of bucket 
*  
* Return Value:
*   - number of elements in buket
*
*/
size_t HashBucketSize(const size_t index, const hash_t *hash);

/*---------------------------------------------------------------------------*/
/* HashIsEmpty:
*   - checks if the hash table is empty or not
* 
* Args:
*   - hash - pointer to hash table given by user
*  
* Return boolean Value:
*   1 - empty (TRUE)
*   0 - not empty. (FALSE)
*
*/
int HashIsEmpty(const hash_t *hash);

/*---------------------------------------------------------------------------*/
/* HashInsert:
* - inserts new element to the hash table.
* 
* Args:
*   - hash - pointer to hash table
*   - data - data to be inserted
*
* Return value:
*   - if succeeded, returns 0
*	- if failed 1
*   
* Comments: 
*	- User should check return value to determine
*	  if function succeeded.
*
*/
int HashInsert(hash_t *hash, void *data);

/*---------------------------------------------------------------------------*/
/* HashRemove:
*   - removes an element from the hash table.
* 
* Args:
*   - hash - pointer to hash table
*   - data - data to be removed
*
*/
void HashRemove(hash_t *hash, void *data);

/*---------------------------------------------------------------------------*/
/* HashFind:
*   - finds data stored in hash table. 
* 
* Args:
*   - hash - pointer to the hash table
*	- data - data to find (may be only part of data stored)
*
* Return Value: 
*	- if succeeded, returns pointer to the matched element
*	- if failed, returns NULL. 
*
*/
void *HashFind(const hash_t *hash, const void *data);

/*---------------------------------------------------------------------------*/
/* HashForEach:
*   - performes action in a function given by the user on all hash table elements.
*
* Args:
*	- hash - pointer to the hash table
*   - do_action - function pointer to the action to do
*	- param - parameter to pass to action function (optional)
*   
* Return value:
*   - 0 - the action succeeds for all the elements in the range
*   - otherwise, the action failed and returns the status returned 
*     from the do_action function  .
*
* Comments: 
*	- Range includes all elements in the hash table.
*	- do_action is a function to be implemeneted by the user. See signature 
*	  in typedef.
*
*/
int HashForEach(hash_t *hash, hash_do_action_func_t do_action ,void *param);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_HASH_TABLE_H */
