//DoubleByteCharacter.h
/*
���ϸ� : DoubleByteCharacter.h
��� : 2����Ʈ �޸𸮸� ���� char�� �����ϴ� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 3��
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
	//��ȯ�� char* �ڿ� const��� const_cast�������
}
#endif // !_DOUBLEBYTECHARACTER_H

