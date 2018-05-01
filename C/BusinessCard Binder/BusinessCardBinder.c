//BusinessCardBinder.c
#include "BusinessCardBinder.h"
#include <stdio.h>
#include <stdlib.h> // FILE
#include <string.h> //strcmp, strcpy
#include <stddef.h> //size_t

#pragma warning(disable : 4996)
/*
int main(int argc, char *argv[])
{
	BusinessCardBinder businessCardBinder;
	BusinessCard businessCard = { { "김길동","대리","01015013","Hong@" },{ "박컴","서울시은평구","025879424","123899","park.co.kr" } ,NULL };;
	BusinessCard *index;
	BusinessCard* (*indexes);
	Long i = 0;
	BusinessCard *first;
	Long count = 0;
	BusinessCard *last;
	BusinessCard *previous = NULL;
	BusinessCard* (*companyName);
	Create(&businessCardBinder);
	//businessCard = { {"홍길동","대리","01015013","Hong@"},{"박컴","서울시서초구","025879424","park.co.kr"} ,NULL};
	index = TakeIn(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, 
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	strcpy(businessCard.personal.name, "가길동");
	strcpy(businessCard.personal.position, "회장");
	strcpy(businessCard.personal.telephoneNumber, "029385899");
	strcpy(businessCard.personal.emailAddress, "choi@");
	strcpy(businessCard.company.name, "넥슨");
	strcpy(businessCard.company.address, "서울시서초구");
	strcpy(businessCard.company.telephoneNumber, "123123123");
	strcpy(businessCard.company.faxNumber, "123123123");
	strcpy(businessCard.company.url, "SamSung.com");
	businessCard.next = NULL;
	index = TakeIn(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, 
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	strcpy(businessCard.personal.name, "홍길동");
	strcpy(businessCard.personal.position, "대리");
	strcpy(businessCard.personal.telephoneNumber, "0202488484");
	strcpy(businessCard.personal.emailAddress, "jeong@");
	strcpy(businessCard.company.name, "삼성");
	strcpy(businessCard.company.address, "서울시서초구");
	strcpy(businessCard.company.telephoneNumber, "123123123");
	strcpy(businessCard.company.faxNumber, "123123123");
	strcpy(businessCard.company.url, "SamSung.com");
	businessCard.next = NULL;
	index = TakeIn(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, 
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	strcpy(businessCard.personal.name, "한길동");
	strcpy(businessCard.personal.position, "사원");
	strcpy(businessCard.personal.telephoneNumber, "34587893");
	strcpy(businessCard.personal.emailAddress, "na@");
	strcpy(businessCard.company.name, "넥슨");
	strcpy(businessCard.company.address, "서울시강남구");
	strcpy(businessCard.company.telephoneNumber, "456456456");
	strcpy(businessCard.company.faxNumber, "456456456");
	strcpy(businessCard.company.url, "LG.com");
	businessCard.next = NULL;
	index = TakeIn(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, 
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	strcpy(businessCard.personal.name, "박길동");
	strcpy(businessCard.personal.position, "부장");
	strcpy(businessCard.personal.telephoneNumber, "283475984");
	strcpy(businessCard.personal.emailAddress, "ga@");
	strcpy(businessCard.company.name, "넥슨");
	strcpy(businessCard.company.address, "서울시관악구");
	strcpy(businessCard.company.telephoneNumber, "858585858");
	strcpy(businessCard.company.faxNumber, "858585858");
	strcpy(businessCard.company.url, "nexon.com");
	businessCard.next = NULL;
	index = TakeIn(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	printf("\n\n\n");

	FindByCompanyName(&businessCardBinder, "넥슨");
	first = First(&businessCardBinder);
	while (first != NULL) {
		if (strcmp("넥슨", first->company.name) == 0) {
			printf("pppp\n");
			first = first->next;
		}
	}


	Find(&businessCardBinder, "홍길동", &indexes, &count);
	
	while (i < count) {
		printf("%s %s %s %s %s %s %s %s %s\n", indexes[i]->personal.name, indexes[i]->personal.position, indexes[i]->personal.telephoneNumber, indexes[i]->personal.emailAddress, 
			indexes[i]->company.name, indexes[i]->company.address, indexes[i]->company.telephoneNumber, indexes[i]->company.faxNumber, indexes[i]->company.url);
		i++;
	}
	printf("\n\n\n");
	if (indexes != NULL) {
		free(indexes);
		indexes = NULL;
	}
	
	businessCard = TakeOut(&businessCardBinder, index);
	printf("%s %s %s %s %s %s %s %s %s\n", businessCard.personal.name, businessCard.personal.position, businessCard.personal.telephoneNumber, businessCard.personal.emailAddress,
		businessCard.company.name, businessCard.company.address, businessCard.company.telephoneNumber, businessCard.company.faxNumber, businessCard.company.url);
	printf("\n\n\njjjj");
	
	Arrange(&businessCardBinder);
	last = Last(&businessCardBinder);
	index = First(&businessCardBinder);
	while (previous != last) {
		printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, 
			index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
		previous = index;
		index = Next(&businessCardBinder);
	}
	
	Destroy(&businessCardBinder);

	system("pause");

	return 0;
}
*/

