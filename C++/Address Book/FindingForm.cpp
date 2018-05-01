//FindingForm.cpp
#include "FindingForm.h"
#include "UpdatingForm.h"
#include "AddressBook.h"
#include <afxcmn.h>

BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnFindButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd *parent) :CDialog(FindingForm::IDD, parent) {
	this->indexes = NULL;
	this->count = 0;
}

BOOL FindingForm::OnInitDialog() {
	CDialog::OnInitDialog();
	// 1.1 리스트뷰에 헤더를 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, (LPCTSTR)"번호", LVCFMT_LEFT, 50, -1);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, (LPCTSTR)"성명", LVCFMT_LEFT, 100, -1);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, (LPCTSTR)"주소", LVCFMT_LEFT, 100, -1);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, (LPCTSTR)"전화번호", LVCFMT_LEFT, 100, -1);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, (LPCTSTR)"이메일", LVCFMT_LEFT, 200, -1);
	return FALSE;
}

void FindingForm::OnFindButtonClicked() {
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	CString number;
	Long index;
	UpdatingForm* updatingForm;
	Long i = 0;
	Personal personal;
	
	// 2.1 조건을 읽는다.
	GetDlgItem(IDC_EDIT_NAME)->GetWindowTextW(name);

	// 2.2 주소록윈도우를 찾는다.
	updatingForm = (UpdatingForm*)CWnd::FindWindowW((LPCTSTR)"#32770", (LPCTSTR)"주소록");

	// 2.3 주소록에서 찾는다.
	updatingForm->addressBook->Find((LPCTSTR)name, &(this->indexes), &(this->count));

	// 2.4 리스트뷰컨트롤의 모든항목을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();

	// 2.5 리스트뷰컨트롤에 찾은 개인을 출력한다.
	while (i < this->count) {
		updatingForm->addressBook->GetAt(this->indexes[i]);

		name = CString(personal.GetName().c_str());
		address = CString(personal.GetAddress().c_str());
		telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
		emailAddress = CString(personal.GetEmailAddress().c_str());

		number.Format(_T("%d"), index + 1);

		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(index, number);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 1, name);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);
		i++;
	}
}

void FindingForm::OnListViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result) {
	Long index;
	UpdatingForm* updatingForm;
	updatingForm = (UpdatingForm*)CWnd::FindWindowW((LPCTSTR)"#32770", (LPCTSTR)"주소록");

	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();

	CString name = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	CString address = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	CString telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	CString emailAddress = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);

	updatingForm->GetDlgItem(IDC_EDIT_NAME)->SetWindowTextW(name);
	updatingForm->GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowTextW(address);
	updatingForm->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowTextW(telephoneNumber);
	updatingForm->GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowTextW(emailAddress);

	((CListCtrl*)(updatingForm->GetDlgItem(IDC_LIST_PERSONALS)))->SetSelectionMark(this->indexes[index]);
	
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	EndDialog(0);
}

void FindingForm::OnClose() {
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	EndDialog(0);
}