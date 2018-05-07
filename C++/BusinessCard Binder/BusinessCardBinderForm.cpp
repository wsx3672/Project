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
	this->businessCardBinder = NULL; //디폴트 생성자, 매개변수를 갖는 생성자
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
		"FROM Company INNER JOIN Personal On Company.companyCode = Personal.companyCode;"; // INNER JOIN, ON 으로 싹 다 가져옴 // 어케함?
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
//1. 윈도우가 생성되었을 때
// 1.1. 명함철을 준비한다
BOOL BusinessCardBinderForm::OnInitDialog() {
	CDialog::OnInitDialog();  //코드재사용//오버라이딩
	this->businessCardBinder = new BusinessCardBinder;
	this->indexes = new Indexes;
	BusinessCard businessCard("홍길동", "WW", "WW", "WW", "삼성", "WW", "WW", "WW", "WW");
	this->businessCardBinder->TakeIn(businessCard);
	//Long length = this->businessCardBinder->GetLength();
	BusinessCard *businessCardIndex = this->businessCardBinder->First();	//오류
	if (businessCardIndex != NULL) {
		//BusinessCard *businessCardIndex = this->businessCardBinder->First();	//오류
		BusinessCard *previous = NULL;
		while (businessCardIndex != previous) {
			this->indexes->TakeIn(businessCardIndex);
			previous = businessCardIndex;
			businessCardIndex = this->businessCardBinder->Next();
		}
	}
	this->indexes->Arrange();
	HTREEITEM hRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->InsertItem("회사들");
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

//2. 넣기버튼을 클릭했을 때
// 2.1. 넣기 윈도우를 출력한다.
void BusinessCardBinderForm::OnTakeInButtonClicked() {
	TakeInForm takeInForm;
	takeInForm.DoModal();
}

//3. 찾기버튼을 눌렀을 때
// 3.1. 찾기 윈도우를 출력한다
void BusinessCardBinderForm::OnFindButtonClicked() {
	FindingForm findingForm;
	findingForm.DoModal();
}

//4. 뽑기버튼을 눌렀을 때
// 4.1. 뽑기 윈도우를 출력한다.
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
	HTREEITEM hRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_COMPANIES))->InsertItem("회사들");
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
//5. 처음 버튼을 눌렀을때
// 5.1. 첫번째 명함으로 이동한다.
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

//6. 이전 버튼을 눌렀을때
// 6.1.  이전 명함으로 이동한다.
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

//7. 다음 버튼을 눌렀을때
// 7.1. 다음 명함으로 이동한다.
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
//8. 마지막 버튼을 눌렀을 때
// 8.1. 마지막 명함으로 이동한다.
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

//9. 닫기 버튼을 눌렀을 때
// 9.1. 명함철을 지운다.
void BusinessCardBinderForm::OnClose() {
	if (businessCardBinder != NULL) {
		//this->Save();
		delete businessCardBinder;
	}
	if (indexes != NULL) {
		delete indexes;
	}
	// 9.2. 윈도우를 닫는다.
	EndDialog(0);
}


