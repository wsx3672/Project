#include "Text.h"


Text::Text(Long capacity):TextComposite(capacity) {
	this->capacity = capacity;
	this->length = 0;
}
Text::~Text() {
}
Text::Text(const Text& source) : TextComposite(source){
	this->textComponents = source.textComponents;
	this->capacity = source.capacity;
	this->length = source.length;
}
Text& Text::operator=(const Text& source) {
	this->textComponents = source.textComponents;
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;
}
Long Text::Add(Row *row) {
	
	if (this->length < this->capacity) {
		this->textComponents.Store(this->length, row);
	}
	else {
		this->textComponents.AppendFromRear(row);
		this->capacity++;
	}
	this->length++;
	return this->length;
}
TextComponent* Text::GetAt(Long index) {
	return this->textComponents.GetAt(index);
}
TextComponent* Text::operator[](Long index) {
	return this->textComponents[index];
}
Long Text::Add(TextComponent *textComponent) {
	Long position = TextComposite::Add(textComponent);
	return position;
}
Long Text::Remove(TextComponent *textComponent) {
	Long position = TextComposite::Remove(textComponent);
	return position;
}
Long Text::Remove(Long index) {
	Long position = TextComposite::Remove(index);
	return position;
}
Long Text::Modify(Long index, TextComponent *textComponent) {
	Long position = TextComposite::Modify(index, textComponent);
	return position;
}
Long Text::Insert(Long index, TextComponent *textComponent) {
	Long position = TextComposite::Insert(index, textComponent);
	return position;
}
TextComponent* Text::Clone() const {
	return new Text(*this);
}
/*
int main(int agrc, char *argv[]) {
	return 0;
}
/
#include <iostream>
#include "Row.h"
#include "SingleByteCharacter.h"
using namespace std;

int main(int argc, char *argv[]) {
	Text text;
	Row *row = new Row; 
	Long capacity;
	Long length;
	
	Long i = 0;
	while (i < 1000) {
		SingleByteCharacter singleByteCharacter('A');
		row->Add(static_cast<Character*>(&singleByteCharacter));
		i++;
	}
	text.Add(row);
	Row *test = text.GetAt(0);

	Long rowLength = test->GetLength();
	Long j = 0;
	while (j < rowLength) {
		SingleByteCharacter *singleByte = static_cast<SingleByteCharacter*>(test->GetAt(j));

		char character = singleByte->GetCharacter();

		cout << character << endl;
		j++;
	}
	capacity = text.GetCapacity();
	length = text.GetLength();

	cout << capacity << " " << length << endl;

	Text text1(text);
	
	i = 0;
	Long text1Length = text1.GetLength();

	while (i < text1Length) {
		Row *testRow = text1.GetAt(i);
		j = 0;
		Long testRowLength = testRow->GetLength();
		while (j < testRowLength) {
			SingleByteCharacter *singleByte = static_cast<SingleByteCharacter*>(testRow->GetAt(j));

			char character = singleByte->GetCharacter();

			cout << character << endl;
			j++;
		}
		i++;
	}
	


	
	return 0;
}
*/