//AddressBook.cpp
#include "AddressBook.h"
//����Ʈ������
AddressBook::AddressBook(Long capacity) : personals(capacity)
{
	this->capacity = capacity;
	this->length = 0;
}

//���������
AddressBook::AddressBook(const AddressBook& source) : personals(source.personals)
{
	this->capacity = source.capacity;
	this->length = source.length;
}

//�Ҹ���
AddressBook::~AddressBook() {
}

Long AddressBook::Record(string name, string address, string telephoneNumber, string emailAddress)
{
	Personal word(name, address, telephoneNumber, emailAddress);
	Long index;
	if (this->length < this->capacity) {
		index = this->personals.Store(this->length, word);
	}
	else {
		index = this->personals.AppendFromRear(word);
		this->capacity++;
	}
	this->length++;

	return index;
}

void AddressBook::Find(string name, Long *(*indexes), Long *count)
{
	this->personals.LinearSearchDuplicate(&name, indexes, count, CompareNames);
}

Long AddressBook::Erase(Long index)
{
	index = this->personals.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}
Long AddressBook::Correct(Long index, string address, string telephoneNumber, string emailAddress) {
	Personal tempPersonal = this->personals.GetAt(index);

	Personal word(tempPersonal.GetName(), address, telephoneNumber, emailAddress); //�򰥸�

	index = this->personals.Modify(index, word);

	return index;
}

void AddressBook::Arrange() {
	this->personals.InsertionSort(ComparePersonals);
}

Personal& AddressBook::GetAt(Long index) {
	return this->personals.GetAt(index);
}

AddressBook& AddressBook::operator=(const AddressBook& source)
{
	this->personals = source.personals;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Personal& AddressBook::operator[](Long index) {
	return this->personals[index];
}

Personal* AddressBook::operator + (Long index) {
	return this->personals + sizeof(index);
}

int CompareNames(void *one, void *other) {
	return (static_cast<Personal*>(one))->GetName().compare(*(static_cast<string*>(other)));
}

int ComparePersonals(void *one, void *other) {
	return (static_cast<Personal*>(one))->GetName().compare((static_cast<Personal*>(other))->GetName());
}


#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
	AddressBook addressBook(3);

	Long index = addressBook.Record("ȫ�浿", "����� ���ʱ�", "021231234", "Hong@");
	cout << addressBook[index].GetName() << " " << addressBook[index].GetAddress() << " " <<
		addressBook[index].GetTelephoneNumber() << " " << addressBook[index].GetEmailAddress() << endl;
	
	index = addressBook.Record("���浿", "����� �ȴޱ�", "02919293", "Ga@");
	cout << addressBook[index].GetName() << " " << addressBook[index].GetAddress() << " " <<
		addressBook[index].GetTelephoneNumber() << " " << addressBook[index].GetEmailAddress() << endl;

	index = addressBook.Record("���浿", "����� ������", "0021234", "Na@");
	cout << addressBook[index].GetName() << " " << addressBook[index].GetAddress() << " " <<
		addressBook[index].GetTelephoneNumber() << " " << addressBook[index].GetEmailAddress() << endl;

	index = addressBook.Record("ȫ�浿", "����� ������", "78949293", "Ha@");
	cout << addressBook[index].GetName() << " " << addressBook[index].GetAddress() << " " <<
		addressBook[index].GetTelephoneNumber() << " " << addressBook[index].GetEmailAddress() << endl;

	index = addressBook.Record("�ٱ浿", "����� ��������", "654193", "Da@");
	cout << addressBook[index].GetName() << " " << addressBook[index].GetAddress() << " " <<
		addressBook[index].GetTelephoneNumber() << " " << addressBook[index].GetEmailAddress() << endl;

	Long(*indexes);
	Long count;
	
	cout << endl << endl;
	addressBook.Find("ȫ�浿", &indexes, &count);
	
	string name;
	string address;
	string telephoneNumber;
	string emailAddress;
	Personal personal;
	Long i = 0;
	while (i < count) {
		personal = addressBook.GetAt(indexes[i]);
		name = personal.GetName();
		address = personal.GetAddress();
		telephoneNumber = personal.GetTelephoneNumber();
		emailAddress = personal.GetEmailAddress();

		cout << name << " " << address << " " << telephoneNumber << " " << emailAddress << endl;
		i++;
	}
	cout << endl << endl << "check" << endl << endl;

	i = 0;
	while (i < count) {
		cout << addressBook[indexes[i]].GetName() << " " << addressBook[indexes[i]].GetAddress() << " " << addressBook[indexes[i]].GetTelephoneNumber() << " " << addressBook[indexes[i]].GetEmailAddress() << endl;
		i++;
	}

	if (indexes != 0) {
		delete[] indexes;
		indexes = 0;
	}

	cout << endl;
	index = addressBook.Correct(2, "�λ� �߱�", "92939393", "busan@");
	cout << addressBook[index].GetName() << " " << addressBook[index].GetAddress() << " " << addressBook[index].GetTelephoneNumber() << " " << addressBook[index].GetEmailAddress() << endl << endl;

	index = addressBook.Erase(2);
	if (index == -1) {
		cout << "������" << endl << endl;
	}

	AddressBook secondAddressBook(addressBook);

	secondAddressBook.Arrange();
	i = 0;
	while (i < secondAddressBook.GetLength()) {
		cout << secondAddressBook[i].GetName() << " " << secondAddressBook[i].GetAddress() << " " << secondAddressBook[i].GetTelephoneNumber() << " " << secondAddressBook[i].GetEmailAddress() << endl;
		i++;
	}
	cout << endl;

	if (addressBook[2] == secondAddressBook[3]) {
		cout << "����" << endl;
	}
	if (addressBook[2] != secondAddressBook[2]) {
		cout << "�ٸ�" << endl;
	}

	return 0;
}