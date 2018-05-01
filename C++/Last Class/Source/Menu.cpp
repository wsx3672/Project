#include "Menu.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"

#include "HistoryGraphic.h"
#include "GraphicCtrlUndoMenuAction.h"
#include "GraphicCtrlRedoMenuAction.h"

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
#include "OpenMenuAction.h"
#include "SaveMenuAction.h"
#include "SaveAsMenuAction.h"
#include "NewMenuAction.h"
#include "FilePrintPreviewMenuAction.h"
#include "SupportMenuAction.h"
#include "FilePrintMenuAction.h"
#include "GraphicCtrlCutMenuAction.h"
#include "GraphicCtrlCopyMenuAction.h"
#include "GraphicCtrlPasteMenuAction.h"
#include "DeleteGraphicKeyMenuAction.h"
#include "AboutMenuAction.h"
#include "ExitKeyMenuAction.h"
#include "ZoomInMenuAction.h"
#include "ZoomOutMenuAction.h"

Menu::Menu(LastClass* lastClass) {
	this->lastClass = lastClass;
	this->mainMenu = new CMenu; // ��ü�޴�
	this->popupMenu = new CMenu; // �Ǿ� �޴�
	this->editMenu = new CMenu; // ���� �޴�
	this->supportMenu = new CMenu; // ����
	this->drawMenu = new CMenu; // �׸��� �޴�
	this->relationMenu = new CMenu; // ���輱 �޴�
	this->seeMenu = new CMenu;//���� �޴�

	this->mainMenu->CreateMenu();

	this->popupMenu->CreatePopupMenu();
	this->editMenu->CreatePopupMenu();
	this->supportMenu->CreatePopupMenu();
	this->drawMenu->CreatePopupMenu();
	this->relationMenu->CreatePopupMenu();
	this->seeMenu->CreatePopupMenu();

	this->mainMenu->AppendMenu(MF_POPUP, (UINT_PTR)this->popupMenu->m_hMenu, "����(F)");
	this->mainMenu->AppendMenu(MF_POPUP, (UINT_PTR)this->editMenu->m_hMenu, "����(E)");
	this->mainMenu->AppendMenu(MF_POPUP, (UINT_PTR)this->drawMenu->m_hMenu, "�׸���(D)");
	this->mainMenu->AppendMenu(MF_POPUP, (UINT_PTR)this->seeMenu->m_hMenu, "����(S)");
	this->mainMenu->AppendMenu(MF_POPUP, (UINT_PTR)this->supportMenu->m_hMenu, "����(H)");
	lastClass->SetMenu(this->mainMenu);
	this->popupMenu->AppendMenu(MF_STRING, 100, "���� �����(N)");
	this->popupMenu->AppendMenu(MF_STRING, 101, "����(O)");
	this->popupMenu->AppendMenu(MF_STRING, 102, "����(S)");
	this->popupMenu->AppendMenu(MF_STRING, 103, "�ٸ��̸����� ����(A)");
	this->popupMenu->AppendMenu(MF_STRING, 104, "�̸�����(F)");
	this->popupMenu->AppendMenu(MF_STRING, 105, "�μ��ϱ�(P)");
	this->popupMenu->AppendMenu(MF_STRING, 106, "������(X)");
	this->editMenu->AppendMenu(MF_STRING, 107, "�����ϱ�(C)");
	this->editMenu->AppendMenu(MF_STRING, 108, "�ٿ��ֱ�(V)");
	this->editMenu->AppendMenu(MF_STRING, 109, "�ڸ���(X)");
	this->editMenu->AppendMenu(MF_STRING, 123, "�ǵ�����(Z)");
	this->editMenu->AppendMenu(MF_STRING, 124, "�����(Y)");
	this->drawMenu->AppendMenu(MF_STRING , 110, "Ŭ���� �׸���(Q)"); //
	this->drawMenu->AppendMenu(MF_STRING, 111, "�޸�ڽ� �׸���(W)"); //
	this->drawMenu->AppendMenu(MF_POPUP, (UINT_PTR)this->relationMenu->m_hMenu, "���輱 �׸���(D)"); // ���輱 �ȿ� ���輱 �׸���
	this->relationMenu->AppendMenu(MF_STRING, 112, "�Ϲ�ȭ(1)");
	this->relationMenu->AppendMenu(MF_STRING, 113, "��üȭ(2)");
	this->relationMenu->AppendMenu(MF_STRING, 114, "����(3)");
	this->relationMenu->AppendMenu(MF_STRING, 115, "����(4)");
	this->relationMenu->AppendMenu(MF_STRING, 116, "��������(5)");
	this->relationMenu->AppendMenu(MF_STRING, 117, "����(6)");
	this->relationMenu->AppendMenu(MF_STRING, 118, "���տ���(7)");
	this->relationMenu->AppendMenu(MF_STRING, 119, "�ռ�(8)");
	this->relationMenu->AppendMenu(MF_STRING, 120, "���տ���(9)");
	this->relationMenu->AppendMenu(MF_STRING, 121, "�޸����(0)");
	this->supportMenu->AppendMenu(MF_STRING, 126, "����(H)");
	this->supportMenu->AppendMenu(MF_STRING, 127, "LastClass ����(A)");
	this->seeMenu->AppendMenu(MF_STRING, 122, "Ȯ���ϱ�");
	this->seeMenu->AppendMenu(MF_STRING, 125, "����ϱ�");

}

