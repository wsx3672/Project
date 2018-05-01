//DeleteKey.h
/*
파일명 : DeleteKey.h
기능 : DeleteKeyProcess를 관리하는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 15일
*/
#ifndef _DELETEKEY_H
#define _DELETEKEY_H

#include "KeyAction.h"
class DeleteKey : public KeyAction {
public:
	DeleteKey();
	virtual ~DeleteKey();
	DeleteKey(const DeleteKey& source);

	DeleteKey& operator= (const DeleteKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_DELETEKEY_H
