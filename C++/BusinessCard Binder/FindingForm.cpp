//FindindForm.cpp

#include "FindingForm.h"
#include "BusinessCardBinder.h"
#include "BusinessCardBinderForm.h"
#include "Indexes.h"
#include <afxcmn.h>


BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnSelectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS2, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT2, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST2, OnLastButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd *parent) :CDialog(FindingForm::IDD, parent) {
	this->indexes = NULL;
	this->current = 0;
	this->count = 0;
}

void FindingForm::OnFindButtonClicked() {
	CString name;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowTextA(name);


	BusinessCardBinderForm *businessCardBinderForm = (BusinessCardBinderForm*)CWnd::FindWindow("#32770", "¸íÇÔÃ¶");

	if (this->indexes != NULL) {
		delete[] this->indexes;
		this->indexes = NULL;
	}
	businessCardBinderForm->businessCardBinder->Find((LPCTSTR)name, &(this->indexes), &(this->count));
	if (this->count > 0) {
		this->current = 0;
		name = CString(this->indexes[this->current]->GetName().c_str());
		CString position = CString(this->indexes[this->current]->GetPosition().c_str());
		CString cellphoneNumber = CString(this->indexes[this->current]->GetCellphoneNumber().c_str());
		CString emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
		CString companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
		CString address = CString(this->indexes[this->current]->GetAddress().c_str());
		CString telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
		CString faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
		CString url = CString(this->indexes[this->current]->GetUrl().c_str());
		GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
		GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
		GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
		GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
		GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
		GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
		GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
		GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
		GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);
	}
	else {
		GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_URL)->SetWindowTextA("");
	}
}

void FindingForm::OnFirstButtonClicked() {
	this->current = 0;
	CString name = CString(this->indexes[this->current]->GetName().c_str());
	CString position = CString(this->indexes[this->current]->GetPosition().c_str());
	CString cellphoneNumber = CString(this->indexes[this->current]->GetCellphoneNumber().c_str());
	CString emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	CString companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	CString address = CString(this->indexes[this->current]->GetAddress().c_str());
	CString telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	CString faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	CString url = CString(this->indexes[this->current]->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
	GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
	GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
	GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
	GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
	GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);
}

void FindingForm::OnPreviousButtonClicked() {
	this->current--;
	if (this->current < 0) {
		this->current = 0;
	}
	CString name = CString(this->indexes[this->current]->GetName().c_str());
	CString position = CString(this->indexes[this->current]->GetPosition().c_str());
	CString cellphoneNumber = CString(this->indexes[this->current]->GetCellphoneNumber().c_str());
	CString emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	CString companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	CString address = CString(this->indexes[this->current]->GetAddress().c_str());
	CString telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	CString faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	CString url = CString(this->indexes[this->current]->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
	GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
	GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
	GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
	GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
	GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);
}

void FindingForm::OnNextButtonClicked() {
	this->current++;
	if (this->current <= this->count) {
		this->current = this->count - 1;
	}
	CString name = CString(this->indexes[this->current]->GetName().c_str());
	CString position = CString(this->indexes[this->current]->GetPosition().c_str());
	CString cellphoneNumber = CString(this->indexes[this->current]->GetCellphoneNumber().c_str());
	CString emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	CString companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	CString address = CString(this->indexes[this->current]->GetAddress().c_str());
	CString telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	CString faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	CString url = CString(this->indexes[this->current]->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
	GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
	GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
	GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
	GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
	GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);
}

void FindingForm::OnLastButtonClicked() {
	this->current = this->count - 1;
	CString name = CString(this->indexes[this->current]->GetName().c_str());
	CString position = CString(this->indexes[this->current]->GetPosition().c_str());
	CString cellphoneNumber = CString(this->indexes[this->current]->GetCellphoneNumber().c_str());
	CString emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	CString companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	CString address = CString(this->indexes[this->current]->GetAddress().c_str());
	CString telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	CString faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	CString url = CString(this->indexes[this->current]->GetUrl().c_str());
	GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
	GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
	GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
	GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
	GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
	GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);
}

void FindingForm::OnSelectButtonClicked() {
	CString name;
	CString position;
	CString cellphoneNumber;
	CString emailAddress;
	CString companyName;
	CString address;
	CString telephoneNumber;
	CString faxNumber;
	CString url;

	GetDlgItem(IDC_STATIC_NAME)->GetWindowTextA(name);
	GetDlgItem(IDC_STATIC_POSITION)->GetWindowTextA(position);
	GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->GetWindowTextA(cellphoneNumber);
	GetDlgItem(IDC_STATIC_EMAILADDRESS)->GetWindowTextA(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANYNAME)->GetWindowTextA(companyName);
	GetDlgItem(IDC_STATIC_ADDRESS)->GetWindowTextA(address);
	GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->GetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_STATIC_FAXNUMBER)->GetWindowTextA(faxNumber);
	GetDlgItem(IDC_STATIC_URL)->GetWindowTextA(url);

	BusinessCardBinderForm *businessCardBinderForm = (BusinessCardBinderForm*)CWnd::FindWindow("#32770", "¸íÇÔÃ¶");


	BusinessCard *businessCardIndex = businessCardBinderForm->businessCardBinder->Move(this->indexes[this->current]);

	businessCardBinderForm->GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
	businessCardBinderForm->GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);

	Index *index = businessCardBinderForm->indexes->Find((LPCTSTR)companyName);
	Long position_ = index->Find(businessCardIndex);
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

	if (this->indexes != NULL) {
		delete[] this->indexes;
		this->indexes = NULL;
	}
	EndDialog(0);
}

void FindingForm::OnClose() {
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	EndDialog(0);
}