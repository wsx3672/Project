//BusinessCardBinderForm.cpp

#include "BusinessCardBinderForm.h"
#include "TakeInForm.h"
#include "FindingForm.h"
#include "TakeOutForm.h"
#include "BusinessCardBinder.h"
#include "Indexes.h"
#include <afxwin.h>
#include <afxcmn.h>
#include <afxdb.h>

BEGIN_MESSAGE_MAP(BusinessCardBinderForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TAKEIN, OnTakeInButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_TAKEOUT, OnTakeOutButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_TAKEOUT, OnArrangeButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_NOTIFY(NM_DBLCLK,IDC_TREE_COMPANIES, OnTreeViewItemDoubleclicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

BusinessCardBinderForm::BusinessCardBinderForm(CWnd *parent) :CDialog(BusinessCardBinderForm::IDD, parent) {
	this->businessCardBinder = NULL; //����Ʈ ������, �Ű������� ���� ������
	this->indexes = NULL;
}
/*
void BusinessCardBinderForm::Load() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql;

	db.OpenEx("DSN=BusinessCardBinder;UID=root;PWD=root");
	sql = "SELECT Company.name, Company.address, Company.telephoneNumber, Company.faxNumber, "
		"Company.url, Personal.name, Personal.position, Personal.cellphoneNumber, Personal.emailAddress "
		"FROM Company INNER JOIN Personal On Company.companyCode = Personal.companyCode;"; // INNER JOIN, ON ���� �� �� ������ // ������?
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	CString name;
	CString position;
	CString cellphoneNumber;
	CString emailAddress;
	CString companyName;
	CString address;
	CString telephoneNumber;
	CString faxNumber;
	CString url;

	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, companyName);
		rs.GetFieldValue((short)1, address);
		rs.GetFieldValue((short)2, telephoneNumber);
		rs.GetFieldValue((short)3, faxNumber);
		rs.GetFieldValue((short)4, url);
		rs.GetFieldValue((short)5, name);
		rs.GetFieldValue((short)6, position);
		rs.GetFieldValue((short)7, cellphoneNumber);
		rs.GetFieldValue((short)8, emailAddress);

		BusinessCard businessCard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellphoneNumber,
			(LPCTSTR)emailAddress, (LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber,
			(LPCTSTR)faxNumber, (LPCTSTR)url);
		this->businessCardBinder->TakeIn(businessCard);

		rs.MoveNext();
	}
	rs.Close();
	db.Close();
}

void BusinessCardBinderForm::Save() {
	CDatabase db;
	CRecordset rs(&db);
	CRecordset temp(&db);
	CString sql;
	CString tempCompanyCode;
	CString tempPersonalCode;
	db.OpenEx("DSN=BusinessCardBinder;UID=root;PWD=root");
	sql = "SELECT Personal.companyCode, Personal.code FROM Personal;";
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	sql = "DELETE FROM Personal;";
	db.ExecuteSQL(sql);
	sql = "DELETE FROM Company;";
	db.ExecuteSQL(sql);

	BusinessCard *previous = NULL;
	BusinessCard *current = this->businessCardBinder->First();
	while (current != previous) {
		rs.GetFieldValue((short)0, tempCompanyCode);
		sql.Format("SELECT Company.companyCode FROM Company WHERE companyCode='%s';", (LPCTSTR)tempCompanyCode);
		temp.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
		if (temp.IsEOF()) {
			sql.Format("INSERT INTO Company(name, address, telephoneNumber,"
				"faxNumber, url, companyCode VALUES ('%s','%s','%s','%s','%s','%s');",
				current->GetCompanyName().c_str(), current->GetAddress().c_str(), current->GetTelephoneNumber().c_str(),
				current->GetFaxNumber().c_str(), current->GetUrl().c_str(), (LPCTSTR)tempCompanyCode);
			db.ExecuteSQL(sql);
		}
		rs.GetFieldValue((short)1, tempPersonalCode);
		sql.Format("INSERT INTO Personal(name, position, telephoneNumber,"
			"emailAddress, code, companyCode) VALUES ('%s','%s','%s','%s','%s','%s');",
			current->GetName().c_str(), current->GetPosition().c_str(), current->GetCellphoneNumber().c_str(),
			current->GetEmailAddress().c_str(), current->GetUrl().c_str(), (LPCTSTR)tempPersonalCode, (LPCTSTR)tempCompanyCode);
		db.ExecuteSQL(sql);
		temp.Close();
		temp.Close();
		rs.MoveNext();
		previous = current;
		current = this->businessCardBinder->Next();
	}
	rs.Close();
	db.Close();
}

void BusinessCardBinderForm::Insert(BusinessCard *index) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql;
	CString companyCode;
	db.OpenEx("DSN=BusinessCardBinder;UID=root;PWD=root");
	sql.Format("SELECT Company.companyCode FROM Company WHERE name = '%s' AND address = '%s' AND "
		"telephoneNumber = '%s' AND faxNumber = '%s' AND url = '%s';", index->GetCompanyName().c_str(),
		index->GetAddress().c_str(), index->GetTelephoneNumber().c_str(), index->GetFaxNumber().c_str(), index->GetUrl().c_str());
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, companyCode);
	}
	else {
		companyCode = GetCompanyCode();
		sql.Format("INSERT INTO Company(name, address, telephoneNumber, faxNumber,"
			"url, companyCode) VALUES ('%s', '%s', '%s', '%s', '%s', '%s');", index->GetCompanyName().c_str(),
			index->GetAddress().c_str(), index->GetTelephoneNumber().c_str(), index->GetFaxNumber().c_str(),
			index->GetUrl().c_str(), (LPCTSTR)companyCode);
		db.ExecuteSQL(sql);
	}
	sql.Format("INSERT INTO Personal(name, position, cellphoneNumber, emailAddress, code, companyCode)"
		"VALUES ('%s', '%s', '%s', '%s', '%s', '%s');", index->GetName().c_str(), index->GetPosition().c_str(),
		index->GetCellphoneNumber().c_str(), index->GetEmailAddress().c_str(), (LPCTSTR)(GetPersonalCode()),
		(LPCTSTR)companyCode);
	db.ExecuteSQL(sql);
	rs.Close();
	db.Close();
}

void BusinessCardBinderForm::Delete(BusinessCard *index) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql;
	CString companyCode;
	CString code;
	db.OpenEx("DSN = BusinessCardCardBinder;UID=root;PWD=root");
	sql.Format("SELECT Personal.code, Personal.companyCode FROM Personal WHERE name = '%s' AND position = '%s' And "
		"cellphoneNumber = '%s';", index->GetName().c_str(), index->GetPosition().c_str(), index->GetCellphoneNumber().c_str(),
		index->GetEmailAddress().c_str());
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	rs.GetFieldValue((short)0, code);
	rs.GetFieldValue((short)1, companyCode);
	rs.Close();
	sql.Format("DELETE FROM Personal WHERE code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);
	sql.Format("SELECT Personal.code From Personal WHERE companyCode='%s';", (LPCTSTR)companyCode);
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	if (rs.IsEOF()) {
		sql.Format("DELETE FROM Company WHERE companyCode='%s';", (LPCTSTR)companyCode);
		db.ExecuteSQL(sql);
	}
	rs.Close();
	db.Close();
}

CString BusinessCardBinderForm::GetCompanyCode() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql;
	db.OpenEx("DSN = BusinessCardCardBinder;UID=root;PWD=root");
	sql = "SELECT Company.companyCode FROM Company ORDER BY companyCode DESC;";
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString bigCode;
	Long codeNumber = 0;
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, bigCode);
		CString tempCode = bigCode.Right(4);
		codeNumber = (Long)atoi((LPCTSTR)tempCode);
	}
	codeNumber++;
	CString ret;
	ret.Format("C%04d", codeNumber);
	rs.Close();
	db.Close();
	return ret;
}

CString BusinessCardBinderForm::GetPersonalCode() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql;
	db.OpenEx("DSN = BusinessCardCardBinder;UID=root;PWD=root");
	sql = "SELECT Personal.code FROM Personal ORDER BY companyCode DESC;";
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString bigCode;
	Long codeNumber = 0;
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, bigCode);
		CString tempCode = bigCode.Right(4);
		codeNumber = (Long)atoi((LPCTSTR)tempCode);
	}
	codeNumber++;
	CString ret;
	ret.Format("P%04d", codeNumber);
	rs.Close();
	db.Close();
	return ret;
}
*/
//1. �����찡 �����Ǿ��� ��
// 1.1. ����ö�� �غ��Ѵ�
BOOL BusinessCardBinderForm::OnInitDialog() {
	CDialog::OnInitDialog();  //�ڵ�����//�������̵�
	this->businessCardBinder = new BusinessCardBinder;
	this->indexes = new Indexes;
	BusinessCard businessCard("ȫ�浿", "WW", "WW", "WW", "�Ｚ", "WW", "WW", "WW", "WW");
	this->businessCardBinder->TakeIn(businessCard);
	//Long length = this->businessCardBinder->GetLength();
	BusinessCard *businessCardIndex = this->businessCardBinder->First();	//����
	if (businessCardIndex != NULL) {
		//BusinessCard *businessCardIndex = this->businessCardBinder->First();	//����
		BusinessCard *previous = NULL;
		while (businessCardIndex != previous) {
			this->indexes->TakeIn(businessCardIndex);
			previous = businessCardIndex;
			businessCardIndex = this->businessCardBinder->Next();
		}
	}
	this->indexes->Arrange();
	HTREEITEM hRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->InsertItem("ȸ���");
	Index(*keys);
	Long count;
	Long i = 0;
	HTREEITEM hParent;
	HTREEITEM hChild;
	CString name;
	CString companyName;
	Long length=0;

	this->indexes->MakeList(&keys, &count);

	while (i < count) {
		companyName = CString(keys[i].GetName().c_str());
		hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->InsertItem(companyName, hRoot);
		 length = keys[i].GetLength();
		Long j = 0;
		while (j < length) {
			businessCardIndex = keys[i].GetAt(j);
			name = CString(businessCardIndex->GetName().c_str());
			((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->InsertItem(name, hParent);
			j++;
		}
		i++;
	}
	if (length > 0) {
		businessCardIndex = this->businessCardBinder->First();
		name = CString(businessCardIndex->GetName().c_str());
		CString position = CString(businessCardIndex->GetPosition().c_str());
		CString cellphoneNumber = CString(businessCardIndex->GetCellphoneNumber().c_str());
		CString emailAddress = CString(businessCardIndex->GetEmailAddress().c_str());
		companyName = CString(businessCardIndex->GetCompanyName().c_str());
		CString address = CString(businessCardIndex->GetAddress().c_str());
		CString telephoneNumber = CString(businessCardIndex->GetTelephoneNumber().c_str());
		CString faxNumber = CString(businessCardIndex->GetFaxNumber().c_str());
		CString url = CString(businessCardIndex->GetUrl().c_str());

		GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
		GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
		GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
		GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
		GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
		GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
		GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
		GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
		GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);
		Index *index = this->indexes->Find((LPCTSTR)companyName);
		Long position_ = index->Find(businessCardIndex);
		hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hRoot, TVGN_CHILD);
		CString indexName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
		while (indexName.Compare(companyName) != 0) {
			hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_NEXT);
			indexName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
		}
		hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_CHILD);
		i = 0;
		while (i < position_) {
			hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hChild, TVGN_NEXT);
			i++;
		}
		((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->SelectItem(hChild);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->SelectDropTarget(hChild);
	}
	return FALSE;
}

//2. �ֱ��ư�� Ŭ������ ��
// 2.1. �ֱ� �����츦 ����Ѵ�.
void BusinessCardBinderForm::OnTakeInButtonClicked() {
	TakeInForm takeInForm;
	takeInForm.DoModal();
}

//3. ã���ư�� ������ ��
// 3.1. ã�� �����츦 ����Ѵ�
void BusinessCardBinderForm::OnFindButtonClicked() {
	FindingForm findingForm;
	findingForm.DoModal();
}

//4. �̱��ư�� ������ ��
// 4.1. �̱� �����츦 ����Ѵ�.
void BusinessCardBinderForm::OnTakeOutButtonClicked() {
	TakeOutForm takeOutForm;
	takeOutForm.DoModal();
}

void BusinessCardBinderForm::OnArrangeButtonClicked() {
	this->indexes->Arrange();
	Index(*keys);
	Long count;
	this->indexes->MakeList(&keys, &count);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->DeleteAllItems();
	HTREEITEM hRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->InsertItem("ȸ���");
	Long i = 0;
	Long j;
	Long length;
	CString companyName;
	CString name;
	HTREEITEM hParent;
	HTREEITEM hChild;
	BusinessCard *businessCardIndex;
	while (i < count) {
		companyName = CString(keys[i].GetName().c_str());
		hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->InsertItem(companyName, hRoot);
		length = keys[i].GetLength();
		j = 0;
		while (j < length) {
			businessCardIndex = keys[i].GetAt(j);
			name = CString(businessCardIndex->GetName().c_str());
			((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->InsertItem(name, hParent);
			j++;
		}
		i++;
	}
	businessCardIndex = this->businessCardBinder->First();
	name = CString(businessCardIndex->GetName().c_str());
	CString position = CString(businessCardIndex->GetPosition().c_str());
	CString cellphoneNumber = CString(businessCardIndex->GetCellphoneNumber().c_str());
	CString emailAddress = CString(businessCardIndex->GetEmailAddress().c_str());
	companyName = CString(businessCardIndex->GetCompanyName().c_str());
	CString address = CString(businessCardIndex->GetAddress().c_str());
	CString telephoneNumber = CString(businessCardIndex->GetTelephoneNumber().c_str());
	CString faxNumber = CString(businessCardIndex->GetFaxNumber().c_str());
	CString url = CString(businessCardIndex->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
	GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
	GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
	GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
	GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
	GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);
	Index *index = this->indexes->Find((LPCTSTR)companyName);
	Long indexPosition = index->Find(businessCardIndex);
	hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hRoot, TVGN_CHILD);
	CString indexName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
	while (indexName.Compare(companyName) != 0) {
		hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_NEXT);
		indexName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
	}
	hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_CHILD);
	i = 0;
	while (i < indexPosition) {
		hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hChild, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->SelectItem(hChild);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->SelectDropTarget(hChild);
}
//5. ó�� ��ư�� ��������
// 5.1. ù��° �������� �̵��Ѵ�.
void BusinessCardBinderForm::OnFirstButtonClicked() {

	BusinessCard *businessCardIndex = this->businessCardBinder->First();

	CString name = CString(businessCardIndex->GetName().c_str());
	CString position = CString(businessCardIndex->GetPosition().c_str());
	CString cellphoneNumber = CString(businessCardIndex->GetCellphoneNumber().c_str());
	CString emailAddress = CString(businessCardIndex->GetEmailAddress().c_str());
	CString companyName = CString(businessCardIndex->GetCompanyName().c_str());
	CString address = CString(businessCardIndex->GetAddress().c_str());
	CString telephoneNumber = CString(businessCardIndex->GetTelephoneNumber().c_str());
	CString faxNumber = CString(businessCardIndex->GetFaxNumber().c_str());
	CString url = CString(businessCardIndex->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
	GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
	GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber); 
	GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
	GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
	GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);

	Index *index = this->indexes->Find((LPCTSTR)companyName);
	Long position_ = index->Find(businessCardIndex);
	HTREEITEM hRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hRoot, TVGN_CHILD);
	CString indexName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
	while (indexName.Compare(companyName) != 0) {
		hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_NEXT);
		indexName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
	}
	HTREEITEM hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_CHILD);
	Long i = 0;
	while (i < position_) {
		hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hChild, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->SelectItem(hChild);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->SelectDropTarget(hChild);
}

