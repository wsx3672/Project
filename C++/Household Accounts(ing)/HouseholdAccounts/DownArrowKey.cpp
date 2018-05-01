#include "DownArrowKey.h"
#include "TextEdit.h"
#include "Caret.h"
#include "TextAreaSelected.h"
DownArrowKey::DownArrowKey() {
}
DownArrowKey::~DownArrowKey() {
}
DownArrowKey::DownArrowKey(const DownArrowKey& source) {
}
DownArrowKey& DownArrowKey::operator=(const DownArrowKey& source) {
	return *this;
}
void DownArrowKey::Action(TextEdit *textEdit) {
	Long length = textEdit->textAreaSelected->GetLength();
	TextComponent *textComponent;
	while (length != 0) {
		textComponent = textEdit->textAreaSelected->GetAt(0);
		textEdit->textAreaSelected->Remove(textComponent);
		length = textEdit->textAreaSelected->GetLength();
	}
	textEdit->selectedArea = false;
	textEdit->caret->DownArrowKeyMovingCaret();
}