#include "ClassDiagramFormMenu.h"
#include "ClassDiagramForm.h"
#include "MenuAction.h"
#include "ClassMenuAction.h"
#include "MemoBoxMenuAction.h"
#include "GeneralizationMenuAction.h"
#include "RealizationMenuAction.h"
#include "DependencyMenuAction.h"
#include "AssociationMenuAction.h"
#include "DirectedAssociationMenuAction.h"
#include "AggregationMenuAction.h"
#include "AggregationsMenuAction.h"
#include "CompositionMenuAction.h"
#include "CompositionsMenuAction.h"
#include "MemoLineMenuAction.h"
#include "GraphicCtrlUndoMenuAction.h"
#include "GraphicCtrlCutMenuAction.h"
#include "GraphicCtrlCopyMenuAction.h"
#include "GraphicCtrlPasteMenuAction.h"
#include "AddTemplateMenuAction.h"
#include "DeleteTemplateMenuAction.h"
#include "DeleteMenuAction.h"
#include "AddAttributeMenuAction.h"
#include "DeleteAttributeMenuAction.h"
#include "AddMethodMenuAction.h"
#include "DeleteMethodMenuAction.h"
#include "AddReceptionMenuAction.h"
#include "DeleteReceptionMenuAction.h"
#include "GraphicCtrlRedoMenuAction.h"

ClassDiagramFormMenu::ClassDiagramFormMenu(ClassDiagramForm* classDiagramForm) {
	this->classDiagramForm = classDiagramForm;
	this->menu1 = new CMenu;  //���õȰ� ������ 
	this->drawMenu = new CMenu; // �׸��� �޴�

	this->menu2 = new CMenu; // ���õȰ� 1��
	this->menu3 = new CMenu;
	
	
//////////////////////////////////////////////////////////////////////
	this->menu1->CreatePopupMenu();
	this->drawMenu->CreatePopupMenu();
	//this->undoMenu->CreatePopupMenu(); ��� �Ǵ���
//////////////////////////////////////////////////////////////////////
	this->menu2->CreatePopupMenu();
	this->menu3->CreatePopupMenu();
//////////////////////////////////////////////////////////////////////////
	this->menu1->AppendMenu(MF_STRING, 123, "�ǵ�����(Z)");
	this->menu1->AppendMenu(MF_STRING, 136, "�����(Y)");
	this->menu1->AppendMenu(MF_STRING, 108, "�ٿ��ֱ�(V)");
	this->menu1->AppendMenu(MF_SEPARATOR);
	this->menu1->AppendMenu(MF_POPUP, (UINT_PTR)this->drawMenu->m_hMenu, "�׸���(D)");
	classDiagramForm->SetMenu(this->menu1);
	this->drawMenu->AppendMenu(MF_STRING, 110, "Ŭ���� �׸���");
	this->drawMenu->AppendMenu(MF_STRING, 112, "�Ϲ�ȭ(1)");
	this->drawMenu->AppendMenu(MF_STRING, 113, "��üȭ(2)");
	this->drawMenu->AppendMenu(MF_STRING, 114, "����(3)");
	this->drawMenu->AppendMenu(MF_STRING, 115, "����(4)");
	this->drawMenu->AppendMenu(MF_STRING, 116, "��������(5)");
	this->drawMenu->AppendMenu(MF_STRING, 117, "����(6)");
	this->drawMenu->AppendMenu(MF_STRING, 118, "���տ���(7)");
	this->drawMenu->AppendMenu(MF_STRING, 119, "�ռ�(8)");
	this->drawMenu->AppendMenu(MF_STRING, 120, "���տ���(9)");
	this->drawMenu->AppendMenu(MF_STRING, 111, "�޸�ڽ� �׸���");
	this->drawMenu->AppendMenu(MF_STRING, 121, "�޸����(0)");
	///////////////////////////////////////////////////////////////////
	this->menu2->AppendMenu(MF_STRING, 109, "�ڸ���(X)");
	this->menu2->AppendMenu(MF_SEPARATOR);
	this->menu2->AppendMenu(MF_STRING, 107, "�����ϱ�(C)");
	this->menu2->AppendMenu(MF_STRING, 108, "�ٿ��ֱ�(V)");
	this->menu2->AppendMenu(MF_STRING, 129, "�����ϱ�(D)");
	this->menu2->AppendMenu(MF_SEPARATOR);
	this->menu2->AppendMenu(MF_STRING, 127, "���ø� �߰�");
	this->menu2->AppendMenu(MF_STRING, 135, "�Ӽ� �߰�");
	this->menu2->AppendMenu(MF_STRING, 130, "���� �߰�");
	this->menu2->AppendMenu(MF_STRING, 133, "������ �߰�");
	this->menu2->AppendMenu(MF_SEPARATOR);
	this->menu2->AppendMenu(MF_STRING, 128, "���ø� ����");
	this->menu2->AppendMenu(MF_STRING, 131, "�Ӽ� ����");
	this->menu2->AppendMenu(MF_STRING, 132, "���� ����");
	this->menu2->AppendMenu(MF_STRING, 134, "������ ����");
/////////////////////////////////////////////////////////////////////////
	//this->menu3->AppendMenu(MF_STRING, 123, "�ǵ�����(Z)");
	//this->menu3->AppendMenu(MF_STRING, 136, "�����(Y)");
	//this->menu3->AppendMenu(MF_SEPARATOR);
	this->menu3->AppendMenu(MF_STRING, 109, "�ڸ���(X)");
	this->menu3->AppendMenu(MF_STRING, 107, "�����ϱ�(C)");

}

