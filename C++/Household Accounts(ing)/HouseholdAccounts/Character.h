//Characet.h
/*
파일명 : Characet.h
기능 : 텍스트 메모리관리를 위한 추상클래스
작성자 : 박상민
작성일자 : 2017년 12월 3일
*/
#ifndef _CHARACTER_H
#define _CHARACTER_H
#include "TextComponent.h"

class Character : public TextComponent {
public:

	Character();
	virtual ~Character() ;
	Character(const Character& source);
	Long CheckingSingleAndDouble();
};
#endif // !_CHARACTER_H
