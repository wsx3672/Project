////RollNameBox.cpp
//
//#include "RollNameBox.h"
//#include <math.h>
//
//RollNameBox* RollNameBox::instance = 0;
//
//RollNameBox* RollNameBox::Instance() {
//	if (instance == 0) {
//		instance = new RollNameBox;
//	}
//	return instance;
//}
//
//RollNameBox::RollNameBox() {
//}
//
//RollNameBox::RollNameBox(const RollNameBox& source) {
//}
//
//RollNameBox::~RollNameBox() {
//}
//
//CPoint RollNameBox::GetFirstRollNamePoint(CPoint startPoint, CPoint endPoint) {
//	CPoint cPoint;
//
//	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // �� ���� ����
//
//	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2)); // �� �� �Ÿ�
//																								   // ��Ʈ�ȿ� = ��Ʈ(����(
//
//	double dX = startPoint.x + (30 * (endPoint.x - startPoint.x) / distance); // ������ 30 ��ŭ �̵� x ��
//	double dY = startPoint.y - (30 * (startPoint.y - endPoint.y) / distance);
//
//	//double degree90 = -(atan2((endPoint.x - startPoint.x) , (startPoint.y - endPoint.y)));      // ���� ����
//
//	cPoint.x = static_cast<LONG>(dX - 20 * cos(degree)); // ����
//	cPoint.y = static_cast<LONG>(dY - 20 * sin(degree));
//
//	return cPoint;
//}
//
//CPoint RollNameBox::GetSecondRollNamePoint(CPoint startPoint, CPoint endPoint) {
//	CPoint cPoint;
//	if (startPoint != endPoint) {
//		double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����
//		double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
//
//		double dX = ((startPoint.x) + (endPoint.x)) / 2 + (1 * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
//		double dY = ((startPoint.y) + (endPoint.y)) / 2 - (1 * (startPoint.y - endPoint.y) / distance);
//
//		cPoint.x = static_cast<LONG>(dX - 20 * cos(degree));
//		cPoint.y = static_cast<LONG>(dY - 20 * sin(degree));
//	}
//	else {
//		cPoint.x = startPoint.x;
//		cPoint.y = startPoint.y - 20;
//	}
//	return cPoint;
//}
//
//CPoint RollNameBox::GetThirdRollNamePoint(CPoint startPoint, CPoint endPoint) {
//	CPoint cPoint;
//	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����
//
//	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
//	// ��Ʈ�ȿ� = ��Ʈ(����(
//	double dX = (endPoint.x) - (30 * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
//	double dY = (endPoint.y) + (30 * (startPoint.y - endPoint.y) / distance); //�ڷ� �� ������ y
//
//	cPoint.x = static_cast<LONG>(dX - 20 * cos(degree));
//	cPoint.y = static_cast<LONG>(dY - 20 * sin(degree));
//
//	return cPoint;
//}
//
//CPoint RollNameBox::GetFourthRollNamePoint(CPoint startPoint, CPoint endPoint) {
//	CPoint cPoint;
//	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����
//	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
//
//	double dX = (startPoint.x) + (40 * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
//	double dY = (startPoint.y) - (40 * (startPoint.y - endPoint.y) / distance);
//
//	cPoint.x = static_cast<LONG>(dX + 20 * cos(degree));
//	cPoint.y = static_cast<LONG>(dY + 20 * sin(degree));
//
//	return cPoint;
//}
//
//CPoint RollNameBox::GetFifthRollNamePoint(CPoint startPoint, CPoint endPoint) {
//
//	CPoint cPoint;
//	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����
//
//	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
//	// ��Ʈ�ȿ� = ��Ʈ(����(
//	double dX = (endPoint.x) - (40 * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
//	double dY = (endPoint.y) + (40 * (startPoint.y - endPoint.y) / distance); //�ڷ� �� ������ y
//
//	cPoint.x = static_cast<LONG>(dX + 20 * cos(degree));
//	cPoint.y = static_cast<LONG>(dY + 20 * sin(degree));
//
//	return cPoint;
//}
//
//CPoint RollNameBox::GetSelfRelationFirstRollNamePoint(CPoint startPoint, CPoint endPoint) {
//	CPoint cPoint;
//
//	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // �� ���� ����
//
//	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2)); // �� �� �Ÿ�
//																								   // ��Ʈ�ȿ� = ��Ʈ(����(
//
//	double dX = startPoint.x + (25 * (endPoint.x - startPoint.x) / distance); // ������ 30 ��ŭ �̵� x ��
//	double dY = startPoint.y - (25 * (startPoint.y - endPoint.y) / distance);
//
//	//double degree90 = -(atan2((endPoint.x - startPoint.x) , (startPoint.y - endPoint.y)));      // ���� ����
//
//	cPoint.x = static_cast<LONG>(dX - 25 * cos(degree)); // ����
//	cPoint.y = static_cast<LONG>(dY - 25 * sin(degree));
//
//	return cPoint;
//}
//CPoint RollNameBox::GetSelfRelationSecondRollNamePoint(CPoint startPoint, CPoint endPoint) {
//	CPoint cPoint;
//	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����
//
//	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
//	// ��Ʈ�ȿ� = ��Ʈ(����(
//	double dX = (endPoint.x) - ((endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
//	double dY = (endPoint.y) + ((startPoint.y - endPoint.y) / distance); //�ڷ� �� ������ y
//
//	cPoint.x = static_cast<LONG>(dX - 20 * cos(degree));
//	cPoint.y = static_cast<LONG>(dY - 20 * sin(degree));
//
//	return cPoint;
//}
//CPoint RollNameBox::GetSelfRelationThirdRollNamePoint(CPoint startPoint, CPoint endPoint) {
//	CPoint cPoint;
//	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����
//
//	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
//	// ��Ʈ�ȿ� = ��Ʈ(����(
//	double dX = (endPoint.x) - (33 * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
//	double dY = (endPoint.y) + (33 * (startPoint.y - endPoint.y) / distance); //�ڷ� �� ������ y
//
//	cPoint.x = static_cast<LONG>(dX - 18 * cos(degree));
//	cPoint.y = static_cast<LONG>(dY - 18 * sin(degree));
//
//	return cPoint;
//}
//CPoint RollNameBox::GetSelfRelationFourthRollNamePoint(CPoint startPoint, CPoint endPoint) {
//	CPoint cPoint;
//	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����
//	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
//
//	double dX = (startPoint.x) + (25 * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
//	double dY = (startPoint.y) - (25 * (startPoint.y - endPoint.y) / distance);
//
//	cPoint.x = static_cast<LONG>(dX + 25 * cos(degree));
//	cPoint.y = static_cast<LONG>(dY + 25 * sin(degree));
//
//	return cPoint;
//}
//CPoint RollNameBox::GetSelfRelationFifthRollNamePoint(CPoint startPoint, CPoint endPoint) {
//	CPoint cPoint;
//	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����
//
//	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
//	// ��Ʈ�ȿ� = ��Ʈ(����(
//	double dX = (endPoint.x) - (33 * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
//	double dY = (endPoint.y) + (33 * (startPoint.y - endPoint.y) / distance); //�ڷ� �� ������ y
//
//	cPoint.x = static_cast<LONG>(dX + 18 * cos(degree));
//	cPoint.y = static_cast<LONG>(dY + 18 * sin(degree));
//
//	return cPoint;
//}

