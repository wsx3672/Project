//KoreanEnglishChangeKey.h
/*
���ϸ� : KoreanEnglishChangeKey.h
��� : �ѿ�Ű�� ���ȴ��� Ȯ���ϴ� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 6��
*/
#ifndef _KOREANENGLISHCHANGEKEY_H
#define _KOREANENGLISHCHANGEKEY_H

#include "KeyAction.h"
class TextEdit;
class KoreanEnglishChangeKey : public KeyAction {
public:
	KoreanEnglishChangeKey();
	virtual ~KoreanEnglishChangeKey();
	KoreanEnglishChangeKey(const KoreanEnglishChangeKey& source);

	KoreanEnglishChangeKey& operator= (const KoreanEnglishChangeKey& source);
	virtual void Action(TextEdit *textEdit);
};
#endif // !_KOREANENGLISHCHANGEKEY_H
