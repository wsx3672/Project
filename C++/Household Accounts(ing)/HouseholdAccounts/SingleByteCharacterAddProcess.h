//SingleByteCharacterAddProcess.h
/*
파일명 : SingleByteCharacterAddProcess.h
기능 : 1바이트 char를 자료구조에 Add해주는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 26일
*/
#ifndef _SINGLEBYTECHARACTERADDPROCESS_H
#define _SINGLEBYTECHARACTERADDPROCESS_H

typedef signed long int Long;
class TextEdit;
class SingleByteCharacterAddProcess {
public:
	SingleByteCharacterAddProcess();
	~SingleByteCharacterAddProcess();
	SingleByteCharacterAddProcess(const SingleByteCharacterAddProcess& source);

	Long SingleByteCharacterAdd(char addChar, TextEdit *textEdit);
};
#endif // !_SINGLEBYTECHARACTERADDPROCESS_H