Menu::Menu(const Menu& source){
	this->mainMenu = source.mainMenu;
	this->popupMenu = source.popupMenu;
	this->editMenu = source.editMenu;
	this->supportMenu = source.supportMenu;
	this->seeMenu = source.seeMenu;//
}

MenuAction* Menu::MenuSelected( UINT parm_control_id) {
	if (this->menuAction != 0) {
		delete this->menuAction;
		this->menuAction = 0;
	}
	switch (parm_control_id) {
	case 100: this->menuAction = new NewMenuAction; break;
	case 101: this->menuAction = new OpenMenuAction; break;
	case 102: this->menuAction = new SaveMenuAction; break;
	case 103: this->menuAction = new SaveAsMenuAction; break;
	case 104: this->menuAction = new FilePrintPreviewMenuAction; break; // ��
	case 105: this->menuAction = new FilePrintMenuAction; break;
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
	case 122: this->menuAction = new ZoomInMenuAction; break;
	case 106:this->menuAction =  new ExitKeyMenuAction; break;
	case 107:this->menuAction =  new GraphicCtrlCopyMenuAction; break;
	case 108:this->menuAction =  new GraphicCtrlPasteMenuAction; break;
	case 109: this->menuAction = new GraphicCtrlCutMenuAction; break;
	case 123: this->menuAction = new GraphicCtrlUndoMenuAction; break;
	case 124: this->menuAction = new GraphicCtrlRedoMenuAction; break;
	case 125: this->menuAction = new ZoomOutMenuAction; break;
	case 126: this->menuAction = new SupportMenuAction; break;
	case 127: this->menuAction = new AboutMenuAction; break;

	default: break;
	}

	return this->menuAction;
}

Menu& Menu::operator=(const Menu& source) {
	if (this->mainMenu != NULL) {
		delete this->mainMenu;
	}
	if (this->popupMenu != NULL) {
		delete this->popupMenu;
	}
	if (this->editMenu != NULL) {
		delete this->editMenu;
	}
	if (this->supportMenu != NULL) {
		delete this->supportMenu;
	}
	if (this->seeMenu != NULL) {
		delete this->seeMenu;
	}
	this->mainMenu = source.mainMenu;
	this->popupMenu = source.popupMenu;
	this->editMenu = source.editMenu;
	this->supportMenu = source.supportMenu;
	this->seeMenu = source.seeMenu;

	return *this;
}

Menu::~Menu() {
	if (this->mainMenu != NULL) {
		delete this->mainMenu;
	}
	if (this->popupMenu != NULL) {
		delete this->popupMenu;
	}
	if (this->editMenu != NULL) {
		delete this->editMenu;
	}
	if (this->supportMenu != NULL) {
		delete this->supportMenu;
	}
	if (this->drawMenu != NULL) {
		delete this->drawMenu;
	}
	if (this->relationMenu != NULL) {
		delete this->relationMenu;
	}
	if (this->seeMenu != NULL) {
		delete this->seeMenu;
	}
}