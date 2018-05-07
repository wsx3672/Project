//TakeOutForm.cpp

#include "TakeOutForm.h"
#include "BusinessCardBinderForm.h"
#include "BusinessCardBinder.h"
#include "Indexes.h"
#include <afxcmn.h>

BEGIN_MESSAGE_MAP(TakeOutForm, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TakeOutForm::TakeOutForm(CWnd *parent) :CDialog(TakeOutForm::IDD, parent) {
}

BOOL TakeOutForm::OnInitDialog() {
	CDialog::OnInitDialog();
	//명함철 윈도우 찾기
	BusinessCardBinderForm *businessCardBinderForm = (BusinessCardBinderForm*)CWnd::FindWindow("#32770", "명함철");

	BusinessCard* businessCardIndex = businessCardBinderForm->businessCardBinder->GetCurrent();

	BusinessCard businessCard = businessCardBinderForm->businessCardBinder->TakeOut(businessCardIndex);
	//businessCardBinderForm->Delete(&businessCard);

	CString name = CString(businessCard.GetName().c_str());
	CString position = CString(businessCard.GetPosition().c_str());
	CString cellphoneNumber = CString(businessCard.GetCellphoneNumber().c_str());
	CString emailAddress = CString(businessCard.GetEmailAddress().c_str());
	CString companyName = CString(businessCard.GetCompanyName().c_str());
	CString address = CString(businessCard.GetAddress().c_str());
	CString telephoneNumber = CString(businessCard.GetTelephoneNumber().c_str());
	CString faxNumber = CString(businessCard.GetFaxNumber().c_str());
	CString url = CString(businessCard.GetUrl().c_str());

	GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
	GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
	GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
	GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
	GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
	GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);

	Index *index_ = businessCardBinderForm->indexes->TakeOut(businessCardIndex, (LPCTSTR)companyName);

	HTREEITEM hCurrent = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetNextItem(TVI_ROOT, TVGN_CARET);
	HTREEITEM hParent;
	
	if (index_ == NULL) {
		hParent = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetNextItem(hCurrent, TVGN_PARENT);
		((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->DeleteItem(hParent);
	}
	else {
		((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->DeleteItem(hCurrent);
	}
	businessCardIndex = businessCardBinderForm->businessCardBinder->GetCurrent();

	if (businessCardIndex != NULL) {
		name = CString(businessCardIndex->GetName().c_str());
		position = CString(businessCardIndex->GetPosition().c_str());
		cellphoneNumber = CString(businessCardIndex->GetCellphoneNumber().c_str());
		emailAddress = CString(businessCardIndex->GetEmailAddress().c_str());
		companyName = CString(businessCardIndex->GetCompanyName().c_str());
		address = CString(businessCardIndex->GetAddress().c_str());
		telephoneNumber = CString(businessCardIndex->GetTelephoneNumber().c_str());
		faxNumber = CString(businessCardIndex->GetFaxNumber().c_str());
		url = CString(businessCardIndex->GetUrl().c_str());

		businessCardBinderForm->GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);

		index_ = businessCardBinderForm->indexes->Find((LPCTSTR)companyName);
		Long position_ = index_->Find(businessCardIndex);

		HTREEITEM hRoot = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetNextItem(0, TVGN_ROOT);
		HTREEITEM hParent = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetNextItem(hRoot, TVGN_CHILD);
		CString indexName = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetItemText(hParent);

		while (indexName.Compare(companyName) != 0) {
			hParent = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetNextItem(hParent, TVGN_NEXT);
			indexName = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetItemText(hParent);
		}
		HTREEITEM hChild = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetNextItem(hParent, TVGN_CHILD);
		Long i = 0;
		while (i < position_) {
			hChild = ((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->GetNextItem(hChild, TVGN_NEXT);
			i++;
		}
		((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->SelectItem(hChild);
		((CTreeCtrl*)(businessCardBinderForm->GetDlgItem(IDC_TREE_COMPANIES)))->SelectDropTarget(hChild);
	}
	else {
		businessCardBinderForm->GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA("");
		businessCardBinderForm->GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA("");
		businessCardBinderForm->GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA("");
		businessCardBinderForm->GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA("");
		businessCardBinderForm->GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA("");
		businessCardBinderForm->GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA("");
		businessCardBinderForm->GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA("");
		businessCardBinderForm->GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA("");
		businessCardBinderForm->GetDlgItem(IDC_STATIC_URL)->SetWindowTextA("");
	}
	return FALSE;
}

void TakeOutForm::OnClose() {
	CString name;
	CString position;
	CString cellphoneNumber;
	CString emailAddress;
	CString companyName;
	CString address;
	CString telephoneNumber;
	CString faxNumber;
	CString url;

	int result = MessageBox("다시 끼우시겠습니까?", "확인", MB_ICONWARNING | MB_YESNOCANCEL);
	if (result == IDYES) {
		GetDlgItem(IDC_STATIC_NAME)->GetWindowTextA(name);
		GetDlgItem(IDC_STATIC_POSITION)->GetWindowTextA(position);
		GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->GetWindowTextA(cellphoneNumber);
		GetDlgItem(IDC_STATIC_EMAILADDRESS)->GetWindowTextA(emailAddress);
		GetDlgItem(IDC_STATIC_COMPANYNAME)->GetWindowTextA(companyName);
		GetDlgItem(IDC_STATIC_ADDRESS)->GetWindowTextA(address);
		GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->GetWindowTextA(telephoneNumber);
		GetDlgItem(IDC_STATIC_FAXNUMBER)->GetWindowTextA(faxNumber);
		GetDlgItem(IDC_STATIC_URL)->GetWindowTextA(url);

		BusinessCardBinderForm *businessCardBinderForm = (BusinessCardBinderForm*)CWnd::FindWindowA("#32770", "명함철");
		BusinessCard businessCard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellphoneNumber, (LPCTSTR)emailAddress,
			(LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);
		businessCardBinderForm->businessCardBinder->TakeIn(businessCard);
		BusinessCard *current = businessCardBinderForm->businessCardBinder->GetCurrent();
		//businessCardBinderForm->Insert(index);

		name = CString(current->GetName().c_str());
		position = CString(current->GetPosition().c_str());
		cellphoneNumber = CString(current->GetCellphoneNumber().c_str());
		emailAddress = CString(current->GetEmailAddress().c_str());
		companyName = CString(current->GetCompanyName().c_str());
		address = CString(current->GetAddress().c_str());
		telephoneNumber = CString(current->GetTelephoneNumber().c_str());
		faxNumber = CString(current->GetFaxNumber().c_str());
		url = CString(current->GetUrl().c_str());

		businessCardBinderForm->GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
		businessCardBinderForm->GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);

		Index *index = businessCardBinderForm->indexes->TakeIn(current);
		companyName = CString(index->GetName().c_str());

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
	else if (result == IDNO) {
		EndDialog(0);
	}
}