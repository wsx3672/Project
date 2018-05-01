//MouseDragMovingCaret.h

/*
파일명 : MouseDragMovingCaret.h
기능 : 마우스드래그시 캐럿이동을 수행하는 클래스
작성자 : 박상민
작성일자 : 2018년 01월 08일
*/
#ifndef _MOUSEDRAGMOVINGCARET_H
#define _MOUSEDRAGMOVINGCARET_H

typedef signed long int Long;
class TextEdit;
class TextComposite;
class CClientDC;
class CSize;
class MouseDragMovingCaret {
public:
	MouseDragMovingCaret();
	~MouseDragMovingCaret();
	MouseDragMovingCaret(const MouseDragMovingCaret& souce);

	void LeftMovingCaret(TextEdit *textEdit , CClientDC *cClientDC ,TextComposite *currentTextComposite , CSize *stringSize,  Long currentCharacterIndex , Long currentX);
	void RightMovingCaret(TextEdit *textEdit, CClientDC *cClientDC ,TextComposite *currentTextComposite , CSize *stringSize,Long currentCharacterIndex , Long currentX);
	
};
#endif // !_MOUSEDRAGMOVINGCARET_H
