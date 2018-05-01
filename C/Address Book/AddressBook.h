
//AddressBook.h
/*
���ϸ�Ī:AddressBook.h
���:�ּҷ� �������
�ۼ���:�ڻ��
�ۼ�����:2017��6��13��
*/
#ifndef  _ADDRESSBOOK_H   //����
#define _ADDRESSBOOK_H   //����

#define NAME 11
#define ADDRESS 128
#define TELEPHONE 12
#define EMAIL 128
//�ڷ�������
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
//�Լ�����
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

