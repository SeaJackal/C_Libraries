#include "RedBlackTree.h"

#include <stdarg.h>
#include "BitAccess.h"

void rotateRight(RedBlackTree* tree_ptr, uint32_t current)
{
	RedBlackTree tree = *tree_ptr;
	uint32_t rotated = tree.lefts[current];
	if (tree.lefts[tree.parents[current]] == current)
		tree.lefts[tree.parents[current]] = rotated;
	else if (tree.rights[tree.parents[current]] == current)
		tree.rights[tree.parents[current]] = rotated;
	tree.parents[rotated] = tree.parents[current];
	tree.lefts[current] = tree.rights[rotated];
	tree.parents[tree.lefts[current]] = current;
	tree.parents[current] = rotated;
	tree.rights[rotated] = current;
}
void rotateLeft(RedBlackTree* tree_ptr, uint32_t current)
{
	RedBlackTree tree = *tree_ptr;
	uint32_t rotated = tree.rights[current];
	if (tree.lefts[tree.parents[current]] == current)
		tree.lefts[tree.parents[current]] = rotated;
	else if (tree.rights[tree.parents[current]] == current)
		tree.rights[tree.parents[current]] = rotated;
	tree.parents[rotated] = tree.parents[current];
	tree.rights[current] = tree.lefts[rotated];
	tree.parents[tree.rights[current]] = current;
	tree.parents[current] = rotated;
	tree.lefts[rotated] = current;
}

