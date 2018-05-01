//Text.h
/*
���ϸ� : Text.h
��� : Row���� �����ϴ� Ŭ����
�ۼ��� : �ڻ��
�ۼ�����  : 2017�� 12�� 4�� 
*/
#ifndef _TEXT_H
#define _TEXT_H

typedef signed long int Long;
#include "Array.h"
#include "Row.h"
#include "TextComposite.h"
class Text : public TextComposite{
public:
	Text(Long capacity = 10000);
	~Text();
	Text(const Text& source);
	Text& operator= (const Text& source);

	virtual Long Add(TextComponent *textComponent);
	virtual Long Remove(TextComponent *textComponent);
	virtual Long Remove(Long index);
	virtual Long Modify(Long index, TextComponent *textComponent);
	virtual Long Insert(Long index, TextComponent *textComponent);

	virtual TextComponent* Clone() const;

	Long Add(Row *row);
	TextComponent* GetAt(Long index);
	TextComponent* operator[](Long index);
	Long GetCapacity();
	Long GetLength();
};
inline Long Text::GetCapacity() {
	return this->capacity;
}
inline Long Text::GetLength() {
	return this->length;
}
#endif // !_TEXT_H
