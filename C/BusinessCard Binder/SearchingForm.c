//SearchingForm.c

//매크로선언

#include "ZipCodeBookUsingArray.h"
#include "SearchingForm.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <CommCtrl.h>
#pragma warning (disable:4996)

BOOL CALLBACK SearchingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG:
		ret = SearchingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND:
		ret = SearchingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY:
		ret = SearchingForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE:
		ret = SearchingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}


BOOL SearchingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	ZipCodeBook *zipCodeBook;
	LVCOLUMN column = { 0, };

	zipCodeBook = (ZipCodeBook *)malloc(sizeof(ZipCodeBook));
	ZipCodeBook_Create(zipCodeBook, 60000);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)zipCodeBook);

	SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

	column.mask = LVCF_WIDTH | LVCF_TEXT;
	column.cx = 50;
	column.pszText = "number";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);

	column.cx = 380;
	column.pszText = "address";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);

	column.cx = 80;
	column.pszText = "zipCode";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);

	return FALSE;
}


BOOL SearchingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_SEARCH:
		ret = SearchingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}


BOOL SearchingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	ZipCodeBook *zipCodeBook;
	Long(*indexes);
	TCHAR dong[27];
	Address address;
	TCHAR line[256];
	TCHAR frontline[256];
	TCHAR rearline[256];
	TCHAR number[64];
	LVITEM item = { 0, };
	Long count;
	Long i = 0;
	Long j = 0;
	Long k = 0;

	if (HIWORD(wParam) == BN_CLICKED)
	{

		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SEARCH), WM_GETTEXT, (WPARAM)27, (LPARAM)dong);

		zipCodeBook = (ZipCodeBook(*))GetWindowLong(hWnd, GWL_USERDATA);

		ZipCodeBook_Load(zipCodeBook);

		ZipCodeBook_Find(zipCodeBook, dong, &indexes, &count);

		//char lineZipCode[100];
		//sprintf(lineZipCode, "%d", count); ??????????????????????????????????
		//MessageBox(hWnd, lineZipCode, "확인", MB_OK | MB_ICONINFORMATION);

		SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		item.mask = LVIF_TEXT;
		while (i < count)
		{
			j = 0;
			k = 0;
			sprintf(number, "%d", i + 1);
			item.iItem = i;
			item.iSubItem = 0;
			item.pszText = number;
			
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

			address = ZipCodeBook_GetAt(zipCodeBook, indexes[i]);
			sprintf(frontline, "%s %s %s %s %s", address.sido, address.gugun, address.dong, address.ri, address.bldg);
			
			while (address.st_bunji[j] != '\0')
			{
				j++;
			}
			while (address.ed_bunji[k] != '\0')
			{
				k++;
			}
			if (j > 0 && k > 0)
			{
				sprintf(rearline, "%s~%s", address.st_bunji, address.ed_bunji);
			}
			else
			{
				sprintf(rearline, "%s %s", address.st_bunji, address.ed_bunji);
			}
			sprintf(line, "%s %s", frontline, rearline);
			item.iSubItem = 1;
			item.pszText = line;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
			item.iSubItem = 2;
			GetAt(&zipCodeBook->addresses, i, &address, sizeof(Address));
			item.pszText = address.zipCode;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
			i++;
		}

		if (indexes != NULL)
		{
			free(indexes);
			indexes = NULL;
		}

	}
	return FALSE;
}


BOOL SearchingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (wParam)
	{
	case IDC_LIST_ADDRESS:
		ret = SearchingForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}


BOOL SearchingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long selected;
	LVITEM item = { 0, };
	TCHAR zipCode[8];
	TCHAR line[256];
	TCHAR lineZipCode[256];
	Long i = 0;
	Long j = 0;
	HWND hTakeInForm;

	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		selected = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		if (selected != -1) {
			item.mask = LVIF_TEXT;
			item.iSubItem = 1;
			item.cchTextMax = 256;
			item.pszText = line;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_GETITEMTEXT, (WPARAM)selected, (LPARAM)&item);
			item.iSubItem = 2;
			item.cchTextMax = 8;
			item.pszText = zipCode;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_GETITEMTEXT, (WPARAM)selected, (LPARAM)&item);

			sprintf(lineZipCode, "%s\n%s", line, zipCode);

			//주소록윈도우를 찾는다
			hTakeInForm = FindWindow("#32770", "넣기");

			//주소록윈도우의 그룹박스에서 에딧박스에 적어준다
			//SendMessage(GetDlgItem(hUpdatingForm, IDC_EDIT_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)name);
			SendMessage(GetDlgItem(hTakeInForm, IDC_EDIT_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)lineZipCode);
			//SendMessage(GetDlgItem(hUpdatingForm, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)telephoneNumber);
			//SendMessage(GetDlgItem(hUpdatingForm, IDC_EDIT_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)emailAddress);

			//주소록윈도우 리스트박스에 마크한다
			//SendMessage(GetDlgItem(hUpdatingForm, IDC_LIST_PERSONALS), LVM_SETSELECTIONMARK, (WPARAM)0, (LPARAM)1);

			MessageBox(hWnd, lineZipCode, "확인", MB_OK | MB_ICONINFORMATION);



			EndDialog(hWnd, 0);
		}
	}
	return FALSE;
}


BOOL SearchingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	ZipCodeBook *zipCodeBook;
	zipCodeBook = (ZipCodeBook(*))GetWindowLong(hWnd, GWL_USERDATA);
	if (zipCodeBook != NULL)
	{
		ZipCodeBook_Destroy(zipCodeBook);
		free(zipCodeBook);
		zipCodeBook = NULL;
	}
	EndDialog(hWnd, 0);
	return FALSE;
}

