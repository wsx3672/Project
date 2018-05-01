//EndKey.h
/*
파일명 : EndKey.h
기능 : 캐럿위치를 현재줄의 제일 마지막줄로 이동시키는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 15일
*/
#ifndef _ENDKEY_H
#define _ENDKEY_H

#include "KeyAction.h"
class EndKey : public KeyAction {
public:
	EndKey();
	virtual ~EndKey();
	EndKey(const EndKey& source);

	EndKey& operator= (const EndKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_ENDKEY_H
