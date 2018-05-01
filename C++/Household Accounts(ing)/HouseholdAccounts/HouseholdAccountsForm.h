//HouseholdAccountsForm.h
/*
파일명 : HouseholdAccountsForm.h
기능 : 화면 출력을 위한 클래스
작성자 :박상민
작성일자 : 2017년 12월 2일 
*/
#ifndef _HOUSEHOLDACCOUNTSFORM_H
#define _HOUSEHOLDACCOUNTSFORM_H

#include <afxwin.h>
class TextEdit;
class HouseholdAccountsForm : public CFrameWnd {
public:
	HouseholdAccountsForm();
public:
	afx_msg void OnClose();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT, CPoint);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar,UINT nRepCnt,UINT nFlags);
	DECLARE_MESSAGE_MAP()
protected:
	TextEdit *textEdit;
};
#endif // !_HOUSEHOLDACCOUNTSFORM_H
