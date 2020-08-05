#include <stdio.h>	/* printf 		*/
#include <stdlib.h>	/* malloc, free */
#include <assert.h> /* assert 		*/

#include "slist.h"
#include "hash_table.h"
/*----------------------------------------------------------------------------*/
#define OFFSET_OF(TYPE, FIELD) ((size_t)(&((TYPE*)0)->FIELD))
/*----------------------------------------------------------------------------*/
typedef struct bucket bucket_t;

struct bucket
{
	slist_t *slist;
	size_t size;
};

struct hash
{
	hash_table_func_t hash_func;
	void *hash_param;
	hash_is_match_func_t match_func;
	size_t capacity;
	bucket_t *table[1];
};
/*---------------------------------------------------------------------------*/
/* Utils functions declarations */
/*---------------------------------------------------------------------------*/
static size_t GetHashValue(hash_t *hash, void *data);
static slist_t *GetSList(hash_t *hash, size_t index);
static slist_iter_t FindIter(hash_t *hash, slist_t *slist, void *data);
static int ForEachElementInList(slist_t *slist, 
								hash_do_action_func_t do_action, 
								void *param);
/*---------------------------------------------------------------------------*/
/* Utils functions definitions */
/*----------------------------------------------------------------------------*/
hash_t *HashCreate(hash_table_func_t hash_func, void *hash_param, 
				   hash_is_match_func_t match_func,
				   size_t table_size)
{
	hash_t *hash = NULL;
	size_t i = 0;
	size_t num_of_elements_created = 0;

	/* allocate administrative struct for 'hash_table',
	   and the container for the table itself. using flexible array */
	hash = (hash_t *)malloc(OFFSET_OF(struct hash, table) +
							sizeof(*hash->table[0]) * table_size);
	if (NULL == hash)
	{
		return (NULL);
	}

	/* sets hash_table fields*/
	hash->hash_func = hash_func;
	hash->hash_param = hash_param;
	hash->match_func = match_func;
	hash->capacity = table_size;

	/* allocates buckets for every index */
	for (i = 0; i < table_size; ++i)
	{
		hash->table[i] = (bucket_t *)malloc(sizeof(bucket_t));
		if (NULL != hash->table[i])
		{
			hash->table[i]->size = 0;
			++num_of_elements_created;
		}
		/* frees the memory in case of failure */
		else
		{
			for (i = 0; i < num_of_elements_created; ++i)
			{
				free(hash->table[i]);
				hash->table[i] = NULL;
			}
			
			free(hash);
			return (NULL);
		}
	}

	num_of_elements_created = 0;

	/* allocates slist for every bucket */
	for (i = 0; i < table_size; ++i)
	{
		hash->table[i]->slist = SListCreate();
		if ( NULL != hash->table[i]->slist)
		{
			++num_of_elements_created;
		}
		else
		{
			/* destroys all lists created */
			for (i = 0; i < num_of_elements_created; ++i)
			{
				SListDestroy(hash->table[i]->slist);
			}
			
			/* destroys all buckets */
			for (i = 0; i < table_size; ++i)
			{
				free(hash->table[i]);
				hash->table[i] = NULL;
			}

			free(hash);
			return (NULL);
		}
	}

	return (hash);
}
/*----------------------------------------------------------------------------*/
void HashDestroy(hash_t *hash)
{
	size_t i = 0;

	assert(hash);

	/* destroys each bucket */
	for (i = 0; i < hash->capacity; ++i)
	{
		/* Destroys the list within the bucket*/
		SListDestroy(hash->table[i]->slist);

		/* destroys buckets */
		free(hash->table[i]);
		hash->table[i] = NULL;
	}

	free(hash);
	hash = NULL;
}
/*----------------------------------------------------------------------------*/
size_t HashSize(const hash_t *hash)
{
	size_t i = 0;
	size_t num_of_elements = 0;

	assert(hash);

	for (i = 0; i < hash->capacity; ++i)
	{
		num_of_elements += HashBucketSize(i, hash);
	}

	return (num_of_elements);
}
/*----------------------------------------------------------------------------*/
size_t HashTableSize(const hash_t *hash)
{
	size_t i = 0;
	size_t num_of_buckets = 0;

	assert(hash);

	for (i = 0; i < hash->capacity; ++i)
	{
		num_of_buckets += (HashBucketSize(i, hash) > 0);
	}

	return (num_of_buckets);
}
/*----------------------------------------------------------------------------*/
size_t HashBucketSize(const size_t index, const hash_t *hash)
{
	assert(hash);

	return (hash->table[index]->size);
}
/*----------------------------------------------------------------------------*/
int HashIsEmpty(const hash_t *hash)
{
	assert(hash);

	return (0 == HashSize(hash));
}
/*----------------------------------------------------------------------------*/
int HashInsert(hash_t *hash, void *data)
{
	size_t hash_value = 0;
	slist_t *slist = NULL;

	assert(hash);

	/* converts data to hash value */
	hash_value = GetHashValue(hash, data);

	/* Gets the relevant slist */
	slist = GetSList(hash, hash_value);

	SListInsert(slist, SListEnd(slist), data);

	++hash->table[hash_value]->size;

	return (0);
}
/*----------------------------------------------------------------------------*/
void HashRemove(hash_t *hash, void *data)
{
	size_t hash_value = 0;
	slist_t *slist = NULL;
	slist_iter_t iter_data = NULL;

	assert(hash);

	/* converts data to hash value */
	hash_value = GetHashValue(hash, data);

	/* Gets the relevant slist */
	slist = GetSList(hash, hash_value);

	/* Finds iterator contaning the desired data */
	iter_data = FindIter(hash, slist, data);

	/* checks if the data exist */
	if (!SListIterIsEqual(iter_data, SListEnd(slist)))
	{
		SListRemove(slist, iter_data);

		--hash->table[hash_value]->size;
	}
}

