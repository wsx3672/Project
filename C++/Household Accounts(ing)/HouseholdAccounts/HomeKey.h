//HomeKey.h
/*
파일명 : HomeKey.h
기능 : 캐럿위치를 현재줄의 제일 첫번째줄로 이동시키는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 15일
*/
#ifndef _HOMEKEY_H
#define _HOMEKEY_H

#include "KeyAction.h"
class TextEdit;
class HomeKey : public KeyAction {
public:
	HomeKey();
	virtual ~HomeKey();
	HomeKey(const HomeKey& source);

	HomeKey& operator= (const HomeKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_HOMEKEY_H
