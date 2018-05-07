//BusinessCardBinderApp.cpp

#include "BusinessCardBinderApp.h"
#include "BusinessCardBinderForm.h"  //메인윈도 만들어야해서

BOOL BusinessCardBinderApp::InitInstance() {
	BusinessCardBinderForm businessCardBinderForm;

	this->m_pMainWnd = &businessCardBinderForm;
	businessCardBinderForm.DoModal();

	return TRUE;
}
BusinessCardBinderApp businessCardBinderApp;