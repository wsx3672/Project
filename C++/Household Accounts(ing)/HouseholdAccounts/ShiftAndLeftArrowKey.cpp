#include "ShiftAndLeftArrowKey.h"
#include "TextEdit.h"
#include "TextAreaSelected.h"
#include "Text.h"
#include "Caret.h"
#include "Character.h"
ShiftAndLeftArrowKey::ShiftAndLeftArrowKey() {
}
ShiftAndLeftArrowKey::~ShiftAndLeftArrowKey() {
}
ShiftAndLeftArrowKey::ShiftAndLeftArrowKey(const ShiftAndLeftArrowKey& source) {
}
ShiftAndLeftArrowKey& ShiftAndLeftArrowKey::operator=(const ShiftAndLeftArrowKey& source) {
	return *this;
}
void ShiftAndLeftArrowKey::Action(TextEdit *textEdit) {
	if (textEdit->selectedArea == false) {
		textEdit->textAreaSelected->Setting(textEdit->caret);
		textEdit->selectedArea = true;
	}
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	TextComponent *textComponent = textEdit->text->GetAt(currentRowIndex - 1);
	TextComposite *textComposite = textComponent->GetComposite();
	Long characterIndex = textEdit->caret->GetCharacterIndex();
	if (characterIndex == 0 && currentRowIndex != 1) {
		currentRowIndex--;
		textEdit->caret->SetCurrentRowIndex(currentRowIndex);
		textComponent = textEdit->text->GetAt(currentRowIndex - 1);
		textComposite = textComponent->GetComposite();
		Long tempCharacterIndex = textComposite->GetLength();
		textEdit->caret->SetCharacterIndex(tempCharacterIndex);
		characterIndex = textEdit->caret->GetCharacterIndex();
		textEdit->caret->PreviousRowMovingCaret();
	}
	TextComponent *getTextComponent = 0;
	TextComponent *compareTextComponent = 0;
	if (characterIndex != 0) {
		getTextComponent = textComposite->GetAt(characterIndex - 1);
	}
	Long length = textEdit->textAreaSelected->GetLength();
	if (length != 0) {
		compareTextComponent = textEdit->textAreaSelected->GetAt(length - 1);
	}
	if (getTextComponent != 0) {
		if (getTextComponent == compareTextComponent) {
			textEdit->textAreaSelected->Remove(length - 1);
			textEdit->caret->LeftArrowKeyMovingCaret();
		}
		else {
			textEdit->textAreaSelected->Add(getTextComponent);
			textEdit->caret->LeftArrowKeyMovingCaret();
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