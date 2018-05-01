#include "UpArrowKey.h"
#include "TextEdit.h"
#include "Caret.h"
#include "TextAreaSelected.h"
UpArrowKey::UpArrowKey() {
}
UpArrowKey::~UpArrowKey() {
}
UpArrowKey::UpArrowKey(const UpArrowKey& source) {
}
UpArrowKey& UpArrowKey::operator=(const UpArrowKey& source) {
	return *this;
}
void UpArrowKey::Action(TextEdit *textEdit) {
	Long length = textEdit->textAreaSelected->GetLength();
	TextComponent *textComponent;
	while (length != 0) {
		textComponent = textEdit->textAreaSelected->GetAt(0);
		textEdit->textAreaSelected->Remove(textComponent);
		length = textEdit->textAreaSelected->GetLength();
	}
	textEdit->selectedArea = false;
	textEdit->caret->UpArrowKeyMovingCaret();
}