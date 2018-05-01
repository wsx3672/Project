//ShiftAndEndKey.h
/*
���ϸ� : ShiftAndEndKey.h
��� : ����ĳ����ġ���� �������� �������ٱ��� �������ִ� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 23��
*/
#ifndef _SHIFTANDENDKEY_H
#define _SHIFTANDENDKEY_H

#include "KeyAction.h"
class TextEdit;
class ShiftAndEndKey : public KeyAction {
public:
	ShiftAndEndKey();
	virtual ~ShiftAndEndKey();
	ShiftAndEndKey(const ShiftAndEndKey& source);

	ShiftAndEndKey& operator= (const ShiftAndEndKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_SHIFTANDENDKEY_H
