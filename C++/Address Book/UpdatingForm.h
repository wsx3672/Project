//UpdatingForm.h
#ifndef _UPDATINGFORM_H
#define _UPDATINGFORM_H
#include <afxwin.h>
#include "resource.h"

class AddressBook; //클래스 전방선언

class UpdatingForm : public CDialog { //상속(Inheritance)관계표현
public:
	enum { IDD = IDD_UPDATINGFORM }; //열거형문자 선언
public:
	UpdatingForm(CWnd *parent = NULL); //디폴트 생성자
	virtual BOOL OnInitDalog();
public:
	AddressBook *addressBook;
protected:
	afx_msg void OnRecordButtonClicked();   // [1] 기재하기
	afx_msg void OnFindButtonClicked();      // [2] 찾기
	afx_msg void OnCorrectButtonClicked();   // [3] 고치기
	afx_msg void OnEraseButtonClicked();      // [4] 지우기
	afx_msg void OnArrangeButtonClicked();   // [5] 정리하기
	afx_msg void OnListViewItemDoubleClcked(NMHDR * pNotifyStruct, LRESULT * result);   // [6] 더블클릭
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};
#endif // _UPDATINGFORM_H