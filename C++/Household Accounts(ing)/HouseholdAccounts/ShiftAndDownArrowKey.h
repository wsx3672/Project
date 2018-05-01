//ShiftAndDownArrowKey.h
/*
파일명 : ShiftAndDownArrowKey.h
기능 : Shift를 누른상태에서 아래쪽 방향키를 눌렀을 때 처리를 위한 클래스
작성자 : 박상민
작성일자 : 2017년 12월 22일 
*/
#ifndef _SHIFTANDDOWNARROWKEY_H
#define _SHIFTANDDOWNARROWKEY_H

#include "KeyAction.h"
class TextEdit;
class ShiftAndDownArrowKey : public KeyAction {
public:
	ShiftAndDownArrowKey();
	virtual ~ShiftAndDownArrowKey();
	ShiftAndDownArrowKey(const ShiftAndDownArrowKey& source);

	ShiftAndDownArrowKey& operator= (const ShiftAndDownArrowKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_SHIFTANDDOWNARROWKEY_H
