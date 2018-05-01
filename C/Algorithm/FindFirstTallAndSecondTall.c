//FindFirstTallAndSecondTall.c
/*
파일명칭:FindFirstTallAndSecondTall.c
기능:키들을 입력받아 가장큰키와 두번째큰키를 구한다
작성자:박상민
작성일자:2017년 5월 23일
*/
//매크로선언
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//자료형설계
typedef unsigned long int ULong;
//함수선언
int main(int argc, char *argv[]);
void Input(ULong(*numbers));
void FindFirstTallAndSecondTall(ULong(*numbers), ULong *firstTall, ULong *secondTall);
void Output(ULong(*numbers), ULong firstTall, ULong secondTall);
//함수정의
int main(int argc, char *argv[])
{
	ULong numbers[MAX];
	ULong firstTall;
	ULong secondTall;
	Input(numbers);
	FindFirstTallAndSecondTall(numbers, &firstTall, &secondTall);
	Output(numbers, firstTall, secondTall);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 키들을 입력받는다
입력:X
출력:키들
*/
void Input(ULong(*numbers))
{
	ULong i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", numbers + i);
	}
}
/*
함수이름:FindFirstTallAndSecondTall
기능:가장큰키와두번째큰키를구한다
입력:키들
출력:가장큰키,두번째큰키
*/
void FindFirstTallAndSecondTall(ULong(*numbers), ULong *firstTall, ULong *secondTall)
{
	ULong temp;
	ULong i = 0;
	ULong j;
	ULong k;
	k = MAX;
	while (k>0)
	{
		j = i + 1;
			while (j < k)
			{
				if (numbers[i] > numbers[j])
				{
					temp = numbers[i];
					numbers[i] = numbers[j];
					numbers[j] = temp;
				}
				i++;
				j++;
			}
			i = 1;
			k--;
	}
	*firstTall = numbers[MAX - 1];
	*secondTall = numbers[MAX - 2];
}
/*
함수이름:Output
기능:가장큰키와두번째큰키를 입력받아 모니터로 출력한다
입력:수들,가장큰키.두번째큰키
출력:X
*/
void Output(ULong(*numbers), ULong firstTall, ULong secondTall)
{
	printf("가장큰키:%d\n두번째큰키:%d", firstTall, secondTall);
}