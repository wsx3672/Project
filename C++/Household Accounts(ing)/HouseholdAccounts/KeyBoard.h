//KeyBoard.h
/*
���ϸ� : KeyBoard.h
��� : Strategy ���������� �ϱ� ���ؼ� KeyAction�����ϴ� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 5�� 
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