int BusinessCardBinder_CompareNames(void *one, void *other) {
	return strcmp(((BusinessCard*)one)->personal.name, (char(*))other); //이름끼리 비교
}

int BusinessCardBinder_CompareBusinessCards(void *one, void *other) {
	int ret;

	if (one == other) { // 주소값이라서 비교할때 그냥 넣어줌
		ret = 0;
	}
	else {
		ret = -1;
	}
	return ret;
}

void BusinessCardBinder_Create(BusinessCardBinder *businessCardBinder) {

	LinkedList_Create(&businessCardBinder->businessCards);
	businessCardBinder->length = 0;
	businessCardBinder->current = NULL;
}

Long BusinessCardBinder_Load(BusinessCardBinder *businessCardBinder) {

		BusinessCard businessCard;
		Node *index;
		FILE *personalFile;
		FILE *companyFile;
		Long flag;
		Long i;
		Long companyIndex;

		personalFile = fopen("Personals.dat", "rb");
		companyFile = fopen("Companies.dat", "rb");
		if (personalFile != NULL && companyFile != NULL) {
			flag = fread(&companyIndex, sizeof(Long), 1, personalFile);
			flag = fread(&businessCard.personal, sizeof(Personal), 1, personalFile);
			while (!feof(personalFile) && flag != 0) {
				i = 1;
				fseek(companyFile, 0L, SEEK_SET);
				flag = fread(&businessCard.company, sizeof(Company), 1, companyFile);
				while (i < companyIndex) {
					flag = fread(&businessCard.company, sizeof(Company), 1, companyFile);
					i++;
				}
				index = LinkedList_AppendFromTail(&businessCardBinder->businessCards, &businessCard, sizeof(BusinessCard));
				businessCardBinder->length++;
				businessCardBinder->current = (BusinessCard*)(index + 1);
				flag = fread(&companyIndex, sizeof(Long), 1, personalFile);
				flag = fread(&businessCard.personal, sizeof(Personal), 1, personalFile);
			}
			fclose(personalFile);
			fclose(companyFile);
		}

		return businessCardBinder->length;
	}

BusinessCard* BusinessCardBinder_TakeIn(BusinessCardBinder *businessCardBinder, BusinessCard businessCard) {
	Node* index;

	index = LinkedList_AppendFromTail(&businessCardBinder->businessCards, &businessCard, sizeof(BusinessCard));

	businessCardBinder->length++;
	businessCardBinder->current = (BusinessCard*)(index + 1); //현재위치를 AppendFromTail 에서 출력된 index 의 object 값에서 형변환 해서 치환해줌

	return businessCardBinder->current;
}

void BusinessCardBinder_Find(BusinessCardBinder *businessCardBinder, char(*name), BusinessCard**(*indexes), Long *count) {

	Node *(*nodes);
	Long i = 0;
	*count = 0;

	LinkedList_LinearSearchDuplicate(&businessCardBinder->businessCards, name, count, &nodes, BusinessCardBinder_CompareNames);
	*indexes = (BusinessCard*(*))calloc(*count, sizeof(BusinessCard*));
	while (i < *count) {
		(*indexes)[i] = (BusinessCard*)(nodes[i] + 1);
		i++;
	}
	if (nodes != NULL) {
		free(nodes);
	}
}

