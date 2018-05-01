//UpArrowKey.h
/*
파일명 : UpArrowKey.h
기능 : 위쪽 방향키처리를 위한 클래스
작성자 : 박상민
작성일자 : 2017년 12월 8일
*/
#ifndef _UPARROWKEY_H
#define _UPARROWKEY_H

#include "KeyAction.h"
class TextEdit;
class UpArrowKey : public KeyAction {
public:
	UpArrowKey();
	virtual ~UpArrowKey();
	UpArrowKey(const UpArrowKey& source);

	UpArrowKey& operator= (const UpArrowKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_UPARROWKEY_H
