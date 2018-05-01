//WriteKoreanTextProcess.h
/*
파일명 : WriteKoreanTextProcess.h
기능 : 한글입력시 각각에 상태에 맞게 처리되는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 6일
*/
#ifndef _WRITEKOREANTEXTPROCESS_H
#define _WRITEKOREANTEXTPROCESS_H

typedef signed long int Long;

class TextEdit;
class WriteKoreanTextProcess {
public:
	WriteKoreanTextProcess();
	WriteKoreanTextProcess(const WriteKoreanTextProcess& source);
	~WriteKoreanTextProcess();
public:
	void EndComposition(TextEdit *textEdit, Long bufferLength, char(*buffer));
	void StartComposition(TextEdit *textEdit, Long bufferLength, char(*buffer));
	void DuringComposition(TextEdit *textEdit, Long bufferLength, char(*buffer));
};

#endif // _WRITEKOREATEXTPROCESS_H