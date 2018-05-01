#include "ShiftAndRightArrowKey.h"
#include "TextEdit.h"
#include "TextAreaSelected.h"
#include "Text.h"
#include "Caret.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
ShiftAndRightArrowKey::ShiftAndRightArrowKey() {
}
ShiftAndRightArrowKey::~ShiftAndRightArrowKey() {
}
ShiftAndRightArrowKey::ShiftAndRightArrowKey(const ShiftAndRightArrowKey& source) {
}
ShiftAndRightArrowKey& ShiftAndRightArrowKey::operator=(const ShiftAndRightArrowKey& source) {
	return *this;
}
void ShiftAndRightArrowKey::Action(TextEdit *textEdit) {
	if (textEdit->selectedArea == false) {
		textEdit->textAreaSelected->Setting(textEdit->caret);
		textEdit->selectedArea = true;
	}
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	Long length = textEdit->text->GetLength();
	TextComponent *textComponent = textEdit->text->GetAt(currentRowIndex - 1);
	TextComposite *textComposite = textComponent->GetComposite();
	Long characterIndex = textEdit->caret->GetCharacterIndex();
	Long rowLength = textComposite->GetLength();
	bool ret = false;
	TextComponent *getTextComponent = 0;
	if (characterIndex == rowLength-1  && length != currentRowIndex) {
		getTextComponent = textComposite->GetAt(characterIndex);
		currentRowIndex++;
		textEdit->caret->SetCurrentRowIndex(currentRowIndex);
		textComponent = textEdit->text->GetAt(currentRowIndex - 1);
		textComposite = textComponent->GetComposite();
		ret = true;
	}
	if (getTextComponent == 0 && rowLength != characterIndex) {
		getTextComponent = textComposite->GetAt(characterIndex);
	}
	Long SelectedLength = textEdit->textAreaSelected->GetLength();
	TextComponent *compareTextComponent = textEdit->textAreaSelected->GetAt(SelectedLength - 1);
	if (getTextComponent != 0) {
		if (getTextComponent == compareTextComponent) {
			textEdit->textAreaSelected->Remove(SelectedLength - 1);
		}
		else {
			textEdit->textAreaSelected->Add(getTextComponent);
		}
		if (ret != true) {
			textEdit->caret->RightArrowKeyMovingCaret();
		}
		else {
			textEdit->caret->NextRowMovingCaret();
		}
	}
	currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	characterIndex = textEdit->caret->GetCharacterIndex();
	Long startRowIndex = textEdit->textAreaSelected->GetStartRowIndex();
	Long startCharacterIndex = textEdit->textAreaSelected->GetStartCharacterIndex();
	if (startRowIndex == currentRowIndex && startCharacterIndex == characterIndex) {
		textEdit->selectedArea = false;
	}
}