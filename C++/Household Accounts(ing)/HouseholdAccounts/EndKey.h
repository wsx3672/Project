//EndKey.h
/*
���ϸ� : EndKey.h
��� : ĳ����ġ�� �������� ���� �������ٷ� �̵���Ű�� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 15��
*/
#ifndef _ENDKEY_H
#define _ENDKEY_H

#include "KeyAction.h"
class EndKey : public KeyAction {
public:
	EndKey();
	virtual ~EndKey();
	EndKey(const EndKey& source);

	EndKey& operator= (const EndKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_ENDKEY_H
