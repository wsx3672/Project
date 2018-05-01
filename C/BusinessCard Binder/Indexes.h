//Indexes.h

#ifndef _INDEXES_H
#define _INDEXES_H
#include "BinaryTree.h"

typedef struct _index Index; //둘다 포인터로 갖다써서 전방선언
typedef struct _businessCard BusinessCard;

typedef signed long int Long;

typedef struct _indexes {
	BinaryTree indexes;
	Long length;
} Indexes;

void Indexes_Create(Indexes *indexes);
Index *Indexes_TakeIn(Indexes *indexes, BusinessCard *businessCardIndex);
Index *Indexes_TakeOut(Indexes *indexes, BusinessCard *businessCardIndex, char(*companyName));
void Indexes_Arrange(Indexes *indexes);
Index *Indexes_Find(Indexes *indexes, char(*name));
void Indexes_MakeList(Indexes *indexes, Index *(*keys), Long *count);
int Indexes_CompareCompanyNames(void *one, void *other);
void PrintRecursion(Indexes *indexes);
void Node_PrintRecursion(BinaryNode *node);
void Indexes_Destroy(Indexes *indexes);
void Indexes_AllDestroy(BinaryNode *node);

#endif // _INDEXES_H