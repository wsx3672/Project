//Indexes.cpp

#include  "Indexes.h"
#include "BusinessCard.h"
Indexes::Indexes() {
	this->length = 0;
}
Indexes::Indexes(const Indexes& source):indexes(source.indexes) {
	this->length = source.length;
}
Indexes::~Indexes() {
}

Index* Indexes::TakeIn(BusinessCard *index) {
	string name = index->GetCompanyName();
	Index key(name);

	BinaryTree<Index>::Node *node = this->indexes.Search(key, CompareCompanyNamess);
	if (node == 0) {
		node = this->indexes.Insert(key, CompareCompanyNamess);
		this->length++;
	}
	Index *keyIndex = &node->GetKey();
	keyIndex->Add(index);
	return keyIndex;
}
Index* Indexes::TakeOut(BusinessCard *index, string name) {
	Long position;
	Index key(name);

	BinaryTree<Index>::Node *node = this->indexes.Search(key, CompareCompanyNamess);
	Index *indexIndex = &node->GetKey();
	position = indexIndex->Find(index);
	indexIndex->Remove(position);
	Long length = indexIndex->GetLength();
	if (length == 0) {
		node = this->indexes.Delete(key,CompareCompanyNamess); // 포인터함수 불확실
		indexIndex = 0;
	}
	return indexIndex;
}
void Indexes::Arrange() {
	this->indexes.MakeBalance();
}
Index* Indexes::Find(string name) {
	Index key(name);
	Index *index = 0;
	BinaryTree<Index>::Node *node = this->indexes.Search(key,CompareCompanyNamess);
	if (node != 0) {
		index = &node->GetKey();
	}
	return index;
}
void Indexes::MakeList(Index *(*indexes), Long *count) {
	this->indexes.CopyToBuffer(indexes, count);
}
int CompareCompanyNamess(void *one, void *other) {
	return (static_cast<Index*>(one))->GetName().compare((static_cast<Index*>(other))->GetName());
}
Indexes& Indexes::operator=(const Indexes& source){
	this->indexes = source.indexes;
	this->length = source.length;
	return *this;
}