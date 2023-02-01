#ifndef ORDER_STATISTICS_
#define ORDER_STATISTICS_

#include <stdint.h>

uint32_t findMax(void* collection, uint32_t length,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void* comparor_data);
uint32_t findMin(void* collection, uint32_t length,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void* comparor_data);
void findMinMax(void* collection, uint32_t length,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	uint32_t* min_out, uint32_t* max_out,
	void* comparor_data);
uint32_t findOrderStatistic(void* collection, uint32_t length, uint32_t order_statistic,
	uint8_t(*isFirstBigger)(void* collection, uint32_t first_index, uint32_t second_index, void* data),
	void* comparor_data);

#endif // !ORDER_STATISTICS_

