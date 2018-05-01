//Combination.c
/*
파일이름:Combination.c
기능:주사위의합을 입력받아 경우의수를 구한다
작성자:박상민
작성일자:2017년5월22일
*/
//매크로선언
#include <stdio.h>
#define MAX 6
#pragma warning (disable:4996)
//자료형설계
typedef unsigned short int UShort;
//함수선언 
int main(int argc, char *argv[]);
UShort Input();
void Combination(UShort sum, UShort(*firstNumbers), UShort(*secondNumbers), UShort *numberOfCase);
void Output(UShort sum, UShort(*firstNumbers), UShort(*secondNumbers), UShort numberOfCase);
//함수정의
int main(int argc, char *argv[])
{
	UShort sum;
	UShort firstNumbers[MAX];
	UShort secondNumbers[MAX];
	UShort numberOfCase;
	sum = Input();
	Combination(sum, firstNumbers, secondNumbers, &numberOfCase);
	Output(sum, firstNumbers, secondNumbers, numberOfCase);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 주사위의합을 입력받는다
입력:X
출력:주사위의합
*/
UShort Input()
{
	UShort sum;
	scanf("%hu", &sum);
	return sum;
}
/*
함수이름:Combination
기능:주사위눈의합을 구한다
입력:주사위의합
출력:첫번째주사위수들,두번째주사위수들,경우의수
*/
void Combination(UShort sum, UShort(*firstNumbers), UShort(*secondNumbers), UShort *numberOfCase)
{
	UShort temp;
	UShort dice1;
	UShort dice2;
	UShort i = 0;
	*numberOfCase = 0;
	for (dice2 = 1; dice2 <= MAX; dice2++)
	{
		for (dice1 = 1; dice1 <= MAX; dice1++)
		{
			temp = dice1 + dice2;
			if (sum == temp)
			{
				firstNumbers[i] = dice1;
				secondNumbers[i] = dice2;
				(*numberOfCase)++;
				i++;
			}
		}
		dice1 = 1;

	}
}
/*
함수이름:Output
기능:첫번째주사위수들과두번째주사위수들을 입력받아 모니터에 출력한다
입력:주사위의합,첫번째주사위수들,두번째주사위수들,경우의수
출력:X
*/
void Output(UShort sum, UShort(*firstNumbers), UShort(*secondNumbers), UShort numberOfCase)
{
	UShort i = 0;
	if (numberOfCase != 0)
	{
		while (i < numberOfCase)
		{
			printf("첫번째주사위수:%d 두번째주사위수:%d\n", firstNumbers[i], secondNumbers[i]);
			i++;
		}
	}
	else
	{
		printf("2이상 12이하의수를 입력해주세요");
	}
}
