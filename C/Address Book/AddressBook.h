
//AddressBook.h
/*
파일명칭:AddressBook.h
기능:주소록 헤더파일
작성자:박상민
작성일자:2017년6월13일
*/
#ifndef  _ADDRESSBOOK_H   //가드
#define _ADDRESSBOOK_H   //가드

#define NAME 11
#define ADDRESS 128
#define TELEPHONE 12
#define EMAIL 128
//자료형설계
typedef signed long int Long;
typedef struct _personal {
	char name[NAME];
	char address[ADDRESS];
	char telephoneNumber[TELEPHONE];
	char emailAddress[EMAIL];
}Personal;
typedef struct _addressBook {
	Personal(*personals);
	Long capacity;
	Long length;
}AddressBook;
//함수선언
void Create(AddressBook *addressBook, Long capacity);
Long Record(AddressBook *addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress));
void Find(AddressBook *addressBook, char(*name), Long*(*indexes), Long *count);
Long Correct(AddressBook *addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress));
Long Erase(AddressBook *addressBook, Long index);
void Arrange(AddressBook *addressBook);
void Destroy(AddressBook *addressBook);
Long Load(AddressBook *addressBook);
Long Save(AddressBook *addressBook);

#endif // ADDRESSBOOK_H

