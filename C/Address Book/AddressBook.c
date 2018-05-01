//AddressBook.c
/*
���ϸ�Ī:AddressBook.c
���:����,�ּ�,��ȭ��ȣ,�̸����� �Է¹޾� �ּҷϿ� ���� �����Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��6��13��
*/
//��ũ�μ���
#include "AddressBook.h"
//#include "Form.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)
//�Լ�����
/*
int main(int argc, char *argv[]) {
	AddressBook addressBook;
	Long menu;
	Create(&addressBook, 60000);
	DisplayMenu(); scanf("%d", &menu);
	while (menu != 0)
	{
		switch (menu)
		{
		case 1:FormForRecording(&addressBook); break;
		case 2:FormForFinding(&addressBook); break;
		case 3:FormForCorrecting(&addressBook); break;
		case 4:FormForErasing(&addressBook); break;
		case 5:FormForArranging(&addressBook); break;
		case 6:FormForViewAll(&addressBook); break;
		default:break;
		}
		DisplayMenu(); rewind(stdin); scanf("%d", &menu);
	}
	Destroy(&addressBook);
	return 0;
}
*/ 

/*
�Լ��̸�:Create
���:�Ҵ緮�� �Է¹޾� �Ҵ緮��ŭ ���ε��� �غ��Ѵ�
�Է�:�Ҵ緮
���:X
*/
void Create(AddressBook *addressBook, Long capacity)
{
	addressBook->personals = (Personal(*))calloc(capacity, sizeof(Personal));
	addressBook->capacity = capacity;
	addressBook->length = 0;
}
/*
�Լ��̸�:Record
���:�̸�,�ּ�,��ȭ��ȣ,�̸����ּҸ� �Է¹޾� ����ִ� �ٿ� ���´� �� ������ ������ ���ο� ǥ�� ���� ���´�.
�Է�:�̸�,�ּ�,��ȭ��ȣ,�̸����ּ�
���:��ȣ
*/
Long Record(AddressBook *addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress))
{
	Long index;
	Long i = 0;
	Long j = 0;
	Personal(*temps);

	while (i < addressBook->capacity && strcmp(addressBook->personals[i].name, "") != 0)
	{
		i++;
	}
	if (i >= addressBook->capacity)
	{
		temps = (Personal(*))calloc(addressBook->capacity + 1, sizeof(Personal));
		while (j < addressBook->length)
		{
			temps[j] = addressBook->personals[j];
			j++;
		}
		if (addressBook->personals != NULL)
		{
			free(addressBook->personals);
		}
		addressBook->personals = temps;
		addressBook->capacity += 1;
	}
	index = i;
	strcpy(addressBook->personals[index].name, name);
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);
	addressBook->length += 1;
	return index;
}
/*
�Լ��̸�:Find
���:�Է¹��� �̸��� ���� ���� ã�´�
�Է�:�̸�
���:�����,������ġ��
*/
void Find(AddressBook *addressBook, char(*name), Long*(*indexes), Long *count)
{
	Long index = 0;
	Long i = 0;
	*count = 0;

	while (index < addressBook->length)
	{
		if (strcmp(addressBook->personals[index].name, name) == 0)
		{
			(*count)++;
		}
		index++;
	}
	if (*count > 0)
	{
		*indexes = (Long(*))calloc((*count), sizeof(Long));
	}
	index = 0;
	while (index < addressBook->length && i<*count)
	{
		if (strcmp(addressBook->personals[index].name, name) == 0)
		{
			(*indexes)[i] = index;
			i++;
		}
		index++;
	}
}

/*
�Լ��̸�:Correct
���:������ ������ġ,�ּ�,��ȭ��ȣ,�̸����ּҸ� �Է¹޾� �ش��ٿ� ���´�
�Է�:������ġ,�ּ�,��ȭ��ȣ,�̸����ּ�
���:������ġ
*/
Long Correct(AddressBook *addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress))
{
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);
	return index;
}
/*
�Լ��̸�:Erase
���:������ġ�� �Է¹޾� �ش����� �����
�Է�:������ġ
���:������ġ
*/
Long Erase(AddressBook *addressBook, Long index)
{
	Long i = 0;
	Long j = 0;
	Personal(*temps);

	if (addressBook->capacity > 1)
	{
		temps = (Personal(*))calloc(addressBook->capacity - 1, sizeof(Personal));
	}
	while (j < addressBook->length)
	{
		if (j != index)
		{
			temps[i] = addressBook->personals[i];
			i++;
		}
		j++;
	}
	if (addressBook->personals != NULL)
	{
		free(addressBook->personals);
		addressBook->personals = NULL;
	}
	if (addressBook->capacity > 1)
	{
		addressBook->personals = temps;
	}
	addressBook->length -= 1;
	addressBook->capacity += 1;
	index = -1;
	return index;
}
/*
�Լ��̸�:Arrange
���:������������ �����Ѵ�
�Է�:X
���:X
*/
void Arrange(AddressBook *addressBook)
{
	Personal personal;
	Long i = 1;
	Long j;
	while (i < addressBook->length)
	{
		j = i - 1;
		personal = addressBook->personals[i];
		while (j >= 0 && strcmp(personal.name, addressBook->personals[j].name) < 0)
		{
			addressBook->personals[j + 1] = addressBook->personals[j];
			j--;
		}
		addressBook->personals[j + 1] = personal;
		i++;
	}
}
/*
�Լ��̸�:Destroy
���:���ε��� �Ҵ������Ѵ�
�Է�:X
���:X
*/
void Destroy(AddressBook *addressBook)
{
	if (addressBook->personals != NULL)
	{
		free(addressBook->personals);
	}
}
/*
�Լ��̸�:Load
���:�ּҷϿ� �����Ѵ�
�Է�:����
���:���ǰ���
*/
Long Load(AddressBook *addressBook) {
	Long count = 0;
	Long i;
	Long index;
	Personal personal;
	Personal (*temps);
	FILE *file;
	int flag;

	file = fopen("AddressBook.dat", "rb");
	if (file != NULL) 
	{
		flag = fread(&personal, sizeof(Personal), 1, file);
		while (!feof(file) && flag != 0) 
		{
			if (addressBook->length >= addressBook->capacity)
			{
				temps = (Personal(*))calloc(addressBook->capacity + 1, sizeof(Personal));
				i = 0;
				while (i < addressBook->length) 
				{
					temps[i] = addressBook->personals[i];
					i++;
				}
				if(addressBook->personals !=NULL)
				{
					free(addressBook->personals);
					addressBook->personals = NULL;
				}
				addressBook->personals = temps;
				(addressBook->capacity)++;
			}
			index = addressBook->length;
			addressBook->personals[index] = personal;
			(addressBook->length)++;
			count++;
			flag = fread(&personal, sizeof(Personal), 1, file);
		}
		fclose(file);
	}
	return count;
}
/*
�Լ��̸�:Save
���:�ּҷ��� �����Ѵ�
�Է�:
���:���ǰ���
*/
Long Save(AddressBook *addressBook) {
	Long count = 0;
	Long i = 0;
	FILE *file;

	file = fopen("AddressBook.dat", "wb");
	if (file != NULL)
	{
		while (i < addressBook->length)
		{
			fwrite(addressBook->personals + i, sizeof(Personal), 1, file);
		    count++;
		    i++;
		}
		fclose(file);
	}
	return count;
}

