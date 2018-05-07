//TakeInForm.cpp

#include "TakeInForm.h"
#include "BusinessCardBinderForm.h"
#include "BusinessCardBinder.h"
#include "Indexes.h"
#include <afxcmn.h>

BEGIN_MESSAGE_MAP(TakeInForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TAKEIN, OnTakeInButtonClicked)
	ON_EN_KILLFOCUS(IDC_EDIT_COMPANYNAME, CompanyNameEditKillForcus)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TakeInForm::TakeInForm(CWnd *parent) :CDialog(TakeInForm::IDD, parent) {
}

BOOL TakeInForm::OnInitDialog() {
	CDialog::OnInitDialog();
	/*CString position[] = { "회장","사장","과장","부장","사원","대리","인턴" };
	CString emailDomain[] = { "google.com","naver.com","nate.com","hanmail.net" };
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString((LPCTSTR)position);
	((CComboBox*)GetDlgItem(IDC_COMBO_EMAILDOMAIN))->AddString((LPCTSTR)emailDomain);*/

	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString("회장");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString("사장");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString("부장");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString("과장");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString("대리");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString("주임");
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION))->AddString("사원");

	((CComboBox*)GetDlgItem(IDC_COMBO_EMAILDOMAIN))->AddString("google.com");
	((CComboBox*)GetDlgItem(IDC_COMBO_EMAILDOMAIN))->AddString("naver.com");
	((CComboBox*)GetDlgItem(IDC_COMBO_EMAILDOMAIN))->AddString("nate.com");
	((CComboBox*)GetDlgItem(IDC_COMBO_EMAILDOMAIN))->AddString("hanmail.com");
	
	return FALSE;
}

void TakeInForm::OnTakeInButtonClicked() {
	CString name;
	CString position;
	CString cellphoneNumber;
	CString emailAddress;
	CString emailID;
	CString emailDomain;
	CString companyName;
	CString address;
	CString telephoneNumber;
	CString faxNumber;
	CString url;

	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	GetDlgItem(IDC_COMBO_POSITION)->GetWindowText(position);
	GetDlgItem(IDC_EDIT_CELLPHONENUMBER)->GetWindowText(cellphoneNumber);

	GetDlgItem(IDC_EDIT_EMAILID)->GetWindowText(emailID);
	GetDlgItem(IDC_COMBO_EMAILDOMAIN)->GetWindowText(emailDomain);
	emailAddress.Format("%s@%s", (LPCSTR)emailID, (LPCSTR)emailDomain);

	GetDlgItem(IDC_EDIT_COMPANYNAME)->GetWindowText(companyName);
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	GetDlgItem(IDC_EDIT_FAXNUMBER)->GetWindowText(faxNumber);
	GetDlgItem(IDC_EDIT_URL)->GetWindowText(url);


	BusinessCard businessCard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellphoneNumber, (LPCTSTR)emailAddress,
		(LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);

	BusinessCardBinderForm *businessCardBinderForm = (BusinessCardBinderForm*)CWnd::FindWindow("#32770", "명함철");
	BusinessCard *businessCardIndex = businessCardBinderForm->businessCardBinder->TakeIn(businessCard);
	Index *index = businessCardBinderForm->indexes->TakeIn(businessCardIndex);
	//businessCardBinderForm->Insert(index);

	name = CString(businessCardIndex->GetName().c_str());
	position = CString(businessCardIndex->GetPosition().c_str());
	cellphoneNumber = CString(businessCardIndex->GetCellphoneNumber().c_str());
	emailAddress = CString(businessCardIndex->GetEmailAddress().c_str());
	companyName = CString(businessCardIndex->GetCompanyName().c_str());
	address = CString(businessCardIndex->GetAddress().c_str());
	telephoneNumber = CString(businessCardIndex->GetTelephoneNumber().c_str());
	faxNumber = CString(businessCardIndex->GetFaxNumber().c_str());
	url = CString(businessCardIndex->GetUrl().c_str());

	businessCardBinderForm->GetDlgItem(IDC_STATIC_NAME)->SetWindowText(name);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_POSITION)->SetWindowText(position);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowText(cellphoneNumber);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowText(emailAddress);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowText(companyName);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowText(address);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowText(faxNumber);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_URL)->SetWindowText(url);

	HTREEITEM hRoot = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM hParent = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetNextItem(hRoot, TVGN_CHILD);
	CString indexName = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetItemText(hParent);

	while (indexName.Compare(companyName) != 0 && hParent != NULL) {
		hParent = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetNextItem(hParent, TVGN_NEXT);
		indexName = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetItemText(hParent);
	}
	if (hParent == NULL) {
		hParent = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->InsertItem(companyName, hRoot);
	}
	HTREEITEM hChild = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->InsertItem(name, hParent);
	((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->SelectItem(hChild);
	((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->SelectDropTarget(hChild);
	EndDialog(0);
}

void TakeInForm::CompanyNameEditKillForcus() {
	CString companyName;
	GetDlgItem(IDC_EDIT_COMPANYNAME)->GetWindowText(companyName);
	
	BusinessCardBinderForm *businessCardBinderForm = (BusinessCardBinderForm*)CWnd::FindWindow("#32770", "명함철");

	BusinessCard *index = businessCardBinderForm->businessCardBinder->FindByCompanyName((LPCTSTR)companyName);
	if (index != NULL) {
		CString address = CString(index->GetAddress().c_str());
		CString telephoneNumber = CString(index->GetTelephoneNumber().c_str());
		CString faxNumber = CString(index->GetFaxNumber().c_str());
		CString url = CString(index->GetUrl().c_str());

		GetDlgItem(IDC_EDIT_COMPANYNAME)->SetWindowText(companyName);
		GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
		GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
		GetDlgItem(IDC_EDIT_FAXNUMBER)->SetWindowText(faxNumber);
		GetDlgItem(IDC_EDIT_URL)->SetWindowText(url);
	}
}

void TakeInForm::OnClose() {
	EndDialog(0);
}