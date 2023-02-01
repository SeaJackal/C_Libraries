#include "OrderStatistics.h"

uint32_t findMax(void* collection, uint32_t length,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void* comparor_data)
{
	uint32_t max_index = 0;
	for (uint32_t i = 1; i < length; i++) 
	{
		if (isFirstBigger(collection, i, max_index, comparor_data))
			max_index = i;
	}
	return max_index;
}
uint32_t findMin(void* collection, uint32_t length,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void* comparor_data)
{
	uint32_t min_index = 0;
	for (uint32_t i = 1; i < length; i++)
	{
		if (isFirstBigger(collection, min_index, i, comparor_data))
			min_index = i;
	}
	return min_index;
}
void findMinMax(void* collection, uint32_t length,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	uint32_t* min_out, uint32_t* max_out,
	void* comparor_data) 
{
	uint32_t max_index = 0;
	uint32_t min_index = 1;
	if (isFirstBigger(collection, min_index, max_index, comparor_data)) 
	{
		max_index = 1;
		min_index = 0;
	}
	uint32_t local_max, local_min;
	for (uint32_t i = 3; i < length; i+=2)
	{
		local_max = i;
		local_min = i - 1;
		if (isFirstBigger(collection, local_min, local_max, comparor_data))
		{
			local_max--;
			local_min++;
		}
		if (isFirstBigger(collection, local_max, max_index, comparor_data))
			max_index = local_max;
		if (isFirstBigger(collection, min_index, local_min, comparor_data))
			min_index = local_min;
	}
	if (length % 2 == 1) 
	{
		local_max = length - 1;
		if (isFirstBigger(collection, local_max, max_index, comparor_data))
			max_index = local_max;
		else if(isFirstBigger(collection, min_index, local_max, comparor_data))
			min_index = local_max;
	}
	*min_out = min_index;
	*max_out = max_index;
}

uint32_t findOrderStatistic(void* collection, uint32_t length, uint32_t order_statistic,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void* comparor_data) 
{
	uint32_t* copy = malloc(length*sizeof(uint32_t));
	for (uint32_t i = 0; i < length; i++) 
	{
		copy[i] = i;
	}
	uint32_t temp;
	uint32_t current_start = 0, current_finish = length - 1;
	uint32_t position, current_separator;
	while (1)
	{
		position = current_start;
		current_separator = current_finish;
		for (; position < current_finish; position++)
		{
			if (isFirstBigger(collection, copy[position], copy[current_finish], comparor_data))
			{
				current_separator = position++;
				break;
			}
		}
		for (; position < current_finish; position++)
		{
			if (isFirstBigger(collection, copy[current_finish], copy[position], comparor_data))
			{
				temp = copy[current_separator];
				copy[current_separator] = copy[position];
				copy[position] = temp;
				current_separator++;
			}
		}
		if (current_separator == order_statistic)
			return copy[current_finish];
		if (current_separator != current_finish)
		{
			temp = copy[current_separator];
			copy[current_separator] = copy[current_finish];
			copy[current_finish] = temp;
		}
		if (current_separator > order_statistic)
			current_finish = current_separator - 1;
		else
			current_start = current_separator + 1;
	}
}