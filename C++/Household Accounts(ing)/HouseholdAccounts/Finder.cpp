#include "Finder.h"
#include "TextEdit.h"
#include "Text.h"
#include "TextComponent.h"
#include "TextComposite.h"
#include "Caret.h"
#include "TextAreaSelected.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "MouseDragMovingCaret.h"
Finder::Finder(TextEdit *textEdit) {
	this->textEdit = textEdit;
}
Finder::Finder(const Finder& source) {
	this->textEdit = source.textEdit;
}
Finder::~Finder() {
}
Finder& Finder::operator=(const Finder& source) {
	this->textEdit = source.textEdit;
	return *this;
}
void Finder::MouseLButtonClick(Long startX, Long startY) {
	Long rowIndex = startY / 17;
	Long length = this->textEdit->text->GetLength();
	rowIndex++;
	if (length < rowIndex) {
		rowIndex = length;
	}
	TextComponent *currentTextComponent = this->textEdit->text->GetAt(rowIndex -1);
	TextComposite *currentTextComposite = currentTextComponent->GetComposite();
	Long rowLength = currentTextComposite->GetLength();
	Long i = 0;
	CSize size;
	CFont font;
	this->textEdit->caret->FontSetting(&font);
	CClientDC dc(this->textEdit);
	dc.SelectObject(font);
	CString cString;
	Long characterIndex;
	Long x = 0;
	Long previousX = 0; 
	while (i < rowLength && x < startX) {
		cString = currentTextComposite->MakeCString(i+1);
		size = dc.GetTextExtent(cString); 
		previousX = x;
		x = size.cx;
		i++;
	}
	if (x < startX) {
		previousX = x;
		characterIndex = rowLength;
	}
	else {
		characterIndex = i-1;
	}
	this->textEdit->caret->SetCharacterIndex(characterIndex);
	this->textEdit->caret->SetCurrentRowIndex(rowIndex);
	this->textEdit->caret->SetCurrentY((rowIndex-1) * 17);
	this->textEdit->caret->SetCurrentX(previousX);
}
void Finder::MouseLButtonDrag(Long currentX, Long currentY) {
	if (this->textEdit->selectedArea == false) {
		this->textEdit->textAreaSelected->Setting(this->textEdit->caret);
	}
	Long startX = this->textEdit->textAreaSelected->GetStartX();
	Long startY = this->textEdit->textAreaSelected->GetStartY();
	Long currentCharacterIndex = this->textEdit->caret->GetCharacterIndex();
	//Long startRowIndex = startY / 17;
	Long currentRowIndex = 1 + (currentY / 17);
	Long length = this->textEdit->text->GetLength();
	if (currentRowIndex > length) {
		currentRowIndex = length;
	}
	TextComponent *currentTextComponent = this->textEdit->text->GetAt(currentRowIndex - 1);
	TextComposite *currentTextComposite = currentTextComponent->GetComposite();
	CClientDC  dc(this->textEdit);
	CSize stringSize;
	CSize currentCharacterSize ;
	CFont font;
	CString cString = '\0';
	CString currentCharacterString = '\0';
	this->textEdit->caret->FontSetting(&font);
	dc.SelectObject(font);
	MouseDragMovingCaret mouseDragMovingCaret;
	Long ret = -1;
	if (currentCharacterIndex != 0) {
		cString = currentTextComposite->MakeCString(currentCharacterIndex);
	}
	//////////////////// currentCharacterIndex가 0일때 문제
	if (cString != '\0') {
		currentCharacterString = currentTextComposite->MakeCString(currentCharacterIndex - 1, currentCharacterIndex);
	}
	
	stringSize = dc.GetTextExtent(cString);
	currentCharacterSize = dc.GetTextExtent(currentCharacterString);
	length = currentTextComposite->GetLength();
	///////////왼쪽 Moving이 아니면 currentCharacterSize 닫시 구해야함
	if (currentCharacterIndex != 0 && stringSize.cx > currentX) {//&& length != currentCharacterIndex) {
		if (stringSize.cx - (currentCharacterSize.cx / 2) > currentX) {
			mouseDragMovingCaret.LeftMovingCaret(this->textEdit, &dc, currentTextComposite, &stringSize, currentCharacterIndex, currentX);
		}
	}
	if (currentCharacterIndex + 1 <= length) {
		if (stringSize.cx + (currentCharacterSize.cx / 2) < currentX) {
			mouseDragMovingCaret.RightMovingCaret(this->textEdit, &dc, currentTextComposite, &stringSize, currentCharacterIndex, currentX);
		}
	}
	
	

	length = this->textEdit->textAreaSelected->GetLength();
	if (length != 0) {
		this->textEdit->selectedArea = true;
	}
}