//6. ���� ��ư�� ��������
// 6.1.  ���� �������� �̵��Ѵ�.
void BusinessCardBinderForm::OnPreviousButtonClicked() {

	BusinessCard *businessCardIndex = this->businessCardBinder->Previous();

	CString name = CString(businessCardIndex->GetName().c_str());
	CString position = CString(businessCardIndex->GetPosition().c_str());
	CString cellphoneNumber = CString(businessCardIndex->GetCellphoneNumber().c_str());
	CString emailAddress = CString(businessCardIndex->GetEmailAddress().c_str());
	CString companyName = CString(businessCardIndex->GetCompanyName().c_str());
	CString address = CString(businessCardIndex->GetAddress().c_str());
	CString telephoneNumber = CString(businessCardIndex->GetTelephoneNumber().c_str());
	CString faxNumber = CString(businessCardIndex->GetFaxNumber().c_str());
	CString url = CString(businessCardIndex->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
	GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
	GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
	GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
	GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
	GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);

	Index *index = this->indexes->Find((LPCTSTR)companyName);
	Long position_ = index->Find(businessCardIndex);
	HTREEITEM hRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hRoot, TVGN_CHILD);
	CString indexName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
	while (indexName.Compare(companyName) != 0) {
		hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_NEXT);
		indexName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
	}
	HTREEITEM hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_CHILD);
	Long i = 0;
	while (i < position_) {
		hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hChild, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->SelectItem(hChild);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->SelectDropTarget(hChild);
}

