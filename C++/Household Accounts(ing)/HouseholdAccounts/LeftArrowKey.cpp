#include "LeftArrowKey.h"
#include "TextEdit.h"
#include "Caret.h"
#include "TextAreaSelected.h"
LeftArrowKey::LeftArrowKey() {
}
LeftArrowKey::~LeftArrowKey() {
}
LeftArrowKey::LeftArrowKey(const LeftArrowKey& source) {
}
LeftArrowKey& LeftArrowKey::operator=(const LeftArrowKey& source) {
	return *this;
}
void LeftArrowKey::Action(TextEdit *textEdit) {
	Long length = textEdit->textAreaSelected->GetLength();
	TextComponent *textComponent;
	while (length != 0){
		textComponent = textEdit->textAreaSelected->GetAt(0);
		textEdit->textAreaSelected->Remove(textComponent);
		length = textEdit->textAreaSelected->GetLength();
	}
	textEdit->selectedArea = false;
	textEdit->caret->LeftArrowKeyMovingCaret();
}