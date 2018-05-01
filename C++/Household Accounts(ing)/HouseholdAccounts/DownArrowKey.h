//DownArrowKey.h
/*
파일명 : DownArrowKey.h
기능 : 아래쪽 방향키처리를 위한 클래스
작성자 : 박상민
작성일자 : 2017년 12월 8일
*/
#ifndef _DOWNARROWKEY_H
#define _DOWNARROWKEY_H

#include "KeyAction.h"
class TextEdit;
class DownArrowKey : public KeyAction {
public:
	DownArrowKey();
	virtual ~DownArrowKey();
	DownArrowKey(const DownArrowKey& source);

	DownArrowKey& operator= (const DownArrowKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_DOWNARROWKEY_H
