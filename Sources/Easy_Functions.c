#include <stdlib.h>
#include <string.h>

#include "Easy_Functions.h"

void swap(void* a, void* b, uint32_t size) 
{
	void* temp = malloc(size);
	memcpy(temp, a, size);
	memcpy(a, b, size);
	memcpy(b, temp, size);
	free(temp);
}
void* pointerShift(void* pointer, int32_t byteShift) 
{
	return (uint8_t*)(pointer)+byteShift;
}

void memoryCopy(void* dest, void* source, uint32_t byte_length) 
{
	char* dest_char = (char*)dest;
	char* source_char = (char*)source;
	if(dest_char < source_char)
	{
		for (int i = 0; i < byte_length; i++)
		{
			*(dest_char + i) = *(source_char + i);
		}
	}
	else if (dest_char > source_char) 
	{
		for (int i = byte_length - 1; i >=0; i--)
		{
			*(dest_char + i) = *(source_char + i);
		}
	}
}