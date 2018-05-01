#include "SelectedRemoveProcess.h"
#include "TextEdit.h"
#include "TextAreaSelected.h"
#include "Caret.h"
#include "TextComponent.h"
#include "Text.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
SelectedRemoveProcess::SelectedRemoveProcess() {
}
SelectedRemoveProcess::~SelectedRemoveProcess() {
}
SelectedRemoveProcess::SelectedRemoveProcess(const SelectedRemoveProcess& source) {
}
void SelectedRemoveProcess::SelectedRemove(TextEdit *textEdit) {
	Long i;
	Long startRowIndex = textEdit->textAreaSelected->GetStartRowIndex();
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	Long characterIndex = textEdit->caret->GetCharacterIndex();
	TextComponent *textComponent;
	TextComposite *textComposite;
	Long length;
	Long selectedLength = textEdit->textAreaSelected->GetLength();
	TextComponent *compareTextComponent = 0;
	Long firstRowIndex;
	Long secondRowIndex;
	Long first;
	Long second;
	if (startRowIndex > currentRowIndex) {
		first = currentRowIndex;
		second = startRowIndex;
	}
	else {
		first = startRowIndex;
		second = currentRowIndex;
	}
	secondRowIndex = second;
	while (selectedLength != 0) { //선택된 글자 삭제
		TextComponent *temp = textEdit->textAreaSelected->GetAt(0);
		bool ret = false;
		firstRowIndex = first;
		while (firstRowIndex <= secondRowIndex && ret == false) {
			textComponent = textEdit->text->GetAt(firstRowIndex - 1);
			textComposite = textComponent->GetComposite();
			length = textComposite->GetLength();
			i = 0;
			compareTextComponent = 0;
			while (i < length && temp != compareTextComponent) {
				compareTextComponent = textComposite->GetAt(i);
				i++;
			}
			if (temp == compareTextComponent) {
				textComposite->Remove(compareTextComponent);
				textEdit->textAreaSelected->Remove(compareTextComponent);
				ret = true;
			}
			firstRowIndex++;
		}
		selectedLength = textEdit->textAreaSelected->GetLength();
	}

	if (startRowIndex > currentRowIndex) { // 시작줄에 Text가 남아있다면 현재줄로 이동
		TextComponent *startTextComponent = textEdit->text->GetAt(startRowIndex - 1);
		TextComposite *startTextComposite = startTextComponent->GetComposite();
		Long startRowLength = startTextComposite->GetLength();
		textComponent = textEdit->text->GetAt(currentRowIndex - 1);
		textComposite = textComponent->GetComposite();
		Long i = 0;
		while (i < startRowLength) {
			Character *temp = static_cast<Character*>(startTextComposite->GetAt(0));
			Long currentRowLength = textComposite->GetLength();
			textComposite->Insert(currentRowLength, temp->Clone());
			startTextComposite->Remove(temp);
 			i++;
		}
	}
	if (startRowIndex < currentRowIndex) { //현재줄에 Text가 남아있다면 시작줄로 이동
		TextComponent *currentTextComponent = textEdit->text->GetAt(currentRowIndex - 1);
		TextComposite *currentTextComposite = currentTextComponent->GetComposite();
		Long currentRowLength = currentTextComposite->GetLength();
		textComponent = textEdit->text->GetAt(startRowIndex - 1);
		textComposite = textComponent->GetComposite();
		Long j = 0;
		while (j < currentRowLength) {
			Character *temp = static_cast<Character*>(currentTextComposite->GetAt(0));
			Long startRowLength = textComposite->GetLength();
			textComposite->Insert(startRowLength, temp->Clone());
			currentTextComposite->Remove(temp);
			j++;
		}
		textEdit->caret->SetCurrentRowIndex(startRowIndex);
		Long currentY = 17 * (startRowIndex - 1); 
		textEdit->caret->SetCurrentY(currentY );
		textEdit->caret->SetCharacterIndex(textEdit->textAreaSelected->GetStartCharacterIndex());
	}
	firstRowIndex = first;
	while (secondRowIndex >= firstRowIndex) { //빈줄 삭제
		textComponent = textEdit->text->GetAt(secondRowIndex - 1);    
		textComposite = textComponent->GetComposite();
		length = textComposite->GetLength();
		if (length == 0) {
			textEdit->text->Remove(textComponent);
		}
		secondRowIndex--;
	}
}
void SelectedRemoveProcess::SelectedRemoveAfterSetCaret(TextEdit *textEdit) {

	Long startRowIndex = textEdit->textAreaSelected->GetStartRowIndex();
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	Long characterIndex = textEdit->caret->GetCharacterIndex();
	TextComponent *textComponent = textEdit->text->GetAt(currentRowIndex - 1);
	TextComposite *textComposite = textComponent->GetComposite();
	CString cString;
	CFont font;
	textEdit->caret->FontSetting(&font);
	CClientDC dc(textEdit);
	dc.SelectObject(font);
	Long startCharacterIndex = textEdit->textAreaSelected->GetStartCharacterIndex();
	if (startRowIndex == currentRowIndex && startCharacterIndex < characterIndex) {
		cString = textComposite->MakeCString(startCharacterIndex);
		textEdit->caret->SetCharacterIndex(startCharacterIndex);
	}
	else if (startRowIndex == currentRowIndex && startCharacterIndex > characterIndex) {
		cString = textComposite->MakeCString(characterIndex);
		textEdit->caret->SetCharacterIndex(characterIndex);
	}
	else if (startRowIndex > currentRowIndex) {
		cString = textComposite->MakeCString(characterIndex);
		textEdit->caret->SetCharacterIndex(characterIndex);
	}
	else {
		cString = textComposite->MakeCString(characterIndex);
		textEdit->caret->SetCharacterIndex(characterIndex);
	}
	CSize size = dc.GetTextExtent(cString);
	textEdit->caret->SetCurrentX(size.cx);

}
//오후작업 Shift + Right 키후 BackSpace시 시작줄에서 현재줄로 이동 완료
//Shift + Up ,Donw 작업 진행예정 , 선택된 글자 화면표시 진행예정