//Characet.h
/*
���ϸ� : Characet.h
��� : �ؽ�Ʈ �޸𸮰����� ���� �߻�Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 3��
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
