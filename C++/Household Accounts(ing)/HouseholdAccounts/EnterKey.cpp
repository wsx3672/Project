#include "EnterKey.h"
#include "Row.h"
#include "Text.h"
#include "TextComponent.h"
#include "TextComposite.h"
#include "TextEdit.h"
#include "SingleByteCharacter.h"
#include "Caret.h"
#include "TextAreaSelected.h"
#include "SelectedRemoveProcess.h"
#include "Row.h"
EnterKey::EnterKey() {
}
EnterKey::~EnterKey() {
}
EnterKey::EnterKey(const EnterKey& source) {
}
EnterKey& EnterKey::operator=(const EnterKey& source) {
	return *this;
}
void EnterKey::Action(TextEdit *textEdit) {

	Long length = textEdit->textAreaSelected->GetLength();
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	if (length > 0) {
		SelectedRemoveProcess selectedRemoveProcess;
		selectedRemoveProcess.SelectedRemove(textEdit);
		length = textEdit->text->GetLength();
		if(length  < currentRowIndex){
			Row *row = new Row;
			currentRowIndex = textEdit->text->Add(row);
		}
		selectedRemoveProcess.SelectedRemoveAfterSetCaret(textEdit);
		textEdit->selectedArea = false;
	}
	Long characterIndex = textEdit->caret->GetCharacterIndex();
	TextComponent *textComponent = textEdit->text->GetAt(currentRowIndex - 1);
	TextComposite *textComposite = textComponent->GetComposite();
	Long rowLength = textComposite->GetLength();
	Long position;
	SingleByteCharacter *singleByteCharacter = new SingleByteCharacter('\n');
	if (rowLength == characterIndex) {
		position = textComponent->Add(singleByteCharacter);
		textEdit->caret->SetCharacterIndex(position);
	}
	else {
		position = textComponent->Insert(characterIndex, singleByteCharacter);
		textEdit->caret->SetCharacterIndex(position + 1);
	}
	rowLength = textComposite->GetLength();
	characterIndex = textEdit->caret->GetCharacterIndex();
	Row *row = new Row(); 
	position = characterIndex;
	while (characterIndex < rowLength) {
		TextComponent *temp = textComposite->GetAt(characterIndex);
		row->Add(temp);
		characterIndex++;
	}
	while (rowLength > position ) {
		TextComponent *temp = textComposite->GetAt(position);
		textComposite->Remove(temp);
		rowLength--;
	}
	 length = textEdit->text->GetLength();
	if (length == currentRowIndex) {
		currentRowIndex = textEdit->text->Add(row);
		textEdit->caret->SetCurrentRowIndex(currentRowIndex);
	}
	else {
		currentRowIndex=textEdit->text->Insert(currentRowIndex, row);
		textEdit->caret->SetCurrentRowIndex(currentRowIndex+1);
	}
	textEdit->caret->NextRowMovingCaret();
}
