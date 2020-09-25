
#include <stdio.h> 			/* printf, puts, fopen, fread, fclose */
#include <stdlib.h> 		/* malloc, free, rand, qsort 			   */
#include <string.h> 		/* strlen, memcpy 						   */
#include <strings.h>		/* strcasecmp 							   */
#include <pthread.h> 		/* pthread_create, pthread_join 	   */
#include <sys/types.h> 	/* stat, struct stat 						   */
#include <sys/stat.h> 	/* stat, struct stat						   */
#include <unistd.h> 		/* stat, struct stat 						   */

typedef struct thread_info
{
	char **p_arr;
	size_t words_in_thread; 
	size_t index;
	pthread_t thread;

}thread_info_t;


/* Function Declarations */
char **CreatePointersArray(char *array, size_t num_of_words, size_t dup);
int Mix(const void *data1, const void *data2);
char *ReadDic(size_t num_of_chars, size_t *num_of_words);
int StrCaseCmpWrapper(const void *data1, const void *data2);
void* Qsort_wraper(void *data);
void* MT_Qsort(void *arr,
			 		   size_t nmemb,
			 		   size_t num_of_threads);

int Merge(thread_info_t *arrays, size_t num_of_arrays);
void SwapBytes(char *byte1, char *byte2, size_t n_bytes);
/*---------------------------------------------------------------------------*/

void *ShuffleAndSort(size_t num_of_threads)
{
	char *file_name = "/usr/share/dict/american-english";
	char *dict = NULL;
	char **p_arr = NULL;
	size_t num_of_words = 0;
	size_t num_of_chars = 0;
	size_t i = 0;
	size_t dup = 5; 	   /* amount of duplications */
	struct stat statbuf; /* obtains file size from stat() */
	
	stat(file_name, &statbuf);
	num_of_chars = (size_t)statbuf.st_size;

	/* reads all words in dictionary to a buffer */
	/* this function also gets the number of words in dictionary through
	   num_of_words parameter */
	dict = ReadDic(num_of_chars, &num_of_words);

	/* creates array of pointers to the words in buffer and duplicates it dup times */
	p_arr = CreatePointersArray(dict, num_of_words, dup);

	/* mixes the words */
	qsort(p_arr, dup * num_of_words, sizeof(char*), Mix);

	/* sorts sections of p_arr separately as the number of threads and merges them */
	MT_Qsort(p_arr,
					dup * num_of_words,
					num_of_threads);

	for (i = 0; i < num_of_words * dup; ++i)
	{
		printf("%s\n", p_arr[i]);
	}

	free(dict);
	free(p_arr);

	return(NULL);
}
/*---------------------------------------------------------------------------*/

char *ReadDic(size_t num_of_chars, size_t *num_of_words)
{
	char *file_name = "/usr/share/dict/american-english";
	FILE *file_ptr = NULL;
	char *dict = NULL;
	char *start = NULL;
	size_t status = 0;
	size_t i = 0;
	
	file_ptr = fopen(file_name, "r");

	/* checks if successeded to open file */
	if(NULL != file_ptr)
	{
		puts("SUCCESS");
	}
	else
	{
		puts("failed");
		return (NULL);
	}

	dict = (char*)malloc(num_of_chars);	

	if (NULL == dict)
	{
		fclose(file_ptr);
		return (NULL);
	}

	status = fread(dict, sizeof(char), num_of_chars, file_ptr);

	fclose(file_ptr);

	if (status != num_of_chars)
	{
		puts("fread failed");
		free(dict);
		return (NULL);
	}

	start = dict;

	for (i = 0; i < num_of_chars; ++i)
	{
		if ('\n' == *dict)
		{ 
			++*num_of_words;
			*dict = '\0'; 
		}

		++dict;
	}	

	return (start);
}
/*---------------------------------------------------------------------------*/

char **CreatePointersArray(char *array, size_t num_of_words, size_t dup)
{
	char **p_arr = NULL;
	size_t i = 0;
	size_t j = 0;
	size_t len = 0;
	char* start = array;

	p_arr = (char**)malloc(sizeof(char*) * dup * num_of_words);

	if (NULL == p_arr)
	{
		return (NULL);
	}

	for (j = 0; j < dup; ++j)
	{
		for (i = j * num_of_words; i < num_of_words * (j + 1); ++i)
		{
			len = strlen(array);
			p_arr[i] = array;
			array += (len + 1);
		}
	
		array = start;
	}

	return (p_arr);
}

