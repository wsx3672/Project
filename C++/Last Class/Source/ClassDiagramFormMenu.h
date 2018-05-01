#ifndef _CLASSDIAGRAMFORMMENU_H	
#define _CLASSDIAGRAMFORMMENU_H

#include <afxwin.h>

using namespace std;
class ClassDiagramForm;
class MenuAction;
class ClassDiagramFormMenu {
public:
	ClassDiagramFormMenu(ClassDiagramForm *classDiagramForm);
	~ClassDiagramFormMenu();
	ClassDiagramFormMenu(const ClassDiagramFormMenu& source);
	MenuAction* MenuSelected(UINT parm_control_id);
	ClassDiagramFormMenu& operator= (const ClassDiagramFormMenu& source);
public:
	CMenu *menu1;  // ���õȰ� ������
private:
	CMenu *drawMenu; 
public:
	CMenu *menu2;	//���õȰ� 1��
public:
	CMenu *menu3;  //���õȰ� 2��
public:
	MenuAction *menuAction;
	ClassDiagramForm *classDiagramForm;
};
#endif // !_CLASSDIAGRAMFORMMENU_H
