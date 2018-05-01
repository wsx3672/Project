//Index.c
#include "Index.h"
#include "BusinessCardBinder.h" 
#include <string.h>

void Index_Create(Index *index, Long capacity) {
	Create(&index->businessCards, capacity, sizeof(BusinessCard*));
	index->capacity = capacity;
	index->length = 0;
	strcpy(index->name, "");
}

Long Index_Add(Index *index, BusinessCard *businessCardIndex) {
	Long position;
	if (index->length < index->capacity) {
		position = Store(&index->businessCards, index->length, &businessCardIndex, sizeof(BusinessCard*));

	}
	else {
		position = AppendFromRear(&index->businessCards, &businessCardIndex, sizeof(BusinessCard*));
		index->capacity++;
	}
	index->length++;
	return position;
}
Long Index_Remove(Index *index, Long position) {
	position = Delete(&index->businessCards, position, sizeof(BusinessCard*));
	index->capacity--;
	index->length--;
	return position;
}
Long Index_Find(Index *index, BusinessCard *businessCardIndex) {
	Long position;
	position = LinearSearchUnique(&index->businessCards, businessCardIndex, sizeof(BusinessCard*), Index_CompareBusinessCardLinks);
	return position;
}
BusinessCard* Index_GetAt(Index *index, Long position) {
	BusinessCard *businessCardIndex;
	GetAt(&index->businessCards, position, &businessCardIndex, sizeof(BusinessCard*));
	return businessCardIndex;
}
int Index_CompareBusinessCardLinks(void* one, void *other) {
	int ret;
	if (*((BusinessCard**)one) == other) {
		ret = 0;
	}
	else {
		ret = -1;
	}
	return ret;
}

void Index_Destroy(Index *index) {
	Destroy(&index->businessCards);
}