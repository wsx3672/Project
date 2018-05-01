//SelectedBackSpaceKey.h
/*
���ϸ�  : SelectedBackSpaceKey.h
��� : ���õ� ���ڵ��� ��������� Ŭ������ �����ϴ� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 15��
*/
#ifndef _SELECTEDBACKSPACEKEY_H
#define _SELECTEDBACKSPACEKEY_H

#include "KeyAction.h"
class TextEdit;
class SelectedBackSpaceKey : public KeyAction {
public:
	SelectedBackSpaceKey();
	virtual ~SelectedBackSpaceKey();
	SelectedBackSpaceKey(const SelectedBackSpaceKey& source);

	SelectedBackSpaceKey& operator= (const SelectedBackSpaceKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_SELECTEDBACKSPACEKEY_H
