//WritingKorean.h
/*
파일명 : WritingKorean.h
기능 : 한글입력시 조합시작 , 조합중 , 조합끝을 관리하는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 6일
*/
#ifndef _WRITINGKOREAN_H
#define _WRITINGKOREAN_H

typedef signed long int Long;
#pragma comment(lib,"imm32")
#include <afxwin.h>
class TextEdit;
class WritingKorean {
public:
	WritingKorean();
	~WritingKorean();
	WritingKorean(const WritingKorean& source);
	WritingKorean& operator=(const WritingKorean& source);
	void WritingHanguel(WPARAM wParam, LPARAM lParam, HIMC hIMC, TextEdit *textEdit);
};
#endif // !_WRITINGKOREAN_H
