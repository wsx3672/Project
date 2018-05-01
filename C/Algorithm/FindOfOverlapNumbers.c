//FindOfOverlapNumbers.c
/*
파일명칭:FindOfOverlapNumbers.c
기능:수들을 입력받아 중복된수를 제외하고 남아있는 수들을 구한다
작성자:박상민
작성일자:2017년5월22일
*/
//매크로선언
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//자료형설계
typedef signed long int Long;
//함수선언
int main(int argc, char *argv[]);
void Input(Long(*numbers));
void FindOfOverlapNumbers(Long(*numbers), Long(*remainingNumbers), Long *length);
void Output(Long(*numbers), Long(*reamainingNumbers), Long length);
//함수정의
int main(int argc, char *argv[])
{
	Long numbers[MAX];
	Long remainingNumbers[MAX];
	Long length;
	Input(numbers);
	FindOfOverlapNumbers(numbers, remainingNumbers, &length);
	Output(numbers, remainingNumbers, length);
	return 0;
}
/*
함수이름:Input
기능:수들을 입력받는다
입력:X
출력:수들
*/
void Input(Long(*numbers))
{
	Long i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", numbers + i);
	}
}
/*
함수이름:FindOfOverlapNumbers
기능:중복된수들을제외하고 남은수들을 구한다
입력:수들
출력:남은수들,사용량
*/
void FindOfOverlapNumbers(Long(*numbers), Long(*remainingNumbers), Long *length)
{
	Long i;
	Long j;
	Long k = 0;
	Long count = 0;
	*length = 0;
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			if (i != j)
				if (numbers[i] == numbers[j])
				{
					count++;
				}
		}

		if (count == 0)
		{
			remainingNumbers[k] = numbers[i];
			k++;
			(*length)++;
		}
		j = 1;
		count = 0;
	}
}
/*
함수이름:Output
기능:남아있는수들을 입력받아 모니터로 출력한다
입력:수들,남아있는수들,사용량
출력:X
*/
void Output(Long(*numbers), Long(*remainingNumbers), Long length)
{
	Long i = 0;
	while (i<length)
	{
		printf("%d ", remainingNumbers[i]);
		i++;
		
	}
}