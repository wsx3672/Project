#include "TextComposite.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
TextComposite::TextComposite(Long capacity) : textComponents(capacity) {
	this->capacity = capacity;
	this->length = 0;
}
TextComposite::~TextComposite() {
}
TextComposite::TextComposite(const TextComposite& source) : textComponents(source.textComponents) {
	this->capacity = source.capacity;
	this->length = source.length; 
}
TextComposite& TextComposite::operator= (const TextComposite& source) {
	this->textComponents = source.textComponents;
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;
}
TextComposite* TextComposite::GetComposite() {
	return this;
}
Long TextComposite::Add(TextComponent *textComponent) {
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
Long TextComposite::Modify(Long index, TextComponent *textComponent) {
	return this->textComponents.Modify(index, textComponent);
}
TextComponent* TextComposite::GetAt(Long index) {
	return this->textComponents.GetAt(index);
}
TextComponent* TextComposite::operator[](Long index) {
	return this->textComponents[index];
}
Long TextComposite::Remove(TextComponent *textComponent) {
	Long i = 0;
	Long index = 0;
	while (i < this->length && this->textComponents.GetAt(i) != textComponent) {
		i++;
	}
	if (i < this->length) {
		index = this->textComponents.Delete(i);
		this->capacity--;
		this->length--;
	}
	return index;
}
Long TextComposite::Remove(Long index) {
	Long position = 0;
	if (this->textComponents.GetAt(index) != 0) {
		position = this->textComponents.Delete(index);
		this->length--;
		this->capacity--;
	}
	return position;
}
CString TextComposite::MakeCString(Long length) {
	char tempChar[1028];
	Long i = 0;
	Long j = 0;
	while (i < length) {
		TextComponent *textComponent = this->GetAt(i);
		if (dynamic_cast<SingleByteCharacter*>(textComponent)) {
			SingleByteCharacter *singleByteCharacter = static_cast<SingleByteCharacter*>(textComponent);
			char temp = singleByteCharacter->GetCharacter();
			if (temp != '\n') {
				tempChar[j] = singleByteCharacter->GetCharacter();
				j++;
			}
		}
		if (dynamic_cast<DoubleByteCharacter*>(textComponent)) {
			DoubleByteCharacter *doubleByteCharacter = static_cast<DoubleByteCharacter*>(textComponent);
			tempChar[j] = doubleByteCharacter->GetCharacter()[0];
			j++;
			tempChar[j] = doubleByteCharacter->GetCharacter()[1];
			j++;
		}
		i++;
	}
	CString cString(tempChar, j);
	return cString;
}
CString TextComposite::MakeCString() {
	char tempChar[1028];
	Long i = 0;
	Long j = 0;
	while (i < this->length) {
		TextComponent *textComponent = this->GetAt(i);
		if (dynamic_cast<SingleByteCharacter*>(textComponent)) {
			SingleByteCharacter *singleByteCharacter = static_cast<SingleByteCharacter*>(textComponent);
			char temp = singleByteCharacter->GetCharacter();
			if(temp != '\n'){
			tempChar[j] = singleByteCharacter->GetCharacter();
			j++;
			}
		}
		if (dynamic_cast<DoubleByteCharacter*>(textComponent)) {
			DoubleByteCharacter *doubleByteCharacter = static_cast<DoubleByteCharacter*>(textComponent);
			tempChar[j] = doubleByteCharacter->GetCharacter()[0];
			j++;
			tempChar[j] = doubleByteCharacter->GetCharacter()[1];
			j++;
		}
		i++;
	}
	CString cString(tempChar, j);
	return cString;
}
CString TextComposite::MakeCString(Long firstIndex, Long secondIndex) {
	char tempChar[1028];
	Long j = 0;
	while (firstIndex < secondIndex) {
		TextComponent *textComponent = this->GetAt(firstIndex);
		if (dynamic_cast<SingleByteCharacter*>(textComponent)) {
			SingleByteCharacter *singleByteCharacter = static_cast<SingleByteCharacter*>(textComponent);
			char temp = singleByteCharacter->GetCharacter();
			if (temp != '\n') {
				tempChar[j] = singleByteCharacter->GetCharacter();
				j++;
			}
		}
		if (dynamic_cast<DoubleByteCharacter*>(textComponent)) {
			DoubleByteCharacter *doubleByteCharacter = static_cast<DoubleByteCharacter*>(textComponent);
			tempChar[j] = doubleByteCharacter->GetCharacter()[0];
			j++;
			tempChar[j] = doubleByteCharacter->GetCharacter()[1];
			j++;
		}
		firstIndex++;
	}
	CString cString(tempChar, j);
	return cString;
}
Long TextComposite::GetSelectedWidth(CDC *cdc) {
	char tempChar[1028];
	Long i = 0;
	Long j = 0;
	while (i < this->length) {
		TextComponent *textComponent = this->GetAt(i);
		if (dynamic_cast<SingleByteCharacter*>(textComponent)) {
			SingleByteCharacter *singleByteCharacter = static_cast<SingleByteCharacter*>(textComponent);
			char temp = singleByteCharacter->GetCharacter();
			if (temp != '\n') {
				tempChar[j] = singleByteCharacter->GetCharacter();
				j++;
			}
		}
		if (dynamic_cast<DoubleByteCharacter*>(textComponent)) {
			DoubleByteCharacter *doubleByteCharacter = static_cast<DoubleByteCharacter*>(textComponent);
			tempChar[j] = doubleByteCharacter->GetCharacter()[0];
			j++;
			tempChar[j] = doubleByteCharacter->GetCharacter()[1];
			j++;
		}
		i++;
	}
	CString cString(tempChar, j);
	CSize size = cdc->GetTextExtent(cString);
	return size.cx;
}
Long TextComposite::Insert(Long index, TextComponent *textComponent) {
	Long position = this->textComponents.Insert(index , textComponent);
	this->length++;
	this->capacity++;
	return position;
}
Long TextComposite::Find(TextComponent *textComponent) {
	Long index = -1;
	Long i = 0;
	TextComponent *compareTextComponent = 0;
	while (i < this->length && compareTextComponent != textComponent) {
		compareTextComponent = this->GetAt(i);
		i++;
	}
	if (compareTextComponent == textComponent) {
		index = 1;
	}
	return index;
}
void TextComposite::DeleteAllItems() {
	while ( this->length != 0) {
		this->textComponents.Delete(0);
		this->length--;
	}
}