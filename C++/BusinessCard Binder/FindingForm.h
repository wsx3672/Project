//FindingForm.h

#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H
#include <afxwin.h>
#include "resource.h"

class BusinessCard;   //전방선언
typedef long int Long;

class FindingForm : public CDialog {
public:
	enum { IDD = IDD_FINDINGFORM };
public:
	FindingForm(CWnd *parent = NULL);
public:
	Long count;
	Long current;
	BusinessCard* (*indexes);

protected:
	afx_msg void OnFindButtonClicked();
	afx_msg void OnSelectButtonClicked();
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};
#endif // _FINDINGFORM_H