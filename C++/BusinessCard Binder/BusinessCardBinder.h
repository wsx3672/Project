//BusinessCardBinder.h

#ifndef _BUSINESSCARDBINDER_H
#define _BUSINESSCARDBINDER_H
#include "BusinessCard.h"
#include "LinkedList.h"
#include <string>

using namespace std;

typedef signed long int Long;

class BusinessCardBinder {
public:
	BusinessCardBinder();
	BusinessCardBinder(const BusinessCardBinder& source);
	~BusinessCardBinder();

	BusinessCard* TakeIn(BusinessCard businessCard);
	BusinessCard TakeOut(BusinessCard *index);
	void Find(string name, BusinessCard**(*indexes), Long *count);
	BusinessCard* First();
	BusinessCard* Previous();
	BusinessCard* Next();
	BusinessCard* Last();
	BusinessCard* Move(BusinessCard *index);
	BusinessCard* FindByCompanyName(string companyName);
	BusinessCardBinder& operator = (const BusinessCardBinder& source);
	BusinessCard& operator [] (Long index);
public:
	Long GetLength() const;
	BusinessCard* GetCurrent() const;
private:
	LinkedList<BusinessCard> businessCards; //라이브러리랑 집단화 관계?
	Long length;
	BusinessCard *current;
};
int CompareNames(void *one, void *other);
int CompareBusinessCardLinkss(void *one, void *other);
int CompareCompanyNames(void *one, void *other);

inline Long BusinessCardBinder::GetLength() const {
	return this->length;
}
inline BusinessCard* BusinessCardBinder::GetCurrent() const {
	return const_cast<BusinessCard*>(this->current);
}

#endif // _BusinessCardBinder_H

