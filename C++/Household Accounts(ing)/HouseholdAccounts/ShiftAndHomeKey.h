//ShiftAndHomeKey.h
/*
파일명 : ShiftAndHomeKey.h
기능 : 현재캐럿위치부터 현재줄의 첫번째줄까지 선택해주는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 23일
*/
#ifndef _SHIFTANDHOMEKEY_H
#define _SHIFTANDHOMEKEY_H

#include "KeyAction.h"
class TextEdit;
class ShiftAndHomeKey : public KeyAction {
public:
	ShiftAndHomeKey();
	virtual ~ShiftAndHomeKey();
	ShiftAndHomeKey(const ShiftAndHomeKey& source);

	ShiftAndHomeKey& operator= (const ShiftAndHomeKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_SHIFTANDHOMEKEY_H
