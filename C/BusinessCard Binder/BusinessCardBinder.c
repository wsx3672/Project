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
	BusinessCard businessCard = { { "��浿","�븮","01015013","Hong@" },{ "����","���������","025879424","123899","park.co.kr" } ,NULL };;
	BusinessCard *index;
	BusinessCard* (*indexes);
	Long i = 0;
	BusinessCard *first;
	Long count = 0;
	BusinessCard *last;
	BusinessCard *previous = NULL;
	BusinessCard* (*companyName);
	Create(&businessCardBinder);
	//businessCard = { {"ȫ�浿","�븮","01015013","Hong@"},{"����","����ü��ʱ�","025879424","park.co.kr"} ,NULL};
	index = TakeIn(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, 
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	strcpy(businessCard.personal.name, "���浿");
	strcpy(businessCard.personal.position, "ȸ��");
	strcpy(businessCard.personal.telephoneNumber, "029385899");
	strcpy(businessCard.personal.emailAddress, "choi@");
	strcpy(businessCard.company.name, "�ؽ�");
	strcpy(businessCard.company.address, "����ü��ʱ�");
	strcpy(businessCard.company.telephoneNumber, "123123123");
	strcpy(businessCard.company.faxNumber, "123123123");
	strcpy(businessCard.company.url, "SamSung.com");
	businessCard.next = NULL;
	index = TakeIn(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, 
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	strcpy(businessCard.personal.name, "ȫ�浿");
	strcpy(businessCard.personal.position, "�븮");
	strcpy(businessCard.personal.telephoneNumber, "0202488484");
	strcpy(businessCard.personal.emailAddress, "jeong@");
	strcpy(businessCard.company.name, "�Ｚ");
	strcpy(businessCard.company.address, "����ü��ʱ�");
	strcpy(businessCard.company.telephoneNumber, "123123123");
	strcpy(businessCard.company.faxNumber, "123123123");
	strcpy(businessCard.company.url, "SamSung.com");
	businessCard.next = NULL;
	index = TakeIn(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, 
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	strcpy(businessCard.personal.name, "�ѱ浿");
	strcpy(businessCard.personal.position, "���");
	strcpy(businessCard.personal.telephoneNumber, "34587893");
	strcpy(businessCard.personal.emailAddress, "na@");
	strcpy(businessCard.company.name, "�ؽ�");
	strcpy(businessCard.company.address, "����ð�����");
	strcpy(businessCard.company.telephoneNumber, "456456456");
	strcpy(businessCard.company.faxNumber, "456456456");
	strcpy(businessCard.company.url, "LG.com");
	businessCard.next = NULL;
	index = TakeIn(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress, 
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	strcpy(businessCard.personal.name, "�ڱ浿");
	strcpy(businessCard.personal.position, "����");
	strcpy(businessCard.personal.telephoneNumber, "283475984");
	strcpy(businessCard.personal.emailAddress, "ga@");
	strcpy(businessCard.company.name, "�ؽ�");
	strcpy(businessCard.company.address, "����ð��Ǳ�");
	strcpy(businessCard.company.telephoneNumber, "858585858");
	strcpy(businessCard.company.faxNumber, "858585858");
	strcpy(businessCard.company.url, "nexon.com");
	businessCard.next = NULL;
	index = TakeIn(&businessCardBinder, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	printf("\n\n\n");

	FindByCompanyName(&businessCardBinder, "�ؽ�");
	first = First(&businessCardBinder);
	while (first != NULL) {
		if (strcmp("�ؽ�", first->company.name) == 0) {
			printf("pppp\n");
			first = first->next;
		}
	}


	Find(&businessCardBinder, "ȫ�浿", &indexes, &count);
	
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
	return strcmp(((BusinessCard*)one)->personal.name, (char(*))other); //�̸����� ��
}

int BusinessCardBinder_CompareBusinessCards(void *one, void *other) {
	int ret;

	if (one == other) { // �ּҰ��̶� ���Ҷ� �׳� �־���
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
	businessCardBinder->current = (BusinessCard*)(index + 1); //������ġ�� AppendFromTail ���� ��µ� index �� object ������ ����ȯ �ؼ� ġȯ����

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
	BusinessCard* index = NULL; //�������� ������ִ°�
	Node* it; //�ݺ�����
	Node* stopper = NULL; //�ݺ����� ���󰡴°�

	it = businessCardBinder->businessCards.head; //��忡������
	while (it != stopper && strcmp(((BusinessCard*)(it+1))->company.name, companyName) != 0) //���̰ų� �̸� ����������
	{
		stopper = it;
		it = it->next; //�Ѿ��
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

	personalFile = fopen("Personals.dat", "rb"); //���� ����
	companyFile = fopen("Companies.dat", "rb"); 
	if (personalFile != NULL && companyFile != NULL) { // �Ѵ� ������� ������
		
		flag = fread(&company, sizeof(Company), 1, companyFile); // ȸ������ ���� �о company �� ����
		while (!feof(companyFile) && flag != 0 && strcmp(company.name, businessCardIndex->company.name) != 0) { // ���� ���� �ƴϰ�, ���� ȸ������ ��ȣ�� ���γ��� Index�� ��ȣ�� ���������� �ݺ�
			companyLength++; // ȸ������ ���̸� ����
			flag = fread(&company, sizeof(Company), 1, companyFile); //�ٽ� ���� ����
		}
		//������� ȸ������ ���� = �ش� ��ȣ�� || flag �� 0 �̸� ��ȣ ���°�

		if (flag == 0) { //���� ȸ���̸��� ������
			companyTempFile = fopen("Companies.tmp", "wb"); // temp ���� ����� ����

			fseek(companyFile, 0L, SEEK_SET); //ù�ٺ��� �ٽ� ����
			flag = fread(&company, sizeof(Company), 1, companyFile);
			while (!feof(companyFile) && flag != 0) { // ȸ������ ÷���� ������ �ݺ�, �о temp ���Ͽ� ���� �о ���� �ݺ�
				fwrite(&company, sizeof(Company), 1, companyTempFile);
				flag = fread(&company, sizeof(Company), 1, companyFile);
			}
			fwrite(&businessCardIndex->company, sizeof(Company), 1, companyTempFile); //�������� �߰��Ǵ� companyIndex ����
			companyLength++; //�߰��Ǹ鼭 ��ü���� ++, �̰� companyLocation ���ҵ� ��

			fclose(companyTempFile); //�ݰ�
			fclose(companyFile);
			remove("Companies.dat"); //�����, temp ���� �̸� �ٲ���
			rename("Companies.tmp", "Companies.dat");
		}

		personalTempFile = fopen("Personals.tmp", "wb"); // ������ �׻� temp ���� ���� �߰�
		flag = fread(&number, sizeof(Long), 1, personalFile);
		flag = fread(&personal, sizeof(Personal), 1, personalFile);

		while (!feof(personalFile) && flag != 0) {
			personalLength++;

			fwrite(&number, sizeof(Long), 1, personalTempFile);
			fwrite(&personal, sizeof(Long), 1, personalTempFile); // ÷���� ������ �а��� �а���

			flag = fread(&number, sizeof(Long), 1, personalFile);
			flag = fread(&personal, sizeof(Personal), 1, personalFile);
		}
		fwrite(&companyLength, sizeof(Long), 1, personalTempFile); // ���� ���� �� �Ű����� ���� �ֱ��ߴ� �ּ��� ���� �߰�
		fwrite(&businessCardIndex->personal, sizeof(Personal), 1, personalTempFile);
		
		fclose(personalTempFile); //�ݰ�
		fclose(personalFile);
		remove("Personals.dat"); //�ٲٰ�
		rename("Personals.tmp", "Personals.dat");
	}
	else { //���ϵ��� �Ѵ� ���������(ó�� �����ϴ°Ÿ�)
		personalFile = fopen("Personals.dat", "wb"); // ���ڸ���
		companyFile = fopen("Companies.dat", "wb");
		fwrite(&businessCardIndex->company, sizeof(Company), 1, companyFile); // �������� ����

		number = 1;
		fwrite(&number, sizeof(Long), 1, personalFile);
		fwrite(&businessCardIndex->personal, sizeof(Personal), 1, personalFile); // ����
		personalLength++; // ���α��� +1

		fclose(companyFile); //���� �ݴ´�
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

	companiesFile = fopen("Companies.dat", "rb"); //���ϵ� ����
	personalsFile = fopen("Personals.dat", "rb");
	if (companiesFile != NULL && personalsFile != NULL) { //����� ��������
		flag = fread(&company, sizeof(Company), 1, companiesFile); // ���۴����� ���� �д´�
		while (!feof(companiesFile) && flag != 0 && strcmp(businessCardLink->company.name, company.name) != 0) { //ã�� ��ȣ�� �����ų�, ������ ������ �ݺ��Ѵ�
			companyLength++; // ���� ���̸� ����
			flag = fread(&company, sizeof(Company), 1, companiesFile); // two read
		}
		companyLocation = companyLength + 1; // ã�� ��ȣ ��ġ�� = ��������� ���� + 1 �� ġȯ

		while (!feof(companiesFile) && flag != 0) { // ������ ���� ������ �д´�
			companyLength++; // ���� ���� ������
			flag = fread(&company, sizeof(Company), 1, companiesFile); // �������� two read
		}
		//������� �ش� ��ȣ ��ġ��, ȸ������ ���� ���س���

		flag = fread(&number, sizeof(Long), 1, personalsFile); //�������� �д´�, ��ȣ���� �ڿ� ���γ��� ����
		flag = fread(&personal, sizeof(Personal), 1, personalsFile);
		while (!feof(personalsFile) && flag != 0) { //������ �д´�
			personalLength++; //�������� ���� ����
			if (number == companyLocation) { //���߿� �ش��ȣ��ȣ ������
				companyEmployees++; //ȸ������ ���� ����
				if (strcmp(businessCardLink->personal.name, personal.name) == 0 && strcmp(businessCardLink->personal.telephoneNumber, personal.telephoneNumber) == 0, strcmp(businessCardLink->personal.emailAddress, personal.emailAddress) == 0) {
					personalLocation = personalLength; //��ȣ��ȣ�� ������, ���γ������ ��ġ�ϸ�(ã�»���̸�), ������ġ�� ����д�
				}
			}
			flag = fread(&number, sizeof(Long), 1, personalsFile); //������
			flag = fread(&personal, sizeof(Personal), 1, personalsFile);
		}
		if (companyEmployees == 1) { //���� ��ȣ ��ġ�� ����� 1��ۿ� ������(������ �ο��̸�)
			if (companyLength > 1) { //ȸ������ �� ���̰� 2 �̻��̸� , (�� �Ʒ��δ� �ű� �ʿ䰡 ���� ��������)
				companiesTemp = fopen("Companies.tmp", "wb"); //���� ȸ�� temp ������ ����

				fseek(companiesFile, 0L, SEEK_SET); //ù�ٺ��� �ٽ� �д´�
				flag = fread(&company, sizeof(Company), 1, companiesFile); //ȸ������ �а�
				while (!feof(companiesFile) && flag != 0 && i < companyLocation) { //�ش��ȣ��ġ ������, ������ ���� �ƴѵ���
					fwrite(&company, sizeof(Company), 1, companiesTemp); //������ ����
					flag = fread(&company, sizeof(Company), 1, companiesFile); //�ٽ� �а�
					i++; //�ݺ�
				}
				while (!feof(companiesFile) && flag != 0 && i < companyLength) { //���� ������ �д´�
					flag = fread(&company, sizeof(Company), 1, companiesFile); //�ش��ȣ��ġ ���Ծ����� �����о �ǳʶٰ�
					fwrite(&company, sizeof(Company), 1, companiesTemp); //�ٽ� ����
					i++; //������ �ݺ�
				}
				fclose(companiesTemp); //ȸ������ ���� ��
				fclose(companiesFile);

				remove("Companies.dat"); //�����ִ� ȸ������ �����ְ�
				if (companyLength > 1) { //ȸ����̰� 2�̻��̸�
					rename("Companies.tmp", "Companies.dat"); //�Ʊ� �Űܵ״� temp ������ �̸��� dat �� �ٲ��ش�
				}
			}
		}
		i = 0; // ����
		if (personalLength > 1) { //���α��̰� 2 �̻��̸�
			personalsTemp = fopen("Personals.tmp", "wb"); //temp ���� ��� �غ�
			fseek(personalsFile, 0L, SEEK_SET); 

			flag = fread(&number, sizeof(Long), 1, personalsFile);
			flag = fread(&personal, sizeof(Personal), 1, personalsFile);
			while (!feof(personalsFile) && flag != 0 && i < personalLocation) {
				if (companyEmployees == 1 && number > companyLocation) { // �ش� ȸ�� ������ ������ �Ѹ��̾���, ���� �������� ���� ȸ���ȣ�� �ش�ȸ�� ��ȣ���� ũ��
					number--; // �ش�ȸ�� ��ȣ �������Ŷ� �ϳ��� �ٿ��� ������
				}
				fwrite(&number, sizeof(Long), 1, personalsTemp); // �ٲܰ� �ٲٰ� ������
				fwrite(&personal, sizeof(Personal), 1, personalsTemp);

				flag = fread(&number, sizeof(Long), 1, personalsFile);
				flag = fread(&personal, sizeof(Personal), 1, personalsFile);
				i++;
			}
			while (!feof(personalsFile) && flag != 0 && i < personalLength) { // ������ġ�� �ǳʶٰ� ������ �а��� �ݺ�
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