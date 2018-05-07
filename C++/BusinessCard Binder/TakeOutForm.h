//TakeOutForm.h

#ifndef _TAKEOUTFORM_H
#define _TAKEOUTFORM_H
#include <afxwin.h>
#include "resource.h"

class TakeOutForm :public CDialog {
public:
	enum { IDD = IDD_TAKEOUTFORM };
public:
	TakeOutForm(CWnd *parent = NULL);
public:
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP();
};

#endif // _TAKEOUTFORM_H