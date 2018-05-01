//DeleteKey.h
/*
���ϸ� : DeleteKey.h
��� : DeleteKeyProcess�� �����ϴ� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 15��
*/
#ifndef _DELETEKEY_H
#define _DELETEKEY_H

#include "KeyAction.h"
class DeleteKey : public KeyAction {
public:
	DeleteKey();
	virtual ~DeleteKey();
	DeleteKey(const DeleteKey& source);

	DeleteKey& operator= (const DeleteKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_DELETEKEY_H
