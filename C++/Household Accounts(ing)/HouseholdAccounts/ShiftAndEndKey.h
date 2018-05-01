//ShiftAndEndKey.h
/*
파일명 : ShiftAndEndKey.h
기능 : 현재캐럿위치부터 현재줄의 마지막줄까지 선택해주는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 23일
*/
#ifndef _SHIFTANDENDKEY_H
#define _SHIFTANDENDKEY_H

#include "KeyAction.h"
class TextEdit;
class ShiftAndEndKey : public KeyAction {
public:
	ShiftAndEndKey();
	virtual ~ShiftAndEndKey();
	ShiftAndEndKey(const ShiftAndEndKey& source);

	ShiftAndEndKey& operator= (const ShiftAndEndKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_SHIFTANDENDKEY_H
