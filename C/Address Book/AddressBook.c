//AddressBook.c
/*
파일명칭:AddressBook.c
기능:성명,주소,전화번호,이메일을 입력받아 주소록에 적고 관리한다
작성자:박상민
작성일자:2017년6월13일
*/
//매크로선언
#include "AddressBook.h"
//#include "Form.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)
//함수정의
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
함수이름:Create
기능:할당량을 입력받아 할당량만큼 개인들을 준비한다
입력:할당량
출력:X
*/
void Create(AddressBook *addressBook, Long capacity)
{
	addressBook->personals = (Personal(*))calloc(capacity, sizeof(Personal));
	addressBook->capacity = capacity;
	addressBook->length = 0;
}
/*
함수이름:Record
기능:이름,주소,전화번호,이메일주소를 입력받아 비어있는 줄에 적는다 단 빈줄이 없으면 새로운 표를 만들어서 적는다.
입력:이름,주소,전화번호,이메일주소
출력:번호
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
함수이름:Find
기능:입력받은 이름이 적힌 줄을 찾는다
입력:이름
출력:성명수,줄의위치들
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
함수이름:Correct
기능:수정할 줄의위치,주소,전화번호,이메일주소를 입력받아 해당줄에 적는다
입력:줄의위치,주소,전화번호,이메일주소
출력:줄의위치
*/
Long Correct(AddressBook *addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress))
{
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);
	return index;
}
/*
함수이름:Erase
기능:줄의위치를 입력받아 해당줄을 지운다
입력:줄의위치
출력:줄의위치
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
함수이름:Arrange
기능:오름차순으로 정렬한다
입력:X
출력:X
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
함수이름:Destroy
기능:개인들을 할당해제한다
입력:X
출력:X
*/
void Destroy(AddressBook *addressBook)
{
	if (addressBook->personals != NULL)
	{
		free(addressBook->personals);
	}
}
/*
함수이름:Load
기능:주소록에 적재한다
입력:개인
출력:줄의개수
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
함수이름:Save
기능:주소록을 저장한다
입력:
출력:줄의개수
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