ClassDiagramFormMenu::ClassDiagramFormMenu(const ClassDiagramFormMenu& source) {
	this->menu1 = source.menu1;
	this->drawMenu = source.drawMenu;
}

MenuAction* ClassDiagramFormMenu::MenuSelected(UINT parm_control_id) {
	if (this->menuAction != 0) {
		delete this->menuAction;
		this->menuAction = 0;
	}
	switch (parm_control_id) {
	case 110: this->menuAction = new ClassMenuAction; break;
	case 111: this->menuAction = new MemoBoxMenuAction; break;
	case 112: this->menuAction = new GeneralizationMenuAction; break;
	case 113: this->menuAction = new RealizationMenuAction; break;
	case 114: this->menuAction = new DependencyMenuAction; break;
	case 115: this->menuAction = new AssociationMenuAction; break;
	case 116: this->menuAction = new DirectedAssociationMenuAction; break;
	case 117: this->menuAction = new AggregationMenuAction; break;
	case 118: this->menuAction = new AggregationsMenuAction; break;
	case 119: this->menuAction = new CompositionMenuAction; break;
	case 120: this->menuAction = new CompositionsMenuAction; break;
	case 121: this->menuAction = new MemoLineMenuAction; break;
	case 123: this->menuAction = new GraphicCtrlUndoMenuAction; break;
	case 107: this->menuAction = new GraphicCtrlCopyMenuAction; break;
	case 108: this->menuAction = new GraphicCtrlPasteMenuAction; break;
	case 109: this->menuAction = new GraphicCtrlCutMenuAction; break;
	case 127: this->menuAction = new AddTemplateMenuAction; break;
	case 128: this->menuAction = new DeleteTemplateMenuAction; break;
	case 129: this->menuAction = new DeleteMenuAction; break;
	case 135: this->menuAction = new AddAttributeMenuAction; break;
	case 131: this->menuAction = new DeleteAttributeMenuAction; break;
	case 130: this->menuAction = new AddMethodMenuAction; break;
	case 132: this->menuAction = new DeleteMethodMenuAction; break;
	case 133: this->menuAction = new AddReceptionMenuAction; break;
	case 134: this->menuAction = new DeleteReceptionMenuAction; break;
	case 136: this->menuAction = new GraphicCtrlRedoMenuAction; break;

	default: break;
	}

	return this->menuAction;
}

ClassDiagramFormMenu& ClassDiagramFormMenu::operator=(const ClassDiagramFormMenu& source) {
	if (this->menu1 != NULL) {
		delete this->menu1;
	}
	if (this->drawMenu != NULL) {
		delete this->drawMenu;
	}
	this->menu1 = source.menu1;
	this->drawMenu = source.drawMenu;

	return *this;
}

ClassDiagramFormMenu::~ClassDiagramFormMenu() {
	if (this->menu1 != NULL) {
		delete this->menu1;
	}
	if (this->menu2 != NULL) {
		delete this->menu2;
	}
	if (this->menu3 != NULL) {
		delete this->menu3;
	}
	if (this->drawMenu != NULL) {
		delete this->drawMenu;
	}
}