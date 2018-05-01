//KeyAction.h
/*
파일명 : KeyAction.h
기능 : Strategy 패턴적용을 하기 위해 필요한 클래스
작성자 : 박상민
작성일자 : 2017년 12월 5일
*/
#ifndef _KEYACTION_H
#define _KEYACTION_H
class TextEdit;
class KeyAction {
public:
	KeyAction();
	virtual ~KeyAction();
	KeyAction(const  KeyAction& source);

	virtual  void Action(TextEdit *textEdit);

	KeyAction& operator= (const  KeyAction& source);
};
#endif // !_KEYACTION_H