/*
void BusinessCardBinder_Arrange(BusinessCardBinder *businessCardBinder)
{
	BusinessCard* previous = NULL;
	BusinessCard* last = NULL;
	BusinessCard* it;
	while (last != businessCardBinder->first->next) {
		businessCardBinder->current = businessCardBinder->first;
		it = businessCardBinder->current->next;
		while(it != last) {
			if (strcmp(it->personal.name, businessCardBinder->current->personal.name) < 0) {
				if (businessCardBinder->first == businessCardBinder->current) {
					businessCardBinder->first = it;
				}
				else {
					previous->next = it;
				}
				previous = it;
				businessCardBinder->current->next = it->next;
				it->next = businessCardBinder->current;
				it = businessCardBinder->current->next;
			}
			else {
				previous = businessCardBinder->current;
				businessCardBinder->current = it;
				it = it->next;
			}
		}
		last = businessCardBinder->current;
	}
}

*/

BusinessCard BusinessCardBinder_TakeOut(BusinessCardBinder *businessCardBinder, BusinessCard *index)
{
	BusinessCard businessCard;
	Node *otherIndex;

	otherIndex = LinkedList_LinearSearchUnique(&businessCardBinder->businessCards, index, BusinessCardBinder_CompareBusinessCards);
	LinkedList_GetAt(&businessCardBinder->businessCards, otherIndex, &businessCard, sizeof(BusinessCard));
	LinkedList_Delete(&businessCardBinder->businessCards, otherIndex);

	businessCardBinder->length--;

	if (businessCardBinder->current != NULL) {
		businessCardBinder->current = (BusinessCard*)(businessCardBinder->current) + 1;
	}
	else {
		businessCardBinder->current = NULL;
	}
	return businessCard;
}

BusinessCard *BusinessCardBinder_First(BusinessCardBinder *businessCardBinder)
{
	Node* index;

	index = LinkedList_First(&businessCardBinder->businessCards);

	businessCardBinder->current = (BusinessCard*)(index + 1);

	return businessCardBinder->current;
}

BusinessCard *BusinessCardBinder_Previous(BusinessCardBinder *businessCardBinder)
{
	Node* index;

	index = LinkedList_Previous(&businessCardBinder->businessCards);

	businessCardBinder->current = (BusinessCard*)(index + 1);

	return businessCardBinder->current;
}

BusinessCard *BusinessCardBinder_Next(BusinessCardBinder *businessCardBinder)
{
	Node* index;

	index = LinkedList_Next(&businessCardBinder->businessCards);

	businessCardBinder->current = (BusinessCard*)(index + 1);

	return businessCardBinder->current;
}

BusinessCard *BusinessCardBinder_Last(BusinessCardBinder *businessCardBinder)
{
	Node* index;

	index = LinkedList_Last(&businessCardBinder->businessCards);

	businessCardBinder->current = (BusinessCard*)(index + 1);

	return businessCardBinder->current;
}


BusinessCard* BusinessCardBinder_FindByCompanyName(BusinessCardBinder *businessCardBinder, char(*companyName)) {
	BusinessCard* index = NULL; //마지막에 출력해주는거
	Node* it; //반복제어
	Node* stopper = NULL; //반복제어 따라가는거

	it = businessCardBinder->businessCards.head; //헤드에서부터
	while (it != stopper && strcmp(((BusinessCard*)(it+1))->company.name, companyName) != 0) //끝이거나 이름 있을때까지
	{
		stopper = it;
		it = it->next; //넘어간다
	}
	if (it == stopper) {
		index = NULL;
	}
	else {
		index = (BusinessCard*)(it + 1);
	}

	return index;
}


