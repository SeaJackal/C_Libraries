#ifndef BINARY_HEAP
#define BINARY_HEAP

#include <stdint.h>

#include "Easy_Functions.h"

#define PARENT(i) i/2
#define LEFT(i) 2*i
#define RIGHT(i) 2*i+1

typedef struct 
{
	void* storage;
	uint32_t size;
	uint32_t length;
	uint32_t heap_size;
	uint8_t (*isFirstBigger) (void* storage, uint32_t first, uint32_t second);
	void(*swapElements) (void* storage, uint32_t first, uint32_t second);
}
BinaryHeap;

void maxHeapify(BinaryHeap* heap, uint32_t index);
void buildMaxHeap(
	BinaryHeap* heap, void* storage, uint32_t length, uint32_t size,
	uint8_t(*isFirstBigger) (void* storage, uint32_t first, uint32_t second),
	void(*swapElements) (void* storage, uint32_t first, uint32_t second));

#endif
