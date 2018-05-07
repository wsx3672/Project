//BusinessCardBinderForm.h

#ifndef _BUSINESSCARDBINDERFORM_H
#define _BUSINESSCARDBINDERFORM_H
#include <afxwin.h>
#include "resource.h"

class BusinessCard;
class BusinessCardBinder; //���漱��
class Indexes;
class BusinessCardBinderForm : public CDialog { //��Ӱ��� ǥ��
public:
	enum { IDD = IDD_BUSINESSCARDBINDERFORM }; // ������ ����
public:
	BusinessCardBinderForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog(); // Ŭ�������̾�׷����� ���ü��� + �Լ� ���� public //virtual
	void Load();
	void Save();
	void Insert(BusinessCard* index);
	void Delete(BusinessCard* index);
	CString GetCompanyCode();
	CString GetPersonalCode();
public:
	BusinessCardBinder *businessCardBinder;
	Indexes *indexes;
protected: // Ŭ�������̾�׷����� #�� ���ü��� �Լ��� ���� protected #
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
	DECLARE_MESSAGE_MAP() //��ũ�� ����
};

#endif // _BUSINESSCARDBINDERFORM_H