Long BusinessCardBinder_Save(BusinessCardBinder *businessCardBinder)
{
	Node *index;
	BusinessCard businessCard;
	Long flag;
	FILE *companyFile;
	FILE *personalFile;
	Node *previous = NULL;
	Long i;
	Company company;

	personalFile = fopen("Personals.dat", "wb");
	companyFile = fopen("Companies.dat", "wb+");
	if (personalFile != NULL && companyFile != NULL) {
		index = LinkedList_First(&businessCardBinder->businessCards);
		while (previous != index) {
			i = 1;
			fseek(companyFile, 0L, SEEK_SET);
			LinkedList_GetAt(&businessCardBinder->businessCards, index, &businessCard, sizeof(BusinessCard));
			flag = fread(&company, sizeof(Company), 1, companyFile);
			while (!feof(companyFile) && flag != 0 && strcmp(company.name, businessCard.company.name) != 0) {
				i++;
				flag = fread(&company, sizeof(Company), 1, companyFile);
			}
			if (flag == 0) {
				fwrite(&businessCard.company, sizeof(Company), 1, companyFile);
			}
			fwrite(&i, sizeof(Long), 1, personalFile);
			fwrite(&businessCard.personal, sizeof(Personal), 1, personalFile);
			previous = index;
			index = LinkedList_Next(&businessCardBinder->businessCards);
		}
		fclose(personalFile);
		fclose(companyFile);
	}

	return businessCardBinder->length;
}

void BusinessCardBinder_GetAt(BusinessCardBinder *businessCardBinder, BusinessCard* index, BusinessCard businessCard, size_t size) {

	LinkedList_GetAt(&businessCardBinder->businessCards, index, &businessCard, size);
}


BusinessCard* Move(BusinessCardBinder *businessCardBinder, BusinessCard *businessCardIndex) {
	Node *node;

	node = LinkedList_Move(&businessCardBinder->businessCards, businessCardIndex, BusinessCardBinder_CompareBusinessCards);

	businessCardBinder->businessCards.current = node;
	businessCardBinder->current = businessCardIndex;

	return businessCardBinder->current;
}

Long BusinessCardBinder_Add(BusinessCardBinder *businessCardBinder, BusinessCard *businessCardIndex) {
	FILE *personalFile;
	FILE *companyFile;
	FILE *companyTempFile;
	FILE *personalTempFile;
	Long flag;
	Long companyLength = 0;
	Long personalLength = 0;
	Long number;
	Company company;
	Personal personal;

	personalFile = fopen("Personals.dat", "rb"); //파일 연다
	companyFile = fopen("Companies.dat", "rb"); 
	if (personalFile != NULL && companyFile != NULL) { // 둘다 비어있지 않으면
		
		flag = fread(&company, sizeof(Company), 1, companyFile); // 회사파일 한줄 읽어서 company 에 저장
		while (!feof(companyFile) && flag != 0 && strcmp(company.name, businessCardIndex->company.name) != 0) { // 파일 끝이 아니고, 읽은 회사파일 상호랑 새로넣은 Index의 상호랑 맞을때까지 반복
			companyLength++; // 회사파일 길이를 센다
			flag = fread(&company, sizeof(Company), 1, companyFile); //다시 한줄 읽음
		}
		//여기까지 회사파일 길이 = 해당 상호명 || flag 가 0 이면 상호 없는거

		if (flag == 0) { //같은 회사이름이 없으면
			companyTempFile = fopen("Companies.tmp", "wb"); // temp 파일 만들어 연다

			fseek(companyFile, 0L, SEEK_SET); //첫줄부터 다시 읽음
			flag = fread(&company, sizeof(Company), 1, companyFile);
			while (!feof(companyFile) && flag != 0) { // 회사파일 첨부터 끝까지 반복, 읽어서 temp 파일에 쓰고 읽어서 쓰고 반복
				fwrite(&company, sizeof(Company), 1, companyTempFile);
				flag = fread(&company, sizeof(Company), 1, companyFile);
			}
			fwrite(&businessCardIndex->company, sizeof(Company), 1, companyTempFile); //마지막은 추가되는 companyIndex 내용
			companyLength++; //추가되면서 전체길이 ++, 이게 companyLocation 역할도 함

			fclose(companyTempFile); //닫고
			fclose(companyFile);
			remove("Companies.dat"); //지우고, temp 파일 이름 바꿔줌
			rename("Companies.tmp", "Companies.dat");
		}

		personalTempFile = fopen("Personals.tmp", "wb"); // 개인은 항상 temp 만들어서 새로 추가
		flag = fread(&number, sizeof(Long), 1, personalFile);
		flag = fread(&personal, sizeof(Personal), 1, personalFile);

		while (!feof(personalFile) && flag != 0) {
			personalLength++;

			fwrite(&number, sizeof(Long), 1, personalTempFile);
			fwrite(&personal, sizeof(Long), 1, personalTempFile); // 첨부터 끝까지 읽고쓰고 읽고쓰고

			flag = fread(&number, sizeof(Long), 1, personalFile);
			flag = fread(&personal, sizeof(Personal), 1, personalFile);
		}
		fwrite(&companyLength, sizeof(Long), 1, personalTempFile); // 기존 내용 다 옮겼으면 새로 넣기했던 주소의 내용 추가
		fwrite(&businessCardIndex->personal, sizeof(Personal), 1, personalTempFile);
		
		fclose(personalTempFile); //닫고
		fclose(personalFile);
		remove("Personals.dat"); //바꾸고
		rename("Personals.tmp", "Personals.dat");
	}
	else { //파일들이 둘다 비어있으면(처음 저장하는거면)
		personalFile = fopen("Personals.dat", "wb"); // 열자마자
		companyFile = fopen("Companies.dat", "wb");
		fwrite(&businessCardIndex->company, sizeof(Company), 1, companyFile); // 넣은내용 쓰고

		number = 1;
		fwrite(&number, sizeof(Long), 1, personalFile);
		fwrite(&businessCardIndex->personal, sizeof(Personal), 1, personalFile); // 쓰고
		personalLength++; // 개인길이 +1

		fclose(companyFile); //파일 닫는다
		fclose(personalFile);
	}
	return personalLength;
}

