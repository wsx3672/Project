//TextAreaSelected.h
/*
파일명 : TextAreaSelected.h
기능 : 선택된 글자들을 관리하는 클래스
작성자 : 박상민 
작성일자 : 2017년 12월 15일
*/

#ifndef _TEXTAREASELECTED_H
#define _TEXTAREASELECTED_H
typedef signed long int Long;

#include "Array.h"
#include "TextComposite.h"
class Caret;
class TextEdit;
class TextAreaSelected : TextComposite{
public:
	TextAreaSelected(Long capacity = 50000);
	TextAreaSelected(const TextAreaSelected& source);
	~TextAreaSelected();

	TextAreaSelected& operator= (const TextAreaSelected& source);
	TextComponent* operator[](Long index);

	void SelectedTextArea(TextEdit *textEdit,CDC *pDC);
	virtual Long Add(TextComponent *textComponent);
	virtual Long Remove(TextComponent *textComponent);
	virtual Long Remove(Long index);
	virtual Long Modify(Long index, TextComponent *textComponent);
	virtual Long Insert(Long index, TextComponent *textComponent);
	virtual Long Find(TextComponent *textComponent);
	virtual TextComponent* Clone() const;
	virtual void DeleteAllItems();
	TextComponent* GetAt(Long index);

	void  Setting(Caret *caret);
	Long SetStartRowIndex(Long rowIndex);
	Long SetStartX(Long x);
	Long SetStartY(Long y);
	Long SetStartCharacterIndex(Long characterIndex);
	Long GetStartRowIndex() const;
	Long GetStartX() const;
	Long GetStartY() const;
	Long GetStartCharacterIndex() const;
	
public:
	Long GetCapacity() const;
	Long GetLength() const;
private:
	Long startRowIndex;
	Long startX;
	Long startY;
	Long startCharacterIndex;
};

inline Long TextAreaSelected::GetCapacity() const {
	return this->capacity;
}
inline Long TextAreaSelected::GetLength() const {
	return this->length;
}
inline Long TextAreaSelected::GetStartRowIndex() const {
	return this->startRowIndex;
}
inline Long TextAreaSelected::GetStartX() const {
	return this->startX;
}
inline Long TextAreaSelected::GetStartY() const {
	return this->startY;
}
inline Long TextAreaSelected::GetStartCharacterIndex() const {
	return this->startCharacterIndex;
}
#endif // !_TEXTAREASELECTED_H