//7. ���� ��ư�� ��������
// 7.1. ���� �������� �̵��Ѵ�.
void BusinessCardBinderForm::OnNextButtonClicked() {

	BusinessCard *businessCardIndex = this->businessCardBinder->Next();

	CString name = CString(businessCardIndex->GetName().c_str());
	CString position = CString(businessCardIndex->GetPosition().c_str());
	CString cellphoneNumber = CString(businessCardIndex->GetCellphoneNumber().c_str());
	CString emailAddress = CString(businessCardIndex->GetEmailAddress().c_str());
	CString companyName = CString(businessCardIndex->GetCompanyName().c_str());
	CString address = CString(businessCardIndex->GetAddress().c_str());
	CString telephoneNumber = CString(businessCardIndex->GetTelephoneNumber().c_str());
	CString faxNumber = CString(businessCardIndex->GetFaxNumber().c_str());
	CString url = CString(businessCardIndex->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
	GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
	GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
	GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
	GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
	GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);

	Index *index = this->indexes->Find((LPCTSTR)companyName);
	Long position_ = index->Find(businessCardIndex);
	HTREEITEM hRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hRoot, TVGN_CHILD);
	CString indexName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
	while (indexName.Compare(companyName) != 0) {
		hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_NEXT);
		indexName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
	}
	HTREEITEM hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_CHILD);
	Long i = 0;
	while (i < position_) {
		hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hChild, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->SelectItem(hChild);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->SelectDropTarget(hChild);
}
//8. ������ ��ư�� ������ ��
// 8.1. ������ �������� �̵��Ѵ�.
void BusinessCardBinderForm::OnLastButtonClicked() {

	BusinessCard *businessCardIndex = this->businessCardBinder->Last();

	CString name = CString(businessCardIndex->GetName().c_str());
	CString position = CString(businessCardIndex->GetPosition().c_str());
	CString cellphoneNumber = CString(businessCardIndex->GetCellphoneNumber().c_str());
	CString emailAddress = CString(businessCardIndex->GetEmailAddress().c_str());
	CString companyName = CString(businessCardIndex->GetCompanyName().c_str());
	CString address = CString(businessCardIndex->GetAddress().c_str());
	CString telephoneNumber = CString(businessCardIndex->GetTelephoneNumber().c_str());
	CString faxNumber = CString(businessCardIndex->GetFaxNumber().c_str());
	CString url = CString(businessCardIndex->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_NAME)->SetWindowTextA(name);
	GetDlgItem(IDC_STATIC_POSITION)->SetWindowTextA(position);
	GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowTextA(cellphoneNumber);
	GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowTextA(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowTextA(companyName);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowTextA(address);
	GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowTextA(faxNumber);
	GetDlgItem(IDC_STATIC_URL)->SetWindowTextA(url);

	Index *index = this->indexes->Find((LPCTSTR)companyName);
	Long position_ = index->Find(businessCardIndex);
	HTREEITEM hRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hRoot, TVGN_CHILD);
	CString indexName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
	while (indexName.Compare(companyName) != 0) {
		hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_NEXT);
		indexName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
	}
	HTREEITEM hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_CHILD);
	Long i = 0;
	while (i < position_) {
		hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hChild, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->SelectItem(hChild);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->SelectDropTarget(hChild);
}

