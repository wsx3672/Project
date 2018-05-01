//ShiftAndLeftArrowKey.h
/*
파일명 : ShiftAndLeftArrowKey.h
기능 : Shift를 누른상태에서 왼쪽 방향키를 눌렀을 때 처리를 위한 클래스
작성자 : 박상민
작성일자 : 2017년 12월 15일
*/
#ifndef _SHIFTANDLEFTARROWKEY_H
#define _SHIFTANDLEFTARROWKEY_H

#include "KeyAction.h"
class TextEdit;
class ShiftAndLeftArrowKey : public KeyAction {
public:
	ShiftAndLeftArrowKey();
	virtual ~ShiftAndLeftArrowKey();
	ShiftAndLeftArrowKey(const ShiftAndLeftArrowKey& source);

	ShiftAndLeftArrowKey& operator= (const ShiftAndLeftArrowKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_SHIFTANDLEFTARROWKEY_H
