//HouseholdAccountsForm.h
/*
���ϸ� : HouseholdAccountsForm.h
��� : ȭ�� ����� ���� Ŭ����
�ۼ��� :�ڻ��
�ۼ����� : 2017�� 12�� 2�� 
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
