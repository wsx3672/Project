//SingleByteCharacter.h
/*
파일명 : SingleByteCharacter.h
기능 : 1바이트 메모리를 가진 char를 관리하는 클래스
작성자 : 박상민
작성일자 : 2017년 12월 3일
*/
#ifndef _SINGLEBYTECHARACTER_H
#define _SINGLEBYTECHARACTER_H

#include "Character.h"

class SingleByteCharacter : public Character {
public:
	SingleByteCharacter();
	SingleByteCharacter(char character);
	virtual ~SingleByteCharacter();
	SingleByteCharacter(const SingleByteCharacter& source);

	virtual TextComponent* Clone() const;

	SingleByteCharacter& operator= (const SingleByteCharacter& source);
	char GetCharacter() const;
private:
	char character;
};
inline char SingleByteCharacter::GetCharacter() const {
	return this->character;
}
#endif // !_SINGLEBYTECHARACTER_H
