//Finder.h
/*
파일명 : Finder.h
기능 : 현재 마우스 위치에 있는 글자를 찾아주는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 29일
*/
#ifndef _FINDER_H
#define _FINDER_H

typedef signed long int Long;

class TextEdit;
class Finder {
public:
	Finder(TextEdit *textEdit);
	Finder(const Finder& source);
	~Finder();
	Finder& operator = (const Finder& source);

	void MouseLButtonClick(Long startX, Long startY);
	void MouseLButtonDrag(Long currentX, Long currentY);
private:
	TextEdit *textEdit;
};
#endif // !_FINDER_H

