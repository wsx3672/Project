#include "CtrlAndAKey.h"
#include "TextEdit.h"
#include "Caret.h"
#include "TextAreaSelected.h"
#include "Text.h"
#include "TextComposite.h"
#include "TextComponent.h"
CtrlAndAKey::CtrlAndAKey() {
}
CtrlAndAKey::~CtrlAndAKey() {
}
CtrlAndAKey::CtrlAndAKey(const CtrlAndAKey& source) {
}
CtrlAndAKey& CtrlAndAKey::operator=(const CtrlAndAKey& source) {
	return *this;
}
void CtrlAndAKey::Action(TextEdit *textEdit) {
	Long i = 0;
	TextComponent *textComponent = 0;
	Long length = textEdit->textAreaSelected->GetLength();
	while (i < length) {
		textComponent = textEdit->textAreaSelected->GetAt(0);
		textEdit->textAreaSelected->Remove(textComponent);
		i++;
	}
	textEdit->textAreaSelected->SetStartRowIndex(1);
	textEdit->textAreaSelected->SetStartCharacterIndex(0);
	textEdit->textAreaSelected->SetStartX(0);
	textEdit->textAreaSelected->SetStartY(0);
	 length = textEdit->text->GetLength();
	Long rowLength;
	TextComponent *rowTextComponent = 0;
	TextComposite *rowTextComposite = 0;

	 i =0;
	Long j;
	while (i < length) {
		rowTextComponent = textEdit->text->GetAt(i);
		rowTextComposite = rowTextComponent->GetComposite();
		rowLength = rowTextComposite->GetLength();
		j = 0;
		while (j < rowLength) {
			textComponent = rowTextComposite->GetAt(j);
			textEdit->textAreaSelected->Add(textComponent);
			j++;
		}
		i++;
	}
	CClientDC  dc(textEdit);
	CSize size;
	CFont font;
	textEdit->caret->FontSetting(&font);
	dc.SelectObject(font);
	CString cString = rowTextComposite->MakeCString(rowLength);
	size = dc.GetTextExtent(cString);
	textEdit->caret->SetCurrentRowIndex(length);
	textEdit->caret->SetCharacterIndex(rowLength);
	textEdit->caret->SetCurrentX(size.cx);
	Long y = (length - 1) * 17;
	textEdit->caret->SetCurrentY(y);
	textEdit->caret->CreateCaret();
	length = textEdit->textAreaSelected->GetLength();
	if (length > 0) {
		textEdit->selectedArea = true;
	}
}