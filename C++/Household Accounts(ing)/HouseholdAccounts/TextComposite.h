//TextComposite.h
/*
파일명 : TextComposite.h
기능 : Composite 패턴을 구상하기 위한 복합객체 클래스
작성자 : 박상민
작성일자 : 2017년 12월 4일
*/
#ifndef _TEXTCOMPOSITE_H
#define _TEXTCOMPOSITE_H
typedef signed long int Long;

#include "TextComponent.h"
#include "Array.h"
#include <afxwin.h>
#include <string>
using namespace std;
class TextComposite : public TextComponent {
public:
	virtual ~TextComposite();
	TextComposite(const TextComposite& source);
	TextComposite& operator=(const TextComposite& source);

	virtual TextComposite* GetComposite();
	virtual Long Add(TextComponent *textComponent);
	virtual Long Remove(TextComponent *textComponent);
	virtual Long Remove(Long index);
	virtual Long Modify(Long index, TextComponent *textComponent);
	virtual Long Insert(Long index, TextComponent *textComponent);
	virtual void DeleteAllItems();
	Long GetCapacity();
	Long GetLength();
	TextComponent *GetAt(Long index);
	TextComponent *operator[](Long ingex);
	TextComposite(Long capacity = 10000 );
	CString MakeCString();
	CString MakeCString(Long index);
//CString MakeCString(Long length);
	CString MakeCString(Long firstIndex, Long secondIndex);
	Long GetSelectedWidth(CDC *cdc);
	Long Find(TextComponent *textComponent);
protected:
	Array<TextComponent*> textComponents;
	Long capacity;
	Long length;
};
inline Long TextComposite::GetCapacity() {
	return this->capacity;
}
inline Long TextComposite::GetLength() {
	return this->length;
}
#endif // !_TEXTCOMPOSITE_H
