#ifndef BINARY_TREE_ITERATOR_
#define BINARY_TREE_ITERATOR_

#include <stdint.h>

typedef enum
{
	START, END
} IteratorStartPosition;

typedef struct
{
	void* tree;
	uint32_t current;
} BinaryTree_Iterator;

#endif