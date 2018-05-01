//KoreanEnglishChangeKey.h
/*
파일명 : KoreanEnglishChangeKey.h
기능 : 한영키가 눌렸는지 확인하는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 6일
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
