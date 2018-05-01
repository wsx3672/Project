#include "TextEdit.h"
#include "HouseholdAccountsForm.h"
#include "Text.h"
#include "Row.h"
#include "SingleByteCharacter.h"
#include "TextComposite.h"
#include "KeyBoard.h"
#include "WritingKorean.h"
#include "DoubleByteCharacter.h"
#include "KeyAction.h"
#include "TextAreaSelected.h"
#include "Caret.h"
#include "SingleByteCharacterAddProcess.h"
#include "SelectedRemoveProcess.h"
#include "Finder.h"
#include <cstring>
using namespace std;
BEGIN_MESSAGE_MAP(TextEdit, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_MESSAGE(WM_IME_COMPOSITION, OnComposition)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_WM_CHAR()
END_MESSAGE_MAP()

TextEdit::TextEdit(HouseholdAccountsForm *householdAccountsForm) {
	this->householdAccountsForm = householdAccountsForm;
	this->keyBoard = NULL;
	this->text = NULL;
	this->caret = NULL;
	this->textAreaSelected = NULL;
	this->finder = NULL;
	this->keyDownCheck = -1;
	this->writingKoreanState = false;
	this->selectedArea = false;
	this->startX = -1;
	this->startY = -1;
	this->currentX = -1;
	this->currentY = -1;
}
void TextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->keyDownCheck = -1;
	KeyAction *keyAction = this->keyBoard->Action(this, nChar, nRepCnt, nFlags);
	if (keyAction != NULL) {
		this->keyDownCheck = 1;
		keyAction->Action(this);
	}
	this->Invalidate();
}
void TextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {

	char addChar = nChar;
	if (this->keyDownCheck < 0 && this->writingKoreanState == false) {
		Long length = this->textAreaSelected->GetLength();
		Long currentRowIndex = this->caret->GetCurrentRowIndex();
		if (length > 0) {
			SelectedRemoveProcess selectedRemoveProcess;
			selectedRemoveProcess.SelectedRemove(this);
			length = this->text->GetLength();
			if (length  < currentRowIndex) {
				Row *row = new Row;
				this->text->Add(row);
			}
			selectedRemoveProcess.SelectedRemoveAfterSetCaret(this);
			this->selectedArea = false;
		}
		SingleByteCharacterAddProcess singleByteCharacterAddProcess;
		Long position = singleByteCharacterAddProcess.SingleByteCharacterAdd(addChar, this);
		if (position != -1) {
			this->caret->CreateCaret();
			this->caret->RightMovingCaret();
		}
	}
	this->Invalidate();
}
void TextEdit::OnLButtonDown(UINT nFlags, CPoint point) {
	this->SetStartXAndY(nFlags, point);
	Long length = this->textAreaSelected->GetLength();
	if (length != 0) {
		this->textAreaSelected->DeleteAllItems();
		length = this->textAreaSelected->GetLength();
		this->selectedArea = false;
	}
	this->finder->MouseLButtonClick(this->startX, this->startY);

	this->caret->CreateCaret();
	this->Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}
void TextEdit::OnLButtonUp(UINT nFlags, CPoint point) {
	this->SetCurrentXAndY(nFlags, point);

	CWnd::OnLButtonUp(nFlags, point);
}
void TextEdit::OnMouseMove(UINT nFlags, CPoint point) {
	//마우스 왼쪽버튼을 누르고 드래그했을때 

	if (nFlags == MK_LBUTTON ) {

		this->SetCurrentXAndY(nFlags, point);
		if (this->startX != -1 && this->currentX != -1) {
			this->finder->MouseLButtonDrag(this->currentX, this->currentY);
		}
		this->Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}
Long TextEdit::OnComposition(WPARAM wParam, LPARAM lParam) {
	HIMC hIMC = ImmGetContext(GetSafeHwnd());

	Long length = this->textAreaSelected->GetLength();
	Long currentRowIndex = this->caret->GetCurrentRowIndex();
	if (length > 0) {
		SelectedRemoveProcess selectedRemoveProcess;
		selectedRemoveProcess.SelectedRemove(this);
		length = this->text->GetLength();
		if (length  < currentRowIndex) {
			Row *row = new Row;
			this->text->Add(row);
		}
		selectedRemoveProcess.SelectedRemoveAfterSetCaret(this);
		this->selectedArea = false;
	}
	WritingKorean *writingKorean = new WritingKorean();
	writingKorean->WritingHanguel(wParam, lParam, hIMC, this);

	if (writingKorean != NULL) {
		delete writingKorean;
	}
	ImmReleaseContext(GetSafeHwnd(), hIMC);
	this->Invalidate();
	return 0;
}
void TextEdit::OnPaint() {
	CPaintDC dc(this);
	
	CRect rect;
	this->GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	CFont font;
	font.CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "고딕체");
	SetFont(&font, TRUE);
	dc.SelectObject(font);
	Long i = 0;
	Long length = this->text->GetLength();
	while (i < length) {
		TextComponent *textComponent = this->text->GetAt(i);
		TextComposite *textComposite = textComponent->GetComposite();
		CString cString = textComposite->MakeCString();
		dc.TextOut(0  ,i *17 ,cString);
		i++;
	}
	if (this->selectedArea == true) {
		this->textAreaSelected->SelectedTextArea(this,&dc);
	}
	CWnd::OnPaint();
}
int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);
	CWnd::SetFocus();

	this->text = new Text();
	Row *row = new Row();
	this->text->Add(row);
	this->keyBoard = new KeyBoard();
	this->caret = new Caret(this);
	this->textAreaSelected = new TextAreaSelected();
	this->caret->CreateCaret();
	this->finder = new Finder(this);
	return 0;
}
void TextEdit::SetStartXAndY(UINT nFlags, CPoint point){
	this->startX = point.x;
	this->startY = point.y;
}
void TextEdit::SetCurrentXAndY(UINT nFlags, CPoint point) {
	this->currentX = point.x;
	this->currentY = point.y;
}
void TextEdit::OnClose() {
	if (this->text != NULL) {
		delete this->text;
	}
	if (this->keyBoard != NULL) {
		delete this->keyBoard;
	}
	if (this->caret != NULL) {
		delete this->caret;
	}
	if (this->textAreaSelected != NULL) {
		delete this->textAreaSelected;
	}
	if (this->finder != NULL) {
		delete this->finder;
	}
	CWnd::OnClose();
}
// Text선택된상태에서 Enter,방향키,글입력시 이벤트 처리해야함.