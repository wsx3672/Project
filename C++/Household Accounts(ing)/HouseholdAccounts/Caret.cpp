#include "Caret.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "TextComponent.h"
#include "TextComposite.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Character.h"
#include <afxwin.h>
Caret::Caret(TextEdit *textEdit) {
	this->textEdit = textEdit;
	this->currentX = 0;
	this->currentY = 0;
	this->currentRowIndex = 1;
	this->characterIndex = 0;
}
Caret::Caret(const Caret& source) {
	this->textEdit = source.textEdit;
}
Caret::~Caret() {
}
Caret& Caret::operator=(const Caret& source) {
	this->textEdit = source.textEdit;
	return *this;
}
void Caret::CreateCaret(Long width , Long height ) {
	this->textEdit->CreateSolidCaret(width, height);
	CPoint cPoint(this->currentX, this->currentY);
	this->textEdit->SetCaretPos(cPoint);
	this->textEdit->ShowCaret();
}
void Caret::ChangeCaretWidth() {
	this->textEdit->CreateSolidCaret(2, 17);
}
Long Caret::SetCurrentX(Long currentX) {
	this->currentX = currentX;
	return this->currentX;
}
Long Caret::SetCurrentY(Long currentY) {
	this->currentY = currentY;
	return this->currentY;
}
void Caret::RightMovingCaret() {
	CClientDC  dc(this->textEdit);
	CSize size;
	CFont font;
	CString cString;
	this->FontSetting(&font);
	dc.SelectObject(font);
	TextComponent *textComponent = this->textEdit->text->GetAt(this->currentRowIndex - 1);
	TextComposite *textComposite = textComponent->GetComposite();
	Long rowLength = textComposite->GetLength();
	if (rowLength == this->characterIndex) {
		cString = textComposite->MakeCString();
	}
	else {
		cString = textComposite->MakeCString(this->characterIndex);
	}
	size = dc.GetTextExtent(cString);
	this->currentX = size.cx ;
	CPoint cPoint(this->currentX, this->currentY);
	this->textEdit->SetCaretPos(cPoint);
}
Long Caret::SetCharacterIndex(Long characterIndex) {
	this->characterIndex = characterIndex;
	return this->characterIndex;
}
void Caret::BackSpaceKeyMovingCaret() {
	CClientDC  dc(this->textEdit);
	CSize size;
	CFont font;
	this->FontSetting(&font);
	dc.SelectObject(font);
	TextComponent *textComponent = this->textEdit->text->GetAt(this->currentRowIndex - 1);
	TextComposite *textComposite = textComponent->GetComposite();
	CString cString = textComposite->MakeCString(this->characterIndex-1);
	size = dc.GetTextExtent(cString);
	this->currentX = size.cx ;
	this->CreateCaret();
	this->characterIndex--;
}
void Caret::LeftArrowKeyMovingCaret() {
	this->characterIndex--;
	CClientDC  dc(this->textEdit);
	CSize size;
	CSize characterSize;
	CString cString;
	CFont font;
	char *temps;
	char temp;
	TextComposite *textComposite = 0;
	TextComponent *textComponent = 0;
	this->FontSetting(&font);
	dc.SelectObject(font);
	if (this->characterIndex >= 0) {
		textComponent = this->textEdit->text->GetAt(this->currentRowIndex-1);
		textComposite = textComponent->GetComposite();
		if (textComposite !=0) {
			cString = textComposite->MakeCString(this->characterIndex+1);
			size = dc.GetTextExtent(cString);
			Character *character = static_cast<Character*>(textComposite->GetAt(this->characterIndex));
			Long checking = character->CheckingSingleAndDouble();
			if (checking > 0) {
				temps = static_cast<DoubleByteCharacter*>(character)->GetCharacter();
				temps[2] = '\0';
				characterSize = dc.GetTextExtent(temps);
			}
			else {
				temp = static_cast<SingleByteCharacter*>(character)->GetCharacter();
				characterSize = dc.GetTextExtent(temp);
			}
			this->currentX = size.cx - characterSize.cx;
			this->CreateCaret();

		}
	}
	else if (this->currentRowIndex == 1) {
		this->characterIndex++;
	}
	else {
		//왼쪽방향키 눌렀을때 이전줄로 가는거 구현
		this->currentRowIndex--;
		TextComponent *textComponent = this->textEdit->text->GetAt(currentRowIndex - 1);
		TextComposite *textComposite = textComponent->GetComposite();
		Long tempCharacterIndex = textComposite->GetLength();
		this->characterIndex = tempCharacterIndex-1;
		this->PreviousRowMovingCaret();
	}

}
void Caret::IncludeDoubleByteCharacter() {
	CClientDC  dc(this->textEdit);
	CSize size;
	CFont font;
	this->FontSetting(&font);
	dc.SelectObject(font);
	TextComponent *textComponent = this->textEdit->text->GetAt(this->currentRowIndex - 1);
	TextComposite *textComposite = textComponent->GetComposite();
	DoubleByteCharacter *doubleByteCharacter = static_cast<DoubleByteCharacter*>(textComposite->GetAt(this->characterIndex - 1));
	char *temps = doubleByteCharacter->GetCharacter();
	temps[2] = '\0';
	size = dc.GetTextExtent(temps);
	this->CreateCaret(size.cx , 17);
}
Long Caret::SetCurrentRowIndex(Long currentRowIndex) {
	this->currentRowIndex = currentRowIndex;
	return this->currentRowIndex;
}
void Caret::RightArrowKeyMovingCaret() {
	CClientDC  dc(this->textEdit);
	CSize characterSize;
	CFont font;
	char *temps;
	char temp = ' ';
	TextComposite *textComposite = 0;
	TextComponent *textComponent = 0;
	bool ret = false;
	this->FontSetting(&font);
	dc.SelectObject(font);
	textComponent = this->textEdit->text->GetAt(this->currentRowIndex - 1);
	textComposite = textComponent->GetComposite();
	if (textComposite != 0) {
		this->characterIndex++;
		Long length = textComposite->GetLength();
		if (this->characterIndex > length) {
			this->characterIndex--;
			ret = true;
		}
		if (ret == false ) {
			Character *character = static_cast<Character*>(textComposite->GetAt(this->characterIndex - 1));
			Long cheak = character->CheckingSingleAndDouble();
			if (cheak > 0) {
				temps = static_cast<DoubleByteCharacter*>(character)->GetCharacter();
				temps[2] = '\0';
				characterSize = dc.GetTextExtent(temps);
			}
			else {
				temp = static_cast<SingleByteCharacter*>(character)->GetCharacter();
				characterSize = dc.GetTextExtent(temp);
			}
			if (temp == '\n') {
				//다음줄로 이동
				Long rowLength = this->textEdit->text->GetLength();
				if (rowLength != this->currentRowIndex) {
					this->currentRowIndex++;
					this->characterIndex = 0;
					this->NextRowMovingCaret();
				}
			}
			else {
				this->currentX += characterSize.cx;
				this->CreateCaret();
			}
		}
	}
}
void Caret::UpArrowKeyMovingCaret() {
	CClientDC  dc(this->textEdit);
	CSize currentSize;
	CString currentCString;
	CSize upSize;
	CString upCString;
	CFont font;
	TextComposite *currentComposite = 0;
	TextComponent *currentComponent = 0;
	TextComposite *upComposite = 0;
	TextComponent *upComponent = 0;
	bool ret = false;
	this->FontSetting(&font);
	dc.SelectObject(font);
	currentComponent = this->textEdit->text->GetAt(this->currentRowIndex - 1);
	currentComposite = currentComponent->GetComposite();
	this->currentRowIndex--;
	if (this->currentRowIndex == 0) {
		this->currentRowIndex++;
	}
	upComponent = this->textEdit->text->GetAt(this->currentRowIndex - 1);
	upComposite = upComponent->GetComposite();
	if (currentComposite == upComposite) {
		ret = true;
	}
	currentCString = currentComposite->MakeCString(this->characterIndex);
	currentSize = dc.GetTextExtent(currentCString);
	upCString = upComposite->MakeCString();
	upSize = dc.GetTextExtent(upCString);
	if (currentSize.cx <= upSize.cx) {
		Long i = 1;
		Long upRowLength = upComposite->GetLength();
		CSize compareCSize;
		CString compareCString;
		Long cx = 0;
		while (i <= upRowLength && currentSize.cx > cx) {
			compareCString = upComposite->MakeCString(i);
			compareCSize = dc.GetTextExtent(compareCString);
			cx = compareCSize.cx;
			i++;
		}
		if (i <= upRowLength && ret == false) {
			i--;
			this->characterIndex = i   ;
			CString string = upComposite->MakeCString(this->characterIndex);
			CSize size = dc.GetTextExtent(string);
			this->currentX = size.cx;
			this->currentY -= 17;
		}
	}
	else if (ret == false){
		this->characterIndex = upComposite->GetLength();
		Character *character = static_cast<Character*>(upComposite->GetAt(upComposite->GetLength() - 1));
		Long ret = character->CheckingSingleAndDouble();
		char temp = ' ';
		if (ret == 0) {
			temp = static_cast<SingleByteCharacter*>(character)->GetCharacter();
		}
		if (temp == '\n') {
			this->characterIndex--;
		}
		this->currentX = upSize.cx;
		this->currentY -= 17;
	}
	this->CreateCaret();
}
void Caret::DownArrowKeyMovingCaret() {
	/////
	CClientDC  dc(this->textEdit);
	CSize currentSize;
	CString currentCString;
	CSize downSize;
	CString downCString;
	CFont font;
	TextComposite *currentComposite = 0;
	TextComponent *currentComponent = 0;
	TextComposite *downComposite = 0;
	TextComponent *downComponent = 0;
	bool ret = false;
	this->FontSetting(&font);
	dc.SelectObject(font);
	currentComponent = this->textEdit->text->GetAt(this->currentRowIndex - 1);
	currentComposite = currentComponent->GetComposite();
	this->currentRowIndex++;
	if (this->currentRowIndex > this->textEdit->text->GetLength()) {
		this->currentRowIndex--;
	}
	downComponent = this->textEdit->text->GetAt(this->currentRowIndex - 1);
	downComposite = downComponent->GetComposite();
	if (currentComposite == downComposite) {
		ret = true;
	}
	currentCString = currentComposite->MakeCString(this->characterIndex );
	currentSize = dc.GetTextExtent(currentCString);
	downCString = downComposite->MakeCString();
	downSize = dc.GetTextExtent(downCString);
	if (currentSize.cx <= downSize.cx) {
		Long i = 1;
		Long downRowLength = downComposite->GetLength();
		CSize compareCSize;
		CString compareCString;
		Long cx = 0;
		while (i <= downRowLength && currentSize.cx > cx) {
			compareCString = downComposite->MakeCString(i);
			compareCSize = dc.GetTextExtent(compareCString);
			cx = compareCSize.cx;
			i++;
		}
		if (i-1 <= downRowLength && ret == false) {
			i--;
			this->characterIndex = i;
			CString string = downComposite->MakeCString(this->characterIndex);
			CSize size = dc.GetTextExtent(string);
			this->currentX = size.cx;
			this->currentY += 17;
		}
		else if (downRowLength == 0 && ret == false) {
			this->characterIndex = 0;
			this->currentX = 0;
			this->currentY += 17;
		}
	}
	else if (ret == false ) {
		Long downCompositeLength = downComposite->GetLength();
		Character *character = 0;
		Long ret = -1;
		if (downCompositeLength != 0) {
			character = static_cast<Character*>(downComposite->GetAt(downComposite->GetLength() - 1));
			ret = character->CheckingSingleAndDouble();
		}
		char temp = ' ';
		if (ret == 0) {
			temp = static_cast<SingleByteCharacter*>(character)->GetCharacter();
		}
		this->characterIndex = downComposite->GetLength();
		if (temp == '\n') {
			this->characterIndex--;
		}
		this->currentX = downSize.cx;
		this->currentY += 17;
	}
	this->CreateCaret();
}
void Caret::NextRowMovingCaret() {
	this->currentX = 0;
	this->currentY += 17;
	this->characterIndex = 0;
	this->CreateCaret();
}
void Caret::PreviousRowMovingCaret() {
	CClientDC  dc(this->textEdit);
	CSize size;
	CFont font;
	this->FontSetting(&font);
	dc.SelectObject(font);
	TextComponent *textComponent = this->textEdit->text->GetAt(this->currentRowIndex - 1);
	TextComposite *textComposite = textComponent->GetComposite();
	CString cString = textComposite->MakeCString(this->characterIndex);
	size = dc.GetTextExtent(cString);
	this->currentX = size.cx;
	this->currentY -= 17;
	this->CreateCaret();
}
void Caret::HomeKeyMovingCaret() {
	this->currentX = 0;
	this->characterIndex = 0;
	this->CreateCaret();
}
void Caret::EndKeyMovingCaret() {
	CClientDC  dc(this->textEdit);
	CSize size;
	CFont font;
	this->FontSetting(&font);
	dc.SelectObject(font);
	TextComponent *textComponent = this->textEdit->text->GetAt(this->currentRowIndex - 1);
	TextComposite *textComposite = textComponent->GetComposite();
	Long length = textComposite->GetLength();
	if (this->currentRowIndex < this->textEdit->text->GetLength()) {
		length--;
	}
	CString cString = textComposite->MakeCString(length);
	size = dc.GetTextExtent(cString);
	this->currentX = size.cx;
	this->characterIndex = length;
	this->CreateCaret();
}
void Caret::ShiftAndLeftArrowCaretMoving(TextComponent *textComponent) {
	CClientDC  dc(this->textEdit);
	CSize size;
	CFont font;
	CString cString;
	textEdit->caret->FontSetting(&font);
	dc.SelectObject(font);
	if (this->characterIndex >= 0) {
		Character *character = static_cast<Character*>(textComponent);
		Long ret = character->CheckingSingleAndDouble();
		char temp;
		char *temps;
		if (ret == 0) {
			temp = static_cast<SingleByteCharacter*>(character)->GetCharacter();
			size = dc.GetTextExtent(temp);
		}
		else {
			temps = static_cast<DoubleByteCharacter*>(character)->GetCharacter();
			temps[2] = '\0';
			size = dc.GetTextExtent(temps);
		}
		this->currentX -= size.cx;
		this->characterIndex--;
		textEdit->caret->CreateCaret();
	}
	else {

	}
}
void Caret::ShiftAndRightArrowCaretMoving(TextComponent *textComponent) {
	CClientDC  dc(this->textEdit);
	CSize size;
	CFont font;
	CString cString;
	textEdit->caret->FontSetting(&font);
	dc.SelectObject(font);
	Character *character = static_cast<Character*>(textComponent);
	Long ret = character->CheckingSingleAndDouble();
	char temp;
	char *temps;
	if (ret == 0) {
		temp = static_cast<SingleByteCharacter*>(character)->GetCharacter();
		size = dc.GetTextExtent(temp);
	}
	else {
		temps = static_cast<DoubleByteCharacter*>(character)->GetCharacter();
		temps[2] = '\0';
		size = dc.GetTextExtent(temps);
	}
	this->currentX += size.cx;
	this->characterIndex++;
	textEdit->caret->CreateCaret();
}
void Caret::FontSetting(CFont *font) {
	font->CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "고딕체");
}