Long BusinessCardBinder_Remove(BusinessCardBinder *businessCardBinder, BusinessCard *businessCardLink) {
	Long index;
	FILE *companiesFile;
	FILE *personalsFile;
	FILE *personalsTemp;
	FILE *companiesTemp;
	Long companyLength = 0;
	Long personalLength = 0;
	Long i = 0;
	Company company;
	Personal personal;
	Long number;
	Long personalLocation = 0;
	Long companyLocation;
	Long companyEmployees = 0;
	int flag;

	companiesFile = fopen("Companies.dat", "rb"); //파일들 연다
	personalsFile = fopen("Personals.dat", "rb");
	if (companiesFile != NULL && personalsFile != NULL) { //제대로 열렸으면
		flag = fread(&company, sizeof(Company), 1, companiesFile); // 컴퍼니파일 한줄 읽는다
		while (!feof(companiesFile) && flag != 0 && strcmp(businessCardLink->company.name, company.name) != 0) { //찾는 상호가 나오거나, 파일의 끝까지 반복한다
			companyLength++; // 파일 길이를 센다
			flag = fread(&company, sizeof(Company), 1, companiesFile); // two read
		}
		companyLocation = companyLength + 1; // 찾는 상호 위치는 = 현재까지의 길이 + 1 로 치환

		while (!feof(companiesFile) && flag != 0) { // 나머지 파일 끝까지 읽는다
			companyLength++; // 파일 길이 세려고
			flag = fread(&company, sizeof(Company), 1, companiesFile); // 마찬가지 two read
		}
		//여기까지 해당 상호 위치랑, 회사파일 길이 구해놨음

		flag = fread(&number, sizeof(Long), 1, personalsFile); //개인파일 읽는다, 번호따로 뒤에 개인내용 따로
		flag = fread(&personal, sizeof(Personal), 1, personalsFile);
		while (!feof(personalsFile) && flag != 0) { //끝까지 읽는다
			personalLength++; //개인파일 길이 센다
			if (number == companyLocation) { //도중에 해당상호번호 있으면
				companyEmployees++; //회사직원 수를 센다
				if (strcmp(businessCardLink->personal.name, personal.name) == 0 && strcmp(businessCardLink->personal.telephoneNumber, personal.telephoneNumber) == 0, strcmp(businessCardLink->personal.emailAddress, personal.emailAddress) == 0) {
					personalLocation = personalLength; //상호번호도 같은데, 개인내용까지 일치하면(찾는사람이면), 개인위치를 적어둔다
				}
			}
			flag = fread(&number, sizeof(Long), 1, personalsFile); //투리드
			flag = fread(&personal, sizeof(Personal), 1, personalsFile);
		}
		if (companyEmployees == 1) { //뺄때 상호 겹치는 사람이 1명밖에 없으면(마지막 인원이면)
			if (companyLength > 1) { //회사파일 총 길이가 2 이상이면 , (그 아래로는 옮길 필요가 없이 날려버림)
				companiesTemp = fopen("Companies.tmp", "wb"); //새로 회사 temp 파일을 연다

				fseek(companiesFile, 0L, SEEK_SET); //첫줄부터 다시 읽는다
				flag = fread(&company, sizeof(Company), 1, companiesFile); //회사파일 읽고
				while (!feof(companiesFile) && flag != 0 && i < companyLocation) { //해당상호위치 전까지, 파일의 끝이 아닌동안
					fwrite(&company, sizeof(Company), 1, companiesTemp); //읽은거 쓰고
					flag = fread(&company, sizeof(Company), 1, companiesFile); //다시 읽고
					i++; //반복
				}
				while (!feof(companiesFile) && flag != 0 && i < companyLength) { //파일 끝까지 읽는다
					flag = fread(&company, sizeof(Company), 1, companiesFile); //해당상호위치 나왔었으면 덮어읽어서 건너뛰고
					fwrite(&company, sizeof(Company), 1, companiesTemp); //다시 쓴다
					i++; //끝까지 반복
				}
				fclose(companiesTemp); //회사파일 볼일 끝
				fclose(companiesFile);

				remove("Companies.dat"); //원래있던 회사파일 지워주고
				if (companyLength > 1) { //회사길이가 2이상이면
					rename("Companies.tmp", "Companies.dat"); //아까 옮겨뒀던 temp 파일의 이름을 dat 로 바꿔준다
				}
			}
		}
		i = 0; // 리셋
		if (personalLength > 1) { //개인길이가 2 이상이면
			personalsTemp = fopen("Personals.tmp", "wb"); //temp 파일 열어서 준비
			fseek(personalsFile, 0L, SEEK_SET); 

			flag = fread(&number, sizeof(Long), 1, personalsFile);
			flag = fread(&personal, sizeof(Personal), 1, personalsFile);
			while (!feof(personalsFile) && flag != 0 && i < personalLocation) {
				if (companyEmployees == 1 && number > companyLocation) { // 해당 회사 직원이 마지막 한명이었고, 읽은 개인파일 줄의 회사번호가 해당회사 번호보다 크면
					number--; // 해당회사 번호 없어질거라서 하나씩 줄여서 땡겨줌
				}
				fwrite(&number, sizeof(Long), 1, personalsTemp); // 바꿀건 바꾸고 적어줌
				fwrite(&personal, sizeof(Personal), 1, personalsTemp);

				flag = fread(&number, sizeof(Long), 1, personalsFile);
				flag = fread(&personal, sizeof(Personal), 1, personalsFile);
				i++;
			}
			while (!feof(personalsFile) && flag != 0 && i < personalLength) { // 개인위치는 건너뛰고 끝까지 읽고쓰고 반복
				flag = fread(&number, sizeof(Long), 1, personalsFile);
				flag = fread(&personal, sizeof(Personal), 1, personalsFile);

				if (companyEmployees == 1 && number > companyLocation) {
					number--;
				}
				fwrite(&number, sizeof(Long), 1, personalsTemp);
				fwrite(&personal, sizeof(Personal), 1, personalsTemp);
				i++;
			}
			fclose(personalsTemp);
			fclose(personalsFile);
			remove(personalsFile);

			if (personalLength > 1) {
				rename("Personals.tmp", "Personals.dat");
			}
		}
	}
	index = -1;

	return index;
}

void BusinessCardBinder_Destroy(BusinessCardBinder *businessCardBinder) {

	LinkedList_Destroy(&businessCardBinder->businessCards);
}