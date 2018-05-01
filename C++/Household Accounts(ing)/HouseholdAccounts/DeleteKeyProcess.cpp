#include "DeleteKeyProcess.h"
#include "TextEdit.h"
#include "Caret.h"
#include "TextComponent.h"
#include "TextComposite.h"
#include "Text.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "SelectedRemoveProcess.h"
DeleteKeyProcess::DeleteKeyProcess() {
}
DeleteKeyProcess::~DeleteKeyProcess() {
}
DeleteKeyProcess::DeleteKeyProcess(const DeleteKeyProcess& source) {
}
DeleteKeyProcess& DeleteKeyProcess::operator=(const DeleteKeyProcess& source) {
	return *this;
}
void DeleteKeyProcess::Delete(TextEdit *textEdit) {
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	Long characterIndex = textEdit->caret->GetCharacterIndex();
	TextComponent *textComponent = textEdit->text->GetAt(currentRowIndex - 1);
	TextComposite *textComposite = textComponent->GetComposite();
	Long length = textComposite->GetLength();
	TextComponent *deleteTextComponent = 0;
	Long ret;
	char temp = ' ';
	if (length > characterIndex) {
		deleteTextComponent = textComposite->GetAt(characterIndex);
		ret = static_cast<Character*>(deleteTextComponent)->CheckingSingleAndDouble();
		if (ret == 0) {
			temp = static_cast<SingleByteCharacter*>(deleteTextComponent)->GetCharacter();
		}
	}
	if (deleteTextComponent != 0) {
		textComposite->Remove(deleteTextComponent);
	}
	if (temp == '\n') {
		TextComponent *downTextComponent = textEdit->text->GetAt(currentRowIndex);
		TextComposite *downTextComposite = downTextComponent->GetComposite();
		Long i = 0;
		Long downTextCompositeLength = downTextComposite->GetLength();
		while (i < downTextCompositeLength) {
			textComponent = downTextComposite->GetAt(i);
			textComposite->Add(textComponent);
			i++;
		}
		textEdit->text->Remove(downTextComponent);
	}

}
void DeleteKeyProcess::SelectionDelete(TextEdit *textEdit) {
	SelectedRemoveProcess selectedRemoveProcess;
	selectedRemoveProcess.SelectedRemove(textEdit);
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	Long length = textEdit->text->GetLength();
	if (length < currentRowIndex) {
		Row *row = new Row;
		textEdit->text->Add(row);
	}
	selectedRemoveProcess.SelectedRemoveAfterSetCaret(textEdit);
	textEdit->caret->CreateCaret();
	textEdit->selectedArea = false;
}