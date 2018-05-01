//BackSpaceKey.h
/*
파일명 : BackSpaceKey.h
기능 : 한글자를 삭제하기 위한 클래스
작성자 : 박상민
작성일자 : 2017년 12월 5일 
*/
#ifndef _BACKSPACEKEY_H
#define _BACKSPACEKEY_H

#include "KeyAction.h"
class TextEdit;
class BackSpaceKey : public KeyAction {
public:
	BackSpaceKey();
	virtual ~BackSpaceKey();
	BackSpaceKey(const BackSpaceKey& source);

	BackSpaceKey& operator= (const BackSpaceKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_BACKSPACEKEY_H
