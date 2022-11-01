#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "Sort.h"

#include "Easy_Functions.h"
#include "Binary_Heap.h"

void sortByInsertion(
	void* collection, uint32_t length, uint32_t element_size,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index),
	void (*moveElementToIndex)(void* collection, uint32_t source_index, uint32_t dest_index))
{
	for (int i = 1; i < length; i++) 
	{
		uint32_t possition = 0;
		for (int j = i - 1; j >= 0; j--) 
		{
			if (isFirstBigger(collection, i, j)) 
			{
				possition = j + 1;
				break;
			}
		}
		if (possition != i) 
		{
			moveElementToIndex(collection, i, possition);
		}
	}
}

void sortByMerge(void* collection, uint32_t length, uint32_t element_size,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index),
	void* (*getElementByIndex)(void* collection, uint32_t index),
	void* (*setElementByIndex)(void* collection, uint32_t index))
{
	
}

void sortByHeap(
	void* collection, uint32_t length, uint32_t element_size,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index),
	void(*swapElements) (void* storage, uint32_t first, uint32_t second))
{
	BinaryHeap heap;
	for (int i = 0; i < length - 1; i++)
	{
		buildMaxHeap(&heap, pointerShift(collection, i * element_size), length - i, element_size, isFirstBigger, swapElements);
	}
}