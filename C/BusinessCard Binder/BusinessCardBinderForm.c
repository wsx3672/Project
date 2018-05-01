//BusinessCardBinderForm.c
#include "BusinessCardBinderForm.h"
#include "BusinessCardBinder.h"
#include "TakeInForm.h"
#include "TakeOutForm.h"
#include "FindingForm.h"
#include "Indexes.h"
#include "Index.h"
#include "resource.h"
#include <stdlib.h>
#include <Commctrl.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_BUSINESSCARDBINDERFORM), NULL, BusinessCardBinderFormProc);
	return response;
}

BOOL CALLBACK BusinessCardBinderFormProc(HWND hWnd, UINT messase, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (messase) {
	case WM_INITDIALOG:
		ret = BusinessCardBinderForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND:
		ret = BusinessCardBinderForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY:
		ret = BusinessCardBinderForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE:
		ret = BusinessCardBinderForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL BusinessCardBinderForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	BusinessCard *businessCardIndex;
	BusinessCard *previous = NULL;
	Indexes *indexes;
	Index *index;
	Index(*keys);
	Long count;
	Long position;
	Long i = 0;
	Long j = 0;
	HTREEITEM hitem;
	TVITEM tvitem = { 0, };
	TCHAR companyName[64];

	TVITEM item = { 0, };
	TVINSERTSTRUCT tvInsertStruct = { 0, };

	businessCardBinder = (BusinessCardBinder*)malloc(sizeof(BusinessCardBinder));
	indexes = (Indexes*)malloc(sizeof(Indexes));

	//1.1 명함철을 준비한다.
	BusinessCardBinder_Create(businessCardBinder);

	//1.2 색인철을 준비한다.
	Indexes_Create(indexes);

	SetWindowLong(hWnd, GWL_USERDATA, (LONG)businessCardBinder);
	SetProp(hWnd, "indexes", (HANDLE)indexes);

	//1.3 적재한다.
	BusinessCardBinder_Load(businessCardBinder);
	if (businessCardBinder->length != 0) {

		//1.4 처음으로 이동한다.
		businessCardIndex = BusinessCardBinder_First(businessCardBinder);

		//1.5 명함철의 처음부터 끝까지 반복한다.
		while (businessCardBinder->current != previous) {

			previous = businessCardBinder->current;

			//1.5.1 색인철에 색인을 넣는다.
			Indexes_TakeIn(indexes, businessCardBinder->current);

			BusinessCardBinder_Next(businessCardBinder);
		}

		//1.6 색인철을 정리한다.
		Indexes_Arrange(indexes);

		item.mask = TVIF_TEXT | TVIF_HANDLE;

		//1.7 트리뷰에 루트를 추가한다.
		item.pszText = "회사들";
		tvInsertStruct.hInsertAfter = TVI_ROOT;
		tvInsertStruct.item = item;

		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);

		//1.8 색인목록을 만든다.
		Indexes_MakeList(indexes, &keys, &count);

		tvInsertStruct.hInsertAfter = TVI_LAST;
		tvInsertStruct.item.mask = TVIF_TEXT;

		//1.9 count만큼 반복한다.
		while (i < count) {

			//1.9.1 트리뷰의 색인에 상호를 추가한다.
			tvInsertStruct.hParent = hitem;
			tvInsertStruct.item.pszText = keys[i].name;
			tvInsertStruct.item.cchTextMax = 64;
			tvInsertStruct.hParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);

			j = 0;
			//1.9.2 색인의 사용량만큼 반복한다.
			while (j < keys[i].length) {

				//1.9.2.1 상호의 하위항목으로 성명을 추가한다.
				businessCardIndex = Index_GetAt(keys + i, j);
				tvInsertStruct.item.pszText = businessCardIndex->personal.name;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);
				j++;
			}
			i++;
		}

		//1.10 처음으로 이동한다.
		businessCardIndex = BusinessCardBinder_First(businessCardBinder);

		//1.11 명함을 출력한다.
		if (businessCardIndex != NULL) {
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);
		}

		//1.12 현재위치의 명함의 상호로 색인철에서 찾는다.
		index = Indexes_Find(indexes, businessCardBinder->current->company.name);

		//1.13 찾은 색인에서 명함을 찾는다.
		position = Index_Find(index, businessCardIndex);

		//1.14 트리뷰에서 루트를 찾는다.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		///1.15 루트의 자식노드에서 상호를 찾는다.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		tvitem.mask = TVIF_HANDLE | TVIF_TEXT;
		tvitem.pszText = companyName;
		tvitem.cchTextMax = 64;
		while (strcmp(index->name, companyName) != 0) {
			tvitem.hItem = hitem;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvitem);
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			hitem = tvitem.hItem;
		}

		//1.16 찾은노드의 자식노드에서 찾은 명함위치의 항목을 찾는다.
		hitem = tvitem.hItem;
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		i = 0;
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}

		//1.17 해당항목을 마크한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
	}
	return FALSE;
}

