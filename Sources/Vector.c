#include <string.h>
#include <stdlib.h>

#include "Vector.h"
#include "Easy_Functions.h"

void initialize_Vector(Vector* vector, uint32_t element_size, uint32_t length) 
{
	vector->element_size = element_size;
	vector->length = length;
	vector->_reserved_length = length;
	vector->storage = malloc(element_size * length);
}
void free_Vector(Vector* vector) 
{
	free(vector->storage);
	vector->storage = NULL;
}
void _extendVector(Vector* vector) 
{
	uint32_t byte_length = vector->length * vector->element_size;
	void* buffer = malloc(byte_length);
	memcpy(buffer, vector->storage, byte_length);
	free(vector->storage);
	vector->storage = malloc(2 * byte_length);
	memcpy(vector->storage, buffer, byte_length);
	free(buffer);
	vector->_reserved_length = 2 * vector->length;
}
uint32_t getLength_Vector(Vector* vector) 
{
	return vector->length;
}
uint8_t isEmpty_Vector(Vector* vector) 
{
	return (vector->length == 0) ? 1 : 0;
}
uint8_t isInitialized_Vector(Vector* vector) 
{
	return vector->storage == NULL;
}
uint8_t isCorrectIndex_Vector(Vector* vector, uint32_t index) 
{
	return index <= vector->length;
}
void* getElement_Vector(Vector* vector, uint32_t index)
{
	return pointerShift(vector->storage, index * vector->element_size);
}
void* replaceElement_Vector(Vector* vector, uint32_t index, const void* element) 
{
	void* target = pointerShift(vector->storage, index * vector->element_size);
	memcpy(pointerShift(target, vector->element_size), target, (vector->length - index) * vector->element_size);
	memcpy(target, element, vector->element_size);
	return target;
}
void* insertElement_Vector(Vector* vector, uint32_t index, const void* element) 
{
	if (vector->_reserved_length-1 < index) 
	{
		_extendVector(vector);
	}
	void* target = pointerShift(vector->storage, index * vector->element_size);
	memcpy(target, element, vector->length);
	vector->length++;
}
void* removeElement_Vector(Vector* vector, uint32_t index) 
{
	if (index != vector->length - 1)
	{
		void* target = pointerShift(vector->storage, index * vector->element_size);
		memcpy(target, pointerShift(target, vector->element_size), (vector->length - index - 1) * vector->element_size);
	}
	vector->length--;
}
void reduce_Vector(Vector* vector) 
{
	uint32_t byte_length = vector->length * vector->element_size;
	void* buffer = malloc(byte_length);
	memcpy(buffer, vector->storage, byte_length);
	free(vector->storage);
	vector->storage = malloc(byte_length);
	memcpy(vector->storage, buffer, byte_length);
	free(buffer);
	vector->_reserved_length = vector->length;
}