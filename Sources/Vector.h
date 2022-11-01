#ifndef VECTOR_
#define VECTOR_

#include <stdint.h>

typedef struct 
{
	void* storage;
	uint32_t element_size;
	uint32_t length;
	uint32_t _reserved_length;
} Vector;

void initialize_Vector(Vector* vector, uint32_t element_size, uint32_t length);
void free_Vector(Vector* vector);

void _extendVector(Vector* vector);

uint32_t getLength_Vector(Vector* vector);
uint8_t isEmpty_Vector(Vector* vector);
uint8_t isInitialized_Vector(Vector* vector);
uint8_t isCorrectIndex_Vector(Vector* vector, uint32_t index);

void* getElement_Vector(Vector* vector, uint32_t index);
void* replaceElement_Vector(Vector* vector, uint32_t index, const void* element);
void* insertElement_Vector(Vector* vector, uint32_t index, const void* element);
void* removeElement_Vector(Vector* vector, uint32_t index);

void reduce_Vector(Vector* vector);

#endif