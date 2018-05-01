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

	//1.1 ����ö�� �غ��Ѵ�.
	BusinessCardBinder_Create(businessCardBinder);

	//1.2 ����ö�� �غ��Ѵ�.
	Indexes_Create(indexes);

	SetWindowLong(hWnd, GWL_USERDATA, (LONG)businessCardBinder);
	SetProp(hWnd, "indexes", (HANDLE)indexes);

	//1.3 �����Ѵ�.
	BusinessCardBinder_Load(businessCardBinder);
	if (businessCardBinder->length != 0) {

		//1.4 ó������ �̵��Ѵ�.
		businessCardIndex = BusinessCardBinder_First(businessCardBinder);

		//1.5 ����ö�� ó������ ������ �ݺ��Ѵ�.
		while (businessCardBinder->current != previous) {

			previous = businessCardBinder->current;

			//1.5.1 ����ö�� ������ �ִ´�.
			Indexes_TakeIn(indexes, businessCardBinder->current);

			BusinessCardBinder_Next(businessCardBinder);
		}

		//1.6 ����ö�� �����Ѵ�.
		Indexes_Arrange(indexes);

		item.mask = TVIF_TEXT | TVIF_HANDLE;

		//1.7 Ʈ���信 ��Ʈ�� �߰��Ѵ�.
		item.pszText = "ȸ���";
		tvInsertStruct.hInsertAfter = TVI_ROOT;
		tvInsertStruct.item = item;

		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);

		//1.8 ���θ���� �����.
		Indexes_MakeList(indexes, &keys, &count);

		tvInsertStruct.hInsertAfter = TVI_LAST;
		tvInsertStruct.item.mask = TVIF_TEXT;

		//1.9 count��ŭ �ݺ��Ѵ�.
		while (i < count) {

			//1.9.1 Ʈ������ ���ο� ��ȣ�� �߰��Ѵ�.
			tvInsertStruct.hParent = hitem;
			tvInsertStruct.item.pszText = keys[i].name;
			tvInsertStruct.item.cchTextMax = 64;
			tvInsertStruct.hParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);

			j = 0;
			//1.9.2 ������ ��뷮��ŭ �ݺ��Ѵ�.
			while (j < keys[i].length) {

				//1.9.2.1 ��ȣ�� �����׸����� ������ �߰��Ѵ�.
				businessCardIndex = Index_GetAt(keys + i, j);
				tvInsertStruct.item.pszText = businessCardIndex->personal.name;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);
				j++;
			}
			i++;
		}

		//1.10 ó������ �̵��Ѵ�.
		businessCardIndex = BusinessCardBinder_First(businessCardBinder);

		//1.11 ������ ����Ѵ�.
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

		//1.12 ������ġ�� ������ ��ȣ�� ����ö���� ã�´�.
		index = Indexes_Find(indexes, businessCardBinder->current->company.name);

		//1.13 ã�� ���ο��� ������ ã�´�.
		position = Index_Find(index, businessCardIndex);

		//1.14 Ʈ���信�� ��Ʈ�� ã�´�.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		///1.15 ��Ʈ�� �ڽĳ�忡�� ��ȣ�� ã�´�.
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

		//1.16 ã������� �ڽĳ�忡�� ã�� ������ġ�� �׸��� ã�´�.
		hitem = tvitem.hItem;
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		i = 0;
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}

		//1.17 �ش��׸��� ��ũ�Ѵ�.
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
//2. �ֱ��ư�� Ŭ��������
BOOL BusinessCardBinderForm_OnTakeInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1 �ֱ� �����츦 ����Ѵ�.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_TAKEINFORM), NULL, TakeInFormProc);
	}

	return FALSE;
}
//3. ã���ư�� Ŭ��������
BOOL BusinessCardBinderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1 ã�� �����츦 ����Ѵ�.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}

	return FALSE;
}
//4. �����ư�� Ŭ��������
BOOL BusinessCardBinderForm_OnTakeOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1 ���� �����츦 ����Ѵ�.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_TAKEOUTFORM), NULL, TakeOutFormProc);
	}

	return FALSE;
}
// �����ϱ��ư�� Ŭ��������
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

		//5.1 ����ö�� �����Ѵ�.
		Indexes_Arrange(indexes);

		//5.2 ���θ���� �����.
		Indexes_MakeList(indexes, &keys, &count);

		//5.3 Ʈ������ ��� �׸��� �����.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_DELETEITEM, (WPARAM)0, (LPARAM)TVI_ROOT);

		//5.4 Ʈ���信 ��Ʈ�� �߰��Ѵ�.
		tvInsertStruct.hInsertAfter = TVI_ROOT;
		tvInsertStruct.item.mask = TVIF_TEXT;
		tvInsertStruct.item.pszText = "ȸ���";
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);

		tvInsertStruct.hInsertAfter = TVI_LAST;
		//5.5 count��ŭ �ݺ��Ѵ�.
		while (i < count) {

			//5.5.1 Ʈ���信 ������ ��ȣ�� �߰��Ѵ�.
			tvInsertStruct.hParent = hitem;
			tvInsertStruct.item.pszText = keys[i].name;
			tvInsertStruct.hParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);

			//5.5.2 ������ ��뷮��ŭ �ݺ��Ѵ�.
			j = 0;
			while (j < keys[i].length) {

				//5.5.2.1 ��ȣ�� ����������� ������ �߰��Ѵ�.
				businessCardIndex = Index_GetAt(keys + i, j);
				tvInsertStruct.item.pszText = businessCardIndex->personal.name;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvInsertStruct);
				j++;
			}
			i++;
		}

		//5.6 ù��° ��ġ�� ������ ����Ѵ�.
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

		//5.7 ������ġ�� ������ ��ȣ�� ����ö���� ã�´�.
		index = Indexes_Find(indexes, businessCardBinder->current->company.name);

		//5.8 ã�� ���ο��� ������ ã�´�.
		position = Index_Find(index, businessCardIndex);

		//5.9 Ʈ���信�� ��Ʈ�� ã�´�.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//5.10 ��Ʈ�� �ڽĳ�忡�� ��ȣ�� ã�´�.
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

		//ã������� �ڽĳ�忡�� ã�� ������ġ�� �׸��� ã�´�.
		hitem = tvitem.hItem;
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		i = 0;
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}

		//�ش��׸��� ��ũ�Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
	}

	return FALSE;
}
//6. ó����ư�� Ŭ�� �Ǿ�����
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

		//6.1 ó������ �̵��Ѵ�.
		businessCardIndex = BusinessCardBinder_First(businessCardBinder);

		//6.2 ������ġ�� ������ ����ö�������� ���Կ� ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);

		//6.3 ������ġ�� ������ ��ȣ�� ����ö���� ã�´�.
		index = Indexes_Find(indexes, businessCardBinder->current->company.name);

		//6.4 ã�� ���ο��� ������ ã�´�.
		position = Index_Find(index, businessCardIndex);

		//6.5 Ʈ���信�� ��Ʈ�� ã�´�.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//6.6 ��Ʈ�� �ڽĳ�忡�� ��ȣ�� ã�´�.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		tvitem.mask = TVIF_HANDLE | TVIF_TEXT;
		tvitem.pszText = companyName;
		tvitem.cchTextMax = 64;
		while (strcmp(index->name, companyName) != 0) {
			tvitem.hItem = hitem;
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvitem);
		}

		//6.7 ã������� �ڽĳ�忡�� ã�� ������ġ�� �׸��� ã�´�.
		hitem = tvitem.hItem;
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}

		//6.8 �ش��׸��� ��ũ�Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
	}

	return FALSE;
}
//7. ������ư�� Ŭ�� �Ǿ�����
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

		//7.1 �������� �̵��Ѵ�.
		businessCardIndex = BusinessCardBinder_Previous(businessCardBinder);

		//7.2 ������ġ�� ������ ����ö�������� ���Կ� ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);

		//7.3 ������ġ�� ������ ��ȣ�� ����ö���� ã�´�.
		index = Indexes_Find(indexes, businessCardBinder->current->company.name);

		//7.4 ã�� ���ο��� ������ ã�´�.
		position = Index_Find(index, businessCardIndex);

		//7.5 Ʈ���信�� ��Ʈ�� ã�´�.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//7.6 ��Ʈ�� �ڽĳ�忡�� ��ȣ�� ã�´�.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		tvitem.mask = TVIF_HANDLE | TVIF_TEXT;
		tvitem.pszText = companyName;
		tvitem.cchTextMax = 64;
		while (strcmp(index->name, companyName) != 0) {
			tvitem.hItem = hitem;
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvitem);
		}

		//7.7 ã������� �ڽĳ�忡�� ã�� ������ġ�� �׸��� ã�´�.
		hitem = tvitem.hItem;
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		i = 0;
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}

		//7.8 �ش��׸��� ��ũ�Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
	}

	return FALSE;
}
//8. ������ư�� Ŭ�� �Ǿ�����
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

		//8.1 �������� �̵��Ѵ�.
		businessCardIndex = BusinessCardBinder_Next(businessCardBinder);

		//8.2 ������ġ�� ������ ����ö�������� ���Կ� ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);

		//8.3 ������ġ�� ������ ��ȣ�� ����ö���� ã�´�.
		index = Indexes_Find(indexes, businessCardBinder->current->company.name);

		//8.4 ã�� ���ο��� ������ ã�´�.
		position = Index_Find(index, businessCardIndex);

		//8.5 Ʈ���信�� ��Ʈ�� ã�´�.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//8.6 ��Ʈ�� �ڽĳ�忡�� ��ȣ�� ã�´�.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		tvitem.mask = TVIF_HANDLE | TVIF_TEXT;
		tvitem.pszText = companyName;
		tvitem.cchTextMax = 64;
		while (strcmp(index->name, companyName) != 0) {
			tvitem.hItem = hitem;
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvitem);
		}

		//8.7 ã������� �ڽĳ�忡�� ã�� ������ġ�� �׸��� ã�´�.
		hitem = tvitem.hItem;
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		i = 0;
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}

		//8.8 �ش��׸��� ��ũ�Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), WM_SETFOCUS, (WPARAM)NULL, (LPARAM)NULL);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hitem);
	}

	return FALSE;
}
//9. ��������ư�� Ŭ�� �Ǿ�����
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

		//9.1 ���������� �̵��Ѵ�.
		businessCardIndex = BusinessCardBinder_Last(businessCardBinder);

		//9.2 ������ġ�� ������ ����ö�������� ���Կ� ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardIndex->company.url);

		//9.3 ������ġ�� ������ ��ȣ�� ����ö���� ã�´�.
		index = Indexes_Find(indexes, businessCardBinder->current->company.name);

		//9.4 ã�� ���ο��� ������ ã�´�.
		position = Index_Find(index, businessCardIndex);

		//9.5 Ʈ���信�� ��Ʈ�� ã�´�.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);

		//9.6 ��Ʈ�� �ڽĳ�忡�� ��ȣ�� ã�´�.
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		tvItem.mask = TVIF_HANDLE | TVIF_TEXT;
		tvItem.pszText = companyName;
		tvItem.cchTextMax = 64;
		while (strcmp(index->name, companyName) != 0) {
			tvItem.hItem = hitem;
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
		}

		//9.7 ã������� �ڽĳ�忡�� ã�� ������ġ�� �׸��� ã�´�.
		hitem = tvItem.hItem;
		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hitem);
		i = 0;
		while (i < position) {
			hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hitem);
			i++;
		}
		//9.8 �ش��׸��� ��ũ�Ѵ�.
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
// 10. Ʈ������ �׸��� ����Ŭ�� ������
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

		//10.1 ���õ� �׸��� ��ġ�� �д´�.

		hitem = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CARET, (LPARAM)0);

		//10.2 ���� ��ġ�� �θ� �д´�.

		hParent = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_PARENT, (LPARAM)hitem);

		//10.3 �θ��� �׸��� �д´�.

		tvItem.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.pszText = companyName;
		tvItem.cchTextMax = 64;
		tvItem.hItem = hParent;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);

		//10.4 �θ��׸񿡼� ���õ� �׸��� ����� ��ġ���� ã�´�.
		hChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hParent);
		while (hChild != hitem) {
			position++;
			hChild = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_COMPANIES), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hChild);
		}

		//10.5 ��ȣ�� ����ö���� ã�´�.
		index = Indexes_Find(indexes, companyName);

		//10.6 ���ο��� ã�� ��ġ�� ������ �д´�.
		businessCardIndex = Index_GetAt(index, position);
		businessCardBinder->current = businessCardIndex;

		//10.7 ����ö�� ���Կ� ã�� ������ ����Ѵ�.
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
// 11.�ݱ��ư�� Ŭ��������
BOOL BusinessCardBinderForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardBinder *businessCardBinder;
	Indexes *indexes;


	indexes = (Indexes*)GetProp(hWnd, "indexes");
	if (indexes != NULL) {
		//11.1 ����ö�� �����.
		Indexes_Destroy(indexes);
		RemoveProp(hWnd, "indexes");
		free(indexes);
	}
	businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);
	if (businessCardBinder != NULL) {
		//11.2 �����Ѵ�.
		BusinessCardBinder_Save(businessCardBinder);
		//11.3 ����ö�� �����.
		BusinessCardBinder_Destroy(businessCardBinder);
		free(businessCardBinder);
	}
	//11.4 �����츦 �ݴ´�
	EndDialog(hWnd, 0);
	return FALSE;
}