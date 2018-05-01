//OddSumAndMinimumOdd.c
/*
파일이름:OddSumAndMinimumOdd.c
기능:수들을 입력받아 홀수들의합과 가장작은홀수를 구한다
작성자:박상민
작성일자:2017년5월22일
*/
//매크로선언
#include <stdio.h>
#define MAX 7
#pragma warning (disable:4996)
//자료형설계
typedef unsigned long int ULong;
//함수선언
int main(int argc, char *argv[]);
void Input(ULong(*numbers));
void OddSumAndMinimumOdd(ULong(*numbers), ULong *sum, ULong *minumumOdd);
void Output(ULong(*numbers), ULong sum, ULong minimumOdd);
//함수정의
int main(int argc, char *argv[])
{
	ULong numbers[MAX];
	ULong sum;
	ULong minimunOdd;
	Input(numbers);
	OddSumAndMinimumOdd(numbers, &sum, &minimunOdd);
	Output(numbers, sum, minimunOdd);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 수들을 입력받는다
입력:X
출력:수들
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
함수이름:OddSumAndMinimumOdd
기능:홀수들의합과 가장작은 홀수를 구한다
입력:수들
출력:홀수들의합,가장작은홀수
*/
void OddSumAndMinimumOdd(ULong(*numbers), ULong *sum, ULong *minumumOdd)
{
	ULong i;
	ULong remainder;
	*sum = 0;
	* minumumOdd = 0;
	for (i =0; i < MAX; i++)
	{
		remainder = numbers[i] % 2;
		if (remainder > 0)
		{
			*sum += numbers[i];
			if (numbers[i] < *minumumOdd || *minumumOdd == 0)
			{
				*minumumOdd = numbers[i];
			}
		}

	}
}
/*
함수이름:Output
기능:홀수들의합과가장작은홀수를 입력받아 모니터로 출력한다
입력:수들,홀수들의합,가장작은홀수
출력:X
*/
void Output(ULong(*numbers), ULong sum, ULong minimumOdd)
{
	if (sum != 0)
	{
		printf("홀수들의합:%d\n가장작은홀수:%d", sum, minimumOdd);
	}
	else
	{
		printf("-1");
	}
}