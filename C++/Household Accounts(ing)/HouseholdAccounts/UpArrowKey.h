//UpArrowKey.h
/*
���ϸ� : UpArrowKey.h
��� : ���� ����Űó���� ���� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 8��
*/
#ifndef _UPARROWKEY_H
#define _UPARROWKEY_H

#include "KeyAction.h"
class TextEdit;
class UpArrowKey : public KeyAction {
public:
	UpArrowKey();
	virtual ~UpArrowKey();
	UpArrowKey(const UpArrowKey& source);

	UpArrowKey& operator= (const UpArrowKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_UPARROWKEY_H
