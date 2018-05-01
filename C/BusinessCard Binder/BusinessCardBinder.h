//BusinessCardBinder.h
#ifndef _BUSINESSCARDBINDER_H
#define _BUSINESSCARDBINDER_H
#include "LinkedList.h"

typedef signed long int Long;

typedef struct _personal {
	char name[11];
	char position[11];
	char telephoneNumber[12];
	char emailAddress[64];
} Personal;

typedef struct _company {
	char name[64];
	char address[128];
	char telephoneNumber[12];
	char faxNumber[12];
	char url[256];
} Company;

typedef struct _businessCard {
	Personal personal;
	Company company;
} BusinessCard;

typedef struct _businessCardBinder {
	LinkedList businessCards;
	Long length;
	BusinessCard *current;
} BusinessCardBinder;

//함수선언
void BusinessCardBinder_Create(BusinessCardBinder *businessCardBinder);
Long BusinessCardBinder_Load(BusinessCardBinder *businessCardBinder);

BusinessCard* BusinessCardBinder_TakeIn(BusinessCardBinder *businessCardBinder, BusinessCard businessCard);
void BusinessCardBinder_Find(BusinessCardBinder *businessCardBinder, char(*name), BusinessCard**(*indexes), Long *count);
//void BusinessCardBinder_Arrange(BusinessCardBinder *businessCardBinder);
BusinessCard BusinessCardBinder_TakeOut(BusinessCardBinder *businessCardBinder, BusinessCard *index);
BusinessCard* BusinessCardBinder_First(BusinessCardBinder *businessCardBinder);
BusinessCard* BusinessCardBinder_Previous(BusinessCardBinder *businessCardBinder);
BusinessCard* BusinessCardBinder_Next(BusinessCardBinder *businessCardBinder);
BusinessCard* BusinessCardBinder_Last(BusinessCardBinder *businessCardBinder);
BusinessCard* BusinessCardBinder_FindByCompanyName(BusinessCardBinder *businessCardBinder, char(*companyName));

int BusinessCardBinder_CompareNames(void *one, void *other);
int BusinessCardBinder_CompareBusinessCards(void *one, void *other);

int CompareBusinessCardIndexes(void *one, void *other);
BusinessCard* Move(BusinessCardBinder *businessCardBinder, BusinessCard *businessCardIndex);

void BusinessCardBinder_GetAt(BusinessCardBinder *businessCardBinder, BusinessCard* index, BusinessCard businessCard, size_t size);

Long BusinessCardBinder_Save(BusinessCardBinder *businessCardBinder);

Long BusinessCardBinder_Add(BusinessCardBinder *businessCardBinder, BusinessCard *businessCardIndex);
Long BusinessCardBinder_Remove(BusinessCardBinder *businessCardBinder, BusinessCard *businessCardLink);

void BusinessCardBinder_Destroy(BusinessCardBinder *businessCardBinder);

#endif // _BUSINESSCARDBINDER_H