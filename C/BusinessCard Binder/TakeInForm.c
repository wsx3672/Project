//TakeInForm.c

#include "TakeInForm.h"
#include "BusinessCardBinder.h"
#include "resource.h"
#include "SearchingForm.h"
#include "Index.h"
#include "Indexes.h"
#include <stdio.h>
#include <CommCtrl.h>
#pragma warning(disable:4996)

BOOL CALLBACK TakeInFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = TakeInForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = TakeInForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = TakeInForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL TakeInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char emails[][16] = { "naver.com", "daum.com", "nate.com", "gmail.com", "icloud.com" };
	char positions[][5] = { "ȸ��", "����", "����", "��", "����", "����", "����", "�븮", "���" };
	Long i = 0;

	while (i < (sizeof(positions) / sizeof(positions[0])))
	{
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)positions[i]);
		i++;
	}
	i = 0;
	while (i < sizeof(emails) / sizeof(emails[0]))
	{
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_EMAILDOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)emails[i]);
		i++;
	}
	return FALSE;
}


BOOL TakeInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_TAKEIN:
		ret = TakeInForm_OnTakeInButtonClicked(hWnd, wParam, lParam); break;
	case IDC_EDIT_COMPANY_NAME:
		ret = TakeInForm_OnCompanyNameEditLosesFocus(hWnd, wParam, lParam); break;
	case IDC_BUTTON_SEARCHING_ADDRESS:
		ret = TakeInForm_OnFindZipCodeButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL TakeInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//4.1�����츦 �ݴ´�
	EndDialog(hWnd, 0);
	return FALSE;
}

BOOL TakeInForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	BusinessCard businessCard = { 0, };
	BusinessCard *businessCardIndex;
	Indexes *indexes;
	Index *index;
	HWND hBusinessCardBinderForm;
	HTREEITEM hRoot;
	HTREEITEM hParent;
	HTREEITEM hChild;
	TCHAR emailID[32];
	TCHAR emailDomain[32];
	TCHAR companyName[64];
	TVITEM tvItem = { 0, };
	TVINSERTSTRUCT tvInsertStruct = { 0, };

	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1 ���Ե� �д´�
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILID), WM_GETTEXT, (WPARAM)32, (LPARAM)emailID);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_EMAILDOMAIN), WM_GETTEXT, (WPARAM)32, (LPARAM)emailDomain);
		sprintf(businessCard.personal.emailAddress, "%s@%s", emailID, emailDomain);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)128, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_URL), WM_GETTEXT, (WPARAM)256, (LPARAM)businessCard.company.url);

		//2.2 ����ö �����츦 ã�´�
		hBusinessCardBinderForm = FindWindow("#32770", "����ö");
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hBusinessCardBinderForm, GWL_USERDATA);
		indexes = (Indexes*)GetProp(hBusinessCardBinderForm, "indexes");

		//2.3 ����ö �������� ����ö�� ���´�.
		businessCardIndex = BusinessCardBinder_TakeIn(businessCardBinder, businessCard);

		BusinessCardBinder_Add(businessCardBinder, businessCardIndex); // ��ũ���Ͽ� �ٷ� �����Ѵ�

		//2.4 ����ö �������� ����ö�� �ִ´�.
		index = Indexes_TakeIn(indexes, businessCardIndex);

		SetProp(hWnd, "indexes", (HANDLE)indexes);

		//2.5 ����ö �������� ����ö�� ������ ����Ѵ�.
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);

		//2.6 Ʈ������ ��Ʈ�� ã�´�.
		hRoot = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//2.7 ����ö �������� Ʈ���信�� ������ ��ȣ�� ���� ������ ã����
		if (index != NULL) {
			hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hRoot);
			tvItem.mask = TVIF_HANDLE | TVIF_TEXT;
			tvItem.pszText = companyName;
			tvItem.cchTextMax = 64;
			tvItem.hItem = hParent;
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
			while (hParent != NULL && strcmp(companyName, businessCardIndex->company.name) != 0) {
				hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hParent);
				tvItem.hItem = hParent;
				SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
			}

			//2.7.1 ã������ ����ö Ʈ���信 ������ �߰��Ѵ�.
			tvInsertStruct.hInsertAfter = TVI_LAST;
			tvInsertStruct.item.mask = TVIF_TEXT;
			if (hParent == NULL) {
				tvInsertStruct.hParent = hRoot;
				tvInsertStruct.item.pszText = businessCardIndex->company.name;
				tvInsertStruct.item.cchTextMax = 64;
				hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);
			}

			//2.7.2 �� ������ �ڽ����� ������ ������ �߰��Ѵ�.
			tvInsertStruct.hParent = hParent;
			tvInsertStruct.item.pszText = businessCardIndex->personal.name;
			tvInsertStruct.item.cchTextMax = 11;
			hChild = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);

			//2.8 Ʈ���信�� �ش� ��ġ�� ��ũ�Ѵ�.
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hChild);
		}
		//2.9 �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
	}
	return FALSE;
}

BOOL TakeInForm_OnCompanyNameEditLosesFocus(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HWND hBusinessCardBinderForm;
	TCHAR companyName[64];
	BusinessCardBinder *businessCardBinder;
	BusinessCard *index = NULL;

	if (HIWORD(wParam) == EN_KILLFOCUS)
	{
		//��ȣ���� �д´�
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)companyName);
		//����ö�����츦 ã�´�
		hBusinessCardBinderForm = FindWindow("#32770", "����ö");
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hBusinessCardBinderForm, GWL_USERDATA);
		index = BusinessCardBinder_FindByCompanyName(businessCardBinder, companyName);

		if (index != NULL) {
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);
		}
	}
	return FALSE;
}

BOOL TakeInForm_OnFindZipCodeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1 zipcode �����츦 ����
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_SEARCHINGFORM), hWnd, SearchingFormProc);
	}
	return FALSE;
}