/*---------------------------------------------------------------------------*/
void *HashFind(const hash_t *hash, const void *data)
{
	hash_t *var_hash = NULL;
	void *var_data = (void *)data;
	size_t hash_value = 0;
	slist_t *slist = NULL;
	slist_iter_t iter_data = NULL;
	
	assert(hash);

	var_hash = (hash_t *)hash;

	/* converts data to hash value */
	hash_value = GetHashValue(var_hash, var_data);

	/* Gets the relevant slist */
	slist = GetSList(var_hash, hash_value);

	/* Finds iterator contaning the desired data */
	iter_data = FindIter(var_hash, slist, var_data);

	if (SListIterIsEqual(iter_data, SListEnd(slist)))
	{
		return (NULL);
	}

	return (SListGetData(iter_data));
}
/*---------------------------------------------------------------------------*/

int HashForEach(hash_t *hash, hash_do_action_func_t do_action ,void *param)
{
	size_t i = 0;
	slist_t *slist = NULL;
	int for_each_status = 0;

	for (i = 0; i < hash->capacity && !for_each_status; ++i)
	{
		slist = GetSList(hash, i);
		for_each_status = ForEachElementInList(slist, do_action, param);		
	}

	return (for_each_status);
}


/*---------------------------------------------------------------------------*/
/* Utils functions definitions */
/*---------------------------------------------------------------------------*/
static size_t GetHashValue(hash_t *hash, void *data)
{
	size_t hash_value = 0;

	assert(hash);

	/* converts data to hash value */
	hash_value = hash->hash_func(data, hash->hash_param);

	hash_value %= hash->capacity;

	return (hash_value);
}
/*---------------------------------------------------------------------------*/
static slist_t *GetSList(hash_t *hash, size_t index)
{
	assert(hash);

	return (hash->table[index]->slist);
}
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
static slist_iter_t FindIter(hash_t *hash, slist_t *slist, void *data)
{
	return (SListFind(SListBegin(slist), 
                       SListEnd(slist),
					   hash->match_func, 
                       data));
}

static int ForEachElementInList(slist_t *slist, 
								hash_do_action_func_t do_action, 
								void *param)
{
	return (SListForEach(SListBegin(slist), 
           	   	         SListEnd(slist), 
					     do_action, 
           	      	     param));
}