void buildRedBlackTree(RedBlackTree* new_tree, uint32_t max_number, uint32_t size,
	uint8_t(*isFirstBigger)(void* first, void* second, ...),
	uint8_t(*isEqual)(void* first, void* second, ...)) 
{
	new_tree->isEqual = isEqual;
	new_tree->isFirstBigger = isFirstBigger;
	new_tree->root = 0;
	new_tree->max_number = max_number;
	new_tree->size = size;
	new_tree->temp = malloc(size * (max_number + 1));
	new_tree->parents = malloc((max_number + 1) * sizeof(uint32_t));
	new_tree->lefts = malloc((max_number + 1) * sizeof(uint32_t));
	new_tree->rights = malloc((max_number + 1) * sizeof(uint32_t));
	uint8_t colors_number = (max_number + 1) / 8 + ((max_number % 8 == 0) ? 0 : 1);
	new_tree->colors = malloc(colors_number);
	for (int i = 0; i <= max_number; i++)
	{
		new_tree->parents[i] = max_number;
		new_tree->lefts[i] = max_number;
		new_tree->rights[i] = max_number;
	}
	for (int i = 0; i < colors_number; i++) 
	{
		new_tree->colors[i] = 0;
	}
	setBitOne(new_tree->colors+max_number / 8, max_number % 8);
	buildMemoryController(&(new_tree->controller), max_number);
}
BinaryTree_Iterator findInRedBlackTree(RedBlackTree* tree_ptr, void* element, ...) 
{
	va_list args;
	va_start(args, element);
	RedBlackTree tree = *tree_ptr;
	uint8_t* current_ptr;
	BinaryTree_Iterator result;
	result.tree = tree_ptr;
	result.current = tree.root;
	while (1)
	{
		current_ptr = tree.temp + result.current * tree.size;
		if (tree.isEqual(element, current_ptr, args))
			return result;
		if (tree.isFirstBigger(element, current_ptr, args))
			result.current = tree.rights[result.current];
		else
			result.current = tree.lefts[result.current];
	}
	return result;
}
BinaryTree_Iterator addToRedBlackTree(RedBlackTree* tree_ptr, void* element, ...) 
{
	va_list args;
	va_start(args, element);
	RedBlackTree tree = *tree_ptr;
	uint32_t current = tree.max_number;
	BinaryTree_Iterator result;
	uint32_t add_index = addNextToControlledMemory(&(tree_ptr->controller));
	while (1)
	{
		if (tree.isFirstBigger(element, tree.temp + current * tree.size, args))
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
	//
	tree.parents[tree.max_number] = add_index;
	//
	result.tree = tree_ptr;
	result.current = add_index;
	current = add_index;
	void (*first_rotate)(RedBlackTree*, uint32_t);
	void (*second_rotate)(RedBlackTree*, uint32_t);
	uint32_t base;
	uint32_t parent = tree.parents[current];;
	uint8_t first_rotate_flag;
	while (!getBit(tree.colors[parent / 8], parent % 8)) 
	{
		if (parent == tree.lefts[tree.parents[parent]]) 
		{
			first_rotate_flag = (current == tree.rights[tree.parents[current]]);
			base = tree.rights[tree.parents[parent]];
			first_rotate = rotateLeft;
			second_rotate = rotateRight;
		}
		else 
		{
			first_rotate_flag = (current == tree.lefts[tree.parents[current]]);
			base = tree.lefts[tree.parents[parent]];
			first_rotate = rotateRight;
			second_rotate = rotateLeft;
		}
		if (!getBit(tree.colors[base / 8], base % 8)) 
		{
			setBitOne(tree.colors+parent / 8, parent % 8);
			setBitOne(tree.colors+base / 8, base % 8);
			current = tree.parents[parent];
			setBitNull(tree.colors+current / 8, current % 8);
		}
		else 
		{
			if (first_rotate_flag) 
			{
				current = parent;
				(*first_rotate)(tree_ptr, current);
				parent = tree.parents[current];
			}
			setBitOne(tree.colors+parent / 8, parent % 8);
			setBitNull(tree.colors+tree.parents[parent] / 8, tree.parents[parent] % 8);
			(*second_rotate)(tree_ptr, tree.parents[parent]);
		}
		parent = tree.parents[current];
	}
	if (tree.rights[tree.max_number] == tree.max_number)
		tree_ptr->root = tree.lefts[tree.max_number];
	else
		tree_ptr->root = tree.rights[tree.max_number];
	setBitOne(tree.colors+tree.root / 8, tree.root % 8);
	tree.parents[tree.max_number] = tree.max_number;
	return result;
}
void deleteFromRedBlackTree(BinaryTree_Iterator iterator) 
{
	RedBlackTree tree = *((RedBlackTree*)iterator.tree);
	uint32_t parent = tree.parents[iterator.current];
	uint32_t left = tree.lefts[iterator.current];
	uint32_t right = tree.rights[iterator.current];
	uint32_t current, base, root;
	uint32_t* link;
	eraseFromControlledMemory(&((RedBlackTree*)iterator.tree)->controller, iterator.current);
	link = (iterator.current == tree.lefts[parent]) ? (tree.lefts + parent) : (tree.rights + parent);
	if (left == tree.max_number && right == tree.max_number)
	{
		*link = tree.max_number;
		current = tree.max_number;
		tree.parents[current] = parent;
		if (parent == tree.max_number) 
		{
			((RedBlackTree*)iterator.tree)->root = getNextOfControlledMemory(&(((RedBlackTree*)iterator.tree)->controller));
			tree.parents[iterator.current] = tree.max_number;
			tree.lefts[iterator.current] = tree.max_number;
			tree.rights[iterator.current] = tree.max_number;
			return;
		}
	}
	else
	{
		if (left == tree.max_number)
		{
			current = right;
			*link = right;
			tree.parents[right] = parent;
			if (parent == tree.max_number)
				((RedBlackTree*)iterator.tree)->root = current;
		}
		else if (right == tree.max_number)
		{
			current = left;
			*link = left;
			tree.parents[left] = parent;
			if (parent == tree.max_number)
				((RedBlackTree*)iterator.tree)->root = current;
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
				if (parent == tree.max_number)
					((RedBlackTree*)iterator.tree)->root = current;
				current = tree.rights[current];
			}
			else
			{
				while (tree.lefts[current] != tree.max_number)
				{
					current = tree.lefts[current];
				}
				tree.lefts[tree.parents[current]] = tree.rights[current];
				tree.parents[tree.rights[current]] = tree.parents[current];
				base = tree.rights[current];
				tree.rights[current] = right;
				tree.lefts[current] = left;
				*link = current;
				tree.parents[left] = current;
				tree.parents[right] = current;
				tree.parents[current] = parent;
				if (parent == tree.max_number)
					((RedBlackTree*)iterator.tree)->root = current;
				current = base;
			}
		}
	}
	tree.parents[iterator.current] = tree.max_number;
	tree.lefts[iterator.current] = tree.max_number;
	tree.rights[iterator.current] = tree.max_number;
	setBitNull(tree.colors + iterator.current / 8, iterator.current % 8);
	if (!getBit(tree.colors[iterator.current / 8], iterator.current % 8))
	{
		tree.parents[tree.max_number] = tree.max_number;
		if (tree.rights[tree.max_number] == tree.max_number)
			((RedBlackTree*)iterator.tree)->root = tree.lefts[tree.max_number];
		else
			((RedBlackTree*)iterator.tree)->root = tree.rights[tree.max_number];
		return;
	}

	uint8_t right_flag, left_flag;
	root = ((RedBlackTree*)iterator.tree)->root;
	tree.parents[current]=parent;
	while (current!=root && getBit(tree.colors[current/8], current%8)) 
	{
		if (current == tree.lefts[parent]) 
		{
			base = tree.rights[parent];
			if (!getBit(tree.colors[base / 8], base % 8)) 
			{
				setBitOne(tree.colors+base / 8, base % 8);
				setBitNull(tree.colors+parent / 8, parent % 8);
				rotateLeft(iterator.tree, parent);
				base = tree.rights[parent];
			}
			right_flag = getBit(tree.colors[tree.rights[base] / 8], tree.rights[base] % 8);
			if (getBit(tree.colors[tree.lefts[base] / 8], tree.lefts[base] % 8) && right_flag)
			{
				setBitNull(tree.colors+base / 8, base % 8);
				current = parent;
				parent = tree.parents[current];
			}
			else 
			{
				if (right_flag) 
				{
					setBitOne(tree.colors+tree.lefts[base] / 8, tree.lefts[base] % 8);
					setBitNull(tree.colors+base / 8, base % 8);
					rotateRight(iterator.tree, base);
					base = tree.rights[parent];
				}
				if (getBit(tree.colors[parent / 8], parent % 8))
					setBitOne(tree.colors+base / 8, base % 8);
				else
					setBitNull(tree.colors+base / 8, base % 8);
				setBitOne(tree.colors+parent / 8, parent % 8);
				setBitOne(tree.colors+tree.rights[base] / 8, tree.rights[base] % 8);
				rotateLeft(iterator.tree, parent);
				current = root;
				break;
			}
		}
		else 
		{
			base = tree.lefts[parent];
			if (!getBit(tree.colors[base / 8], base % 8))
			{
				setBitOne(tree.colors+base / 8, base % 8);
				setBitNull(tree.colors+parent / 8, parent % 8);
				rotateLeft(iterator.tree, parent);
				base = tree.lefts[parent];
			}
			left_flag = getBit(tree.colors[tree.lefts[base] / 8], tree.lefts[base] % 8);
			if (left_flag && getBit(tree.colors[tree.rights[base] / 8], tree.rights[base] % 8))
			{
				setBitNull(tree.colors+base / 8, base % 8);
				current = parent;
				parent = tree.parents[current];
			}
			else
			{
				if (left_flag)
				{
					setBitOne(tree.colors+tree.rights[base] / 8, tree.rights[base] % 8);
					setBitNull(tree.colors+base / 8, base % 8);
					rotateRight(iterator.tree, base);
					base = tree.lefts[parent];
				}
				if (getBit(tree.colors[parent / 8], parent % 8))
					setBitOne(tree.colors+base / 8, base % 8);
				else
					setBitNull(tree.colors+base / 8, base % 8);
				setBitOne(tree.colors+parent / 8, parent % 8);
				setBitOne(tree.colors+tree.lefts[base] / 8, tree.lefts[base] % 8);
				rotateRight(iterator.tree, parent);
				current = root;
				break;
			}
		}
	}
	setBitOne(tree.colors+current / 8, current % 8);
	tree.parents[tree.max_number] = tree.max_number;
	if (tree.rights[tree.max_number] == tree.max_number)
		((RedBlackTree*)iterator.tree)->root = tree.lefts[tree.max_number];
	else
		((RedBlackTree*)iterator.tree)->root = tree.rights[tree.max_number];	
}

