#include "RightArrowKey.h"
#include "TextEdit.h"
#include "Caret.h"
#include "TextAreaSelected.h"
RightArrowKey::RightArrowKey() {
}
RightArrowKey::~RightArrowKey() {
}
RightArrowKey::RightArrowKey(const RightArrowKey& source) {
}
RightArrowKey& RightArrowKey::operator=(const RightArrowKey& source) {
	return *this;
}
void RightArrowKey::Action(TextEdit *textEdit) {
	Long length = textEdit->textAreaSelected->GetLength();
	TextComponent *textComponent;
	while (length != 0) {
		textComponent = textEdit->textAreaSelected->GetAt(0);
		textEdit->textAreaSelected->Remove(textComponent);
		length = textEdit->textAreaSelected->GetLength();
	}
	textEdit->selectedArea = false;
	textEdit->caret->RightArrowKeyMovingCaret();
}