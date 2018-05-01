//FindeForm.c
#include "FindingForm.h"
#include "AddressBook.h"
#include "resource.h"
#include "UpdatingForm.h"
#include <stdio.h>
#include <CommCtrl.h>


BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	
	switch (message) {
	case WM_INITDIALOG:ret = FindingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND:ret=FindingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY:ret=FindingForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE:ret=FindingForm_OnClose(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}
BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN column = { 0, };

	//1.1 ����Ʈ�信 ����� �����
	//wParam=(LPARAM)(int)icol;
	//lParam=(LPARAM)(comst LV_COLUMN FAR *)pcol;
	////����Ʈ�� �� ��üŬ�� , ���м� �߰�
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	column.mask = LVCF_WIDTH | LVCF_TEXT;
	column.cx = 50;
	column.pszText = "��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "����";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 170;
	column.pszText = "�ּ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "��ȭ��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);
	column.cx = 160;
	column.pszText = "�̸���";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);
	return FALSE;
}
BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIND:ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}
BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR name[NAME];
	LVITEM item = { 0, };
	HWND hUpdatingForm;
	Long (*indexes);
	Long count;
	Long index=0;
	TCHAR number[64];
	AddressBook *addressBook;

	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1 ������ �д´�
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)NAME, (LPARAM)name);
		//2.2 �ּҷ������츦 ã�´�
		hUpdatingForm = FindWindow("#32770", "�ּҷ�");
		//2.3 �ּҷ� �����쿡�� �ּҷ��� ã�´�
		addressBook = (AddressBook(*))GetWindowLong(hUpdatingForm, GWL_USERDATA);
		//2.4 �ּҷϿ��� ������ ã�´�
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL) {
			free(indexes);
			indexes = NULL;
		}
		Find(addressBook, name, &indexes, &count);
		SetWindowLong(hWnd, GWL_USERDATA,(LONG)indexes);
		//2.5 ����Ʈ���� ��� �׸��� �����
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);
		//2.6 ����Ʈ�信 ã�� ������ �߰��Ѵ�
		item.mask = LVIF_TEXT;
		while (index < count) {
			item.iItem = index;
			sprintf(number, "%d", index + 1);
			item.iSubItem = 0; item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);
			item.iSubItem = 1; item.pszText = addressBook->personals[indexes[index]].name;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 2; item.pszText = addressBook->personals[indexes[index]].address;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 3; item.pszText = addressBook->personals[indexes[index]].telephoneNumber;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 4; item.pszText = addressBook->personals[indexes[index]].emailAddress;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			index++;
		}
	}
	return FALSE;
}
BOOL FindingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (wParam)
	{
	case IDC_LIST_PERSONALS:ret = FindingForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}
BOOL FindingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR name[NAME];
	TCHAR address[ADDRESS];
	TCHAR telephoneNumber[TELEPHONE];
	TCHAR emailAddress[EMAIL];
	Long index;
	Long(*indexes);
	HWND hUpdatingForm;
	LVITEM item = { 0, };
	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//3.1 ����Ʈ�信�� ���õ� �׸��� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		//3.2 ����Ʈ�信�� �ش� �׸��� �д´�.
		item.mask = LVIF_TEXT;
		item.iSubItem = 1;
		item.cchTextMax = NAME;
		item.pszText = name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2;
		item.cchTextMax = ADDRESS;
		item.pszText = address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.cchTextMax = TELEPHONE;
		item.pszText = telephoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.cchTextMax = EMAIL;
		item.pszText = emailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		//3.3 �ּҷ� �����츦 ã�´�.
		hUpdatingForm = FindWindow("#32770", "�ּҷ�");
		//3.4 ���� �׸���� �ּҷ� �������� ���ο� ���´�.
		SendMessage(GetDlgItem(hUpdatingForm, IDC_EDIT_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)name);
		SendMessage(GetDlgItem(hUpdatingForm, IDC_EDIT_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)address);
		SendMessage(GetDlgItem(hUpdatingForm, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hUpdatingForm, IDC_EDIT_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)emailAddress);
		//3.5 �ּҷ� �������� �ش� �׸��� ��ũ�Ѵ�.
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		SendMessage(GetDlgItem(hUpdatingForm, IDC_LIST_PERSONALS), LVM_SETSELECTIONMARK, (WPARAM)0, (LPARAM)indexes[index]);
		//3.6 ã�� �����츦 �ݴ´�.
		if (indexes != NULL) {
			free(indexes);
		}
		EndDialog(hWnd, 0);
	}

	return FALSE;
}
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	//4.1 �����츦 �ݴ´�
	EndDialog(hWnd, 0);
	return FALSE;
}