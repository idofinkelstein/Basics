char *StrStr(const char *haystack, const char *needle)
{
	size_t i = 0, j = 0, k = 0, cnt = 0;
	size_t hay_length = StrLen(haystack);
	size_t nee_length = StrLen(needle);
	char *curr = (char*)haystack;
	char *tmp_curr = (char*)haystack;

	assert(haystack);
	assert(needle);

	for (i = 0; i < hay_length; ++i)
	{
		curr = curr + i;
		cnt = 0;

		for(j = i; j < hay_length; ++j)
		{
			if (*(haystack + j) == *(needle + k))
			{
				++cnt;

				if (cnt == 1)
				{
					curr += j;
				}

				k++;
			}
			else
			{
				k = 0;
				cnt = 0;
				curr = tmp_curr;
				
			}

			if (cnt == nee_length)
			{
				return (curr);
			}
			
		}
	}

	return (curr = NULL);
}



