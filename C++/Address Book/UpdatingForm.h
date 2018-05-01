//UpdatingForm.h
#ifndef _UPDATINGFORM_H
#define _UPDATINGFORM_H
#include <afxwin.h>
#include "resource.h"

class AddressBook; //Ŭ���� ���漱��

class UpdatingForm : public CDialog { //���(Inheritance)����ǥ��
public:
	enum { IDD = IDD_UPDATINGFORM }; //���������� ����
public:
	UpdatingForm(CWnd *parent = NULL); //����Ʈ ������
	virtual BOOL OnInitDalog();
public:
	AddressBook *addressBook;
protected:
	afx_msg void OnRecordButtonClicked();   // [1] �����ϱ�
	afx_msg void OnFindButtonClicked();      // [2] ã��
	afx_msg void OnCorrectButtonClicked();   // [3] ��ġ��
	afx_msg void OnEraseButtonClicked();      // [4] �����
	afx_msg void OnArrangeButtonClicked();   // [5] �����ϱ�
	afx_msg void OnListViewItemDoubleClcked(NMHDR * pNotifyStruct, LRESULT * result);   // [6] ����Ŭ��
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};
#endif // _UPDATINGFORM_H