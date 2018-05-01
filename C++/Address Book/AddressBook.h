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
	AddressBook(Long capacity = 20000);	//����Ʈ������,�Ű������� ���� ������
	AddressBook(const AddressBook& source);//���������
	~AddressBook();//�Ҹ���
	Long Record(string name, string address, string telephoneNumber, string emailAddress);	//�����ϱ�
	void Find(string name, Long *(*indexes), Long *count);	//ã��
	Long Correct(Long index, string address, string telephoneNumber, string emailAddress);
	Long Erase(Long index);		//�����
	void Arrange();		//�����ϱ�
	Personal& GetAt(Long index);

	AddressBook& operator=(const AddressBook& source);	//ġȯ������
	Personal& operator[](Long index);	//÷�ڿ�����
	Personal* operator+(Long index);	//�����ͻ��������

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