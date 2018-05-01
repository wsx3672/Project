#ifndef _WORDBOOK_H
#define _WORDBOOK_H

#include "Array.h"
#include "Word.h"
#include <String>

using namespace std;
typedef signed long int Long;

class WordBook {
public:
	//디폴트생성자, 매개변수를 갖는 생성자
	WordBook(Long capacity = 20000);
	//복사생성자
	WordBook(const WordBook& source);
	//소멸자
	~WordBook();
	//기재하기
	Long Record(string spelling, string meaning, string wordClass, string example);
	//찾기
	void Find(string spelling, Long *(*indexes), Long *count);
	//지우기
	Long Erase(Long index);
	//고치기
	Long Correct(Long index, string meaning, string wordClass, string example);
	//정리하기
	void Arrange();
	Word& GetAt(Long index);
	//치환연산자
	WordBook& operator=(const WordBook& source);
	//첨자연산자
	Word& operator[](Long index);
	//포인터산술연산자
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