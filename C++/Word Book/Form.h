//Form.h
#ifndef _FORM_H
#define _FORM_H
#include "WordBook.h"

class WordBook;
class Form {
public:
	void DisplayMenu();   // 메뉴
	void FormForRecording(WordBook& wordBook);   // [1] 기재하기
	void FormForFinding(WordBook& wordBook);      // [2] 찾기
	void FormForCorrecting(WordBook& wordBook);   // [3] 고치기
	void FormForErasing(WordBook& wordBook);      // [4] 지우기
	void FormForArranging(WordBook& wordBook);   // [5] 정리하기
	void FormForViewAll(WordBook& wordBook);      // [6] 전체보기
private:
	WordBook wordBook;
};
#endif //_FORM_H