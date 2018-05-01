#include "ShiftAndHomeKey.h"
#include "TextEdit.h"
#include "TextAreaSelected.h"
#include "Text.h"
#include "Caret.h"
#include "TextComponent.h"
#include "TextComposite.h"
ShiftAndHomeKey::ShiftAndHomeKey() {
}
ShiftAndHomeKey::~ShiftAndHomeKey() {
}
ShiftAndHomeKey::ShiftAndHomeKey(const ShiftAndHomeKey& source) {
}
ShiftAndHomeKey& ShiftAndHomeKey::operator=(const ShiftAndHomeKey& source) {
	return *this;
}
void ShiftAndHomeKey::Action(TextEdit *textEdit) {
	if (textEdit->selectedArea == false) {
		textEdit->textAreaSelected->Setting(textEdit->caret);
		textEdit->selectedArea = true;
	}
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	Long currentCharacterIndex = textEdit->caret->GetCharacterIndex();
	Long startRowIndex = textEdit->textAreaSelected->GetStartRowIndex();
	Long startCharacterIndex = textEdit->textAreaSelected->GetStartCharacterIndex();
	TextComponent *currentTextComponent = textEdit->text->GetAt(currentRowIndex - 1);
	TextComposite *currentTextComposite = currentTextComponent->GetComposite();
	TextComponent *textComponent = 0;
	while (currentCharacterIndex > startCharacterIndex) {
		textComponent = currentTextComposite->GetAt(currentCharacterIndex - 1);
		textEdit->textAreaSelected->Remove(textComponent);
		currentCharacterIndex--;
	}
	while (currentCharacterIndex != 0) {
		textComponent = currentTextComposite->GetAt(currentCharacterIndex - 1);
		textEdit->textAreaSelected->Add(textComponent);
		currentCharacterIndex--;
	}
	textEdit->caret->HomeKeyMovingCaret();
	TextComponent *startTextComponent = textEdit->text->GetAt(startRowIndex - 1);
	TextComposite *startTextComposite = startTextComponent->GetComposite();
	currentCharacterIndex = textEdit->caret->GetCharacterIndex();
	if (currentTextComposite == startTextComposite && startCharacterIndex == currentCharacterIndex) {
		textEdit->selectedArea = false;
	}
}