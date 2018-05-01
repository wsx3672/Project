#ifndef _WORDBOOK_H
#define _WORDBOOK_H

#include "Array.h"
#include "Word.h"
#include <String>

using namespace std;
typedef signed long int Long;

class WordBook {
public:
	//����Ʈ������, �Ű������� ���� ������
	WordBook(Long capacity = 20000);
	//���������
	WordBook(const WordBook& source);
	//�Ҹ���
	~WordBook();
	//�����ϱ�
	Long Record(string spelling, string meaning, string wordClass, string example);
	//ã��
	void Find(string spelling, Long *(*indexes), Long *count);
	//�����
	Long Erase(Long index);
	//��ġ��
	Long Correct(Long index, string meaning, string wordClass, string example);
	//�����ϱ�
	void Arrange();
	Word& GetAt(Long index);
	//ġȯ������
	WordBook& operator=(const WordBook& source);
	//÷�ڿ�����
	Word& operator[](Long index);
	//�����ͻ��������
	Word* operator+(Long index);

	Long GetCapacity() const;
	Long GetLength() const;

private:
	Array<Word> words;
	Long capacity;
	Long length;
};

int CompareSpellings(void *one, void *other);
int CompareWords(void *one, void *other);

inline Long WordBook::GetCapacity() const {
	return this->capacity;
}
inline Long WordBook::GetLength()const {
	return this->length;
}
#endif // _WORDBOOK_H