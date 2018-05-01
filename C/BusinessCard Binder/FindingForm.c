//FindingForm.c

#include "FindingForm.h"
#include "BusinessCardBinderForm.h"
#include "BusinessCardBinder.h"
#include "resource.h"

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;

	switch (message) {
	case WM_COMMAND:
		ret = FindingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE:
		ret = FindingForm_OnClose(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}

BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;

	switch (LOWORD(wParam)){
	case IDC_BUTTON_FIND:
		ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_SELECT:
		ret = FindingForm_OnSelectButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIRST:
		ret = FindingForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS2:
		ret = FindingForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT2:
		ret = FindingForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST2:
		ret = FindingForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HWND hBusinessCardBinderForm;
	TCHAR name[11];
	BusinessCardBinder *businessCardBinder;
	BusinessCard *(*indexes);
	Long count;
	Long current;

	if (HIWORD(wParam) == BN_CLICKED)
	{
		//조건을 읽는다
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)name);

		//명함철 윈도우를 찾는다
		hBusinessCardBinderForm = FindWindow("#32770", "명함철");
		//명함철 윈도우의 명함철을 가져온다
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hBusinessCardBinderForm, GWL_USERDATA);

		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA); //indexes 가져다가 초기화
		if (indexes != NULL) {
			free(indexes);
			indexes = NULL;
		}
		// 명함철에서 조건에 맞는 명함들을 찾는다
		BusinessCardBinder_Find(businessCardBinder, name, &indexes, &count);

		//찾았으면 찾은 명함들중에 처음 위치 명함으로 이동한다
		if (count > 0) {
			current = 0;
			SetProp(hWnd, "count", (HANDLE)count); //찾았으면 개수 고정
			SetProp(hWnd, "current", (HANDLE)current); //찾았으면 current (indexes의 첨자로 쓰일 변수) 고정
			SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes); //찾았으면 indexes 고정
			//indexes current번째 출력해준다
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.position);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.emailAddress);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.url);
		}
		else {
			// 암것도 없으면 공백
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		}
	}
	return FALSE;
}

BOOL FindingForm_OnSelectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HWND hBusinessCardBinderForm;
	BusinessCardBinder *businessCardBinder;
	BusinessCard businessCard;
	BusinessCard *(*indexes);
	Long current;
	Long count;

	if (HIWORD(wParam) == BN_CLICKED)
	{
		//명함의 항목들을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)128, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_GETTEXT, (WPARAM)256, (LPARAM)businessCard.company.url);

		//명함철 윈도우를 찾는다
		hBusinessCardBinderForm = FindWindow("#32770", "명함철");
		businessCardBinder = (BusinessCardBinder*)GetWindowLong(hWnd, GWL_USERDATA);

		//indexes, 그 첨자 current, 가져다 준비한다
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "current");
		
		//명함철 윈도의 명함철 현재위치를 indexes 첫칸 주소로 바꿔준다
		businessCardBinder->current = indexes[current];

		//명함철 윈도우의 명함에 읽은 항목을 적는다.
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.emailAddress);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hBusinessCardBinderForm, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.url);
		//찾기윈도우를 닫는다.
		if (indexes != NULL) {
			free(indexes);
		}
		RemoveProp(hWnd, "current");
		
		EndDialog(hWnd, 0);
	}
	return FALSE;
}

BOOL FindingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCard* (*indexes);
	Long count;
	Long current = 0;
	if (HIWORD(wParam) == BN_CLICKED) {
		//찾은 명함들중 처음 위치 명함으로 이동한다.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "count");

		//현재위치의 명함을 명함에 적는다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.url);
		SetProp(hWnd, "current", (HANDLE)current);
	}
	return FALSE;
}
BOOL FindingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);
	Long count;
	Long current;
	if (HIWORD(wParam) == BN_CLICKED) {
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "count");
		current = (Long)GetProp(hWnd, "current");

		current--;
		if (current < 0) {
			current = 0;
		}

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.url);
		SetProp(hWnd, "current", (HANDLE)current);
	}
	return FALSE;
}
BOOL FindingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);
	Long count;
	Long current;
	if (HIWORD(wParam) == BN_CLICKED) {
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "count");
		current = (Long)GetProp(hWnd, "current");
		current++;
		if (current >= count) {
			current = count - 1;
		}
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.url);
		SetProp(hWnd, "current", (HANDLE)current);
	}
	return FALSE;
}
BOOL FindingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);
	Long count;
	Long current;
	if (HIWORD(wParam) == BN_CLICKED) {
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "count");
		current = (Long)GetProp(hWnd, "current");
		current = count - 1;

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_DATA_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[current]->company.url);
		SetProp(hWnd, "current", (HANDLE)current);
	}
	return FALSE;
}

BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCard* (*indexes);
	indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
	if (indexes != NULL) {
		free(indexes);
	}
	RemoveProp(hWnd, "current");
	RemoveProp(hWnd, "count");
	EndDialog(hWnd, 0);
	return FALSE;
}