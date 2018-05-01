//KeyAction.h
/*
���ϸ� : KeyAction.h
��� : Strategy ���������� �ϱ� ���� �ʿ��� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 5��
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
