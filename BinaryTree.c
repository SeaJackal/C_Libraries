#include "BinaryTree.h"

#include <stdlib.h>
#include <string.h>

void buildBinaryTree(BinaryTree* new_tree, uint32_t max_number, uint32_t size,
	uint8_t(*isFirstBigger)(void* first, void* second, void* data),
	uint8_t(*isEqual)(void* first, void* second, void* data)) 
{
	new_tree->isEqual = isEqual;
	new_tree->isFirstBigger = isFirstBigger;
	new_tree->root = 0;
	new_tree->max_number = max_number;
	new_tree->size = size;
	new_tree->temp = malloc(size*(max_number+1));
	new_tree->parents = malloc((max_number+1) * sizeof(uint32_t));
	new_tree->lefts = malloc((max_number+1) * sizeof(uint32_t));
	new_tree->rights = malloc((max_number+1) * sizeof(uint32_t));
	for (int i = 0; i <= max_number; i++) 
	{
		new_tree->parents[i] = max_number;
		new_tree->lefts[i] = max_number;
		new_tree->rights[i] = max_number;
	}
	buildMemoryController(&(new_tree->controller), max_number);
}
BinaryTree_Iterator findInBinaryTree(BinaryTree* tree_ptr, void* element, void* equaler_data, void* comparor_data)
{
	BinaryTree tree = *tree_ptr;
	uint8_t* current_ptr;
	BinaryTree_Iterator result;
	result.tree = tree_ptr;
	result.current = tree.root;
	while (1) 
	{
		current_ptr = tree.temp + result.current*tree.size;
		if (tree.isEqual(element, current_ptr, equaler_data)) 
			return result;
		if (tree.isFirstBigger(element, current_ptr, comparor_data))
			result.current = tree.rights[result.current];
		else
			result.current = tree.lefts[result.current];
	}
	return result;
}
BinaryTree_Iterator addToBinaryTree(BinaryTree* tree_ptr, void* element, void* comparor_data) 
{
	BinaryTree tree = *tree_ptr;
	uint32_t current = tree.max_number;
	BinaryTree_Iterator result;
	uint32_t add_index = addNextToControlledMemory(&(tree_ptr->controller));
	while (1)
	{
		if (tree.isFirstBigger(element, tree.temp + current*tree.size, comparor_data)) 
		{
			if (tree.rights[current] == tree.max_number)
			{
				tree.rights[current] = add_index;
				break;
			}
			else
				current = tree.rights[current];
		}
		else
		{
			if (tree.lefts[current] == tree.max_number)
			{
				tree.lefts[current] = add_index;
				break;
			}
			else
				current = tree.lefts[current];
		}
	}
	memcpy(tree.temp + add_index * tree.size, element, tree.size);
	tree.parents[add_index] = current;
	result.tree = tree_ptr;
	result.current = add_index;
	return result;
}
void deleteFromBinaryTree(BinaryTree_Iterator iterator) 
{
	BinaryTree tree = *((BinaryTree*)iterator.tree);
	uint32_t parent = tree.parents[iterator.current];
	uint32_t left = tree.lefts[iterator.current];
	uint32_t right = tree.rights[iterator.current];
	uint32_t current;
	uint32_t* link;
	if (parent != tree.max_number)
		link = (iterator.current == tree.lefts[parent]) ? (tree.lefts + parent) : (tree.rights + parent);
	else
		link = &link;
	if (left == tree.max_number && right == tree.max_number) 
	{
		*link = tree.max_number;
	}
	else 
	{
		if (left == tree.max_number) 
		{
			current = right;
			*link = right;
			tree.parents[right] = parent;
		}
		else if(right == tree.max_number)
		{
			current = left;
			*link = left;
			tree.parents[left] = parent;
		}
		else 
		{
			current = right;
			if (tree.lefts[current] == tree.max_number) 
			{
				tree.lefts[current] = left;
				tree.parents[left] = current;
				tree.parents[current] = parent;
				*link = current;
			}
			else
			{
				while (tree.lefts[current] != tree.max_number)
				{
					current = tree.lefts[current];
				}
				tree.lefts[tree.parents[current]] = tree.rights[current];
				tree.parents[tree.rights[current]] = tree.parents[current];
				tree.rights[current] = right;
				tree.lefts[current] = left;
				*link = current;
				tree.parents[left] = current;
				tree.parents[right] = current;
				tree.parents[current] = parent;
			}
		}
	}
	tree.parents[iterator.current] = tree.max_number;
	tree.lefts[iterator.current] = tree.max_number;
	tree.rights[iterator.current] = tree.max_number;
	if (parent == tree.max_number)
		((BinaryTree*)iterator.tree)->root = current;
}

