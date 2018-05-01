//TextAreaSelectedProcess.h
/*
파일명 : TextAreaSelectedProcess.h
기능 : 선택된 글자들을 화면에 표시를 해주는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 22일
*/

#ifndef _TEXTAREASELECTEDPROCESS_H
#define _TEXTAREASELECTEDPROCESS_H

typedef signed long int Long;
class TextEdit;
class CDC;
class TextComposite;
class TextAreaSelectedProcess {
public:
	TextAreaSelectedProcess();
	~TextAreaSelectedProcess();
	TextAreaSelectedProcess(const TextAreaSelectedProcess& source);
	TextAreaSelectedProcess& operator= (const TextAreaSelectedProcess& source);

	void AllRowAreaSelected(TextEdit *textEdit,CDC *pDC, TextComposite *textComposite, Long index);
	void SingleRowAreaSelected(TextEdit *textEdit, CDC *pDC, TextComposite *textComposite, Long index , Long length ,Long rowIndex);
	void FirstRowAreaSelected(TextEdit *textEdit, CDC *pDC, TextComposite *textComposite, Long index, Long length, Long rowIndex);
	void LastRowAreaSelected(TextEdit *textEdit, CDC *pDC, TextComposite *textComposite, Long index, Long length, Long rowIndex);
};
#endif // !_TEXTAREASELECTEDPROCESS_H

