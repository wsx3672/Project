#include "UpdatingForm.h"
#include "FindingForm.h"
#include "AddressBook.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <CommCtrl.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine,int nCmdShow) {
	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_UPDATINGFORM), NULL, UpdatingFormProc);
}



BOOL CALLBACK UpdatingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG:ret = UpdatingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND:ret= UpdatingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY:ret = UpdatingForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE:ret = UpdatingForm_OnClose(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}


BOOL UpdatingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook *addressBook;
	LVCOLUMN column = { 0, };
	LVITEM item = { 0. };
	Long index = 0;
	TCHAR number[64];
	//1.1 주소록을 준비한다
	addressBook = (AddressBook*)malloc(sizeof(AddressBook));
	Create(addressBook, 60000);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)addressBook);
	////리스트뷰 줄 전체클릭 , 구분선 추가
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//1.2 리스트뷰의 헤더를 만들다
	//wParam=(LPARAM)(int)icol;
	//lParam=(LPARAM)(comst LV_COLUMN FAR *)pcol;
	column.mask = LVCF_WIDTH | LVCF_TEXT;
	column.cx = 50;
	column.pszText = "번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "성명";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 170;
	column.pszText = "주소";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "전화번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);
	column.cx = 160;
	column.pszText = "이메일";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);
	//1.3 주소록에 적재한다
	Load(addressBook);
	//1.4 리스트뷰에 개인들을 추가한다
	item.mask = LVIF_TEXT;
	while (index < addressBook->length)
	{
		item.iItem = index;
		sprintf(number, "%d", index + 1);
		item.pszText = number; item.iSubItem = 0;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);
		item.pszText = addressBook->personals[index].name; item.iSubItem = 1;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.pszText = addressBook->personals[index].address; item.iSubItem = 2;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.pszText = addressBook->personals[index].telephoneNumber; item.iSubItem = 3;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.pszText = addressBook->personals[index].emailAddress; item.iSubItem = 4;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		index++;
	}
	return FALSE;
}
BOOL UpdatingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_RECORD:ret = UpdatingForm_OnRecordButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIND:ret=UpdatingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_CORRECT:ret=UpdatingForm_OnCorrectButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ERASE:ret=UpdatingForm_OnEraseButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ARRANGE:ret=UpdatingForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}
BOOL UpdatingForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook *addressBook;
	Long index;
	TCHAR name[NAME];
	TCHAR address[ADDRESS];
	TCHAR telephoneNumber[TELEPHONE];
	TCHAR emailAddress[EMAIL];
	TCHAR number[64];
	LVITEM item = { 0, };
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1개인을 읽는다
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)NAME, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)ADDRESS, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)TELEPHONE, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_GETTEXT, (WPARAM)EMAIL, (LPARAM)emailAddress);
		//2.2주소록에 개인을 적는다
		addressBook = (AddressBook(*))GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(addressBook, name, address, telephoneNumber, emailAddress);
		//2.3리스트뷰에 항목을 추가한다
		item.mask = LVIF_TEXT;
		item.iItem = index;
		sprintf(number, "%d", index + 1);
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);
		item.iSubItem = 1;
		item.pszText = addressBook->personals[index].name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = addressBook->personals[index].address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = addressBook->personals[index].telephoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = addressBook->personals[index].emailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return FALSE;
}
BOOL UpdatingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1찾기윈도우를 생성한다
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), hWnd, FindingFormProc);
	}
	return FALSE;

}
BOOL UpdatingForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook *addressBook;
	TCHAR name[NAME];
	TCHAR address[ADDRESS];
	TCHAR telephoneNumber[TELEPHONE];
	TCHAR emailAddress[EMAIL];
	Long index;
	LVITEM item = { 0, };
	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1 개인을 읽는다
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)NAME, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)NAME, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)NAME, (LPARAM)telephoneNumber);
        SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_GETTEXT, (WPARAM)NAME, (LPARAM)emailAddress);
        //4.2 리스트뷰에서 선택된 항목의 위치를 읽는다
        index = (LONG)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
