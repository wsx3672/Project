//DownArrowKey.h
/*
���ϸ� : DownArrowKey.h
��� : �Ʒ��� ����Űó���� ���� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 8��
*/
#ifndef _DOWNARROWKEY_H
#define _DOWNARROWKEY_H

#include "KeyAction.h"
class TextEdit;
class DownArrowKey : public KeyAction {
public:
	DownArrowKey();
	virtual ~DownArrowKey();
	DownArrowKey(const DownArrowKey& source);

	DownArrowKey& operator= (const DownArrowKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_DOWNARROWKEY_H
