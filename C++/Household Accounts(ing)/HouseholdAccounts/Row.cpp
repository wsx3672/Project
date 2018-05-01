#include "Row.h"

Row::Row(Long capacity) : TextComposite(capacity){
	this->capacity = capacity;
	this->length = 0;
}
Row::~Row() {
}
Row::Row(const Row& source) : TextComposite(source) {
	this->textComponents = source.textComponents;
	this->capacity = source.capacity;
	this->length = source.length;
}
Row& Row::operator=(const Row& source) {
	this->textComponents = source.textComponents;
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;
}
Long Row::Add(TextComponent *textComponent) {
	Long position = TextComposite::Add(textComponent);
	return position;
}
Long Row::Remove(TextComponent *textComponent) {
	Long position = TextComposite::Remove(textComponent);
	return position;
}
Long Row::Remove(Long index) {
	Long position = TextComposite::Remove(index);
	return position;
}
Long Row::Modify(Long index, TextComponent *textComponent) {
	Long position = TextComposite::Modify(index, textComponent);
	return position;
}
Long Row::Insert(Long index, TextComponent *textComponent) {
	Long position = TextComposite::Insert(index, textComponent);
	return position;
}
TextComponent* Row::Clone() const {
	return new Row(*this);
}
/*
Long Row::Add(TextComponent *textComponent) {
	if (this->length < this->capacity) {
		this->textComponents.Store(this->length, textComponent);
	}
	else {
		this->textComponents.AppendFromRear(textComponent);
		this->capacity++;
	}
	this->length++;
	return this->length;
}
*/
TextComponent* Row::GetAt(Long index) {
	return this->textComponents.GetAt(index);
}
TextComponent* Row::operator[] (Long index) {
	return this->textComponents[index];
}
/*
#include <iostream>
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
using namespace std;
int main(int argc, char *argv[]) {
	Row row;
	Long i = 0;
	while (i < 100) {
		SingleByteCharacter *singleByteCharacter = new SingleByteCharacter('A');
		DoubleByteCharacter *doubleByteCharacter =  new DoubleByteCharacter("วั");

		row.Add(singleByteCharacter);
		row.Add(doubleByteCharacter);
		i++;
	}
	CString cString = row.MakeCString();

	cout << cString << endl;
	return 0;
}
*/