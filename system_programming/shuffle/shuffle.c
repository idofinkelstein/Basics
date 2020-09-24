
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct thread_info
{
	char **p_arr;
	size_t words_in_thread;
	pthread_t thread;

}thread_info_t;

typedef struct arr_info
{
	char **arr;
	size_t stop_index;
	size_t curr_index;

}arr_info_t;

/* Function Declarations */
char **CreatePointersArray(char *array, size_t num_of_words, size_t dup);
int Compare(const void *data1, const void *data2);
char *ReadDic(size_t num_of_chars, size_t *num_of_words);
void GetNumOfWordsAndCharacters(size_t *num_of_words, size_t *num_of_chars);
int StrCaseCmpWrapper(const void *data1, const void *data2);
void* Qsort_wraper(void *data);
void* MT_Qsort(void *arr,
			  size_t nmemb,
			  size_t num_of_threads);

void Merge(char **sorted, size_t num_of_words, size_t num_of_threads);
void SwapBytes(char *byte1, char *byte2, size_t n_bytes);

void *ShuffleAndSort(size_t num_of_threads)
{
	char *file_name = "/usr/share/dict/american-english";
	char *dict = NULL;
	char **p_arr = NULL;
	size_t num_of_words = 0;
	size_t num_of_chars = 0;
	size_t i = 0;
	size_t dup = 3;
	struct stat statbuf; /* obtains file size from stat() */
	
	stat(file_name, &statbuf);
	num_of_chars = (size_t)statbuf.st_size;

	dict = ReadDic(num_of_chars, &num_of_words);

	printf("chars = %ld\n", num_of_chars);
	printf("words = %ld\n", num_of_words);	

	p_arr = CreatePointersArray(dict, num_of_words, dup);

	qsort(p_arr, dup * num_of_words, sizeof(char*), Compare);

	/*for (i = 0; i < num_of_words * 3; ++i)
	{
		printf("%s\n", p_arr[i]);
	}*/


	MT_Qsort(p_arr,
			 dup * num_of_words,
			 num_of_threads);

	for (i = 0; i < num_of_words * 3; ++i)
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
		puts("SECCESS");
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

void* Qsort_wraper(void *data)
{
	thread_info_t *info = (thread_info_t*)data;
	size_t word_in_thread = info->words_in_thread;
	char** arr = info->p_arr;

	qsort(arr, word_in_thread, sizeof(char*), StrCaseCmpWrapper);

	return (arr);
}
/*---------------------------------------------------------------------------*/

void* MT_Qsort(void *arr,
			  size_t nmemb,
			  size_t num_of_threads)
{
	thread_info_t *info = NULL;
	int status = 0;
	size_t i = 0;
	size_t num_of_words = nmemb;
	size_t elem_in_thread = num_of_words / num_of_threads;
	size_t elem_reminder = num_of_words % num_of_threads;
	size_t elem_correction = elem_in_thread + elem_reminder;
	char **p_arr = (char**)arr;

	printf("elem in thr = %ld\n", elem_in_thread);
	printf("elem in thr + reminder = %ld\n", elem_correction);	
	printf("reminder = %ld\n", elem_reminder);	

	info = (thread_info_t*)malloc(sizeof(thread_info_t) * num_of_threads);

	if (info == NULL)
	{
		return (NULL);
	}

	for(i = 0; i < num_of_threads && !status; ++i)
	{
		(info + i)->p_arr = p_arr;
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
	
	/*Merge(arr, num_of_words, num_of_threads);*/

	free(info);

	return (arr);
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

	/*for (i = 0; i < num_of_words * dup; ++i)
	{
		printf("%s\n", p_arr[i]);
	}*/

	return (p_arr);
}

/*---------------------------------------------------------------------------*/
int Compare(const void *data1, const void *data2)
{
	(void)data1;
	(void)data2;

	return (1 - rand() % 2);
}

/*---------------------------------------------------------------------------*/

/* compares array of pointers to char (char**) */
int StrCaseCmpWrapper(const void *data1, const void *data2)
{
	return (strcasecmp(*(const char**)data1, *(const char**)data2));
}
/*---------------------------------------------------------------------------*/
void GetNumOfWordsAndCharacters(size_t *num_of_words, size_t *num_of_chars)
{
	char *file_name = "/usr/share/dict/american-english";
	FILE *file_ptr = fopen(file_name, "r");
	char c = '\0';

	if(NULL != file_ptr)
	{
		puts("SECCESS");
	}
	else
	{
		puts("failed");
		return;
	}

	while((c = fgetc(file_ptr)) && c != EOF)
	{
		++*num_of_chars;
		if ('\n' == c)
		{ 
			++*num_of_words; 
		}
	}	

	fclose(file_ptr);
}

void Merge(char **sorted, size_t num_of_words, size_t num_of_threads)
{
	arr_info_t *to_merge = NULL;
	char **merged = NULL;
	size_t elem_in_thread = num_of_words / num_of_threads;
	size_t elem_reminder = num_of_words % num_of_threads;
	size_t elem_correction = elem_in_thread + elem_reminder;
	size_t i = 0;
	size_t j = 0;
	size_t start_index = 0;
	size_t min_index = 0;
	size_t num_of_index = 0;
	char *elem = NULL;
	
	to_merge = (arr_info_t*)malloc(num_of_words * sizeof(arr_info_t));

	if (NULL == to_merge)
	{
		return;
	}

	merged = (char**)malloc(num_of_words * sizeof(char*));

	if (NULL == merged)
	{
		free(to_merge);
		return;
	}

	to_merge->arr = sorted;
	to_merge->stop_index = elem_correction;
	
	for (i =  1; i < num_of_threads; ++i)
	{
		(to_merge + i)->arr = sorted + elem_correction;
		(to_merge + i)->curr_index =  0;
		elem_correction += elem_in_thread;

		(to_merge + i)->stop_index = elem_in_thread;

	}
		
	for (i = 0; i < num_of_words/10; ++i)
	{
		min_index = (to_merge)->curr_index;
		num_of_index = 0;
		elem = to_merge->arr[min_index];



		for (j = 0; j < num_of_threads - 1; ++j)
		{
			if ((to_merge + j + 1)->curr_index < (to_merge + j + 1)->stop_index &&
				0 < StrCaseCmpWrapper(&elem , &(to_merge + j + 1)->arr[(to_merge + j + 1)->curr_index]))
			{
				elem = (to_merge + j + 1)->arr[(to_merge + j + 1)->curr_index];
				min_index = (to_merge + j + 1)->curr_index;
				num_of_index = j + 1;
			}
	

			/*for (j = 0; j < num_of_threads - 1; ++j)
			{
				 if ((to_merge + j + 1)->curr_index >= (to_merge + j + 1)->stop_index)
				{
					SwapBytes((char*)(to_merge + j + 1), 
									   (char*)(to_merge + num_of_threads - 1),
										sizeof(arr_info_t));
					--num_of_threads;
				}
			}*/


		}
		merged[i] = elem;
		++(to_merge + num_of_index)->curr_index;
	}

	memcpy(sorted, merged, num_of_words * sizeof(char*));

	/*free(merged);
	free(to_merge);*/
}

void SwapBytes(char *byte1, char *byte2, size_t n_bytes)
{
	char temp = 0;

	while (n_bytes)
	{
		temp = *byte1; 
   	 	*byte1++ = *byte2;
    	*byte2++ = temp;

		--n_bytes;
	}
}
