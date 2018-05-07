#pragma once
//Indexes.h
#ifndef _INDEXES_H
#define _INDEXES_H

#include "Index.h"
#include "BinaryTree.h"
#include <string>

using namespace std;

class BusinessCard;
class Indexes {
public:
	Indexes();
	Indexes(const Indexes& source);
	~Indexes();

	Index* TakeIn(BusinessCard *index);
	Index* TakeOut(BusinessCard *index, string name);
	void Arrange();
	Index* Find(string name);
	void MakeList(Index *(*indexes), Long *count);

	Long GetLength()const;
	Indexes& operator=(const Indexes& source);
private:
	BinaryTree<Index> indexes;
	Long length;
};
int CompareCompanyNamess(void *one, void *other);

inline Long Indexes::GetLength()const {
	return this->length;
}
#endif // !_INDEXES_H
