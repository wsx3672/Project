//TextComponent.h
/*
파일명 : TextComponent.h
기능 : Composite 패턴을 구상하기 위한 말단객체 클래스
작성자 : 박상민
작성일자 : 2017년 12월 4일 
*/
#ifndef _TEXTCOMPONENT_H
#define _TEXTCOMPONENT_H
typedef signed long int Long;

class TextComposite;
class TextComponent {
protected:
	TextComponent();
public:
	virtual ~TextComponent();
	TextComponent(const TextComponent& source);
	TextComponent& operator= (const TextComponent& source);


	virtual TextComponent* Clone() const = 0;

	virtual Long Add(TextComponent *textComponent);
	virtual Long Insert(Long index,TextComponent *textComponent);
	virtual Long Remove(TextComponent *textComponent);
	virtual TextComposite* GetComposite();

};
#endif // !_TEXTCOMPONENT_H
