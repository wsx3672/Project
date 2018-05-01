//Indexes.c
#include "Indexes.h"
#include "BusinessCardBinder.h"
#include "Index.h" // �����ͷ� ���پ����� ���漱��, ���� ������ ������� �����پ�
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)


//�Լ�����


int main(int argc, char *argv[]) {
	
	Indexes indexes;
	BusinessCard *businessCardIndex;
	Index(*keys);
	Index *index;
	BusinessCard businessCard = { { "ȫ�浿", "�븮", "0101111", "Hong@" },{ "�Ｚ", "����� ���ʱ�", "0211232", "023213", "www.sam.com" } };
	Long position;
	BusinessCardBinder businessCardBinder;
	Long i = 0;
	Long count;

	BusinessCardBinder_Create(&businessCardBinder);
	businessCardIndex = BusinessCardBinder_TakeIn(&businessCardBinder, businessCard);
	Indexes_Create(&indexes);
	index = Indexes_TakeIn(&indexes, businessCardIndex);
	position = Index_Find(index, businessCardIndex);
	businessCardIndex = Index_GetAt(index, position);
	printf("��ȣ : %s\n", index->name);
	printf("%s %s %s %s %s %s %s %s %s\n\n", businessCardIndex->personal.name, businessCardIndex->personal.position, businessCardIndex->personal.telephoneNumber, businessCardIndex->personal.emailAddress, businessCardIndex->company.name, businessCardIndex->company.address, businessCardIndex->company.telephoneNumber, businessCardIndex->company.faxNumber, businessCardIndex->company.url);

	strcpy(businessCard.personal.name, "��浿");
	strcpy(businessCard.personal.position, "��");
	strcpy(businessCard.personal.telephoneNumber, "01022122");
	strcpy(businessCard.personal.emailAddress, "Kim@");
	strcpy(businessCard.company.name, "����");
	strcpy(businessCard.company.address, "����� �����");
	strcpy(businessCard.company.telephoneNumber, "019209302");
	strcpy(businessCard.company.faxNumber, "01202301");
	strcpy(businessCard.company.url, "www.Goog@");

	businessCardIndex = BusinessCardBinder_TakeIn(&businessCardBinder, businessCard);
	index = Indexes_TakeIn(&indexes, businessCardIndex);
	position = Index_Find(index, businessCardIndex);
	businessCardIndex = Index_GetAt(index, position);
	printf("��ȣ : %s\n", index->name);
	printf("%s %s %s %s %s %s %s %s %s\n\n", businessCardIndex->personal.name, businessCardIndex->personal.position, businessCardIndex->personal.telephoneNumber, businessCardIndex->personal.emailAddress, businessCardIndex->company.name, businessCardIndex->company.address, businessCardIndex->company.telephoneNumber, businessCardIndex->company.faxNumber, businessCardIndex->company.url);

	strcpy(businessCard.personal.name, "�ڱ浿");
	strcpy(businessCard.personal.position, "���");
	strcpy(businessCard.personal.telephoneNumber, "011282122");
	strcpy(businessCard.personal.emailAddress, "Ka@");
	strcpy(businessCard.company.name, "�Ｚ");
	strcpy(businessCard.company.address, "����� ���۱�");
	strcpy(businessCard.company.telephoneNumber, "0192139302");
	strcpy(businessCard.company.faxNumber, "0120244");
	strcpy(businessCard.company.url, "www.Goog@");

	businessCardIndex = BusinessCardBinder_TakeIn(&businessCardBinder, businessCard);
	index = Indexes_TakeIn(&indexes, businessCardIndex);
	position = Index_Find(index, businessCardIndex);
	businessCardIndex = Index_GetAt(index, position);
	printf("��ȣ : %s\n", index->name);
	printf("%s %s %s %s %s %s %s %s %s\n\n", businessCardIndex->personal.name, businessCardIndex->personal.position, businessCardIndex->personal.telephoneNumber, businessCardIndex->personal.emailAddress, businessCardIndex->company.name, businessCardIndex->company.address, businessCardIndex->company.telephoneNumber, businessCardIndex->company.faxNumber, businessCardIndex->company.url);

	strcpy(businessCard.personal.name, "���浿");
	strcpy(businessCard.personal.position, "�븮");
	strcpy(businessCard.personal.telephoneNumber, "01022122");
	strcpy(businessCard.personal.emailAddress, "Na@");
	strcpy(businessCard.company.name, "���");
	strcpy(businessCard.company.address, "����� ���ʱ�");
	strcpy(businessCard.company.telephoneNumber, "019234302");
	strcpy(businessCard.company.faxNumber, "012234301");
	strcpy(businessCard.company.url, "www.kia");

	businessCardIndex = BusinessCardBinder_TakeIn(&businessCardBinder, businessCard);
	index = Indexes_TakeIn(&indexes, businessCardIndex);
	position = Index_Find(index, businessCardIndex);
	businessCardIndex = Index_GetAt(index, position);
	printf("��ȣ : %s\n", index->name);
	printf("%s %s %s %s %s %s %s %s %s\n\n", businessCardIndex->personal.name, businessCardIndex->personal.position, businessCardIndex->personal.telephoneNumber, businessCardIndex->personal.emailAddress, businessCardIndex->company.name, businessCardIndex->company.address, businessCardIndex->company.telephoneNumber, businessCardIndex->company.faxNumber, businessCardIndex->company.url);

	printf("**�����ϱ�**\n\n");
	Indexes_Arrange(&indexes);

	PrintRecursion(&indexes);

	BusinessCardBinder_First(&businessCardBinder);

	printf("\n");
	index = Indexes_TakeOut(&indexes, businessCardIndex, "�Ｚ");
	if (index == NULL) {
		printf("�Ｚ�� ���� �Ǿ����ϴ�.\n\n");
	}
	else {
		printf("%d��°�� ��ġ�� %s ������ �����Ǿ����ϴ�.\n\n", index->length, index->name);
	}
	BusinessCardBinder_Next(&businessCardBinder);

	index = Indexes_Find(&indexes, "�Ｚ");
	printf("%s�� ã�ҽ��ϴ�.\n\n", index->name);

	Indexes_MakeList(&indexes, &keys, &count);
	printf("**MakeList**\n\n");
	printf("%d", count);
	while (i < count) {
		printf("%s ", keys[i].name);
		i++;
	}
	printf("\n\n");
	printf("************\n");
	Indexes_Destroy(&indexes);
	BusinessCardBinder_Destroy(&businessCardBinder);

	return 0;
	
}



