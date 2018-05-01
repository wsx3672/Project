#include "EndKey.h"
#include "TextEdit.h"
#include "Caret.h"
#include "TextAreaSelected.h"
EndKey::EndKey() {
}
EndKey::~EndKey() {
}
EndKey::EndKey(const EndKey& source) {
}
EndKey& EndKey::operator=(const EndKey& source) {
	return *this;
}
void EndKey::Action(TextEdit *textEdit) {
	Long length = textEdit->textAreaSelected->GetLength();
	TextComponent *textComponent;
	while (length != 0) {
		textComponent = textEdit->textAreaSelected->GetAt(0);
		textEdit->textAreaSelected->Remove(textComponent);
		length = textEdit->textAreaSelected->GetLength();
	}
	textEdit->selectedArea = false;
	textEdit->caret->EndKeyMovingCaret();
}