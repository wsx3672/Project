#include "HomeKey.h"
#include "TextEdit.h"
#include "Caret.h"
#include "TextAreaSelected.h"
HomeKey::HomeKey() {
}
HomeKey::~HomeKey() {
}
HomeKey::HomeKey(const HomeKey& source) {
}
HomeKey& HomeKey::operator=(const HomeKey& source) {
	return *this;
}
void HomeKey::Action(TextEdit *textEdit) {
	Long length = textEdit->textAreaSelected->GetLength();
	TextComponent *textComponent;
	while (length != 0) {
		textComponent = textEdit->textAreaSelected->GetAt(0);
		textEdit->textAreaSelected->Remove(textComponent);
		length = textEdit->textAreaSelected->GetLength();
	}
	textEdit->selectedArea = false;
	textEdit->caret->HomeKeyMovingCaret();
}