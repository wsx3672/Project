#include "BackSpaceKey.h"
#include "Row.h"
#include "Text.h"
#include "TextComponent.h"
#include "TextComposite.h"
#include "TextEdit.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "Caret.h"
BackSpaceKey::BackSpaceKey() {
}
BackSpaceKey::~BackSpaceKey() {
}
BackSpaceKey::BackSpaceKey(const BackSpaceKey& source) {
}
BackSpaceKey& BackSpaceKey::operator=(const BackSpaceKey& source) {
	return *this;
}	
void BackSpaceKey::Action(TextEdit *textEdit) {
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	TextComposite *textComposite = static_cast<TextComposite*>(textEdit->text->GetAt(currentRowIndex - 1));
	Long chacracterIndex = textEdit->caret->GetCharacterIndex();
	TextComponent *textComponent = 0;
	Long ret = -1;
	Long i = 0;
	Long rowLength = textComposite->GetLength();
	if (chacracterIndex == 0 && currentRowIndex != 1 ) {
		TextComposite *upTextComposite = static_cast<TextComposite*>(textEdit->text->GetAt(currentRowIndex - 2));
		Long upRowLength = upTextComposite->GetLength();
		Character *character = static_cast<Character*>(upTextComposite->GetAt(upTextComposite->GetLength() - 1));
		 ret = character->CheckingSingleAndDouble();
		if (ret == 0) {
			char temp = static_cast<SingleByteCharacter*>(character)->GetCharacter();
			if (temp == '\n') {
				upTextComposite->Remove(character);
				 i = 0;
				while (i < rowLength) {
					textComponent = textComposite->GetAt(i);
					upTextComposite->Add(textComponent);
					i++;
				}
			}
		}
		textEdit->text->Remove(textComposite);
		currentRowIndex--;
		textEdit->caret->SetCurrentRowIndex(currentRowIndex);
		chacracterIndex = textEdit->caret->SetCharacterIndex(upRowLength - 1);
		textEdit->caret->PreviousRowMovingCaret();
	}
	if (ret == -1 && chacracterIndex != 0 ) {
		textComponent = textComposite->GetAt(chacracterIndex - 1);
		textComposite->Remove(textComponent);
		textEdit->caret->BackSpaceKeyMovingCaret();
	}
}