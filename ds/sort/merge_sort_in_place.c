#include <stdlib.h>
#ifdef NDEBUG
#include <stdio.h> /* printf */
#endif

#include "sort.h"

static void Merge(void *l,				/* left hand side array  */
				  void *r, 				/* right hand side array */
 				  size_t s_l,   		/* size of left 		 */
 				  size_t s_r,   		/* size of right 		 */
				  sort_cmp_func_t cmp,  /* compare func pointer  */
				  size_t size); 		/* size of element 		 */

void SwapBytes(char *byte1, char *byte2, size_t n_bytes);

int MergeSortInPlace(void *arr_to_sort,
				     size_t num_elements,
 				 	 size_t size,
                 	 sort_cmp_func_t cmp,
                 	 void *arg)
{
	size_t middle = num_elements / 2;
	size_t s_l = num_elements / 2;
	size_t s_r = num_elements - s_l;

	if (2 > num_elements)
	{
		return 0;
	}
	
	MergeSortInPlace(arr_to_sort, s_l, size, cmp, arg);

	MergeSort((char*)arr_to_sort + middle * size, s_r, size, cmp, arg);
		
	Merge(arr_to_sort, (char*)arr_to_sort + middle * size, s_l, s_r, cmp, size);

	return 0;
}


static void Merge(void *l,
				  void *r,
				  size_t s_l,
				  size_t s_r,
				  sort_cmp_func_t cmp,
				  size_t size)
{
	size_t i_l = 0;

	while (i_l < s_l)
	{
		if (0 < cmp(l, r, NULL))
		{
			SwapBytes(l, r , 4);
			MergeSortInPlace(r, s_r, size, cmp, NULL);	
		}
	
		l = (char*)l + size;					
		++i_l;						
	}	
}