//4.3 주소록에 해당 개인을 고친다
addressBook = (AddressBook(*))GetWindowLong(hWnd, GWL_USERDATA);
index = Correct(addressBook, index, address, telephoneNumber, emailAddress);
// 4.4 리스트뷰에 해당항목을 수정한다
item.mask = LVIF_TEXT;
item.iItem = index;
item.iSubItem = 2;
item.pszText = addressBook->personals[index].address;
SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
item.iSubItem = 3;
item.pszText = addressBook->personals[index].telephoneNumber;
SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
item.iSubItem = 4;
item.pszText = addressBook->personals[index].emailAddress;
SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return FALSE;
}
BOOL UpdatingForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook *addressBook;
	TCHAR number[64];
	Long index;
	Long i;
	LVITEM item = { 0, };
	if (HIWORD(wParam) == BN_CLICKED) {
		//5.1 리스트뷰에서 선택된 항목의 위치를 읽는다
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK,(WPARAM)0, (LPARAM)0);
		//5.2 주소록에서 해당개인을 지운다
		addressBook = (AddressBook(*))GetWindowLong(hWnd, GWL_USERDATA);
		Erase(addressBook, index);
		//5.3 리스트뷰에서 해당항목을 지운다
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEITEM, (WPARAM)index, (LPARAM)0);
		//5.4 리스트뷰에서 해당항목 이후 번호를 수정한다
		item.mask = LVIF_TEXT;
		item.iSubItem = 0;
		i = index;
		while (i < addressBook->length) {
			sprintf(number,"%d", i + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
			i++;
		}
	}
	return FALSE;
}
BOOL UpdatingForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook *addressBook;
	TCHAR number[64];
	LVITEM item = { 0, };
	Long index = 0;
	if (HIWORD(wParam) == BN_CLICKED) {
		//6.1 주소록을 정리한다
		addressBook = (AddressBook(*))GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(addressBook);
		//6.2리스트뷰에 모든 항목을 지운다
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);
		//6.3 리스트뷰에 모든 주소록을 추가한다
		item.mask = LVIF_TEXT;

		while (index < addressBook->length) {
			item.iItem = index;
			sprintf(number,"%d", index + 1);
			item.iSubItem = 0;
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);
			item.iSubItem = 1;
			item.pszText = addressBook->personals[index].name;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 2;
			item.pszText = addressBook->personals[index].address;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 3;
			item.pszText = addressBook->personals[index].telephoneNumber;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 4;
			item.pszText = addressBook->personals[index].emailAddress;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			index++;
		}
	}
	return FALSE;
}
BOOL UpdatingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (wParam) {
	case IDC_LIST_PERSONALS:ret = UpdatingForm_OnListViewItemDoubleClicked(hWnd,wParam,lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}
BOOL UpdatingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	LVITEM item = { 0, };
	TCHAR name[NAME];
	TCHAR address[ADDRESS];
	TCHAR telephoneNumber[TELEPHONE];
	TCHAR emailAddress[EMAIL];
	if (((LPNMHDR)lParam)->code == NM_DBLCLK){
		//7.1 리스트뷰에서 선택된 항목의 위치를 읽는다
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK,(WPARAM)0, (LPARAM)0);
		//7.2 리스트뷰에서 해당항목을 읽는다
		item.mask = LVIF_TEXT;
		item.iSubItem = 1; item.cchTextMax = NAME; item.pszText = name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2; item.cchTextMax = ADDRESS; item.pszText = address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3; item.cchTextMax = TELEPHONE; item.pszText = telephoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4; item.cchTextMax = EMAIL; item.pszText = emailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		//7.3 읽은항목을 개인에 적는다
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_SETTEXT,(WPARAM)0,  (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)emailAddress);
   }
	return FALSE;
}
BOOL UpdatingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook *addressBook;

	//8.1주소록을 지운다
	addressBook = (AddressBook(*))GetWindowLong(hWnd, GWL_USERDATA);
	if (addressBook != NULL) {
		Save(addressBook);
		Destroy(addressBook);
		free(addressBook);
	}
	//8.2 윈도우를 닫는다
	EndDialog(hWnd, 0);
	return FALSE;
}