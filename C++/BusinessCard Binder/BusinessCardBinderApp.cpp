//BusinessCardBinderApp.cpp

#include "BusinessCardBinderApp.h"
#include "BusinessCardBinderForm.h"  //�������� �������ؼ�

BOOL BusinessCardBinderApp::InitInstance() {
	BusinessCardBinderForm businessCardBinderForm;

	this->m_pMainWnd = &businessCardBinderForm;
	businessCardBinderForm.DoModal();

	return TRUE;
}
BusinessCardBinderApp businessCardBinderApp;