BinaryTree_Iterator buildRedBlackTree_Iterator(RedBlackTree* tree, IteratorStartPosition start_position)
{
	BinaryTree_Iterator iterator;
	iterator.tree = tree;
	iterator.current = tree->root;
	uint32_t* lefts = tree->lefts;
	uint32_t* rights = tree->rights;
	uint32_t null = tree->max_number;
	if (isControlledMemoryEmpty(&(tree->controller))) 
	{
		iterator.current = null;
		return iterator;
	}
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
	return iterator;
}
void goNextInRedBlackTree(BinaryTree_Iterator* iterator)
{
	RedBlackTree tree = *((RedBlackTree*)iterator->tree);
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
void goPreviousInRedBlackTree(BinaryTree_Iterator* iterator)
{
	RedBlackTree tree = *((RedBlackTree*)iterator->tree);
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
void* getElementFromRedBlackTree(BinaryTree_Iterator* iterator)
{
	return ((RedBlackTree*)iterator->tree)->temp + iterator->current * ((RedBlackTree*)iterator->tree)->size;
}
uint8_t isNotLastInRedBlackTree(BinaryTree_Iterator* iterator)
{
	RedBlackTree tree = *((RedBlackTree*)iterator->tree);
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
uint8_t isNotFirstInRedBlackTree(BinaryTree_Iterator* iterator)
{
	RedBlackTree tree = *((RedBlackTree*)iterator->tree);
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
uint8_t isNotNullOfRedBlackTree(BinaryTree_Iterator* iterator) 
{
	return iterator->current != ((RedBlackTree*)iterator->tree)->max_number;
}