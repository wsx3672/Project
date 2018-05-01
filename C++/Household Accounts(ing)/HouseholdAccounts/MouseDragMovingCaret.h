//MouseDragMovingCaret.h

/*
���ϸ� : MouseDragMovingCaret.h
��� : ���콺�巡�׽� ĳ���̵��� �����ϴ� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2018�� 01�� 08��
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
