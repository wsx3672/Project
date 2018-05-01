//WriteKoreanTextProcess.cpp

#pragma comment(lib,"imm32")

#include "WriteKoreanTextProcess.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "TextComponent.h"
#include "DoubleByteCharacter.h"
#include "Caret.h"

WriteKoreanTextProcess::WriteKoreanTextProcess() {
}
WriteKoreanTextProcess::WriteKoreanTextProcess(const WriteKoreanTextProcess& source) {
}
WriteKoreanTextProcess::~WriteKoreanTextProcess() {
}

void WriteKoreanTextProcess::EndComposition(TextEdit *textEdit, Long bufferLength, char(*buffer)) {
	Long i = 0; // 조합이 끝날 때
	char(*tempChar) = new char[bufferLength];
	while (i < bufferLength) {
		tempChar[i] = buffer[i];
		i++;
	}
	DoubleByteCharacter *doubleByteCharacter =  new DoubleByteCharacter(tempChar);
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	TextComponent *textComponent = textEdit->text->GetAt(currentRowIndex -1);
	TextComposite *textComposite = textComponent->GetComposite();
	Long characterIndex = textEdit->caret->GetCharacterIndex();
	textComposite->Modify(characterIndex - 1, doubleByteCharacter);
	textEdit->writingKoreanState = false;
	delete[] tempChar;
}
void WriteKoreanTextProcess::StartComposition(TextEdit *textEdit, Long bufferLength, char(*buffer)) {
	Long i = 0; //조합 시작할때
	char(*tempChar) = new char[bufferLength];
	while (i < bufferLength) {
		tempChar[i] = buffer[i];
		i++;
	}
	DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter(tempChar);
	Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
	TextComponent *textComponent = textEdit->text->GetAt(currentRowIndex -1);
	TextComposite *textComposite = textComponent->GetComposite();
	Long rowLegnth = textComposite->GetLength();
	Long position;
	Long characterIndex = textEdit->caret->GetCharacterIndex();
	if (rowLegnth == characterIndex) {
		position = textComposite->Add(doubleByteCharacter);
		textEdit->caret->SetCharacterIndex(position);
	}
	else {
		position = textComposite->Insert(characterIndex, doubleByteCharacter);
		textEdit->caret->SetCharacterIndex(position + 1);
	}
	textEdit->writingKoreanState = true;
	delete[] tempChar;
}

void WriteKoreanTextProcess::DuringComposition(TextEdit *textEdit, Long bufferLength, char(*buffer)) {
	Long i = 0;
	if (bufferLength > 0) { // 조합중일때
		char(*tempChar) = new char[bufferLength];
		while (i < bufferLength) {
			tempChar[i] = buffer[i];
			i++;
		}
		DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter(tempChar);
		Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
		TextComponent *textComponent = textEdit->text->GetAt(currentRowIndex - 1);
		TextComposite *textComposite = textComponent->GetComposite();
		Long characterIndex = textEdit->caret->GetCharacterIndex();
		textComposite->Modify(characterIndex -1,doubleByteCharacter);
		delete[] tempChar;
	}
	else if (bufferLength == 0) {//BackSpace 를 눌렀을 때
		Long currentRowIndex = textEdit->caret->GetCurrentRowIndex();
		TextComponent *textComponent = textEdit->text->GetAt(currentRowIndex - 1);
		TextComposite *textComposite = textComponent->GetComposite();		
		Long characterIndex = textEdit->caret->GetCharacterIndex();
		TextComponent *doubleByteCharacter = textComposite->GetAt(characterIndex - 1);
		textComposite->Remove(doubleByteCharacter);
		textEdit->caret->CreateCaret();
		textEdit->caret->BackSpaceKeyMovingCaret();
		textEdit->writingKoreanState = false;
	}
}