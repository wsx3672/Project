//Row.h
/*
파일명 : Row.h
기능 : 한줄에 해당하는 Character들을 관리하는 클래스
작성자 : 박상민
작성일자 : 2017년12월3일
*/
#ifndef _ROW_H
#define _ROW_H

typedef signed long int Long;

#include "Array.h"
#include "TextComposite.h"
class Character;
class Row  :  public TextComposite{
public:
	Row(Long capacity = 1028);
	~Row();
	Row(const Row& source);

	Row& operator= (const Row& source);

	virtual Long Add(TextComponent *textComponent);
	virtual Long Remove(TextComponent *textComponent);
	virtual Long Remove(Long index);
	virtual Long Modify(Long index, TextComponent *textComponent);
	virtual Long Insert(Long index, TextComponent *textComponent);

	virtual TextComponent* Clone() const;

	TextComponent* GetAt(Long index);
	TextComponent* operator [] (Long index);
	Long GetCapacity()const;
	Long GetLength()const;
};
inline Long Row::GetCapacity()const {
	return this->capacity;
}
inline Long Row::GetLength()const {
	return this->length;
}
#endif // !_ROW_H