BOOL BusinessCardBinderForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_TAKEIN:
		ret = BusinessCardBinderForm_OnTakeInButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIND:
		ret = BusinessCardBinderForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_TAKEOUT:
		ret = BusinessCardBinderForm_OnTakeOutButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ARRANGE:
		ret = BusinessCardBinderForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIRST:
		ret = BusinessCardBinderForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS:
		ret = BusinessCardBinderForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT:
		ret = BusinessCardBinderForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST:
		ret = BusinessCardBinderForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
//2. 넣기버튼을 클릭했을때
BOOL BusinessCardBinderForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1 넣기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_TAKEINFORM), NULL, TakeInFormProc);
	}

	return FALSE;
}
//3. 찾기버튼을 클릭했을때
BOOL BusinessCardBinderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1 찾기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}

	return FALSE;
}
//4. 빼기버튼을 클릭했을때
BOOL BusinessCardBinderForm_OnTakeOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1 빼기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_TAKEOUTFORM), NULL, TakeOutFormProc);
	}

	return FALSE;
}
// 정리하기버튼을 클릭했을때
BOOL BusinessCardBinderForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBinder *businessCardBinder;
	BusinessCard *businessCardIndex;
	Indexes *indexes;
	Index *index;
	Index(*keys);
	Long position;
	Long count;
	Long i = 0;
	Long j = 0;
	TCHAR companyName[64];
	HTREEITEM hitem;
	TVITEM tvitem = { 0, };
	TVINSERTSTRUCT tvInsertStruct = { 0, };

	if (HIWORD(wParam) == BN_CLICKED) {
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexes = (Indexes*)GetProp(hWnd, "indexes");

		//5.1 색인철을 정리한다.
		Indexes_Arrange(indexes);

		//5.2 색인목록을 만든다.
		Indexes_MakeList(indexes, &keys, &count);

		//5.3 트리뷰의 모든 항목을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_DELETEITEM, (WPARAM)0, (LPARAM)TVI_ROOT);

		//5.4 트리뷰에 루트를 추가한다.
		tvInsertStruct.hInsertAfter = TVI_ROOT;
		tvInsertStruct.item.mask = TVIF_TEXT;
		tvInsertStruct.item.pszText = "회사들";
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);

		tvInsertStruct.hInsertAfter = TVI_LAST;
		//5.5 count만큼 반복한다.
		while (i < count) {

			//5.5.1 트리뷰에 색인의 상호를 추가한다.
			tvInsertStruct.hParent = hitem;
			tvInsertStruct.item.pszText = keys[i].name;
			tvInsertStruct.hParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);

			//5.5.2 색인의 사용량만큼 반복한다.
			j = 0;
			while (j < keys[i].length) {

				//5.5.2.1 상호의 하위목록으로 성명을 추가한다.
				businessCardIndex = Index_GetAt(keys + i, j);
				tvInsertStruct.item.pszText = businessCardIndex->personal.name;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);
				j++;
			}
			i++;
		}

		//5.6 첫번째 위치의 명함을 출력한다.
		businessCardIndex = BusinessCardBinder_First(businessCardBinder);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);

		//5.7 현재위치의 명함의 상호로 색인철에서 찾는다.
		index = Indexes_Find(indexes, businessCardBinder->current->company.name);

		//5.8 찾은 색인에서 명함을 찾는다.
		position = Index_Find(index, businessCardIndex);

		//5.9 트리뷰에서 루트를 찾는다.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//5.10 루트의 자식노드에서 상호를 찾는다.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		tvitem.mask = TVIF_HANDLE | TVIF_TEXT;
		tvitem.pszText = companyName;
		tvitem.cchTextMax = 64;
		while (strcmp(index->name, companyName) != 0) {
			tvitem.hItem = hitem;
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvitem);
			hitem = tvitem.hItem;
		}

		//찾은노드의 자식노드에서 찾은 명함위치의 항목을 찾는다.
		hitem = tvitem.hItem;
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		i = 0;
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}

		//해당항목을 마크한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
	}

	return FALSE;
}
//6. 처음버튼이 클릭 되었을때
BOOL BusinessCardBinderForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BusinessCardBinder *businessCardBinder;
	BusinessCard *businessCardIndex;
	Indexes *indexes;
	Index *index;
	Long position;
	Long i = 0;
	TCHAR companyName[64];
	HTREEITEM hitem;
	TVITEM tvitem = { 0, };

	if (HIWORD(wParam) == BN_CLICKED) {
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexes = (Indexes*)GetProp(hWnd, "indexes");

		//6.1 처음으로 이동한다.
		businessCardIndex = BusinessCardBinder_First(businessCardBinder);

		//6.2 현재위치의 명함을 명함철윈도우의 명함에 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);

		//6.3 현재위치의 명함의 상호로 색인철에서 찾는다.
		index = Indexes_Find(indexes, businessCardBinder->current->company.name);

		//6.4 찾은 색인에서 명함을 찾는다.
		position = Index_Find(index, businessCardIndex);

		//6.5 트리뷰에서 루트를 찾는다.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//6.6 루트의 자식노드에서 상호를 찾는다.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		tvitem.mask = TVIF_HANDLE | TVIF_TEXT;
		tvitem.pszText = companyName;
		tvitem.cchTextMax = 64;
		while (strcmp(index->name, companyName) != 0) {
			tvitem.hItem = hitem;
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvitem);
		}

		//6.7 찾은노드의 자식노드에서 찾은 명함위치의 항목을 찾는다.
		hitem = tvitem.hItem;
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}

		//6.8 해당항목을 마크한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
	}

	return FALSE;
}
//7. 이전버튼이 클릭 되었을때
BOOL BusinessCardBinderForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	BusinessCardBinder *businessCardBinder;
	BusinessCard *businessCardIndex;
	Indexes *indexes;
	Index *index;
	Long position;
	Long i = 0;
	TCHAR companyName[64];
	HTREEITEM hitem;
	TVITEM tvitem = { 0, };

	if (HIWORD(wParam) == BN_CLICKED) {
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexes = (Indexes*)GetProp(hWnd, "indexes");

		//7.1 이전으로 이동한다.
		businessCardIndex = BusinessCardBinder_Previous(businessCardBinder);

		//7.2 현재위치의 명함을 명함철윈도우의 명함에 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);

		//7.3 현재위치의 명함의 상호로 색인철에서 찾는다.
		index = Indexes_Find(indexes, businessCardBinder->current->company.name);

		//7.4 찾은 색인에서 명함을 찾는다.
		position = Index_Find(index, businessCardIndex);

		//7.5 트리뷰에서 루트를 찾는다.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//7.6 루트의 자식노드에서 상호를 찾는다.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		tvitem.mask = TVIF_HANDLE | TVIF_TEXT;
		tvitem.pszText = companyName;
		tvitem.cchTextMax = 64;
		while (strcmp(index->name, companyName) != 0) {
			tvitem.hItem = hitem;
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvitem);
		}

		//7.7 찾은노드의 자식노드에서 찾은 명함위치의 항목을 찾는다.
		hitem = tvitem.hItem;
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		i = 0;
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}

		//7.8 해당항목을 마크한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
	}

	return FALSE;
}
//8. 다음버튼이 클릭 되었을때
BOOL BusinessCardBinderForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	BusinessCard *businessCardIndex;
	Indexes *indexes;
	Index *index;
	Long position;
	TCHAR companyName[64];
	Long i = 0;
	TVITEM tvitem = { 0, };
	HTREEITEM hitem;

	if (HIWORD(wParam) == BN_CLICKED) {
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexes = (Indexes*)GetProp(hWnd, "indexes");

		//8.1 다음으로 이동한다.
		businessCardIndex = BusinessCardBinder_Next(businessCardBinder);

		//8.2 현재위치의 명함을 명함철윈도우의 명함에 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);

		//8.3 현재위치의 명함의 상호로 색인철에서 찾는다.
		index = Indexes_Find(indexes, businessCardBinder->current->company.name);

		//8.4 찾은 색인에서 명함을 찾는다.
		position = Index_Find(index, businessCardIndex);

		//8.5 트리뷰에서 루트를 찾는다.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//8.6 루트의 자식노드에서 상호를 찾는다.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		tvitem.mask = TVIF_HANDLE | TVIF_TEXT;
		tvitem.pszText = companyName;
		tvitem.cchTextMax = 64;
		while (strcmp(index->name, companyName) != 0) {
			tvitem.hItem = hitem;
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvitem);
		}

		//8.7 찾은노드의 자식노드에서 찾은 명함위치의 항목을 찾는다.
		hitem = tvitem.hItem;
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		i = 0;
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}

		//8.8 해당항목을 마크한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
	}

	return FALSE;
}
//9. 마지막버튼이 클릭 되었을때
BOOL BusinessCardBinderForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	BusinessCard *businessCardIndex;
	HTREEITEM hitem;
	Indexes *indexes;
	Index *index;
	Long position;
	Long i;
	TCHAR companyName[64];
	TVITEM tvItem = { 0, };

	if (HIWORD(wParam) == BN_CLICKED) {
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexes = GetProp(hWnd, "indexes");

		//9.1 마지막으로 이동한다.
		businessCardIndex = BusinessCardBinder_Last(businessCardBinder);

		//9.2 현재위치의 명함을 명함철윈도우의 명함에 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);

		//9.3 현재위치의 명함의 상호로 색인철에서 찾는다.
		index = Indexes_Find(indexes, businessCardBinder->current->company.name);

		//9.4 찾은 색인에서 명함을 찾는다.
		position = Index_Find(index, businessCardIndex);

		//9.5 트리뷰에서 루트를 찾는다.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//9.6 루트의 자식노드에서 상호를 찾는다.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		tvItem.mask = TVIF_HANDLE | TVIF_TEXT;
		tvItem.pszText = companyName;
		tvItem.cchTextMax = 64;
		while (strcmp(index->name, companyName) != 0) {
			tvItem.hItem = hitem;
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
		}

		//9.7 찾은노드의 자식노드에서 찾은 명함위치의 항목을 찾는다.
		hitem = tvItem.hItem;
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		i = 0;
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}
		//9.8 해당항목을 마크한다.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
	}

	return FALSE;
}

