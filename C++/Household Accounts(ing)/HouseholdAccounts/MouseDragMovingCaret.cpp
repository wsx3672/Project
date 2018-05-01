#include "MouseDragMovingCaret.h"
#include "TextEdit.h"
#include "TextComposite.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "TextAreaSelected.h"
#include "Caret.h"
MouseDragMovingCaret::MouseDragMovingCaret() {
}
MouseDragMovingCaret::~MouseDragMovingCaret() {
}
MouseDragMovingCaret::MouseDragMovingCaret(const MouseDragMovingCaret& source) {
}
void MouseDragMovingCaret::LeftMovingCaret(TextEdit *textEdit, CClientDC *cClientDC, TextComposite *currentTextComposite, CSize *stringSize , Long currentCharacterIndex , Long currentX) {

	TextComponent *textComponent = currentTextComposite->GetAt(currentCharacterIndex - 1);
	Character *character = static_cast<Character*>(textComponent);
	Long ret = character->CheckingSingleAndDouble();
	CSize size;
	char temp;
	char *temps;
	if (ret == 0) {
		SingleByteCharacter* singleByteCharacter = static_cast<SingleByteCharacter*>(character);
		temp = singleByteCharacter->GetCharacter();
		size = cClientDC->GetTextExtent(temp);
	}
	else {
		DoubleByteCharacter* doubleByteCharacter = static_cast<DoubleByteCharacter*>(character);
		temps = doubleByteCharacter->GetCharacter();
		temps[2] = '\0';
		size = cClientDC->GetTextExtent(temps);
	}
	Long index = textEdit->textAreaSelected->Find(textComponent);
	if (index == -1) {
		textEdit->textAreaSelected->Add(textComponent);
	}
	else {
		textEdit->textAreaSelected->Remove(textComponent);
	}
	textEdit->caret->LeftArrowKeyMovingCaret();
}
void MouseDragMovingCaret::RightMovingCaret(TextEdit *textEdit, CClientDC *cClientDC, TextComposite *currentTextComposite, CSize *stringSize , Long currentCharacterIndex , Long currentX) {
	TextComponent *textComponent = currentTextComposite->GetAt(currentCharacterIndex);
	Character *character = static_cast<Character*>(textComponent);
	Long ret = character->CheckingSingleAndDouble();
	CSize size;
	char temp;
	char *temps;
	if (ret == 0) {
		SingleByteCharacter *singleByteCharacter = static_cast<SingleByteCharacter*>(character);
		temp = singleByteCharacter->GetCharacter();
		size = cClientDC->GetTextExtent(temp);
	}
	else {
		DoubleByteCharacter *doubleByteCharacter = static_cast<DoubleByteCharacter*>(character);
		temps = doubleByteCharacter->GetCharacter();
		temps[2] = '\0';
		size = cClientDC->GetTextExtent(temps);
	}
	Long index = textEdit->textAreaSelected->Find(textComponent);
	if (index == -1) {
		textEdit->textAreaSelected->Add(textComponent);
	}
	else {
		textEdit->textAreaSelected->Remove(textComponent);
	}
	textEdit->caret->RightArrowKeyMovingCaret();
}