//TakeInForm.h

#ifndef _TAKEINFORM_H
#define _TAKEINFORM_H
#include <afxwin.h>
#include "resource.h"

using namespace std;
class TakeInForm:public CDialog {
public:
	enum {IDD=IDD_TAKEINFORM};
public:
	TakeInForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnTakeInButtonClicked();
	afx_msg void CompanyNameEditKillForcus();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif // _TAKEINFORM_H
