//RightArrowKey.h
/*
파일명 : RightArrowKey.h
기능 : 오른쪽 방향키처리를 위한 클래스
작성자 : 박상민
작성일자 : 2017년 12월 8일
*/
#ifndef _RIGHTARROWKEY_H
#define _RIGHTARROWKEY_H

#include "KeyAction.h"
class TextEdit;
class RightArrowKey : public KeyAction {
public:
	RightArrowKey();
	virtual ~RightArrowKey();
	RightArrowKey(const RightArrowKey& source);

	RightArrowKey& operator= (const RightArrowKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_RIGHTARROWKEY_H
