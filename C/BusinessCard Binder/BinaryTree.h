//BinaryTree.h
#ifndef _BINARYTREE_H
#define _BINARYTREE_H
#include <stddef.h>

typedef signed long int Long;
typedef struct _binaryNode BinaryNode;
typedef struct _binaryNode {
	BinaryNode *left;
	BinaryNode *right;
}BinaryNode;
typedef struct _binaryTree {
	BinaryNode *root;
	Long length;
	Long balance;
}BinaryTree;

void BinaryTree_Create(BinaryTree *binaryTree);
BinaryNode* BinaryTree_Insert(BinaryTree *binaryTree, void *key, size_t size, int(*compare)(void*, void*));
BinaryNode* Search(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*));
BinaryNode* BinaryTree_Delete(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*));
void MakeBalance(BinaryTree *binaryTree, size_t size);
void CopyToBuffer(BinaryTree *binaryTree, void *(*keys), Long *length, size_t size);
void Node_CopyToBuffer(BinaryNode *node, void (*keys), Long *length, Long *i, size_t size);
void BinaryTree_DeleteAllItems(BinaryTree *binaryTree);
void BinaryTree_Node_DeleteAllItems(BinaryNode *node);
BinaryNode* MakeTree(BinaryTree *binaryTree, void(*keys), Long length, size_t size);
BinaryNode* Node_MakeTree(void (*keys), Long low, Long high, size_t size);
void BinaryTree_Destroy(BinaryTree *binaryTree);
void BinaryTree_Node_Destroy(BinaryNode *node);
void BinaryTree_GetAt(BinaryTree *binaryTree, BinaryNode *index, void *key, size_t size);

#endif // _BINARYTREE_H
