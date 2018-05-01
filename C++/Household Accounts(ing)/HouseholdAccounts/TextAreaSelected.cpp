#include "TextAreaSelected.h"
#include "TextEdit.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "Caret.h"
#include "Text.h"
#include "DoubleByteCharacter.h"
#include "TextAreaSelectedProcess.h"
#include <afxwin.h>
TextAreaSelected::TextAreaSelected(Long capacity) : TextComposite(capacity){
	this->length = 0;
	this->capacity = capacity;
	this->startRowIndex = -1;
	this->startCharacterIndex = -1;
	this->startX = -1;
	this->startY = -1;
}
void TextAreaSelected::Setting(Caret *caret) {
	this->startRowIndex = caret->GetCurrentRowIndex();
	this->startCharacterIndex = caret->GetCharacterIndex();
	this->startX = caret->GetCurrentX();
	this->startY = caret->GetCurrentY();
}
TextAreaSelected::TextAreaSelected(const TextAreaSelected& source): TextComposite(source) {
	this->length = source.length;
	this->capacity = source.capacity;
}
TextAreaSelected::~TextAreaSelected() {
}
TextAreaSelected& TextAreaSelected::operator=(const TextAreaSelected& source) {
	this->textComponents = source.textComponents;
	this->length = source.length;
	this->capacity = source.capacity;
	return *this;
}
Long TextAreaSelected::Add(TextComponent *textComponent) {
	Long position = TextComposite::Add(textComponent);
	return position;
}
Long TextAreaSelected::Remove(TextComponent *textComponent) {
	Long position = TextComposite::Remove(textComponent);
	return position;
}
Long TextAreaSelected::Remove(Long index) {
	Long position = TextComposite::Remove(index);
	return position;
}
Long TextAreaSelected::Modify(Long index, TextComponent *textComponent) {
	Long position = TextComposite::Modify(index, textComponent);
	return position;
}
Long TextAreaSelected::Insert(Long index, TextComponent *textComponent) {
	Long position = TextComposite::Insert(index, textComponent);
	return position;
}
Long TextAreaSelected::Find(TextComponent *textComponent) {
	Long position = TextComposite::Find(textComponent);
	return position;
}
void TextAreaSelected::SelectedTextArea(TextEdit *textEdit, CDC *pDC) {
	CString cString;
	CSize size;
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	Long startRowIndex = textEdit->textAreaSelected->GetStartRowIndex();
	TextComponent *textComponent = 0;
	TextComposite *textComposite = 0;
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkColor(RGB(51, 153, 255));
	pDC->SetBkMode(OPAQUE);//텍스트 배경을 SetBkColor 사용
	Long startCharacterIndex ;
	Long endCharacterIndex ;
	Long firstRowStartCharacterIndex;
	Long firstRowEndCharacterIndex;
	Long lastRowStartCharacterIndex;
	Long lastRowEndCharacterIndex;
	Long index = 0;
	Long length = 0;
	TextAreaSelectedProcess textAreaSelectedProcess;
	if (startRowIndex > currentRowIndex) {
		index = currentRowIndex;
		length = startRowIndex;
		firstRowStartCharacterIndex = textEdit->caret->GetCharacterIndex();
		firstRowEndCharacterIndex = textEdit->text->GetAt(currentRowIndex - 1)->GetComposite()->GetLength() ;   // -1 해야하는지
		lastRowStartCharacterIndex = 0;
		lastRowEndCharacterIndex = textEdit->textAreaSelected->GetStartCharacterIndex();
	}
	else if(startRowIndex < currentRowIndex) {
		index = startRowIndex;
		length = currentRowIndex;
		firstRowStartCharacterIndex = textEdit->textAreaSelected->GetStartCharacterIndex();
		firstRowEndCharacterIndex = textEdit->text->GetAt(startRowIndex - 1)->GetComposite()->GetLength();   // -1 해야하는지
		lastRowStartCharacterIndex = 0;
		lastRowEndCharacterIndex = textEdit->caret->GetCharacterIndex();
	}
	
	else {
		if (textEdit->textAreaSelected->GetStartCharacterIndex() > textEdit->caret->GetCharacterIndex()) {
			startCharacterIndex = textEdit->caret->GetCharacterIndex();
			endCharacterIndex = textEdit->textAreaSelected->GetStartCharacterIndex();
		}
		else {
			startCharacterIndex = textEdit->textAreaSelected->GetStartCharacterIndex();
			endCharacterIndex = textEdit->caret->GetCharacterIndex();
		}
		index = currentRowIndex;
		length = currentRowIndex;
	}

	textComponent = textEdit->text->GetAt(index - 1);
	textComposite = textComponent->GetComposite();
	//첫번째줄 , 마지막줄 , 한줄 추가 예정
	if (index == length) {
		textAreaSelectedProcess.SingleRowAreaSelected(textEdit, pDC, textComposite, startCharacterIndex, endCharacterIndex, index);
	}
	else {
		textAreaSelectedProcess.FirstRowAreaSelected(textEdit, pDC, textComposite, firstRowStartCharacterIndex, firstRowEndCharacterIndex, index);
	}
	while (index < length - 1) {
		textComponent = textEdit->text->GetAt(index);
		textComposite = textComponent->GetComposite();
		textAreaSelectedProcess.AllRowAreaSelected(textEdit, pDC, textComposite,index);
		index++;
	}
	textComponent = textEdit->text->GetAt(length - 1);
	textComposite = textComponent->GetComposite();
	if (index != length) {
		textAreaSelectedProcess.LastRowAreaSelected(textEdit, pDC, textComposite, lastRowStartCharacterIndex, lastRowEndCharacterIndex, length);
	}
}
TextComponent* TextAreaSelected::GetAt(Long index) {
	return this->textComponents.GetAt(index);
}
TextComponent* TextAreaSelected::operator[](Long index) {
	return this->textComponents[index];
}
TextComponent* TextAreaSelected::Clone() const {
	return new TextAreaSelected(*this);
}
Long TextAreaSelected::SetStartRowIndex(Long rowIndex) {
	this->startRowIndex = rowIndex;
	return this->startRowIndex;
}
Long TextAreaSelected::SetStartX(Long x) {
	this->startX = x;
	return this->startX;
}
Long TextAreaSelected::SetStartY(Long y) {
	this->startY = y;
	return this->startY;
}
Long TextAreaSelected::SetStartCharacterIndex(Long characterIndex) {
	this->startCharacterIndex = characterIndex;
	return startCharacterIndex;
}
void TextAreaSelected::DeleteAllItems() {
	TextComposite::DeleteAllItems();
}