BinaryTree_Iterator buildBinaryTree_Iterator(BinaryTree* tree, IteratorStartPosition start_position) 
{
	BinaryTree_Iterator iterator;
	iterator.current = tree->root;
	uint32_t* lefts = tree->lefts;
	uint32_t* rights = tree->rights;
	uint32_t null = tree->max_number;
	switch (start_position) 
	{
	case START:
		while (lefts[iterator.current] != null)
		{
			iterator.current = lefts[iterator.current];
		}
		break;
	case END:
		while (rights[iterator.current] != null)
		{
			iterator.current = rights[iterator.current];
		}
		break;
	}
	iterator.tree = tree;
	return iterator;
}
void goNextInBinaryTree(BinaryTree_Iterator* iterator)
{
	BinaryTree tree = *((BinaryTree*)iterator->tree);
	uint32_t current = iterator->current;
	uint32_t last;
	if (tree.rights[current] == tree.max_number) 
	{
		last = current;
		current = tree.parents[current];
		while (last == tree.rights[current]) 
		{
			last = current;
			current = tree.parents[current];
		}
		iterator->current = current;
	}
	else 
	{
		current = tree.rights[current];
		while (tree.lefts[current] != tree.max_number)
			current = tree.lefts[current];
		iterator->current = current;
	}
}
void goPreviousInBinaryTree(BinaryTree_Iterator* iterator)
{
	BinaryTree tree = *((BinaryTree*)iterator->tree);
	uint32_t current = iterator->current;
	uint32_t last;
	if (tree.lefts[current] == tree.max_number)
	{
		last = current;
		current = tree.parents[current];
		while (last == tree.lefts[current])
		{
			last = current;
			current = tree.parents[current];
		}
		iterator->current = current;
	}
	else
	{
		current = tree.lefts[current];
		while (tree.rights[current] != tree.max_number)
			current = tree.rights[current];
		iterator->current = current;
	}
}
void* getElementFromBinaryTree(BinaryTree_Iterator* iterator) 
{
	return ((BinaryTree*)iterator->tree)->temp + iterator->current * ((BinaryTree*)iterator->tree)->size;
}
uint8_t isNotLastInBinaryTree(BinaryTree_Iterator* iterator) 
{
	BinaryTree tree = *((BinaryTree*)iterator->tree);
	uint32_t current = iterator->current;
	uint32_t last;
	if (tree.rights[current] == tree.max_number)
	{
		last = current;
		current = tree.parents[current];
		while (last == tree.rights[current])
		{
			last = current;
			current = tree.parents[current];
		}
		if (current == tree.max_number)
			return 0;
		else
			return 1;
	}
	else
	{
		return 1;
	}
}
uint8_t isNotFirstInBinaryTree(BinaryTree_Iterator* iterator) 
{
	BinaryTree tree = *((BinaryTree*)iterator->tree);
	uint32_t current = iterator->current;
	uint32_t last;
	if (tree.lefts[current] == tree.max_number)
	{
		last = current;
		current = tree.parents[current];
		while (last == tree.lefts[current])
		{
			last = current;
			current = tree.parents[current];
		}
		if (current == tree.max_number)
			return 0;
		else
			return 1;
	}
	else
	{
		return 1;
	}
}