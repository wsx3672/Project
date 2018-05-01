//DeleteKeyProcess.h
/*
파일명 : DeleteKeyProcess.h
기능 : 현재캐럿위치의 다음줄을 지우기 위한 클래스
작성자 : 박상민
작성일자 : 2017년 12월 23일
*/
#ifndef _DELETEKEYPROCESS_H
#define _DELETEKEYPROCESS_H

class TextEdit;
class DeleteKeyProcess {
public:
	DeleteKeyProcess();
	~DeleteKeyProcess();
	DeleteKeyProcess(const DeleteKeyProcess& source);
	DeleteKeyProcess& operator=(const DeleteKeyProcess& source);

	void SelectionDelete(TextEdit *textEdit);
	void Delete(TextEdit *textEdit);
};
#endif // !_DELETEKEYPROCESS_H
