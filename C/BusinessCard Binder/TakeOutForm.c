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
	 
	//1.1 명함철윈도우를 찾는다
	hBusinessCardBinderForm = FindWindow("#32770", "명함철");
	businessCardBinder = (BusinessCardBinder*)GetWindowLong(hBusinessCardBinderForm, GWL_USERDATA);

	//1.2 현재위치를 읽는다
	businessCardIndex = businessCardBinder->current;
	//여기에서 미리 위치 바꿔줘야함 맨 뒤면 이전으로, 그외엔 다음으로
	if (businessCardBinder->current == BusinessCardBinder_Next(&businessCardBinder->businessCards)) {
		businessCardBinder->current = BusinessCardBinder_Previous(&businessCardBinder->businessCards);
	}
	else {
		businessCardBinder->current = BusinessCardBinder_Next(&businessCardBinder->businessCards);
	}

	//1.3 현재위치의 명함을 명함윈도우의명함철에서 뺀다
	businessCard = BusinessCardBinder_TakeOut(businessCardBinder, businessCardIndex);

	//+뺀 명함을 출력한다.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.emailAddress);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.faxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.url);

	//1.5 명함철 윈도우에 있는 색인철에서 상호로 색인의 주소를 찾는다.
	indexes = (Indexes*)GetProp(hBusinessCardBinderForm, "indexes");
	index = Indexes_Find(indexes, businessCard.company.name); //뺀 명함에서 상호를 이용(주소 x) 해서 색인을 찾는다

	//1.7 명함철 윈도우의 트리뷰에서 root를 찾는다.
	hRoot = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

	//1.8 상호항목과 읽은 상호가 같을때까지 반복한다.
	//if (index != NULL) { //뺀 명함의 상호가 있으면?

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
		//1.6 찾은 색인의 주소와 현재위치를 색인에 있는 명함의 위치를 찾는다.
		position = Index_Find(index, businessCardIndex);

		//1.9 상호항목의 핸들의 위치를 갖는다.
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}

		//1.10 핸들을 가지는 성명을 뺀다.
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_DELETEITEM, (WPARAM)0, (LPARAM)hitem);

		//1.11 명함철 윈도우에 있는 색인철에서 현재 위치와 상호로 명함의 주소를 지운다.
		index = Indexes_TakeOut(indexes, businessCardIndex, companyName);

		SetProp(hWnd, "indexes", (HANDLE)indexes);

		//명함의 주소를 Index 에서 지우고 나서 명함주소배열이 비어서 Indexes 까지 빠졌는지 확인해서,
		//1.12 색인이 빠졌으면 트리뷰에 있는 상호를 뺀다.
		if (index == NULL) {
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_DELETEITEM, (WPARAM)0, (LPARAM)hParent);

			//명함에는 일단 빈칸출력?
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


		//1.13.1 현재명함이 있으면 명함철 윈도우에 명함이 현재위치의 명함을 출력한다.
		else {
			businessCardIndex = businessCardBinder->current; //위치 바꿔줘야함

			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.telephoneNumber);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.emailAddress);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.telephoneNumber);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.faxNumber);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.url);

			//1.13.2 명함철윈도우에 있는 색인철에서 상호로 색인의 주소를 찾는다.
			index = Indexes_Find(indexes, businessCard.company.name);

			//1.13.3 찾은 색인의 주소와 현재 위치로 색인에 있는 명함의 위치를 찾는다.
			position = Index_Find(index, businessCardIndex);

			//1.13.4 상호의 항목과 읽은 상호가 같을때까지 반복한다.
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

				//1.13.5 상호항목의 핸들의 위치를 갖는다.
				while (i < position) {
					hitem = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
					i++;
				}

				//1.13.6 핸들을 가지는 성명을 마크한다.
				SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
				SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
			}
		}
	//}

	//1.14 상호가 없으면 빈 명함을 출력한다. //필요없을듯?
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

	//2.1 메세지 박스를 출력한다.
	result = MessageBox(hWnd, "다시 끼우시겠습니까?", "확인", MB_YESNOCANCEL | MB_ICONWARNING);
	//2.2 "예"를 클릭하면 명함철 윈도우 명함에 출력한다.
	if (result == IDYES)
	{
		//2.3 명함철 윈도우를 찾는다.
		hBusinessCardBinderForm = FindWindow("#32770", "명함철");
		businessCardBinder = (BusinessCardBinder(*))GetWindowLong(hBusinessCardBinderForm, GWL_USERDATA);
		indexes = (Indexes*)GetProp(hBusinessCardBinderForm, "indexes");

		//2.4 뽑기윈도우의 명함을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)128, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_GETTEXT, (WPARAM)256, (LPARAM)businessCard.company.url);

		//2.6 명함철 윈도우의 명함철에 다시 끼운다.
		businessCardIndex = BusinessCardBinder_TakeIn(businessCardBinder, businessCard);

		//2.5 명함철 윈도우의 명함에 읽은 명함을 출력한다.
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);

		//2.7 상호를 읽는다.
		strcpy(companyName, businessCardIndex->company.name);

		//2.8 현재위치와 상호로 색인철에 끼운다.
		index = Indexes_TakeIn(indexes, businessCardIndex);

		SetProp(hWnd, "indexes", (HANDLE)indexes);

		//2.9  명함철 윈도우의 트리뷰에서 root를 찾는다.
		hRoot = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//if (index != NULL) { 필요없을듯?

			hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hRoot);
			tvItem.mask = TVIF_HANDLE | TVIF_TEXT;
			tvItem.pszText = companyName;
			tvItem.cchTextMax = 64;
			tvItem.hItem = hParent;

			//2.10 트리뷰에서 상호를 찾는다
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
			while (hParent != NULL && strcmp(companyName, businessCardIndex->company.name) != 0) {
				hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hParent);
				tvItem.hItem = hParent;
				SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
			}

			//2.11 트리뷰의 색인에 상호를 넣는다.
			tvInsertStruct.hInsertAfter = TVI_LAST;
			tvInsertStruct.item.mask = TVIF_TEXT;
			
			if (hParent == NULL) { //트리뷰에 상호가 없으면 상호 만들어준다
				tvInsertStruct.hParent = hRoot;
				tvInsertStruct.item.pszText = businessCardIndex->company.name;
				tvInsertStruct.item.cchTextMax = 64;
				hParent = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);
			}

			//찾은 상호 || 만든 상호 하위노드로 성명을 적는다
			tvInsertStruct.hParent = hParent;
			tvInsertStruct.item.pszText = businessCardIndex->personal.name;
			tvInsertStruct.item.cchTextMax = 11;
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);

			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
			SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
		//}

		EndDialog(hWnd, 0);
	}

	//"아니오"를 누루면 윈도를 닫는다.
	else if (result == IDNO)
	{
		EndDialog(hWnd, 0);
	}

	return FALSE;
}