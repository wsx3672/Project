//Index.h
#ifndef  _INDEX_H
#define  _INDEX_H
#include "Array.h"
typedef struct _businessCard BusinessCard;
typedef signed long int Long;
typedef struct _index {
	Array businessCards;
	char name[64];
	Long capacity;
	Long length;
}Index;
void Index_Create(Index *index, Long capacity);
Long Index_Add(Index *index, BusinessCard *businessCardIndex);
Long Index_Remove(Index *index, Long Position);
Long Index_Find(Index *index, BusinessCard *businessCardIndex);
BusinessCard* Index_GetAt(Index *index, Long position);
int Index_CompareBusinessCardLinks(void* one, void *other);
void Index_Destroy(Index *index);

#endif // ! _INDEX_H