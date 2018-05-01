//UpdatingForm.c
#include "UpdatingForm.h"
#include "Vocabulary.h"
#include "FindingForm.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <CommCtrl.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_UPDATINGFORM), NULL, UpdatingFormProc);
}


BOOL CALLBACK UpdatingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG: ret = UpdatingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND:ret = UpdatingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY:ret = UpdatingForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE:ret = UpdatingForm_OnClose(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}
BOOL UpdatingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Vocabulary *vocabulary;
	LVCOLUMN column = { 0, };
	LVITEM item = { 0. };
	Long index = 0;
	TCHAR number[64];
	//1.1 �ܾ������غ��Ѵ�
	vocabulary = (Vocabulary*)malloc(sizeof(Vocabulary));
	Create(vocabulary, 60000);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)vocabulary);
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//1.2 ����Ʈ��������� �����
	//wParam=(WPARAM)(int)icol;
	//lParam=(LPARAM)(const LV_COLUMN FAR*)pcol;
	column.mask = LVCF_WIDTH | LVCF_TEXT;
	column.cx = 50;
	column.pszText = "��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "�ܾ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "�ǹ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);
	column.cx = 70;
	column.pszText = "ǰ��";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);
	column.cx = 240;
	column.pszText = "����";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);
	//1.3 �ܾ��忡 �����Ѵ�
	Load(vocabulary);
	//1.4 ����Ʈ�信 �ܾ���� �߰��Ѵ�
	item.mask = LVIF_TEXT;
	while (index < vocabulary->length)
	{
		item.iItem = index;
		sprintf(number, "%d", index + 1);
		item.pszText = number; item.iSubItem = 0;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);
		item.pszText = vocabulary->words[index].name; item.iSubItem = 1;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.pszText = vocabulary->words[index].mean; item.iSubItem = 2;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.pszText = vocabulary->words[index].partOfSpeech; item.iSubItem = 3;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.pszText = vocabulary->words[index].exampleSentence; item.iSubItem = 4;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		index++;
	}
	return FALSE;
}
BOOL UpdatingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_RECORD:ret = UpdatingForm_OnRecordButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIND:ret = UpdatingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_CORRECT:ret = UpdatingForm_OnCorrectButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ERASE:ret = UpdatingForm_OnEraseButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ARRANGE:ret = UpdatingForm_OnArrageButtonClicked(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}
BOOL UpdatingForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Vocabulary *vocabulary;
	Long index;
	TCHAR name[NAME];
	TCHAR mean[MEAN];
	TCHAR partOfSpeech[PARTOFSPEECH];
	TCHAR exampleSentence[EXAMPLESENTENCE];
	TCHAR number[64];
	LVITEM item = { 0, };
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1�ܾ �д´�
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)NAME, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEAN), WM_GETTEXT, (WPARAM)MEAN, (LPARAM)mean);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PARTOFSPEECH), WM_GETTEXT, (WPARAM)PARTOFSPEECH, (LPARAM)partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_GETTEXT, (WPARAM)EXAMPLESENTENCE, (LPARAM)exampleSentence);
		//2.2 �ܾ��忡 �ܾ ���´�
		vocabulary = (Vocabulary(*)) GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(vocabulary, name, mean, partOfSpeech, exampleSentence);
		//2.3 ����Ʈ�信 �׸��� �߰��Ѵ�
		item.mask = LVIF_TEXT;
		item.iItem = index;
		sprintf(number, "%d", index + 1);
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);
		item.iSubItem = 1;
		item.pszText = vocabulary->words[index].name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = vocabulary->words[index].mean;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = vocabulary->words[index].partOfSpeech;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = vocabulary->words[index].exampleSentence;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return FALSE;
}
BOOL UpdatingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1ã�������츦 �����Ѵ�
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), hWnd, FindingFormProc);
	}
	return FALSE;

}
BOOL UpdatingForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Vocabulary *vocabulary;
	TCHAR name[NAME];
	TCHAR mean[MEAN];
	TCHAR partOfSpeech[PARTOFSPEECH];
	TCHAR exampleSentence[EXAMPLESENTENCE];
	Long index;
	LVITEM item = { 0, };
	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1.�ܾ��� �д´�
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)NAME, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEAN), WM_GETTEXT, (WPARAM)MEAN, (LPARAM)mean);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PARTOFSPEECH), WM_GETTEXT, (WPARAM)PARTOFSPEECH, (LPARAM)partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_GETTEXT, (WPARAM)EXAMPLESENTENCE, (LPARAM)exampleSentence);
		//4.2.����Ʈ�信�� ���õ��׸�����ġ�� �д´�
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		//4.3.�ܾ��忡 �ش�ܾ�����ģ��
		vocabulary = (Vocabulary(*))GetWindowLong(hWnd, GWL_USERDATA);
		index = Correct(vocabulary, index, mean, partOfSpeech, exampleSentence);
		//4.4.����Ʈ�信 �ش��׸��� �����Ѵ�
		item.mask = LVIF_TEXT;
		item.iItem = index;
		item.iSubItem = 2;
		item.pszText = vocabulary->words[index].mean;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = vocabulary->words[index].partOfSpeech;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = vocabulary->words[index].exampleSentence;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return FALSE;
}
BOOL UpdatingForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Vocabulary *vocabulary;
	TCHAR number[64];
	Long index;
	Long i;
	LVITEM item = { 0, };
	if (HIWORD(wParam) == BN_CLICKED) {
		//5.1.����Ʈ�信�� ���õ��׸�����ġ�� �д´�
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		//5.2.�ܾ��忡�� �ش�ܾ �����
		vocabulary = (Vocabulary(*))GetWindowLong(hWnd, GWL_USERDATA);
		Erase(vocabulary, index);
		//5.3.����Ʈ�信�� �ش��׸��������
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEITEM, (WPARAM)index, (LPARAM)0);
		//5.4.����Ʈ�信�� �ش��׸� ���� ��ȣ�� �����Ѵ�
		item.mask = LVIF_TEXT;
		item.iSubItem = 0;
		i = index;
		while (i < vocabulary->length) {
			sprintf(number, "%d", i + 1);
			item.iItem = i; item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
			i++;
		}
	}
	return FALSE;
}
BOOL UpdatingForm_OnArrageButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Vocabulary *vocabulary;
	TCHAR number[64];
	LVITEM item = { 0, };
	Long index = 0;
	if (HIWORD(wParam) == BN_CLICKED) {
		//6.1.�ܾ����� �����Ѵ�
		vocabulary = (Vocabulary(*))GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(vocabulary);
		//6.2.����Ʈ�信 ��� �׸��� �����
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);
		//6.3.����Ʈ�信 �ܾ����� ���´�
		item.mask = LVIF_TEXT;
		while (index < vocabulary->length) {
			item.iItem = index;
			item.iSubItem = 0;
			sprintf(number, "%d", index + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);
			item.iSubItem = 1;
			item.pszText = vocabulary->words[index].name;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 2;
			item.pszText = vocabulary->words[index].mean;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 3;
			item.pszText = vocabulary->words[index].partOfSpeech;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 4;
			item.pszText = vocabulary->words[index].exampleSentence;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			index++;
		}
	}
	return FALSE;
}
BOOL UpdatingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (wParam) {
	case IDC_LIST_WORDS:ret = UpdatingForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam); break;
	default:ret = FALSE;
	}
	return ret;
}
BOOL UpdatingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	LVITEM item = { 0, };
	TCHAR name[NAME];
	TCHAR mean[MEAN];
	TCHAR partOfSpeech[PARTOFSPEECH];
	TCHAR exampleSentence[EXAMPLESENTENCE];
	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//7.1.����Ʈ�信�� ���õ��׸�����ġ�� �д´�
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		//7.2.����Ʈ�信�� �ش��׸��� �д´�
		item.iSubItem = 1; item.cchTextMax = NAME; item.pszText = name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2; item.cchTextMax = MEAN; item.pszText = mean;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3; item.cchTextMax = PARTOFSPEECH; item.pszText = partOfSpeech;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4; item.cchTextMax = EXAMPLESENTENCE; item.pszText = exampleSentence;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		//7.3.�����׸��� �ܾ ���´�
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEAN), WM_SETTEXT, (WPARAM)0, (LPARAM)mean);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PARTOFSPEECH), WM_SETTEXT, (WPARAM)0, (LPARAM)partOfSpeech);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLESENTENCE), WM_SETTEXT, (WPARAM)0, (LPARAM)exampleSentence);
	}
	return FALSE;
}
BOOL UpdatingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Vocabulary *vocabulary;
	//8.1.�ܾ����������
	vocabulary = (Vocabulary(*))GetWindowLong(hWnd, GWL_USERDATA);
	if (vocabulary != NULL) {
		Save(vocabulary);
		Destroy(vocabulary);
		free(vocabulary);
	}
	//8.2.�����츦 �ݴ´�
	EndDialog(hWnd, 0);
	return FALSE;
}
