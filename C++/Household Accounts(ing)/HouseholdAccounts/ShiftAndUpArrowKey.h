//ShiftAndUpArrowKey.h
/*
���ϸ� : ShiftAndUpArrowKey.h
��� : Shift�� �������¿��� ���� ����Ű�� ������ �� ó���� ���� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 22��
*/
#ifndef _SHIFTANDUPARROWKEY_H
#define _SHIFTANDUPARROWKEY_H

#include "KeyAction.h"
class TextEdit;
class ShiftAndUpArrowKey : public KeyAction {
public:
	ShiftAndUpArrowKey();
	virtual ~ShiftAndUpArrowKey();
	ShiftAndUpArrowKey(const ShiftAndUpArrowKey& source);

	ShiftAndUpArrowKey& operator= (const ShiftAndUpArrowKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_SHIFTANDUPARROWKEY_H
