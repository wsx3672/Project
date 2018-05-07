//BusinessCardBinderForm.h

#ifndef _BUSINESSCARDBINDERFORM_H
#define _BUSINESSCARDBINDERFORM_H
#include <afxwin.h>
#include "resource.h"

class BusinessCard;
class BusinessCardBinder; //전방선언
class Indexes;
class BusinessCardBinderForm : public CDialog { //상속관계 표현
public:
	enum { IDD = IDD_BUSINESSCARDBINDERFORM }; // 열거형 선언
public:
	BusinessCardBinderForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog(); // 클래스다이어그램에서 가시성이 + 함수 선언 public //virtual
	void Load();
	void Save();
	void Insert(BusinessCard* index);
	void Delete(BusinessCard* index);
	CString GetCompanyCode();
	CString GetPersonalCode();
public:
	BusinessCardBinder *businessCardBinder;
	Indexes *indexes;
protected: // 클래스다이어그램에서 #이 가시성인 함수들 선언 protected #
	afx_msg void OnTakeInButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnTakeOutButtonClicked();
	afx_msg void OnArrangeButtonClicked();
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnTreeViewItemDoubleclicked(NMHDR *pNotifySource, LRESULT *result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP() //매크로 선언
};

#endif // _BUSINESSCARDBINDERFORM_H
