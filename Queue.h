#ifndef QUEUE_
#define QUEUE_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Easy_Functions.h"

typedef struct {
	uint8_t* storage;
	uint32_t element_size;
	uint32_t max_length;
	uint8_t* head;
	uint8_t* tail;
	uint32_t length;
}
Queue;

void buildQueue(Queue* queue, uint32_t element_size, uint32_t max_length);
void deleteQueue(Queue* queue);

void Enqueue(Queue* queue, void* element);
void Dequeue(Queue* queue, void* element);
uint8_t TryEnqueue(Queue* queue, void* element);
uint8_t TryDequeue(Queue* queue, void* element);
uint8_t isQueueEmpty(Queue* queue);
uint8_t isQueueNotFull(Queue* queue);
uint32_t getQueueLength(Queue* queue);
void* getQueueStorage(Queue* queue);
uint32_t getQueueHeadIndex(Queue* queue);
void clearQueue(Queue* queue);
#endif