//RollNameBox.cpp

#include "RollNameBox.h"
#include <math.h>

#include "LastClass.h"
#include "ClassDiagramForm.h"

RollNameBox* RollNameBox::instance = 0;

RollNameBox* RollNameBox::Instance() {
	if (instance == 0) {
		instance = new RollNameBox;
	}
	return instance;
}

RollNameBox::RollNameBox() {
}

RollNameBox::RollNameBox(const RollNameBox& source) {
}

RollNameBox::~RollNameBox() {
}

CPoint RollNameBox::GetFirstRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;

	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // �� ���� ����

	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2)); // �� �� �Ÿ�
																								   // ��Ʈ�ȿ� = ��Ʈ(����(

	LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));

	double dX = startPoint.x + ((30 * lastClass->classDiagramForm->zoomRate / 100) * (endPoint.x - startPoint.x) / distance); // ������ 30 ��ŭ �̵� x ��
	double dY = startPoint.y - ((30 * lastClass->classDiagramForm->zoomRate / 100) * (startPoint.y - endPoint.y) / distance);

	//double degree90 = -(atan2((endPoint.x - startPoint.x) , (startPoint.y - endPoint.y)));      // ���� ����

	cPoint.x = static_cast<LONG>(dX - (20 * lastClass->classDiagramForm->zoomRate / 100) * cos(degree)); // ����
	cPoint.y = static_cast<LONG>(dY - (20 * lastClass->classDiagramForm->zoomRate / 100) * sin(degree));

	return cPoint;
}

