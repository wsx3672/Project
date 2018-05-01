//KeyBoard.h
/*
파일명 : KeyBoard.h
기능 : Strategy 패턴적용을 하기 위해서 KeyAction관리하는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 5일 
*/
#ifndef _KEYBOARD_H
#define _KEYBOARD_H

class KeyAction;
class TextEdit;

#include <afxwin.h>

class KeyBoard {
public:
	KeyBoard();
	KeyBoard(const KeyBoard& source);
	~KeyBoard();

	KeyBoard& operator=(const KeyBoard& source);

	KeyAction* Action(TextEdit *textEdit, UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	KeyAction *keyAction;
};
#endif // !_KEYBOARD_H

