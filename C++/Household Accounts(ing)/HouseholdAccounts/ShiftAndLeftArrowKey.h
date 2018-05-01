//ShiftAndLeftArrowKey.h
/*
���ϸ� : ShiftAndLeftArrowKey.h
��� : Shift�� �������¿��� ���� ����Ű�� ������ �� ó���� ���� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 15��
*/
#ifndef _SHIFTANDLEFTARROWKEY_H
#define _SHIFTANDLEFTARROWKEY_H

#include "KeyAction.h"
class TextEdit;
class ShiftAndLeftArrowKey : public KeyAction {
public:
	ShiftAndLeftArrowKey();
	virtual ~ShiftAndLeftArrowKey();
	ShiftAndLeftArrowKey(const ShiftAndLeftArrowKey& source);

	ShiftAndLeftArrowKey& operator= (const ShiftAndLeftArrowKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_SHIFTANDLEFTARROWKEY_H