CPoint RollNameBox::GetSecondRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;
	if (startPoint != endPoint) {
		double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����
		double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));

		double dX = ((startPoint.x) + (endPoint.x)) / 2 + (1 * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
		double dY = ((startPoint.y) + (endPoint.y)) / 2 - (1 * (startPoint.y - endPoint.y) / distance);

		LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));

		cPoint.x = static_cast<LONG>(dX - (20 * lastClass->classDiagramForm->zoomRate / 100) * cos(degree));
		cPoint.y = static_cast<LONG>(dY - (20 * lastClass->classDiagramForm->zoomRate / 100) * sin(degree));
	}
	else {
		cPoint.x = startPoint.x;
		cPoint.y = startPoint.y - 20;
	}
	return cPoint;
}

CPoint RollNameBox::GetThirdRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;
	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����

	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(

	LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));

	double dX = (endPoint.x) - ((30 * lastClass->classDiagramForm->zoomRate / 100) * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
	double dY = (endPoint.y) + ((30 * lastClass->classDiagramForm->zoomRate / 100) * (startPoint.y - endPoint.y) / distance); //�ڷ� �� ������ y

	cPoint.x = static_cast<LONG>(dX - (20 * lastClass->classDiagramForm->zoomRate / 100) * cos(degree));
	cPoint.y = static_cast<LONG>(dY - (20 * lastClass->classDiagramForm->zoomRate / 100) * sin(degree));

	return cPoint;
}

CPoint RollNameBox::GetFourthRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;
	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����
	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));

	LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));

	double dX = (startPoint.x) + ((40 * lastClass->classDiagramForm->zoomRate / 100) * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
	double dY = (startPoint.y) - ((40 * lastClass->classDiagramForm->zoomRate / 100) * (startPoint.y - endPoint.y) / distance);

	cPoint.x = static_cast<LONG>(dX + (20 * lastClass->classDiagramForm->zoomRate / 100) * cos(degree));
	cPoint.y = static_cast<LONG>(dY + (20 * lastClass->classDiagramForm->zoomRate / 100) * sin(degree));

	return cPoint;
}

CPoint RollNameBox::GetFifthRollNamePoint(CPoint startPoint, CPoint endPoint) {

	CPoint cPoint;
	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����

	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(

	LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));

	double dX = (endPoint.x) - ((40 * lastClass->classDiagramForm->zoomRate / 100) * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
	double dY = (endPoint.y) + ((40 * lastClass->classDiagramForm->zoomRate / 100) * (startPoint.y - endPoint.y) / distance); //�ڷ� �� ������ y

	cPoint.x = static_cast<LONG>(dX + (20 * lastClass->classDiagramForm->zoomRate / 100) * cos(degree));
	cPoint.y = static_cast<LONG>(dY + (20 * lastClass->classDiagramForm->zoomRate / 100) * sin(degree));

	return cPoint;
}

