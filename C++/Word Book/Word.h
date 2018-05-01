#pragma once
//Word.h
#ifndef _WORD_H
#define _WORD_H
#include <string>
using namespace std;

class Word {				//클래스
public:
	Word();		//디폴트생성자
	Word(string spelling, string meaning, string wordClass, string example);		//매개변수가 속성개수인 생성자
	Word(const Word& source);//복사생성자
	~Word();		//소멸자
	bool IsEqual(const Word& source);		//같음을 확인
	bool IsNotEqual(const Word& source);	//같지않음을확인
	bool operator ==(const Word& source);	//==연산자
	bool operator !=(const Word& source);	//!=연산자						//멤버함수
	Word& operator =(const Word& source);	//치환연산자
	string& GetSpelling() const;	//스펠링 뽑기
	string& GetMeaning() const;		//의미 뽑기
	string& GetWordClass() const;	//품사뽑기
	string& GetExample() const;		//예문뽑기																			//클래스멤버

private:

	string spelling;
	string meaning;
	string wordClass;														//데이터멤버
	string example;
};

inline string& Word::GetSpelling() const {		//반환이 &이거나 뒤에 const가 붙으면 const_cast
	return const_cast<string&>(this->spelling);
}
inline string& Word::GetMeaning() const {		//반환이 &이거나 뒤에 const가 붙으면 const_cast
	return const_cast<string&>(this->meaning);
}
inline string& Word::GetWordClass() const {		//반환이 &이거나 뒤에 const가 붙으면 const_cast
	return const_cast<string&>(this->wordClass);
}
inline string& Word::GetExample() const {		//반환이 &이거나 뒤에 const가 붙으면 const_cast
	return const_cast<string&>(this->example);
}
#endif // _WORD_H
