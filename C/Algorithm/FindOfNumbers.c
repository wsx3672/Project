//FindOfNumbers.c
/*
파일명칭:FindOfNumbers.c
기능:정답들과 수들을 입력받아 자리수와숫자동일개수와숫자동일개수를 구한다
작성자:박상민
작성일자:2017년5월20일
*/
//매크로선언
#include <stdio.h>
#define MAX 4
#pragma warning (disable:4996)
//자료형구조
typedef unsigned char Char;
//함수선언
int main(int argc, char *argv[]);
void Input(Char(*answers), Char(*numbers));
void FindOfNumbers(Char(*answers), Char(*numbers), Char *hit, Char *blow);
void Output(Char(*answers), Char(*numbers), Char hit, Char blow);
//함수정의
int main(int argc, char *argv[])
{
	Char answers[MAX];
	Char numbers[MAX];
	Char hit;
	Char blow;
	Input(answers, numbers);
	FindOfNumbers(answers, numbers, &hit, &blow);
	Output(answers, numbers, hit, blow);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 정답들과 수들을 입력받는다
입력:X
출력:정답들,수들
*/
void Input(Char(*answers), Char(*numbers))
{
	Char i;
	printf("정답들을 입력하시오\n");
		for (i = 0; i < MAX; i++)
		{
			scanf("%d", answers + i);
		}
		for (i = 0; i < MAX; i++)
		{
			scanf("%d", numbers + i);

		}
}
/*
함수이름:FindOfNumbers
기능:자리수와숫자동일개수와 숫자동일개수를 구한다
입력:정답들,수들
출력:자리수와숫자동일개수,숫자동일개수
*/
void FindOfNumbers(Char(*answers), Char(*numbers), Char *hit, Char *blow)
{
	Char i;
	Char j;
	*hit = 0;
	*blow = 0;
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			if (answers[i] == numbers[j]) 
				if (j == i)
				{
					*hit = *hit + 1;
					
				}
				else
				{
					*blow = *blow + 1;
				}
			 
			
		}
		
	}
	
}
/*
함수이름:Output
기능:자리수와숫자동일개수와 숫자동일개수를입력받아 모니터에 출력한다
입력:정답들,수들,자리수와숫자동일개수,숫자동일개수
출력:X
*/
void Output(Char(*answers), Char(*numbers), Char hit, Char blow)
{
	if (hit != 0)
	{
		printf("hit:%d   blow:%d", hit, blow);
	}
	else
	{
		printf("blow:%d", blow);
	}
}
