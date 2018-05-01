#pragma once
//Word.h
#ifndef _WORD_H
#define _WORD_H
#include <string>
using namespace std;

class Word {				//Ŭ����
public:
	Word();		//����Ʈ������
	Word(string spelling, string meaning, string wordClass, string example);		//�Ű������� �Ӽ������� ������
	Word(const Word& source);//���������
	~Word();		//�Ҹ���
	bool IsEqual(const Word& source);		//������ Ȯ��
	bool IsNotEqual(const Word& source);	//����������Ȯ��
	bool operator ==(const Word& source);	//==������
	bool operator !=(const Word& source);	//!=������						//����Լ�
	Word& operator =(const Word& source);	//ġȯ������
	string& GetSpelling() const;	//���縵 �̱�
	string& GetMeaning() const;		//�ǹ� �̱�
	string& GetWordClass() const;	//ǰ��̱�
	string& GetExample() const;		//�����̱�																			//Ŭ�������

private:

	string spelling;
	string meaning;
	string wordClass;														//�����͸��
	string example;
};

inline string& Word::GetSpelling() const {		//��ȯ�� &�̰ų� �ڿ� const�� ������ const_cast
	return const_cast<string&>(this->spelling);
}
inline string& Word::GetMeaning() const {		//��ȯ�� &�̰ų� �ڿ� const�� ������ const_cast
	return const_cast<string&>(this->meaning);
}
inline string& Word::GetWordClass() const {		//��ȯ�� &�̰ų� �ڿ� const�� ������ const_cast
	return const_cast<string&>(this->wordClass);
}
inline string& Word::GetExample() const {		//��ȯ�� &�̰ų� �ڿ� const�� ������ const_cast
	return const_cast<string&>(this->example);
}
#endif // _WORD_H
