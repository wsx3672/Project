#include "SingleByteCharacterAddProcess.h"
#include "TextEdit.h" 
#include "SingleByteCharacter.h"
#include "Caret.h"
#include "Text.h"

SingleByteCharacterAddProcess::SingleByteCharacterAddProcess() {
}
SingleByteCharacterAddProcess::~SingleByteCharacterAddProcess() {
}
SingleByteCharacterAddProcess::SingleByteCharacterAddProcess(const SingleByteCharacterAddProcess& source) {
}
Long SingleByteCharacterAddProcess::SingleByteCharacterAdd(char addChar, TextEdit *textEdit) {
	SingleByteCharacter *singleByteCharacter = new SingleByteCharacter(addChar);
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	TextComponent *textComponent = textEdit->text->GetAt(currentRowIndex - 1);
	TextComposite *textComposite = textComponent->GetComposite();
	Long rowLegnth = textComposite->GetLength();
	Long position = -1;
	Long characterIndex = textEdit->caret->GetCharacterIndex();
	if (rowLegnth == characterIndex) {
		position = textComponent->Add(singleByteCharacter);
		textEdit->caret->SetCharacterIndex(position);
	}
	else {
		position = textComponent->Insert(characterIndex, singleByteCharacter);
		textEdit->caret->SetCharacterIndex(position + 1);
	}
	return position;
}