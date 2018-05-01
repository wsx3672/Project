//TakeOutForm.c
#include "TakeOutForm.h"
#include "BusinessCardBinder.h"
#include "Index.h"
#include "Indexes.h"
#include "resource.h"
#include <stdio.h>
#include <Commctrl.h>
#pragma warning(disable:4996)

BOOL CALLBACK TakeOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG:
		ret = TakeOutForm_OnInitDiaglog(hWnd, wParam, lParam); break;
	case WM_CLOSE:
		ret = TakeOutForm_OnClose(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}

BOOL TakeOutForm_OnInitDiaglog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	BusinessCard businessCard;
	BusinessCard *businessCardIndex;
	Indexes *indexes;
	Index *index;
	Long position;
	Long i;
	HWND hBusinessCardBinderForm;
	HTREEITEM hRoot;
	HTREEITEM hParent;
	HTREEITEM hitem;
	TCHAR companyName[64];

	TVITEM tvItem = { 0, };
	TVINSERTSTRUCT tvInsertStruct = { 0, };
	 
	//1.1 ����ö�����츦 ã�´�
	hBusinessCardBinderForm = FindWindow("#32770", "����ö");
	businessCardBinder = (BusinessCardBinder*)GetWindowLong(hBusinessCardBinderForm, GWL_USERDATA);

	//1.2 ������ġ�� �д´�
	businessCardIndex = businessCardBinder->current;
	//���⿡�� �̸� ��ġ �ٲ������ �� �ڸ� ��������, �׿ܿ� ��������
	if (businessCardBinder->current == BusinessCardBinder_Next(&businessCardBinder->businessCards)) {
		businessCardBinder->current = BusinessCardBinder_Previous(&businessCardBinder->businessCards);
	}
	else {
		businessCardBinder->current = BusinessCardBinder_Next(&businessCardBinder->businessCards);
	}

	//1.3 ������ġ�� ������ �����������Ǹ���ö���� ����
	businessCard = BusinessCardBinder_TakeOut(businessCardBinder, businessCardIndex);

	//+�� ������ ����Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.emailAddress);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.faxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.url);

	//1.5 ����ö �����쿡 �ִ� ����ö���� ��ȣ�� ������ �ּҸ� ã�´�.
	indexes = (Indexes*)GetProp(hBusinessCardBinderForm, "indexes");
	index = Indexes_Find(indexes, businessCard.company.name); //�� ���Կ��� ��ȣ�� �̿�(�ּ� x) �ؼ� ������ ã�´�

	//1.7 ����ö �������� Ʈ���信�� root�� ã�´�.
	hRoot = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

	//1.8 ��ȣ�׸�� ���� ��ȣ�� ���������� �ݺ��Ѵ�.
	//if (index != NULL) { //�� ������ ��ȣ�� ������?

		hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hRoot);
		tvItem.mask = TVIF_HANDLE | TVIF_TEXT;
		tvItem.pszText = companyName;
		tvItem.cchTextMax = 64;
		tvItem.hItem = hParent;

		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
		while (hParent != NULL && strcmp(companyName, businessCard.company.name) != 0) {
			hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hParent);
			tvItem.hItem = hParent;
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
		}

		hitem = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hParent);
		i = 0;
		//1.6 ã�� ������ �ּҿ� ������ġ�� ���ο� �ִ� ������ ��ġ�� ã�´�.
		position = Index_Find(index, businessCardIndex);

		//1.9 ��ȣ�׸��� �ڵ��� ��ġ�� ���´�.
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}

		//1.10 �ڵ��� ������ ������ ����.
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_DELETEITEM, (WPARAM)0, (LPARAM)hitem);

		//1.11 ����ö �����쿡 �ִ� ����ö���� ���� ��ġ�� ��ȣ�� ������ �ּҸ� �����.
		index = Indexes_TakeOut(indexes, businessCardIndex, companyName);

		SetProp(hWnd, "indexes", (HANDLE)indexes);

		//������ �ּҸ� Index ���� ����� ���� �����ּҹ迭�� �� Indexes ���� �������� Ȯ���ؼ�,
		//1.12 ������ �������� Ʈ���信 �ִ� ��ȣ�� ����.
		if (index == NULL) {
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_DELETEITEM, (WPARAM)0, (LPARAM)hParent);

			//���Կ��� �ϴ� ��ĭ���?
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		}


		//1.13.1 ��������� ������ ����ö �����쿡 ������ ������ġ�� ������ ����Ѵ�.
		else {
			businessCardIndex = businessCardBinder->current; //��ġ �ٲ������

			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.telephoneNumber);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.emailAddress);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.telephoneNumber);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.faxNumber);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.url);

			//1.13.2 ����ö�����쿡 �ִ� ����ö���� ��ȣ�� ������ �ּҸ� ã�´�.
			index = Indexes_Find(indexes, businessCard.company.name);

			//1.13.3 ã�� ������ �ּҿ� ���� ��ġ�� ���ο� �ִ� ������ ��ġ�� ã�´�.
			position = Index_Find(index, businessCardIndex);

			//1.13.4 ��ȣ�� �׸�� ���� ��ȣ�� ���������� �ݺ��Ѵ�.
			if (index != NULL) {
				hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hRoot);
				tvItem.pszText = companyName;
				tvItem.cchTextMax = 64;
				tvItem.hItem = hParent;
				SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);

				while (hParent != NULL && strcmp(companyName, businessCardIndex->company.name) != 0) {
					hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hParent);
					tvItem.hItem = hParent;
					SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
				}

				hitem = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hParent);
				i = 0;

				//1.13.5 ��ȣ�׸��� �ڵ��� ��ġ�� ���´�.
				while (i < position) {
					hitem = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
					i++;
				}

				//1.13.6 �ڵ��� ������ ������ ��ũ�Ѵ�.
				SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
				SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
			}
		}
	//}

	//1.14 ��ȣ�� ������ �� ������ ����Ѵ�. //�ʿ������?
	/* {
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	}*/
	return FALSE;
}

