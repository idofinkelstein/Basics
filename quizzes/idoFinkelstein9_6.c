
#define NUM_OF_AIRPLANES 1000

int AirPlaneToStay(int *EnteringID, int *LeavingID, size_t size_ent, size_t size_Leav)
{
	int *id_lut = (int*)malloc(sizeof(int) * NUM_OF_AIRPLANES);
	size_t i = 0;

	if (NULL = id_lut)
	{
		return (NULL);
	}
	
	for (i = 0; i < NUM_OF_AIRPLANES; ++i)
	{
		id_lut[i] = 0;
	}

	for (i = 0; i < size_ent; ++i)
	{
		id_lut[EnteringID[i]] = 1;
	}

	for (i = 0; i < size_Leav; ++i)
	{
		if (1 == id_lut[LeavingID[i]])
		{
			id_lut[LeavingID[i]] = 0;
		}
	}

	for (i = 0; i < NUM_OF_AIRPLANES; ++i)
	{
		if (1 == id_lut[i])
		{
			id = id_lut[i];
			free(id_lut);
			return (id);
		}
		
	}
	free(id_lut);
	return (-1);
}


int AirPlaneToStay2(int *air_plane_id, size_t size)
{
	int *id_lut = (int*)malloc(sizeof(int) * NUM_OF_AIRPLANES);
	int id = 0;
	size_t i = 0;

	if (NULL = id_lut)
	{
		return (NULL);
	}

	for (i = 0; i < NUM_OF_AIRPLANES; ++i)
	{
		id_lut[i] = 0;
	}

	for (i = 0; i < size; ++i)
	{
		if (0 == id_lut[air_plane_id[i]])
		{
			id_lut[air_plane_id[i]] = 1;
		}
		else
		{
			id_lut[air_plane_id[i]] = 0;
		}
	}

	for (i = 0; i < NUM_OF_AIRPLANES; ++i)
	{
		if (1 == id_lut[i])
		{
			id = id_lut[i];
			free(id_lut);
			return (id);
		}
	}

	free(id_lut);
	return (-1);
}

