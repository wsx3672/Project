//AscendingMerger.c
/*
파일명칭:AscendingMerger.c
기능:첫번째수들가두번째수들을 입력받아 오름차순으로 병합한다
작성자:박상민
작성일자:2017년5월24일
*/
//매크로선언
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//자료형설계
typedef unsigned long int ULong;
//함수선언
int main(int argc, char *argv[]);
void Input(ULong(*firstNumbers), ULong(*secondNumbers));
void AscendingMerger(ULong(*firstNumbers), ULong(*secondNumbers), ULong(*mergerNumbers));
void Output(ULong(*firstNumbers), ULong(*secondNumbers), ULong(*mergerNumbers));
//함수정의
int main(int argc, char *argv[])
{
	ULong firstNumbers[MAX];
	ULong secondNumbers[MAX];
	ULong mergerNumbers[MAX * 2];
	Input(firstNumbers, secondNumbers);
	AscendingMerger(firstNumbers, secondNumbers, mergerNumbers);
	Output(firstNumbers, secondNumbers, mergerNumbers);
	return 0;
}
/*
함수이름:Input
기능:첫번째수들과두번째수들을 입력받는다
입력:X
출력:첫번째수들,두번째수들
*/
void Input(ULong(*firstNumbers), ULong(*secondNumbers))
{
	ULong i;
	printf("첫번째수들을 입력하세요");
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", firstNumbers + i);
	}
	printf("두번째수들을 입력하세요");
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", secondNumbers + i);
	}
}
/*
함수이름:AscendingMerger
기능:첫번째수들과두번째수들을 오름차순으로 병합한다
입력:첫번째수들,두번째수들
출력:병합된수들
*/
void AscendingMerger(ULong(*firstNumbers), ULong(*secondNumbers), ULong(*mergerNumbers))
{
	ULong i = 0;
	ULong j = 0;
	ULong k = 0;
	while (i < MAX&&j < MAX)
	{
		if (firstNumbers[i] < secondNumbers[j])
		{
			mergerNumbers[k] = firstNumbers[i];
			k++;
			i++;
		}
		else
		{
			mergerNumbers[k] = secondNumbers[j];
			k++;
			j++;
		}
	}
	while (j < MAX)
	{
		mergerNumbers[k] = secondNumbers[j];
		k++;
		j++;
	}
	while (i < MAX)
	{
		mergerNumbers[k] = firstNumbers[i];
		k++;
		i++;
	}

}
/*
함수이름:Output 
기능:병합된수들을 입력받아 모니터로 출력한다
입력:첫번째수들,두번째수들,병합된수들
출력:X
*/
void Output(ULong(*firstNumbers), ULong(*secondNumbers), ULong(*mergerNumbers))
{
	ULong i;
	for (i = 0; i < MAX*2; i++)
	{
		printf("%d ", mergerNumbers[i]);
	}
}