#ifndef EASY_FUNCTIONS
#define EASY_FUNCTIONS

#include <stdint.h>

void swap(void* a, void* b, uint32_t size);
void* pointerShift(void* pointer, int32_t byteShift);
void memoryCopy(void* dest, void* source, uint32_t byte_length);

#endif