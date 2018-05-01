//DoubleByteCharacter.h
/*
파일명 : DoubleByteCharacter.h
기능 : 2바이트 메모리를 가진 char를 관리하는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 3일
*/
#ifndef _DOUBLEBYTECHARACTER_H
#define _DOUBLEBYTECHARACTER_H

#include "Character.h"

class DoubleByteCharacter : public Character{
public:
	DoubleByteCharacter();
	DoubleByteCharacter(char *(characters));
	virtual ~DoubleByteCharacter();
	DoubleByteCharacter(const DoubleByteCharacter& source);


	virtual TextComponent* Clone() const;


	DoubleByteCharacter& operator= (const DoubleByteCharacter& source);
	char* GetCharacter() const;
private:
	char characters[2];
};

inline char* DoubleByteCharacter::GetCharacter()const {
	return const_cast<char*>(this->characters);
	//반환이 char* 뒤에 const라면 const_cast해줘야함
}
#endif // !_DOUBLEBYTECHARACTER_H