BOOL BusinessCardBinderForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (wParam) {
	case IDC_TREE_COMPANIES:
		ret = BusinessCardBinderForm_OnTreeViewItemDoubleClicked(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}
// 10. 트리뷰의 항목을 더블클릭 했을때
BOOL BusinessCardBinderForm_OnTreeViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	BusinessCard *businessCardIndex;
	Indexes *indexes;
	Index *index;
	Long position = 0;
	TCHAR companyName[64];
	HTREEITEM hParent;
	HTREEITEM hChild;
	HTREEITEM hitem;
	TVITEM tvItem = { 0, };

	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexes = (Indexes*)GetProp(hWnd, "indexes");

		//10.1 선택된 항목의 위치를 읽는다.

		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CARET, (LPARAM)0);

		//10.2 읽은 위치의 부모를 읽는다.

		hParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_PARENT, (LPARAM)hitem);

		//10.3 부모의 항목을 읽는다.

		tvItem.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.pszText = companyName;
		tvItem.cchTextMax = 64;
		tvItem.hItem = hParent;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);

		//10.4 부모항목에서 선택된 항목이 몇번재 위치인지 찾는다.
		hChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hParent);
		while (hChild != hitem) {
			position++;
			hChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hChild);
		}

		//10.5 상호로 색인철에서 찾는다.
		index = Indexes_Find(indexes, companyName);

		//10.6 색인에서 찾은 위치의 명함을 읽는다.
		businessCardIndex = Index_GetAt(index, position);
		businessCardBinder->current = businessCardIndex;

		//10.7 명함철의 명함에 찾은 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);
	}
	return FALSE;
}
// 11.닫기버튼을 클릭했을때
BOOL BusinessCardBinderForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	Indexes *indexes;


	indexes = (Indexes*)GetProp(hWnd, "indexes");
	if (indexes != NULL) {
		//11.1 색인철을 지운다.
		Indexes_Destroy(indexes);
		RemoveProp(hWnd, "indexes");
		free(indexes);
	}
	businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
	if (businessCardBinder != NULL) {
		//11.2 저장한다.
		BusinessCardBinder_Save(businessCardBinder);
		//11.3 명함철을 지운다.
		BusinessCardBinder_Destroy(businessCardBinder);
		free(businessCardBinder);
	}
	//11.4 윈도우를 닫는다
	EndDialog(hWnd, 0);
	return FALSE;
}