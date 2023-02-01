#include "Stack.h"

void buildStack(Stack* stack, uint32_t element_size, uint32_t max_length) 
{
	stack->element_size = element_size;
	stack->max_length = max_length;
	stack->storage = malloc(element_size * max_length);
	stack->top = stack->storage;
}
void buildStackFromData(Stack* stack, uint32_t element_size, uint32_t max_length, uint32_t current_top, void* storage) 
{
	stack->element_size = element_size;
	stack->max_length = max_length;
	stack->storage = storage;
	stack->top = stack->storage + current_top*element_size;
}
void deleteStack(Stack* stack) 
{
	free(stack->storage);
}
void push(Stack* stack, void* element) 
{
	memcpy(stack->top, element, stack->element_size);
	stack->top += stack->element_size;
}
void pop(Stack* stack, void* element) 
{
	stack->top -= stack->element_size;
	memcpy(element, stack->top, stack->element_size);
}
uint8_t tryPush(Stack* stack, void* element) 
{
	if (stack->top - stack->storage >= stack->max_length * stack->element_size)
		return 0;
	memcpy(stack->top, element, stack->element_size);
	stack->top += stack->element_size;
	return 1;
}
uint8_t tryPop(Stack* stack, void* element) 
{
	if (stack->top == stack->storage)
		return 0;
	stack->top -= stack->element_size;
	memcpy(element, stack->top, stack->element_size);
	return 1;
}
uint8_t isStackEmpty(Stack* stack) 
{
	return stack->top == stack->storage;
}
uint8_t isStackNotFull(Stack* stack) 
{
	return stack->top - stack->storage < (stack->max_length)* stack->element_size;
}
uint32_t getStackLength(Stack* stack)
{
	return (stack->top - stack->storage) / stack->element_size;
}
void* getStackStorage(Stack* stack)
{
	return stack->storage;
}
void clearStack(Stack* stack) 
{
	stack->top = stack->storage;
}