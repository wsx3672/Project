#include "SelectedBackSpaceKey.h"
#include "TextEdit.h"
#include "TextAreaSelected.h"
#include "Text.h"
#include "Caret.h"
#include "SelectedRemoveProcess.h"
SelectedBackSpaceKey::SelectedBackSpaceKey() {
}
SelectedBackSpaceKey::~SelectedBackSpaceKey() {
}
SelectedBackSpaceKey::SelectedBackSpaceKey(const SelectedBackSpaceKey& source) {
}
SelectedBackSpaceKey& SelectedBackSpaceKey::operator=(const SelectedBackSpaceKey& source) {
	return *this;
}
void SelectedBackSpaceKey::Action(TextEdit *textEdit) {
	SelectedRemoveProcess selectedRemoveProcess;
	Long length = textEdit->textAreaSelected->GetLength();
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
		selectedRemoveProcess.SelectedRemove(textEdit);
		length = textEdit->text->GetLength();
		if (length < currentRowIndex) {
			Row *row = new Row;
			textEdit->text->Add(row);
		}
		selectedRemoveProcess.SelectedRemoveAfterSetCaret(textEdit);
	
	textEdit->selectedArea = false;
	textEdit->caret->CreateCaret();
}
