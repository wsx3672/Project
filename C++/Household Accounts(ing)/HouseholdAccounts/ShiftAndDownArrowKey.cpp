#include "ShiftAndDownArrowKey.h"
#include "TextEdit.h"
#include "TextAreaSelected.h"
#include "Caret.h"
#include "Text.h"
#include "TextComposite.h"
#include "TextComponent.h"
ShiftAndDownArrowKey::ShiftAndDownArrowKey() {
}
ShiftAndDownArrowKey::~ShiftAndDownArrowKey() {
}
ShiftAndDownArrowKey::ShiftAndDownArrowKey(const ShiftAndDownArrowKey& source) {
}
ShiftAndDownArrowKey& ShiftAndDownArrowKey::operator=(const ShiftAndDownArrowKey& source) {
	return *this;
}
void ShiftAndDownArrowKey::Action(TextEdit *textEdit) {
	if (textEdit->selectedArea == false) {
		textEdit->textAreaSelected->Setting(textEdit->caret);
		textEdit->selectedArea = true;
	}
	Long length = textEdit->text->GetLength();
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	Long currentCharacterIndex = textEdit->caret->GetCharacterIndex();
	Long startRowIndex = textEdit->textAreaSelected->GetStartRowIndex();
	TextComponent *currentTextComponent = textEdit->text->GetAt(currentRowIndex - 1);
	TextComposite *currentTextComposite = currentTextComponent->GetComposite();
	TextComposite *previousTextComposite = currentTextComposite;
	TextComponent *textComponent = 0;
	Long startLength = currentTextComposite->GetLength();

	if (currentRowIndex != length) {
		if (startRowIndex < currentRowIndex + 1) {
			while (currentCharacterIndex < startLength ) { //시작줄 Add
				textComponent = currentTextComposite->GetAt(currentCharacterIndex);
				textEdit->textAreaSelected->Add(textComponent);
				currentCharacterIndex++;
			}
		}
		else {
			while (currentCharacterIndex < startLength ) { //시작줄 Remove
				textComponent = currentTextComposite->GetAt(currentCharacterIndex);
				textEdit->textAreaSelected->Remove(textComponent);
				currentCharacterIndex++;
			}
		}
	}

	textEdit->caret->DownArrowKeyMovingCaret();

    currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	currentCharacterIndex = textEdit->caret->GetCharacterIndex();
	currentTextComponent = textEdit->text->GetAt(currentRowIndex - 1);
	currentTextComposite = currentTextComponent->GetComposite();
	Long i = 0;
	if (currentTextComposite != previousTextComposite) {
		if (startRowIndex < currentRowIndex ) {
			while (i < currentCharacterIndex) { //아랫줄 Add
				textComponent = currentTextComposite->GetAt(i);
				textEdit->textAreaSelected->Add(textComponent);
				i++;
			}
		}
		else {
			while (i < currentCharacterIndex) { //아랫줄 Remove
				textComponent = currentTextComposite->GetAt(i);
				textEdit->textAreaSelected->Remove(textComponent);
				i++;
			}
		}
	}
	else {
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

//Shift 위아래시 Remove 구현예정, 선택된 배열 화면에 출력 예정 (Part부분)