void Indexes_Create(Indexes *indexes)
{
	BinaryTree_Create(&indexes->indexes);

	indexes->length = 0;
}

Index *Indexes_TakeIn(Indexes *indexes, BusinessCard *businessCardIndex)
{
	Index key;
	BinaryNode *node;
	Index *index;

	strcpy(key.name, businessCardIndex->company.name);

	node = Search(&indexes->indexes, &key, Indexes_CompareCompanyNames);

	if (node == NULL) {

		Index_Create(&key, 100);

		strcpy(key.name, businessCardIndex->company.name);

		node = BinaryTree_Insert(&indexes->indexes, &key, sizeof(Index), Indexes_CompareCompanyNames);

		indexes->length++;
	}
	index = (Index*)(node + 1);

	Index_Add(index, businessCardIndex);

	return index;
}

Index *Indexes_TakeOut(Indexes *indexes, BusinessCard *businessCardIndex, char(*companyName))
{
	Index *index;
	Long position;
	Index key;
	BinaryNode *node;

	strcpy(key.name, companyName);

	node = Search(&indexes->indexes, &key, Indexes_CompareCompanyNames);

	index = (Index*)(node + 1);

	position = Index_Find((Index*)(node + 1), businessCardIndex);

	position = Index_Remove((Index*)(node + 1), position);

	if (((Index*)(node + 1))->length == 0) {

		node = BinaryTree_Delete(&indexes->indexes, (Index*)(node + 1), Indexes_CompareCompanyNames);

		indexes->length--;
		index = NULL;
	}
	return index;
}

void Indexes_Arrange(Indexes *indexes)
{
	MakeBalance(&indexes->indexes, sizeof(Index));
}

Index *Indexes_Find(Indexes *indexes, char(*name))
{
	Index *index = NULL;
	Index key;
	BinaryNode *node;

	strcpy(key.name, name);

	node = Search(&indexes->indexes, &key, Indexes_CompareCompanyNames);
	if (node != NULL) {
		index = (Index*)(node + 1);
	}
	return index;
}

void Indexes_MakeList(Indexes *indexes, Index *(*keys), Long *count)
{
	CopyToBuffer(&indexes->indexes, keys, count, sizeof(Index));
}

int Indexes_CompareCompanyNames(void *one, void *other)
{
	return strcmp(((Index*)one)->name, ((Index*)other)->name);
}

void PrintRecursion(Indexes *indexes)
{
	Node_PrintRecursion(indexes->indexes.root);
}

void Node_PrintRecursion(BinaryNode *node)
{
	if (node != NULL) {

		Node_PrintRecursion(node->left);

		printf("%s\n", ((Index*)(node + 1))->name);

		Node_PrintRecursion(node->right);
	}
}

void Indexes_Destroy(Indexes *indexes)
{
	Indexes_AllDestroy(indexes->indexes.root);
	BinaryTree_Destroy(&indexes->indexes);
}

void Indexes_AllDestroy(BinaryNode *node)
{
	if (node != NULL) {
		Indexes_AllDestroy(node->left);
		Indexes_AllDestroy(node->right);
		Index_Destroy((Index*)(node + 1));
	}
}