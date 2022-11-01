#ifndef SORT_
#define SORT_

void sortByInsertion(
	void* collection, uint32_t length, uint32_t element_size,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index),
	void (*moveElementToIndex)(void* collection, uint32_t source_index, uint32_t dest_index));
void sortByHeap(
	void* collection, uint32_t length, uint32_t element_size,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index),
	void(*swapElements) (void* storage, uint32_t first, uint32_t second));

#endif