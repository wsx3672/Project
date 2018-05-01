//CtrlAndAKey.h
/*
파일명 : CtrlAndAKey.h
기능 : 모든 텍스트를 선택해주는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 28일 
*/

#ifndef _CTRLANDAKEY_H
#define _CTRLANDAKEY_H

#include "KeyAction.h"
class TextEdit;
class CtrlAndAKey : public KeyAction {
public:
	CtrlAndAKey();
	virtual ~CtrlAndAKey();
	CtrlAndAKey(const CtrlAndAKey& source);

	CtrlAndAKey& operator= (const CtrlAndAKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_CTRLANDAKEY_H