void BusinessCardBinderForm::OnTreeViewItemDoubleclicked(NMHDR *pNotifySource, LRESULT *result) {
	HTREEITEM hItem = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(TVI_ROOT, TVGN_CARET);
	HTREEITEM hParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hItem, TVGN_CHILD);
	CString companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetItemText(hParent);
	HTREEITEM hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hParent, TVGN_CHILD);
	Long position_ = 0;
	while (hItem != hChild) {
		position_++;
		hChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->GetNextItem(hChild, TVGN_NEXT);
	}
	Index *index = this->indexes->Find((LPCTSTR)companyName);
	BusinessCard *businessCardIndex = index->GetAt(position_);

	CString name = CString(businessCardIndex->GetName().c_str());
	CString position = CString(businessCardIndex->GetPosition().c_str());
	CString cellphoneNumber = CString(businessCardIndex->GetCellphoneNumber().c_str());
	CString emailAddress = CString(businessCardIndex->GetEmailAddress().c_str());
	companyName = CString(businessCardIndex->GetCompanyName().c_str());
	CString address = CString(businessCardIndex->GetAddress().c_str());
	CString telephoneNumber = CString(businessCardIndex->GetTelephoneNumber().c_str());
	CString faxNumber = CString(businessCardIndex->GetFaxNumber().c_str());
	CString url = CString(businessCardIndex->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(name);
	GetDlgItem(IDC_STATIC_POSITION)->SetWindowText(position);
	GetDlgItem(IDC_STATIC_CELLPHONENUMBER)->SetWindowText(cellphoneNumber);
	GetDlgItem(IDC_STATIC_EMAILADDRESS)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANYNAME)->SetWindowText(companyName);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetWindowText(address);
	GetDlgItem(IDC_STATIC_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_STATIC_FAXNUMBER)->SetWindowText(faxNumber);
	GetDlgItem(IDC_STATIC_URL)->SetWindowText(url);
}

//9. �ݱ� ��ư�� ������ ��
// 9.1. ����ö�� �����.
void BusinessCardBinderForm::OnClose() {
	if (businessCardBinder != NULL) {
		//this->Save();
		delete businessCardBinder;
	}
	if (indexes != NULL) {
		delete indexes;
	}
	// 9.2. �����츦 �ݴ´�.
	EndDialog(0);
}


