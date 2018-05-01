//SelectedBackSpaceKey.h
/*
파일명  : SelectedBackSpaceKey.h
기능 : 선택된 글자들을 지우기위한 클래스를 관리하는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 15일
*/
#ifndef _SELECTEDBACKSPACEKEY_H
#define _SELECTEDBACKSPACEKEY_H

#include "KeyAction.h"
class TextEdit;
class SelectedBackSpaceKey : public KeyAction {
public:
	SelectedBackSpaceKey();
	virtual ~SelectedBackSpaceKey();
	SelectedBackSpaceKey(const SelectedBackSpaceKey& source);

	SelectedBackSpaceKey& operator= (const SelectedBackSpaceKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_SELECTEDBACKSPACEKEY_H
