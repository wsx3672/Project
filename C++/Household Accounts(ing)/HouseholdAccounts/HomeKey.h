//HomeKey.h
/*
���ϸ� : HomeKey.h
��� : ĳ����ġ�� �������� ���� ù��°�ٷ� �̵���Ű�� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 15��
*/
#ifndef _HOMEKEY_H
#define _HOMEKEY_H

#include "KeyAction.h"
class TextEdit;
class HomeKey : public KeyAction {
public:
	HomeKey();
	virtual ~HomeKey();
	HomeKey(const HomeKey& source);

	HomeKey& operator= (const HomeKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_HOMEKEY_H
