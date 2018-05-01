//ShiftAndUpArrowKey.h
/*
파일명 : ShiftAndUpArrowKey.h
기능 : Shift를 누른상태에서 위쪽 방향키를 눌렀을 때 처리를 위한 클래스
작성자 : 박상민
작성일자 : 2017년 12월 22일
*/
#ifndef _SHIFTANDUPARROWKEY_H
#define _SHIFTANDUPARROWKEY_H

#include "KeyAction.h"
class TextEdit;
class ShiftAndUpArrowKey : public KeyAction {
public:
	ShiftAndUpArrowKey();
	virtual ~ShiftAndUpArrowKey();
	ShiftAndUpArrowKey(const ShiftAndUpArrowKey& source);

	ShiftAndUpArrowKey& operator= (const ShiftAndUpArrowKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_SHIFTANDUPARROWKEY_H
