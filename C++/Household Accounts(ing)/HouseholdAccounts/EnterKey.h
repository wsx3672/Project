//EnterKey.h
/*
파일명 : EnterKey.h
기능 : 개행을 위한 클래스
작성자 : 박상민
작성일자 : 2017년 12월 5일 
*/
#ifndef _ENTERKEY_H
#define _ENTERKEY_H
#include "KeyAction.h"
class TextEdit;
class EnterKey : public KeyAction{
public:
	EnterKey();
	virtual ~EnterKey();
	EnterKey(const EnterKey& source);

	EnterKey& operator= (const EnterKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_ENTERKEY_H
