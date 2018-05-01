//UpdatingForm.cpp
#include "UpdatingForm.h"
#include "FindingForm.h"
#include "AddressBook.h"
#include <afxcmn.h>

BEGIN_MESSAGE_MAP(UpdatingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClcked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

UpdatingForm::UpdatingForm(CWnd *parent) :CDialog(UpdatingForm::IDD, parent) {
	this->addressBook = NULL;
}
BOOL UpdatingForm::OnInitDalog() {
	CDialog::OnInitDialog(); //코드 재사용
	// 1.1 주소록을 준비한다.
	this->addressBook = new AddressBook;
	// 1.2 리스트뷰에 헤더를 만든다.
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, (LPCTSTR)"번호", LVCFMT_LEFT, 50, -1);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, (LPCTSTR)"성명", LVCFMT_LEFT, 100,-1);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, (LPCTSTR)"주소", LVCFMT_LEFT, 100, -1);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, (LPCTSTR)"전화번호", LVCFMT_LEFT, 100, -1);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, (LPCTSTR)"이메일", LVCFMT_LEFT, 200, -1);
	return FALSE;
}

void UpdatingForm::OnRecordButtonClicked() {
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Long index;

	GetDlgItem(IDC_EDIT_NAME)->GetWindowTextW(name);
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowTextW(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowTextW(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowTextW(emailAddress);

	index = this->addressBook->Record((LPSTR)(LPCTSTR)name, (LPSTR)(LPCTSTR)address, (LPSTR)(LPCTSTR)telephoneNumber, (LPSTR)(LPCTSTR)emailAddress);

	Personal personal = this->addressBook->GetAt(index);

	name = CString(personal.GetName().c_str());
	address = CString(personal.GetAddress().c_str());
	telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
	emailAddress = CString(personal.GetEmailAddress().c_str());

	CString number;
	number.Format(_T("%d"), index + 1);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(index, number);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 1, name);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);
}

void UpdatingForm::OnFindButtonClicked() {
	FindingForm findingForm;
	findingForm.DoModal();
}

void UpdatingForm::OnCorrectButtonClicked() {
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Long index;

	//4.1 개인을 읽는다.
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowTextW(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowTextW(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowTextW(emailAddress);

	//4.2 리스트뷰에서 선택된 항목을 읽는다.
	index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();

	// 4.3 성명장에서 해당성명를 고친다.
	index = this->addressBook->Correct(index, (LPSTR)(LPCTSTR)address, (LPSTR)(LPCTSTR)telephoneNumber, (LPSTR)(LPCTSTR)emailAddress);

	// 4.4 리스트뷰의 해당항목을 수정한다.
	Personal personal = this->addressBook->GetAt(index);

	address = CString(personal.GetAddress().c_str());
	telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
	emailAddress = CString(personal.GetEmailAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, address);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, telephoneNumber);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, emailAddress);
}

void UpdatingForm::OnEraseButtonClicked() {
	CString number;
	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();

	this->addressBook->Erase(index);
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteItem(index);
	Long length = this->addressBook->GetLength();

	while (index < length) {
		number.Format(_T("%d"), index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 0, number);
		index++;
	}
}

void UpdatingForm::OnArrangeButtonClicked() {
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	CString number;
	Long index = 0;
	this->addressBook->Arrange();
	((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();
	Long length = this->addressBook->GetLength();

	while (index < length) {
		Personal personal = this->addressBook->GetAt(index);
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
		index++;
	}
}

void UpdatingForm::OnListViewItemDoubleClcked(NMHDR *pNotifyStruct, LRESULT *result) {
	
	Long index = (Long)(((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark());

	CString name = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	CString address = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	CString telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	CString emailAddress = ((CListCtrl*)GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);

	GetDlgItem(IDC_EDIT_NAME)->SetWindowTextW(name);
	GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowTextW(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowTextW(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowTextW(emailAddress);
}

void UpdatingForm::OnClose() {
	if (this->addressBook != 0) {
		delete this->addressBook;
	}
	EndDialog(0);
}