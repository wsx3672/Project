#include "LastClass.h"
#include "LastClassApp.h"

BOOL LastClassApp::InitInstance() {
	LastClass *lastClass = new LastClass;

	lastClass->Create(NULL, "LastClass"); //CFrameWnd �� ���پ��µ�??
	lastClass->ShowWindow(SW_MAXIMIZE);
	lastClass->UpdateWindow();
	this->m_pMainWnd = lastClass;

	return TRUE;
}

LastClassApp classDiagramApp;