#include "ShiftAndUpArrowKey.h"
#include "TextEdit.h"
#include "TextAreaSelected.h"
#include "Caret.h"
#include "Text.h"
#include "TextComposite.h"
#include "TextComponent.h"
ShiftAndUpArrowKey::ShiftAndUpArrowKey() {
}
ShiftAndUpArrowKey::~ShiftAndUpArrowKey() {
}
ShiftAndUpArrowKey::ShiftAndUpArrowKey(const ShiftAndUpArrowKey& source) {
}
ShiftAndUpArrowKey& ShiftAndUpArrowKey::operator=(const ShiftAndUpArrowKey& source) {
	return *this;
}
void ShiftAndUpArrowKey::Action(TextEdit *textEdit) {
	if (textEdit->selectedArea == false) {
		textEdit->textAreaSelected->Setting(textEdit->caret);
		textEdit->selectedArea = true;
	}
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	Long startRowIndex = textEdit->textAreaSelected->GetStartRowIndex();
	Long currentCharacterIndex = textEdit->caret->GetCharacterIndex();
	TextComponent *currentTextComponent = textEdit->text->GetAt(currentRowIndex - 1);
	TextComposite *currentTextComposite = currentTextComponent->GetComposite();
	TextComposite *previousTextComposite = currentTextComposite;
	TextComponent *textComponent = 0;

	if (currentRowIndex != 1) {
		if (startRowIndex > currentRowIndex -1) {
			while (currentCharacterIndex >= 1) { //시작줄 Add
				textComponent = currentTextComposite->GetAt(currentCharacterIndex - 1);
				textEdit->textAreaSelected->Add(textComponent);
				currentCharacterIndex--;
			}
		}
		else {
			while (currentCharacterIndex >= 1) { //시작줄 Remove
				textComponent = currentTextComposite->GetAt(currentCharacterIndex - 1);
				textEdit->textAreaSelected->Remove(textComponent);
				currentCharacterIndex--;
			}
		}
	}

	textEdit->caret->UpArrowKeyMovingCaret();

	 currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	 currentCharacterIndex = textEdit->caret->GetCharacterIndex();
	currentTextComponent = textEdit->text->GetAt(currentRowIndex - 1);
	currentTextComposite = currentTextComponent->GetComposite();
	Long currentLength = currentTextComposite->GetLength();
	if (currentTextComposite != previousTextComposite) {
		if (startRowIndex > currentRowIndex) {
			while (currentLength > currentCharacterIndex) { //윗줄 Add
				textComponent = currentTextComposite->GetAt(currentLength - 1);
				textEdit->textAreaSelected->Add(textComponent);
				currentLength--;
			}
		}
		else {
			while (currentLength > currentCharacterIndex) { //윗줄 Add
				textComponent = currentTextComposite->GetAt(currentLength - 1);
				textEdit->textAreaSelected->Remove(textComponent);
				currentLength--;
			}
		}
	}
	else { //첫줄에서 이벤트 실행시 
		Long selectionLength = textEdit->textAreaSelected->GetLength();
		if (selectionLength == 0) {
			textEdit->selectedArea = false;
		}
	}
	currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	currentCharacterIndex = textEdit->caret->GetCharacterIndex();
    startRowIndex = textEdit->textAreaSelected->GetStartRowIndex();
	Long startCharacterIndex = textEdit->textAreaSelected->GetStartCharacterIndex();
	if (startRowIndex == currentRowIndex && startCharacterIndex == currentCharacterIndex) {
		textEdit->selectedArea = false;
	}
}