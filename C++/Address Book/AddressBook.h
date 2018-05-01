#pragma once
#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H
#include "Array.h"
#include "Personal.h"
#include <String>
using namespace std;

typedef signed long int Long;


class AddressBook {
public:
	AddressBook(Long capacity = 20000);	//디폴트생성자,매개변수를 갖는 생성자
	AddressBook(const AddressBook& source);//복사생성자
	~AddressBook();//소멸자
	Long Record(string name, string address, string telephoneNumber, string emailAddress);	//기재하기
	void Find(string name, Long *(*indexes), Long *count);	//찾기
	Long Correct(Long index, string address, string telephoneNumber, string emailAddress);
	Long Erase(Long index);		//지우기
	void Arrange();		//정리하기
	Personal& GetAt(Long index);

	AddressBook& operator=(const AddressBook& source);	//치환연산자
	Personal& operator[](Long index);	//첨자연산자
	Personal* operator+(Long index);	//포인터산술연산자

	Long GetCapacity() const;
	Long GetLength() const;

private:
	Array<Personal> personals;
	Long capacity;
	Long length;
};
int CompareNames(void *one, void *other);
int ComparePersonals(void *one, void *other);
inline Long AddressBook::GetCapacity() const {
	return this->capacity;
}
inline Long AddressBook::GetLength()const {
	return this->length;
}
#endif // _ADDRESSBOOK_H