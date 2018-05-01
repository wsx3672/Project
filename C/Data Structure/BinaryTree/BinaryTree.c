//BinaryTree.c
#include "BinaryTree.h"
#include <stdlib.h> //calloc, malloc
#include <memory.h> //memcpy

void BinaryTree_Create(BinaryTree *binaryTree)
{
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

BinaryNode* BinaryTree_Insert(BinaryTree *binaryTree, void *key, size_t size, int(*compare)(void*, void*))
{
	BinaryNode *node;
	BinaryNode *it;
	BinaryNode *parent = NULL;
	it = binaryTree->root;
	while (it != NULL) {
		parent = it;
		if (compare(it + 1, key) > 0) {
			it = it->left;
		}
		else {
			it = it->right;
		}
	}
	node = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
	memcpy(node + 1, key, size);
	node->left = NULL;
	node->right = NULL;
	if (parent != NULL) {
		if (compare(parent + 1, node + 1) > 0) {
			parent->left = node;
		}
		else {
			parent->right = node;
		}
		if (compare(binaryTree->root + 1, node + 1) > 0) {
			binaryTree->balance--;
		}
		else {
			binaryTree->balance++;
		}
	}
	else {
		binaryTree->root = node;
	}
	binaryTree->length++;
	return node;

}

BinaryNode* Search(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*))
{
	BinaryNode *index;
	index = binaryTree->root;
	while (index != NULL&&compare(index + 1, key) != 0) {
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	return index;
}

BinaryNode* BinaryTree_Delete(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*))
{
	BinaryNode *index;
	BinaryNode *otherIndex = NULL;
	BinaryNode *parent = NULL;
	BinaryNode *parentIndex = NULL;

	index = binaryTree->root;
	while (compare(index + 1, key) != 0)
	{
		parent = index;
		if (compare(index + 1, key) > 0)
		{
			index = index->left;
		}
		else
		{
			index = index->right;
		}

	}
	if (index->right != NULL)
	{
		otherIndex = index->right;
		while (otherIndex->left != NULL)
		{
			parentIndex = otherIndex;
			otherIndex = otherIndex->left;
		}
		if (parentIndex != NULL)
		{
			parentIndex->left = otherIndex->right;
			otherIndex->right = index->right;
		}
		otherIndex->left = index->left;
	}
	else if (index->left != NULL)
	{
		otherIndex = index->left;
		while (otherIndex->right != NULL)
		{
			parentIndex = otherIndex;
			otherIndex = otherIndex->right;
		}
		if (parentIndex != NULL)
		{
			parentIndex->right = otherIndex->left;
			otherIndex->left = index->left;
		}
	}
	if (compare(binaryTree->root + 1, key) != 0)
	{
		if (parent != NULL)
		{
			if (compare(parent + 1, key) > 0)
			{
				parent->left = otherIndex;
			}
			else
			{
				parent->right = otherIndex;
			}
		}
		if (compare(binaryTree->root + 1, key) < 0)
		{
			binaryTree->balance--;
		}
		else
		{
			binaryTree->balance++;
		}
	}
	else
	{
		binaryTree->root = otherIndex;
		if (index->right != NULL)
		{
			binaryTree->balance--;
		}
		else if (index->left != NULL)
		{
			binaryTree->balance++;
		}
	}
	if (index != NULL)
	{
		free(index);
		index = NULL;
	}
	binaryTree->length--;

	return index;

}

void MakeBalance(BinaryTree *binaryTree, size_t size)
{
	void(*keys);
	Long length;

	CopyToBuffer(binaryTree, &keys, &length, size);
	BinaryTree_DeleteAllItems(binaryTree);
	MakeTree(binaryTree, keys, length, size);
	if (keys != NULL) {
		free(keys);
		keys = NULL;
	}
}

void CopyToBuffer(BinaryTree *binaryTree, void *(*keys), Long *length, size_t size)
{
	Long i = 0;
	*length = 0;

	*keys = calloc(binaryTree->length, size);
	Node_CopyToBuffer(binaryTree->root, *keys, length, &i, size);
}

void Node_CopyToBuffer(BinaryNode *node, void(*keys), Long *length, Long *i, size_t size)
{
	if (node != NULL) {
		Node_CopyToBuffer(node->left, keys, length, i, size);
		memcpy(((char*)keys) + ((*i)*size), node + 1, size);
		(*length)++;
		(*i)++;
		Node_CopyToBuffer(node->right, keys, length, i, size);
	}
}

void BinaryTree_DeleteAllItems(BinaryTree *binaryTree) {
	BinaryTree_Node_DeleteAllItems(binaryTree->root);
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

void BinaryTree_Node_DeleteAllItems(BinaryNode *node) {
	if (node != NULL) {
		BinaryTree_Node_DeleteAllItems(node->left);
		BinaryTree_Node_DeleteAllItems(node->right);
		free(node);
		node = NULL;
	}
}

BinaryNode* MakeTree(BinaryTree *binaryTree, void(*keys), Long length, size_t size)
{
	BinaryNode *node;
	Long low = 0;
	Long high;
	Long remainder;
	high = length - 1;

	node = Node_MakeTree(keys, low, high, size);
	binaryTree->root = node;
	binaryTree->length = length;
	remainder = length % 2;
	if (remainder == 0) {
		binaryTree->balance = 1;
	}
	else {
		binaryTree->balance = 0;
	}
	return node;
}

BinaryNode* Node_MakeTree(void(*keys), Long low, Long high, size_t size) {
	Long middle;
	BinaryNode *node = NULL;
	if (low <= high) {
		node = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
		middle = (low + high) / 2;
		memcpy(node + 1, ((char*)keys) + (middle*size), size);
		node->left = Node_MakeTree(keys, low, middle - 1, size);
		node->right = Node_MakeTree(keys, middle + 1, high, size);
	}
	return node;
}

void BinaryTree_GetAt(BinaryTree *binaryTree, BinaryNode *index, void *key, size_t size) {

	memcpy(key, index + 1, size);
}

void BinaryTree_Destroy(BinaryTree *binaryTree) {
	BinaryTree_Node_Destroy(binaryTree->root);
}

void BinaryTree_Node_Destroy(BinaryNode* node) {
	if (node != NULL) {
		BinaryTree_Node_Destroy(node->left);
		BinaryTree_Node_Destroy(node->right);
		free(node);
	}
}