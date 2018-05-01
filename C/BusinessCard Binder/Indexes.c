//Indexes.c
#include "Indexes.h"
#include "BusinessCardBinder.h"
#include "Index.h" // 포인터로 갖다쓸때는 전방선언, 직접 쓸때는 헤더파일 가져다씀
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)


//함수정의


int main(int argc, char *argv[]) {
	
	Indexes indexes;
	BusinessCard *businessCardIndex;
	Index(*keys);
	Index *index;
	BusinessCard businessCard = { { "홍길동", "대리", "0101111", "Hong@" },{ "삼성", "서울시 서초구", "0211232", "023213", "www.sam.com" } };
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
	printf("상호 : %s\n", index->name);
	printf("%s %s %s %s %s %s %s %s %s\n\n", businessCardIndex->personal.name, businessCardIndex->personal.position, businessCardIndex->personal.telephoneNumber, businessCardIndex->personal.emailAddress, businessCardIndex->company.name, businessCardIndex->company.address, businessCardIndex->company.telephoneNumber, businessCardIndex->company.faxNumber, businessCardIndex->company.url);

	strcpy(businessCard.personal.name, "김길동");
	strcpy(businessCard.personal.position, "상무");
	strcpy(businessCard.personal.telephoneNumber, "01022122");
	strcpy(businessCard.personal.emailAddress, "Kim@");
	strcpy(businessCard.company.name, "구교");
	strcpy(businessCard.company.address, "서울시 노원구");
	strcpy(businessCard.company.telephoneNumber, "019209302");
	strcpy(businessCard.company.faxNumber, "01202301");
	strcpy(businessCard.company.url, "www.Goog@");

	businessCardIndex = BusinessCardBinder_TakeIn(&businessCardBinder, businessCard);
	index = Indexes_TakeIn(&indexes, businessCardIndex);
	position = Index_Find(index, businessCardIndex);
	businessCardIndex = Index_GetAt(index, position);
	printf("상호 : %s\n", index->name);
	printf("%s %s %s %s %s %s %s %s %s\n\n", businessCardIndex->personal.name, businessCardIndex->personal.position, businessCardIndex->personal.telephoneNumber, businessCardIndex->personal.emailAddress, businessCardIndex->company.name, businessCardIndex->company.address, businessCardIndex->company.telephoneNumber, businessCardIndex->company.faxNumber, businessCardIndex->company.url);

	strcpy(businessCard.personal.name, "박길동");
	strcpy(businessCard.personal.position, "사원");
	strcpy(businessCard.personal.telephoneNumber, "011282122");
	strcpy(businessCard.personal.emailAddress, "Ka@");
	strcpy(businessCard.company.name, "삼성");
	strcpy(businessCard.company.address, "서울시 동작구");
	strcpy(businessCard.company.telephoneNumber, "0192139302");
	strcpy(businessCard.company.faxNumber, "0120244");
	strcpy(businessCard.company.url, "www.Goog@");

	businessCardIndex = BusinessCardBinder_TakeIn(&businessCardBinder, businessCard);
	index = Indexes_TakeIn(&indexes, businessCardIndex);
	position = Index_Find(index, businessCardIndex);
	businessCardIndex = Index_GetAt(index, position);
	printf("상호 : %s\n", index->name);
	printf("%s %s %s %s %s %s %s %s %s\n\n", businessCardIndex->personal.name, businessCardIndex->personal.position, businessCardIndex->personal.telephoneNumber, businessCardIndex->personal.emailAddress, businessCardIndex->company.name, businessCardIndex->company.address, businessCardIndex->company.telephoneNumber, businessCardIndex->company.faxNumber, businessCardIndex->company.url);

	strcpy(businessCard.personal.name, "나길동");
	strcpy(businessCard.personal.position, "대리");
	strcpy(businessCard.personal.telephoneNumber, "01022122");
	strcpy(businessCard.personal.emailAddress, "Na@");
	strcpy(businessCard.company.name, "기아");
	strcpy(businessCard.company.address, "서울시 서초구");
	strcpy(businessCard.company.telephoneNumber, "019234302");
	strcpy(businessCard.company.faxNumber, "012234301");
	strcpy(businessCard.company.url, "www.kia");

	businessCardIndex = BusinessCardBinder_TakeIn(&businessCardBinder, businessCard);
	index = Indexes_TakeIn(&indexes, businessCardIndex);
	position = Index_Find(index, businessCardIndex);
	businessCardIndex = Index_GetAt(index, position);
	printf("상호 : %s\n", index->name);
	printf("%s %s %s %s %s %s %s %s %s\n\n", businessCardIndex->personal.name, businessCardIndex->personal.position, businessCardIndex->personal.telephoneNumber, businessCardIndex->personal.emailAddress, businessCardIndex->company.name, businessCardIndex->company.address, businessCardIndex->company.telephoneNumber, businessCardIndex->company.faxNumber, businessCardIndex->company.url);

	printf("**정렬하기**\n\n");
	Indexes_Arrange(&indexes);

	PrintRecursion(&indexes);

	BusinessCardBinder_First(&businessCardBinder);

	printf("\n");
	index = Indexes_TakeOut(&indexes, businessCardIndex, "삼성");
	if (index == NULL) {
		printf("삼성이 삭제 되었습니다.\n\n");
	}
	else {
		printf("%d번째에 위치한 %s 명함이 삭제되었습니다.\n\n", index->length, index->name);
	}
	BusinessCardBinder_Next(&businessCardBinder);

	index = Indexes_Find(&indexes, "삼성");
	printf("%s을 찾았습니다.\n\n", index->name);

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