//GraphicCtrlPasteKey.cpp

#include "GraphicCtrlPasteKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "Diagram.h"
#include "SmartPointer.h"
#include "ArrayIterator.h"
#include "Line.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "MemoBox.h"
#include "Template.h"
#include "Relation.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "Reception.h"
#include "MemoLine.h"
#include "Finder.h"
#include "RollNameBox.h"
#include "MouseLButton.h"
#include "SelfRelation.h"
#include "LastClass.h"
#include "RollNameBox.h"
#include "SelfRelation.h"
#include "StatusBar.h"
#include "HistoryGraphic.h"

GraphicCtrlPasteKey::GraphicCtrlPasteKey() {
}

GraphicCtrlPasteKey::GraphicCtrlPasteKey(const GraphicCtrlPasteKey& source) {
}

GraphicCtrlPasteKey::~GraphicCtrlPasteKey() {
}

void GraphicCtrlPasteKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->copyBuffer != NULL) {
		Long i = 0;
		Long j = 0;
		Long k = 0;

		int vertCurPos = classDiagramForm->GetScrollPos(SB_VERT);
		int horzCurPos = classDiagramForm->GetScrollPos(SB_HORZ);

		CPoint point;

		CPoint clientArea;
		CRect rect;
		::GetCursorPos(&point); // ����ȭ�� Ŀ����ġ Get

		classDiagramForm->GetClientRect(&rect); //Ŭ�������̾�׷� ���� clientrect
		clientArea.x = rect.left;
		clientArea.y = rect.top;
		::ClientToScreen(classDiagramForm->GetSafeHwnd(), &clientArea); // windowrect�� ��ǥ�� ȭ������� ��ȯ

		if (point.x < clientArea.x || point.y < clientArea.y) { //�޴���ư�� �ִ� �ٿ��ֱ� ���� (10,10)��ġ��
			point.x = classDiagramForm->currentX_ ;
			point.y = classDiagramForm->currentY_ ;
		}
		else {
			::ScreenToClient(classDiagramForm->GetSafeHwnd(), &point); // �������� ��ǥ�� ��ȯ
		}

		CPoint selectionPoint = classDiagramForm->selection->GetTopLeftPoint(*classDiagramForm->copyBuffer);

		classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram, classDiagramForm->zoomRate);

		Selection *tempBuffer = classDiagramForm->selection->MakeSelectionBuffer(*classDiagramForm->copyBuffer);

		Long distanceX = point.x  - selectionPoint.x;
		Long distanceY = point.y  - selectionPoint.y;

		Figure *figure;
		MovingVisitor movingVisitor;
		classDiagramForm->selection->DeleteAllItems();
		SmartPointer<Figure*>tempBufferSmartPointer(tempBuffer->CreateIterator());
		for (tempBufferSmartPointer->First(); !tempBufferSmartPointer->IsDone(); tempBufferSmartPointer->Next()) {
			figure = tempBufferSmartPointer->Current();
			if (dynamic_cast<Class*>(figure)) { //Ŭ������ �޸��
				static_cast<Class*>(figure)->Accept(movingVisitor, distanceX, distanceY);
				classDiagramForm->diagram->Add(figure);
				classDiagramForm->selection->Add(classDiagramForm->diagram->GetAt(classDiagramForm->diagram->GetLength() - 1));
			}
			else if (dynamic_cast<MemoBox*>(figure)) {
				static_cast<MemoBox*>(figure)->Accept(movingVisitor, distanceX, distanceY);
				classDiagramForm->diagram->Add(figure);	
				classDiagramForm->selection->Add(classDiagramForm->diagram->GetAt(classDiagramForm->diagram->GetLength() - 1));
			}
		}

		if (tempBuffer != 0) {
			delete tempBuffer;
			tempBuffer = 0;
		}

		classDiagramForm->lastClass->statusBar->DestroyStatus();
		classDiagramForm->lastClass->statusBar->MakeStatusBar(classDiagramForm->lastClass, classDiagramForm->lastClass->GetSafeHwnd(), 0, 0, 5);
	}
	if (classDiagramForm->selection->GetLength() == 1) {
		classDiagramForm->mouseLButton->ChangeSelectionState();
	}
	else {
		classDiagramForm->mouseLButton->ChangeMultipleState();
	}
}


void GraphicCtrlPasteKey::KeyPress(TextEdit *textEdit) {
}