#ifndef BINARY_TREE_
#define BINARY_TREE_

#include <stdint.h>
#include "MemoryController.h"
#include "BinaryTreeIterator.h"

typedef struct 
{
	uint32_t max_number;
	uint32_t size;
	uint32_t root;
	uint8_t* temp;
	uint32_t* parents;
	uint32_t* lefts;
	uint32_t* rights;
	MemoryController_t controller;
	uint8_t (*isFirstBigger)(void* first, void* second, void* data);
	uint8_t(*isEqual)(void* first, void* second, void* data);
} BinaryTree;

void buildBinaryTree(BinaryTree* new_tree, uint32_t max_number, uint32_t size,
	uint8_t(*isFirstBigger)(void* first, void* second, void* data),
	uint8_t(*isEqual)(void* first, void* second, void* data));
BinaryTree_Iterator findInBinaryTree(BinaryTree* tree, void* element, void* equaler_data, void* comparor_data);
BinaryTree_Iterator addToBinaryTree(BinaryTree* tree, void* element, void* comparor_data);
void deleteFromBinaryTree(BinaryTree_Iterator iterator);

BinaryTree_Iterator buildBinaryTree_Iterator(BinaryTree* tree, IteratorStartPosition start_position);
void goNextInBinaryTree(BinaryTree_Iterator* iterator);
void goPreviousInBinaryTree(BinaryTree_Iterator* iterator);
void* getElementFromBinaryTree(BinaryTree_Iterator* iterator);
uint8_t isNotLastInBinaryTree(BinaryTree_Iterator* iterator);
uint8_t isNotFirstInBinaryTree(BinaryTree_Iterator* iterator);

#endif