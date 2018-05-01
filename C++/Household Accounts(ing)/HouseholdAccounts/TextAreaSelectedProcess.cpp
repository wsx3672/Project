#include "TextAreaSelectedProcess.h"
#include "TextEdit.h"
#include "TextComposite.h"
#include "Caret.h"
#include "TextAreaSelected.h"
#include <afxwin.h>


TextAreaSelectedProcess::TextAreaSelectedProcess() {
}
TextAreaSelectedProcess::~TextAreaSelectedProcess() {
}
TextAreaSelectedProcess::TextAreaSelectedProcess(const TextAreaSelectedProcess& source) {
}
TextAreaSelectedProcess& TextAreaSelectedProcess::operator=(const TextAreaSelectedProcess& source) {
	return *this;
}
void TextAreaSelectedProcess::AllRowAreaSelected(TextEdit *textEdit, CDC *pDC, TextComposite *textComposite , Long index) {
	CFont font;
	textEdit->caret->FontSetting(&font);
	pDC->SelectObject(font);
	CString cString = textComposite->MakeCString();
	CSize size = pDC->GetTextExtent(cString);
	CRect rect(0, index * 17, size.cx, size.cx + (index * 17) + size.cy);
	pDC->DrawText(cString, &rect, DT_EXPANDTABS);
}
void TextAreaSelectedProcess::SingleRowAreaSelected(TextEdit *textEdit, CDC *pDC, TextComposite *textComposite, Long index, Long length , Long rowIndex) {
	CFont font;
	textEdit->caret->FontSetting(&font);
	pDC->SelectObject(font);
	CString cString = textComposite->MakeCString(index,length);
	CSize size = pDC->GetTextExtent(cString);
	CString indexCString = textComposite->MakeCString(index);
	CSize indexSize = pDC->GetTextExtent(indexCString);
	CRect rect;
	if (textEdit->textAreaSelected->GetStartCharacterIndex() < textEdit->caret->GetCharacterIndex()) {
		rect.left = indexSize.cx;
		rect.top = (rowIndex - 1) * 17;
		rect.right = textEdit->caret->GetCurrentX();
		rect.bottom = size.cx + (rowIndex - 1) * 17 + size.cy;
	}
	else {
		rect.left = indexSize.cx;
		rect.top = (rowIndex - 1) * 17;
		rect.right = textEdit->textAreaSelected->GetStartX();
		rect.bottom = size.cx + (rowIndex - 1) * 17 + size.cy;
	}
	pDC->DrawText(cString, &rect, DT_EXPANDTABS);
}
void TextAreaSelectedProcess::FirstRowAreaSelected(TextEdit *textEdit, CDC *pDC, TextComposite *textComposite, Long index, Long length, Long rowIndex) {
	CFont font;
	textEdit->caret->FontSetting(&font);
	pDC->SelectObject(font);

	CString cString = textComposite->MakeCString(index, length);
	CSize size = pDC->GetTextExtent(cString);
	CString indexCString = textComposite->MakeCString(index);
	CSize indexSize = pDC->GetTextExtent(indexCString);
	CRect rect;
	rect.left = indexSize.cx;
	rect.top = (rowIndex - 1) * 17;
	rect.right = indexSize.cx + size.cx;
	rect.bottom = size.cx + (rowIndex - 1) * 17 + size.cy;

	pDC->DrawText(cString, &rect, DT_EXPANDTABS);
}
void TextAreaSelectedProcess::LastRowAreaSelected(TextEdit *textEdit, CDC *pDC, TextComposite *textComposite, Long index, Long length, Long rowIndex) {
	CFont font;
	textEdit->caret->FontSetting(&font);
	pDC->SelectObject(font);

	CString cString = textComposite->MakeCString(index, length);
	CSize size = pDC->GetTextExtent(cString);
	CString indexCString = textComposite->MakeCString(index);
	CSize indexSize = pDC->GetTextExtent(indexCString);
	CRect rect;

		rect.left = 0;
		rect.top = (rowIndex - 1) * 17;
		rect.right = size.cx;
		rect.bottom = size.cx + (rowIndex - 1) * 17 + size.cy;
	
	pDC->DrawText(cString, &rect, DT_EXPANDTABS);
}