//DownArrowKey.cpp

#include "DownArrowKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Character.h"
#include "FontSet.h"
#include "ClassDiagramForm.h"

DownArrowKey::DownArrowKey() {
}

DownArrowKey::DownArrowKey(const DownArrowKey& source) {
}

DownArrowKey::~DownArrowKey() {
}

void DownArrowKey::KeyPress(TextEdit *textEdit) {
	CPaintDC dc(textEdit);
	if (GetKeyState(VK_SHIFT) >= 0) {
		if (textEdit->flagSelection == 1) {
			textEdit->flagSelection = 0;
		}
	}
	else {
		if (textEdit->flagSelection == 0) {
			textEdit->flagSelection = 1;
			textEdit->selectedX = textEdit->caret->GetCharacterIndex();
			textEdit->selectedY = textEdit->caret->GetRowIndex();
		}
	}
	CFont cFont;
	cFont.CreateFont(textEdit->rowHeight, 0, 0, 0, textEdit->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, textEdit->fontSet->GetFaceName().c_str());
	textEdit->SetFont(&cFont, TRUE);

	CFont *oldFont = dc.SelectObject(&cFont); // ��Ʈ ����

	Long x = textEdit->caret->GetCurrentCaretX();
	Long y = textEdit->caret->GetCurrentCaretY();
	Long previousCharacterIndex = textEdit->caret->GetCharacterIndex();
	Long previousRowIndex = textEdit->caret->GetRowIndex();

	Long rowIndex = y + textEdit->GetRowHeight();

	textEdit->caret->MoveToPoint(textEdit, &dc, CPoint(x, rowIndex));
	if (previousCharacterIndex == textEdit->text->GetAt(previousRowIndex)->GetLength() &&
		previousRowIndex < textEdit->text->GetLength()) {
		textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());
	}
	dc.SelectObject(oldFont);
	cFont.DeleteObject(); // ��Ʈ
}

void DownArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}