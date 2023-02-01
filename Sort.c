#include <math.h>
#include "Sort.h"
#include "Stack.h"

#define PARENT(a) (a >> 1)
#define LEFT(a) a << 1
#define RIGHT(a) (a << 1) + 1

#define SMALL_PACK 10

void maxHeapify(uint32_t current, void* collection, uint32_t heap_size,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void (*swapElements)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void* comparor_data, void* swaper_data)
{
	uint32_t left, right, largest;
	largest = current;
	while (1)
	{
		left = LEFT(current);
		if (left > heap_size)
			break;
		if (isFirstBigger(collection, left - 1, largest - 1, comparor_data))
			largest = left;
		right = RIGHT(current);
		if (right <= heap_size)
			if (isFirstBigger(collection, right - 1, largest - 1, comparor_data))
				largest = right;
		if (largest != current)
		{
			swapElements(collection, current - 1, largest - 1, swaper_data);
			current = largest;
		}
		else
			break;
	}
}
void sortByInsertion(
	void* collection, uint32_t length,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index),
	void (*moveElementToIndex)(void* collection, uint32_t source_index, uint32_t dest_index))
{
	uint8_t flag = 1;
	for (uint32_t i = 1; i < length; i++) 
	{
		uint32_t possition = 0;
		for (uint32_t j = i - 1; j > 0; j--) 
		{
			if (isFirstBigger(collection, i, j)) 
			{
				possition = j + 1;
				flag = 0;
				break;
			}
		}
		if (flag) 
		{
			if (isFirstBigger(collection, i, 0))
				possition = 1;

		}
		if (possition != i) 
		{
			moveElementToIndex(collection, i, possition);
		}
	}
}

void sortByHeap(void* collection, uint32_t length,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void (*swapElements)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void* comparor_data, void* swaper_data) 
{
	uint32_t heap_size = length;
	uint32_t left, right, largest;
	for (uint32_t current = heap_size >> 1; current > 0; current--) 
	{
		maxHeapify(current, collection, length, isFirstBigger, swapElements, comparor_data, swaper_data);
	}
	heap_size--;
	for (; heap_size > 0; heap_size--) 
	{
		swapElements(collection, 0, heap_size, swaper_data);
		maxHeapify(1, collection, heap_size, isFirstBigger, swapElements, comparor_data, swaper_data);
	}
}

void quickSort(void* collection, uint32_t length,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void (*swapElements)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void* comparor_data, void* swaper_data) 
{
	Stack start_temp;
	Stack finish_temp;
	Stack* start = &start_temp;
	Stack* finish = &finish_temp;
	uint32_t stack_length = log2(length);
	/*stack_length = (stack_length >> 1)+1;*/
	buildStack(start, sizeof(uint32_t), stack_length);
	buildStack(finish, sizeof(uint32_t), stack_length);
	uint32_t current_start = 0, current_finish = length - 1, current_separator, current_middle;
	uint32_t* start_pointer = &current_start;
	uint32_t* finish_pointer = &current_finish;
	uint32_t next_finish, next_start;
	uint32_t* next_finish_pointer = &next_finish;
	uint32_t* next_start_pointer = &next_start;
	uint32_t possition;
	uint8_t first_block_flag, second_block_flag;

	uint32_t max = 0;
	while(1)
	{
		//median
		current_middle = (current_start + current_finish) >> 1;
		/*if (isFirstBigger(collection, current_start, current_finish, comparor_data))
		{
			if (isFirstBigger(collection, current_middle, current_start, comparor_data))
				swapElements(collection, current_start, current_finish, swaper_data);
			else if (isFirstBigger(collection, current_middle, current_finish, comparor_data))
				swapElements(collection, current_middle, current_finish, swaper_data);
		}
		else
		{
			if (!isFirstBigger(collection, current_middle, current_finish, comparor_data))
				if (isFirstBigger(collection, current_middle, current_start, comparor_data))
					swapElements(collection, current_middle, current_finish, swaper_data);
				else
					swapElements(collection, current_start, current_finish, swaper_data);
		}*/

		possition = current_start;
		current_separator = current_finish;
		for (; possition < current_finish; possition++)
		{
			if (isFirstBigger(collection, possition, current_finish, comparor_data))
			{
				current_separator = possition++;
				break;
			}
		}
		for (; possition < current_finish; possition++)
		{
			if (isFirstBigger(collection, current_finish, possition, comparor_data))
			{
				swapElements(collection, current_separator, possition, swaper_data);
				current_separator++;
			}
		}
		if (current_separator != current_finish)
			swapElements(collection, current_finish, current_separator, swaper_data);
		next_finish = current_separator - 1;
		next_start = current_separator + 1;

		first_block_flag = (next_finish > current_start)  && current_separator != 0;
		second_block_flag = current_finish > next_start;
		if (first_block_flag && second_block_flag) 
		{
			if (current_separator > current_middle) 
			{
				push(start, start_pointer);
				push(finish, next_finish_pointer);
				current_start = next_start;
			}
			else 
			{
				push(start, next_start_pointer);
				push(finish, finish_pointer);
				current_finish = next_finish;
			}
		}
		else 
		{
			if (first_block_flag)
				current_finish = next_finish;
			else if (second_block_flag)
				current_start = next_start;
			else 
			{
				if (isStackEmpty(start))
					break;
				pop(start, start_pointer);
				pop(finish, finish_pointer);
			}
		}
	}
	deleteStack(start);
	deleteStack(finish);
}

void sortByCount(void* collection, uint32_t length, uint32_t element_size, uint32_t max_key,
	uint32_t(*getElementsKey)(void* collection, uint32_t index, void* data),
	void (*getElement)(void* collection, uint32_t index, void* buffer, void* data),
	void (*setElement)(void* collection, uint32_t index, void* source, void* data),
	void* keyer_data, void* getter_data, void* setter_data)
{
	max_key++;
	uint32_t* counts = malloc(sizeof(uint32_t) * max_key);
	uint8_t* buffer = malloc(element_size * length);
	uint32_t i;
	uint32_t* current_count;
	for (i = 0; i < max_key; i++)
		counts[i] = 0;
	for (i = 0; i < length; i++)
		counts[getElementsKey(collection, i, keyer_data)]++;
	for (i = 1; i < max_key; i++)
		counts[i] += counts[i - 1];
	for (i = 0; i < length; i++) 
	{
		getElement(collection, i, (buffer+element_size*(--counts[getElementsKey(collection, i, keyer_data)])), getter_data);
	}
	for (i = 0; i < length; i++) 
	{
		setElement(collection, i, buffer+element_size*i, setter_data);
	}
	free(counts);
	free(buffer);
}
