//Index.cpp
#include "Index.h"

Index::Index(Long capacity) :businesscards(capacity), name("") {
	this->capacity = capacity;
	this->length = 0;
}
Index::Index(string name, Long capacity) : name(name), businesscards(capacity) {
	this->capacity = capacity;;
	this->length = 0;
}
Index::Index(const Index& source) : businesscards(source.businesscards), name(source.name) {
	this->capacity = source.capacity;
	this->length = source.capacity;
}
Index::~Index() {
}
bool Index::IsEqual(const Index& source) {
	bool ret = false;
	if (this->name.compare(source.name) == 0) {
		ret = true;
	}
	return true;
}
bool Index::IsNotEqual(const Index& source) {
	bool ret = false;
	if (this->name.compare(source.name) != 0) {
		ret = true;
	}
	return ret;
}
bool Index::operator==(const Index& source) {
	bool ret = false;
	if (this->name.compare(source.name) == 0) {
		ret = true;
	}
	return true;
}
bool Index::operator!=(const Index& source) {
	bool ret = false;
	if (this->name.compare(source.name) != 0) {
		ret = true;
	}
	return ret;
}
Index& Index::operator= (const Index& source) {
	this->businesscards = source.businesscards;
	this->name = source.name;
	this->capacity = source.capacity;
	this->length = source.length;
	return*this;
}
BusinessCard* Index::operator[](Long index) {
	return this->businesscards[index];
}
Long Index::Add(BusinessCard *index) {
	Long position;
	if (this->length < this->capacity) {
		position = this->businesscards.Store(this->length, index);
	}
	else {
		position = this->businesscards.AppendFromRear(index);
		this->capacity++;
	}
	this->length++;
	return position;
}
Long Index::Remove(Long position) {
	position = this->businesscards.Delete(position);
	this->length--;
	this->capacity--;
	return position;
}
Long Index::Find(BusinessCard *index) {
	Long position;
	position = this->businesscards.LinearSearchUnique(index, CompareBusinessCardLinks);
	return position;
}
BusinessCard* Index::GetAt(Long position) {
	BusinessCard *index;
	index = this->businesscards.GetAt(position);
	return index;
}
int CompareBusinessCardLinks(void *one, void *other) {
	int ret = 1;
	if (*(static_cast<BusinessCard**>(one)) == other){
	ret = 0;
}
return ret;
}