BOOL TakeOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	BusinessCard businessCard = { 0, };
	BusinessCard *businessCardIndex;
	Indexes *indexes;
	Index *index;
	TCHAR companyName[64];
	int result;
	HWND hBusinessCardBinderForm;
	HTREEITEM hRoot;
	HTREEITEM hParent;
	HTREEITEM hitem;

	TVINSERTSTRUCT tvInsertStruct = { 0, };
	TVITEM tvItem = { 0, };

	//2.1 �޼��� �ڽ��� ����Ѵ�.
	result = MessageBox(hWnd, "�ٽ� ����ðڽ��ϱ�?", "Ȯ��", MB_YESNOCANCEL | MB_ICONWARNING);
	//2.2 "��"�� Ŭ���ϸ� ����ö ������ ���Կ� ����Ѵ�.
	if (result == IDYES)
	{
		//2.3 ����ö �����츦 ã�´�.
		hBusinessCardBinderForm = FindWindow("#32770", "����ö");
		businessCardBinder = (BusinessCardBinder(*))GetWindowLong(hBusinessCardBinderForm, GWL_USERDATA);
		indexes = (Indexes*)GetProp(hBusinessCardBinderForm, "indexes");

		//2.4 �̱��������� ������ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)128, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_GETTEXT, (WPARAM)256, (LPARAM)businessCard.company.url);

		//2.6 ����ö �������� ����ö�� �ٽ� �����.
		businessCardIndex = BusinessCardBinder_TakeIn(businessCardBinder, businessCard);

		//2.5 ����ö �������� ���Կ� ���� ������ ����Ѵ�.
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);

		//2.7 ��ȣ�� �д´�.
		strcpy(companyName, businessCardIndex->company.name);

		//2.8 ������ġ�� ��ȣ�� ����ö�� �����.
		index = Indexes_TakeIn(indexes, businessCardIndex);

		SetProp(hWnd, "indexes", (HANDLE)indexes);

		//2.9  ����ö �������� Ʈ���信�� root�� ã�´�.
		hRoot = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//if (index != NULL) { �ʿ������?

			hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hRoot);
			tvItem.mask = TVIF_HANDLE | TVIF_TEXT;
			tvItem.pszText = companyName;
			tvItem.cchTextMax = 64;
			tvItem.hItem = hParent;

			//2.10 Ʈ���信�� ��ȣ�� ã�´�
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
			while (hParent != NULL && strcmp(companyName, businessCardIndex->company.name) != 0) {
				hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hParent);
				tvItem.hItem = hParent;
				SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
			}

			//2.11 Ʈ������ ���ο� ��ȣ�� �ִ´�.
			tvInsertStruct.hInsertAfter = TVI_LAST;
			tvInsertStruct.item.mask = TVIF_TEXT;
			
			if (hParent == NULL) { //Ʈ���信 ��ȣ�� ������ ��ȣ ������ش�
				tvInsertStruct.hParent = hRoot;
				tvInsertStruct.item.pszText = businessCardIndex->company.name;
				tvInsertStruct.item.cchTextMax = 64;
				hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);
			}

			//ã�� ��ȣ || ���� ��ȣ �������� ������ ���´�
			tvInsertStruct.hParent = hParent;
			tvInsertStruct.item.pszText = businessCardIndex->personal.name;
			tvInsertStruct.item.cchTextMax = 11;
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);

			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
		//}

		EndDialog(hWnd, 0);
	}

	//"�ƴϿ�"�� ����� ������ �ݴ´�.
	else if (result == IDNO)
	{
		EndDialog(hWnd, 0);
	}

	return FALSE;
}