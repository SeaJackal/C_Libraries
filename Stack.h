#ifndef STACK_
#define STACK_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	uint8_t* storage;
	uint32_t element_size;
	uint32_t max_length;
	uint8_t* top;
} Stack;

void buildStack(Stack* stack, uint32_t element_size, uint32_t max_length);
void buildStackFromData(Stack* stack, uint32_t element_size, uint32_t max_length, uint32_t current_top, void* storage);
void deleteStack(Stack* stack);

void push(Stack* stack, void* element);
void pop(Stack* stack, void* element);
uint8_t tryPush(Stack* stack, void* element);
uint8_t tryPop(Stack* stack, void* element);
uint8_t isStackEmpty(Stack* stack);
uint8_t isStackNotFull(Stack* stack);
uint32_t getStackLength(Stack* stack);
void* getStackStorage(Stack* stack);
void clearStack(Stack* stack);

#endif