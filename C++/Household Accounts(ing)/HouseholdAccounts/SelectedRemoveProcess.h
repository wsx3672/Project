//SelectedRemoveProcess.h
/*
파일명: SelectedRemoveProcess.h
기능 : 선택된 글자들을 지우는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 21일 
*/
#ifndef _SELECTEDREMOVEPROCESS_H
#define _SELECTEDREMOVEPROCESS_H
 
typedef signed long int Long;

class TextEdit;
class SelectedRemoveProcess {
public:
	SelectedRemoveProcess();
	~SelectedRemoveProcess();
	SelectedRemoveProcess(const SelectedRemoveProcess& source);

	void SelectedRemove(TextEdit *textEdit);
	void SelectedRemoveAfterSetCaret(TextEdit *textEdit);
};
#endif // !_SELECTEDREMOVEPROCESS_H
