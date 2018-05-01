//UpdatingForm.cpp
#include "UpdatingForm.h"
#include "FindingForm.h"
#include "WordBook.h"
#include <afxcmn.h>
BEGIN_MESSAGE_MAP(UpdatingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK,IDC_LIST_VOCABULARIES, OnListViewItemDoubleClcked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

UpdatingForm::UpdatingForm(CWnd *parent) :CDialog(UpdatingForm::IDD, parent) {
	this->wordBook = NULL;
}
BOOL UpdatingForm::OnInitDialog() {
	CDialog::OnInitDialog();
	// 1.1 �ܾ����� �غ��Ѵ�.
	this->wordBook = new WordBook;
	// 1.2 ����Ʈ�信 ����� �����.
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->InsertColumn(0, "��ȣ", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->InsertColumn(1, "�ܾ�", LVCFMT_LEFT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->InsertColumn(2, "�ǹ�", LVCFMT_LEFT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->InsertColumn(3, "ǰ��", LVCFMT_LEFT, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->InsertColumn(4, "����", LVCFMT_LEFT, 200);
	return FALSE;
}

void UpdatingForm::OnRecordButtonClicked() {
	CString spelling;
	CString meaning;
	CString wordClass;
	CString example;
	Long index;

	GetDlgItem(IDC_EDIT_SPELLING)->GetWindowTextA(spelling);
	GetDlgItem(IDC_EDIT_MEANING)->GetWindowTextA(meaning);
	GetDlgItem(IDC_EDIT_WORDCLASS)->GetWindowTextA(wordClass);
	GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowTextA(example);

	index = this->wordBook->Record((LPCTSTR)spelling, (LPCTSTR)meaning, (LPCTSTR)wordClass, (LPCTSTR)example);

	Word word = this->wordBook->GetAt(index);

	spelling = CString(word.GetSpelling().c_str());
	meaning = CString(word.GetMeaning().c_str());
	wordClass = CString(word.GetWordClass().c_str());
	example = CString(word.GetExample().c_str());

	CString number;
	number.Format("%d", index + 1);
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->InsertItem(index, number);
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->SetItemText(index, 1, spelling);
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->SetItemText(index, 2, meaning);
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->SetItemText(index, 3, wordClass);
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->SetItemText(index, 4, example);
}

void UpdatingForm::OnFindButtonClicked() {
	FindingForm findingForm;
	findingForm.DoModal();
}

void UpdatingForm::OnCorrectButtonClicked() {
	CString meaning;
	CString wordClass;
	CString example;
	Long index;

	//4.1 ������ �д´�.
	GetDlgItem(IDC_EDIT_WORD)->GetWindowTextA(meaning);
	GetDlgItem(IDC_EDIT_WORD)->GetWindowTextA(wordClass);
	GetDlgItem(IDC_EDIT_WORD)->GetWindowTextA(example);

	//4.2 ����Ʈ�信�� ���õ� �׸��� �д´�.
	index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->GetSelectionMark();

	// 4.3 �ܾ��忡�� �ش�ܾ ��ģ��.
	index = this->wordBook->Correct(index, (LPCTSTR)meaning, (LPCTSTR)wordClass, (LPCTSTR)example);

	// 4.4 ����Ʈ���� �ش��׸��� �����Ѵ�.
	Word word = this->wordBook->GetAt(index);

	meaning = CString(word.GetMeaning().c_str());
	wordClass = CString(word.GetWordClass().c_str());
	example = CString(word.GetExample().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->SetItemText(index, 2, meaning);
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->SetItemText(index, 3, wordClass);
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->SetItemText(index, 4, example);
}

void UpdatingForm::OnEraseButtonClicked() {
	CString number;
	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->GetSelectionMark();

	this->wordBook->Erase(index);
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->DeleteItem(index);
	Long length = this->wordBook->GetLength();

	while (index < length) {
		number.Format("%d", index + 1);
		((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->SetItemText(index, 0, number);
		index++;
	}
}

void UpdatingForm::OnArrangeButtonClicked() {
	CString spelling;
	CString meaning;
	CString wordClass;
	CString example;
	CString number;
	Word word;
	Long index = 0;

	this->wordBook->Arrange();
	((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->DeleteAllItems();
	Long length = this->wordBook->GetLength();

	while (index < length) {
		word = this->wordBook->GetAt(index);
		spelling = CString(word.GetSpelling().c_str());
		meaning = CString(word.GetMeaning().c_str());
		wordClass = CString(word.GetWordClass().c_str());
		example = CString(word.GetExample().c_str());
		number.Format("%d", index + 1);

		((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->InsertItem(index, number);
		((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->SetItemText(index, 1, spelling);
		((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->SetItemText(index, 2, meaning);
		((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->SetItemText(index, 3, wordClass);
		((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->SetItemText(index, 4, example);
		index++;
	}
}

void UpdatingForm::OnListViewItemDoubleClcked(NMHDR *pNotifyStruct, LRESULT *result) {

	Long index = (Long)((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->GetSelectionMark();

	CString spelling = ((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->GetItemText(index, 1);
	CString meaning = ((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->GetItemText(index, 2);
	CString wordClass = ((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->GetItemText(index, 3);
	CString example = ((CListCtrl*)GetDlgItem(IDC_LIST_VOCABULARIES))->GetItemText(index, 4);

	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowTextA(spelling);
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowTextA(meaning);
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowTextA(wordClass);
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowTextA(example);
}

void UpdatingForm::OnClose() {
	if (this->wordBook != 0) {
		delete this->wordBook;
	}
	EndDialog(0);
}