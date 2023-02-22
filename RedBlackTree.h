#ifndef RED_BLACK_TREE_
#define RED_BLACK_TREE_

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
	uint8_t* colors;
	MemoryController_t controller;
	uint8_t(*isFirstBigger)(void* first, void* second, ...);
	uint8_t(*isEqual)(void* first, void* second, ...);
} RedBlackTree;

void buildRedBlackTree(RedBlackTree* new_tree, uint32_t max_number, uint32_t size,
	uint8_t(*isFirstBigger)(void* first, void* second, ...),
	uint8_t(*isEqual)(void* first, void* second, ...));
BinaryTree_Iterator findInRedBlackTree(RedBlackTree* tree, void* element, ...);
BinaryTree_Iterator addToRedBlackTree(RedBlackTree* tree, void* element, ...);
void deleteFromRedBlackTree(BinaryTree_Iterator iterator);

BinaryTree_Iterator buildRedBlackTree_Iterator(RedBlackTree* tree, IteratorStartPosition start_position);
void goNextInRedBlackTree(BinaryTree_Iterator* iterator);
void goPreviousInRedBlackTree(BinaryTree_Iterator* iterator);
void* getElementFromRedBlackTree(BinaryTree_Iterator* iterator);
uint8_t isNotLastInRedBlackTree(BinaryTree_Iterator* iterator);
uint8_t isNotFirstInRedBlackTree(BinaryTree_Iterator* iterator);
uint8_t isNotNullOfRedBlackTree(BinaryTree_Iterator* iterator);

#endif
