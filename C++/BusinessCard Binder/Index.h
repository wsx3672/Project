#pragma once
//Index.h
#ifndef _INDEX_H
#define _INDEX_H
#include "Array.h"
#include <string>
class BusinessCard;
typedef signed long int Long;
using namespace std;
class Index {
public:
	Index(Long capacity = 0);
	Index(string name, Long capacity = 0);
	Index(const Index& source);
	~Index();

	bool IsEqual(const Index& source);
	bool IsNotEqual(const Index& source);
	Long Add(BusinessCard *index);
	Long Remove(Long position);
	Long Find(BusinessCard *index);
	BusinessCard* GetAt(Long position);
	Index& operator =(const Index& source);
	BusinessCard* operator [](Long index);
	bool operator ==(const Index& source);
	bool operator !=(const Index& source);
	string& GetName()const;
	Long GetCapacity()const;
	Long GetLength()const;
private:
	string name;
	Array<BusinessCard*> businesscards;
	Long capacity;
	Long length;
};
int CompareBusinessCardLinks(void *one, void *other);

inline string& Index::GetName() const {
	return const_cast<string&>(this->name);
}
inline Long Index::GetCapacity()const {
	return this->capacity;
}
inline Long Index::GetLength()const {
	return this->length;
}
#endif // !_INDEX_H