/*---------------------------------------------------------------------------*/

void* MT_Qsort(void *arr,
					   size_t nmemb,
			 		   size_t num_of_threads)
{
	thread_info_t *info = NULL;
	int status = 0;
	size_t i = 0;
	size_t elem_in_thread = nmemb / num_of_threads;
	size_t elem_reminder = nmemb % num_of_threads;
	size_t elem_correction = elem_in_thread + elem_reminder;
	char **p_arr = (char**)arr;

	info = (thread_info_t*)malloc(sizeof(thread_info_t) * num_of_threads);

	if (info == NULL)
	{
		return (NULL);
	}

	/* assigns relevant data to info array to pass to thread's function */
	/* info[o] gets extra words because of the reminder 					  */
	for(i = 0; i < num_of_threads && !status; ++i)
	{
		(info + i)->p_arr = p_arr;
		(info + i)->index = 0;
		(info + i)->words_in_thread = elem_correction;
		p_arr += elem_correction;

		elem_correction = elem_in_thread;

		status = pthread_create(&(info + i)->thread, NULL, Qsort_wraper, info + i);
	}

	if (status)
	{
		free(info);
		return (NULL);
	}

	for(i = 0; i < num_of_threads; ++i)
	{
		pthread_join((info + i)->thread, NULL);
	}
	
	Merge(info, num_of_threads);

	free(info);

	return (arr);
}
/*---------------------------------------------------------------------------*/

void* Qsort_wraper(void *data)
{
	thread_info_t *info = (thread_info_t*)data;
	size_t word_in_thread = info->words_in_thread;
	char** arr = info->p_arr;

	qsort(arr, word_in_thread, sizeof(char*), StrCaseCmpWrapper);

	return (arr);
}

/*---------------------------------------------------------------------------*/

int Merge(thread_info_t *arrays, size_t num_of_arrays)
{
	char **merged = NULL;
	size_t num_of_words = 0;
	size_t i = 0;
	size_t j = 0;
	size_t num_of_index = 0;
	
	for (i = 0; i < num_of_arrays; ++i)
	{
		num_of_words += (arrays + i)->words_in_thread;
	}
	
	/* temporary buffer for the merged arrays */ 
	merged = (char**)malloc(num_of_words * sizeof(char*));

	if (NULL == merged)
	{
		return 1;
	}

	for (i = 0; i < num_of_words; ++i)
	{		
		char *elem = "\xFF"; /* string of 1 char with the heighest ascii value */

		for (j = 0; j < num_of_arrays; ++j)
		{
			/* checks if current index is in bound and compares the corresponding
				element */
			if ((arrays + j)->index < (arrays + j)->words_in_thread &&
				0 < StrCaseCmpWrapper(&elem , &(arrays + j)->p_arr[(arrays + j)->index]))
			{
				elem = (arrays + j)->p_arr[(arrays + j)->index];

				/* saves the index of smallest element for incrementing
					corresopnding array index*/
				num_of_index = j;
			}
		}
		merged[i] = elem;
		++(arrays + num_of_index)->index;
	}

	memcpy(arrays->p_arr, merged, num_of_words * sizeof(char*));

	free(merged);

	return 0;
}
/*---------------------------------------------------------------------------*/

int Mix(const void *data1, const void *data2)
{
	(void)data1;
	(void)data2;

	return (1 - rand() % 2);
}
/*---------------------------------------------------------------------------*/

int StrCaseCmpWrapper(const void *data1, const void *data2)
{
	return (strcasecmp(*(const char**)data1, *(const char**)data2));
}
/*---------------------------------------------------------------------------*/

void SwapBytes(char *byte1, char *byte2, size_t n_bytes)
{
	char temp = 0;

	while (n_bytes--)
	{
		temp = *byte1; 
   	 	*byte1++ = *byte2;
    	*byte2++ = temp;
	}
}
