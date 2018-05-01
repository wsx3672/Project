//LeftArrowKey.h
/*
파일명 : LeftArrowKey.h
기능 : 왼쪽 방향키처리를 위한 클래스
작성자 : 박상민
작성일자 : 2017년 12월 7일
*/
#ifndef _LEFTARROWKEY_H
#define _LEFTARROWKEY_H

#include "KeyAction.h"
class TextEdit;
class LeftArrowKey : public KeyAction {
public:
	LeftArrowKey();
	virtual ~LeftArrowKey();
	LeftArrowKey(const LeftArrowKey& source);

	LeftArrowKey& operator= (const LeftArrowKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_LEFTARROWKEY_H