CPoint RollNameBox::GetSelfRelationFirstRollNamePoint(CPoint startPoint, CPoint endPoint ) {
	CPoint cPoint;

	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // �� ���� ����

	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2)); // �� �� �Ÿ�
																								   // ��Ʈ�ȿ� = ��Ʈ(����(

	LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));

	double dX = startPoint.x + ((25 * lastClass->classDiagramForm->zoomRate / 100) * (endPoint.x - startPoint.x) / distance); // ������ 30 ��ŭ �̵� x ��
	double dY = startPoint.y - ((25 * lastClass->classDiagramForm->zoomRate / 100) * (startPoint.y - endPoint.y) / distance);

	//double degree90 = -(atan2((endPoint.x - startPoint.x) , (startPoint.y - endPoint.y)));      // ���� ����

	cPoint.x = static_cast<LONG>(dX - (25 * lastClass->classDiagramForm->zoomRate / 100) * cos(degree)); // ����
	cPoint.y = static_cast<LONG>(dY - (25 * lastClass->classDiagramForm->zoomRate / 100) * sin(degree));

	return cPoint;
}
CPoint RollNameBox::GetSelfRelationSecondRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;
	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����

	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(

	LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));

	double dX = (endPoint.x) - (((endPoint.x - startPoint.x) * lastClass->classDiagramForm->zoomRate / 100) / distance); //�ڷ� �� ������ x
	double dY = (endPoint.y) + (((startPoint.y - endPoint.y) * lastClass->classDiagramForm->zoomRate / 100) / distance); //�ڷ� �� ������ y

	cPoint.x = static_cast<LONG>(dX - (20 * lastClass->classDiagramForm->zoomRate / 100) * cos(degree));
	cPoint.y = static_cast<LONG>(dY - (20 * lastClass->classDiagramForm->zoomRate / 100) * sin(degree));

	return cPoint;
}
CPoint RollNameBox::GetSelfRelationThirdRollNamePoint(CPoint startPoint, CPoint endPoint ) {
	CPoint cPoint;
	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����

	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(

	LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));

	double dX = (endPoint.x) - ((33 * lastClass->classDiagramForm->zoomRate / 100) * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
	double dY = (endPoint.y) + ((33 * lastClass->classDiagramForm->zoomRate / 100) * (startPoint.y - endPoint.y) / distance); //�ڷ� �� ������ y

	cPoint.x = static_cast<LONG>(dX - (18 * lastClass->classDiagramForm->zoomRate / 100) * cos(degree));
	cPoint.y = static_cast<LONG>(dY - (18 * lastClass->classDiagramForm->zoomRate / 100) * sin(degree));

	return cPoint;
}
CPoint RollNameBox::GetSelfRelationFourthRollNamePoint(CPoint startPoint, CPoint endPoint ) {
	CPoint cPoint;
	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����
	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));

	LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));

	double dX = (startPoint.x) + ((25 * lastClass->classDiagramForm->zoomRate / 100) * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
	double dY = (startPoint.y) - ((25 * lastClass->classDiagramForm->zoomRate / 100) * (startPoint.y - endPoint.y) / distance);

	cPoint.x = static_cast<LONG>(dX + (25 * lastClass->classDiagramForm->zoomRate / 100) * cos(degree));
	cPoint.y = static_cast<LONG>(dY + (25 * lastClass->classDiagramForm->zoomRate / 100) * sin(degree));

	return cPoint;
}
CPoint RollNameBox::GetSelfRelationFifthRollNamePoint(CPoint startPoint, CPoint endPoint) {
	CPoint cPoint;
	double degree = atan2(endPoint.x - startPoint.x, startPoint.y - endPoint.y); // ����

	double distance = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(

	LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));

	double dX = (endPoint.x) - ((33 * lastClass->classDiagramForm->zoomRate / 100) * (endPoint.x - startPoint.x) / distance); //�ڷ� �� ������ x
	double dY = (endPoint.y) + ((33 * lastClass->classDiagramForm->zoomRate / 100) * (startPoint.y - endPoint.y) / distance); //�ڷ� �� ������ y

	cPoint.x = static_cast<LONG>(dX + (18 * lastClass->classDiagramForm->zoomRate / 100) * cos(degree));
	cPoint.y = static_cast<LONG>(dY + (18 * lastClass->classDiagramForm->zoomRate / 100) * sin(degree));

	return cPoint;
}