//ShiftAndRightArrowKey.h
/*
파일명 : ShiftAndRightArrowKey.h
기능 :  Shift를 누른상태에서 오른쪽 방향키를 눌렀을 때 처리를 위한 클래스
작성자 : 박상민 
작성일자 : 2017년 12월 18일
*/
#ifndef _SHIFTANDRIGHTARROWKEY_H
#define _SHIFTANDRIGHTARROWKEY_H

#include "KeyAction.h"
class TextEdit;
class ShiftAndRightArrowKey : public KeyAction {
public:
	ShiftAndRightArrowKey();
	virtual ~ShiftAndRightArrowKey();
	ShiftAndRightArrowKey(const ShiftAndRightArrowKey& source);

	ShiftAndRightArrowKey& operator= (const ShiftAndRightArrowKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_SHIFTANDRIGHTARROWKEY_H
