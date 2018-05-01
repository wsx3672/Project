#include "HouseholdAccountsApp.h"
#include "HouseholdAccountsForm.h"

BOOL HouseholdAccountsApp::InitInstance() {
	HouseholdAccountsForm *householdAccountsForm = new HouseholdAccountsForm;
	householdAccountsForm->Create(NULL, "HouseholdAccounts");
	householdAccountsForm->ShowWindow(SW_MAXIMIZE);
	householdAccountsForm->UpdateWindow();
	
	this->m_pMainWnd = householdAccountsForm;
	return TRUE;
}

HouseholdAccountsApp householdAccountsFormApp;