#include "Queue.h"
void buildQueue(Queue* queue, uint32_t element_size, uint32_t max_length) 
{
	queue->storage = malloc(max_length * element_size);
	queue->max_length = max_length;
	queue->element_size = element_size;
	queue->head = queue->storage;
	queue->tail = queue->storage;
	queue->length = 0;
}
void deleteQueue(Queue* queue) 
{
	free(queue->storage);
}
void Enqueue(Queue* queue, void* element) 
{
	memcpy(queue->tail, element, queue->element_size);
	if (queue->storage - queue->tail + 1 == queue->max_length)
		queue->tail = queue->storage;
	else
		queue->tail += queue->element_size;
	queue->length++;
}
void Dequeue(Queue* queue, void* element) 
{
	memcpy(element, queue->head, queue->element_size);
	if (queue->storage - queue->head + 1 == queue->max_length)
		queue->head = queue->storage;
	else
		queue->head += queue->element_size;
	queue->length--;
}
uint8_t TryEnqueue(Queue* queue, void* element) 
{
	if (queue->length == queue->max_length)
		return 0;
	memcpy(queue->tail, element, queue->element_size);
	if (queue->storage - queue->tail + 1 == queue->max_length)
		queue->tail = queue->storage;
	else
		queue->tail += queue->element_size;
	queue->length++;
	return 1;
}
uint8_t TryDequeue(Queue* queue, void* element) 
{
	if (!queue->length)
		return 0;
	memcpy(element, queue->head, queue->element_size);
	if (queue->storage - queue->head + 1 == queue->max_length)
		queue->head = queue->storage;
	else
		queue->head += queue->element_size;
	queue->length--;
	return 1;
}
uint8_t isQueueEmpty(Queue* queue) 
{
	return (!queue->length);
}
uint8_t isQueueNotFull(Queue* queue) 
{
	return !(queue->length == queue->max_length);
}
uint32_t getQueueLength(Queue* queue) 
{
	return queue->length;
}
void* getQueueStorage(Queue* queue) 
{
	return queue->storage;
}
uint32_t getQueueHeadIndex(Queue* queue) 
{
	return queue->head - queue->storage;
}
void clearQueue(Queue* queue) 
{
	queue->head = queue->storage;
	queue->tail = queue->storage;
	queue->length = 0;
}