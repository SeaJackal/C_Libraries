#include "Binary_Heap.h"

void maxHeapify(BinaryHeap* heap, uint32_t index)
{
	uint32_t largest;
	uint32_t left;
	uint32_t right;
	for (int i = index; i <= heap->heap_size; i = largest)
	{
		largest = i;
		left = LEFT(i);
		if (left > heap->heap_size)
			break;
		if (heap->isFirstBigger(heap->storage, left-1, i-1))
			largest = left;
		right = RIGHT(i);
		if (right <= heap->heap_size)
		{
			if (heap->isFirstBigger(heap->storage, right-1, largest-1))
				largest = right;
		}
		if (largest != i)
			heap->swapElements(heap->storage, (i - 1), (largest - 1));
		else
			break;
	}
}

void buildMaxHeap(
	BinaryHeap* heap, void* storage, uint32_t length, uint32_t size,
	uint8_t(*isFirstBigger) (void* storage, uint32_t first, uint32_t second),
	void(*swapElements) (void* storage, uint32_t first, uint32_t second))
{
	heap->length = length;
	heap->heap_size = length;
	heap->size = size;
	heap->isFirstBigger = isFirstBigger;
	heap->swapElements = swapElements;
	heap->storage = storage;
	for (uint32_t i = length / 2; i > 0; i--) 
	{
		maxHeapify(heap, i);
	}
}