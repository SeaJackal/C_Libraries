#ifndef SORT_
#define SORT_

#include <stdint.h>

void sortByInsertion(
	void* collection, uint32_t length,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index),
	void (*moveElementToIndex)(void* collection, uint32_t source_index, uint32_t dest_index));
void sortByHeap(void* collection, uint32_t length, 
	uint8_t (*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void (*swapElements)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void* comparor_data, void* swaper_data);
void quickSort(void* collection, uint32_t length,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void (*swapElements)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void* comparor_data, void* swaper_data);
void sortByCount(void* collection, uint32_t length, uint32_t element_size, uint32_t max_key,
	uint32_t (*getElementsKey)(void* collection, uint32_t index, void* data),
	void (*getElement)(void* collection, uint32_t index, void* buffer, void* data),
	void (*setElement)(void* collection, uint32_t index, void* source, void* data),
	void* keyer_data, void* getter_data, void* setter_data);
//void radixSort(void* collection, uint32_t length, )

#endif