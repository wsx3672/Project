//ArrangeNumbers4.c
/*
파일명칭:ArrangeNumbers4.c
기능:규칙성을 찾아 수를 입력한다
작성자:박상민
작성일자:2017년5월25일
*/
//매크로선언
#include <stdio.h>
#define ROWS 5
#define COLUMNS 5
#pragma warning (disable:4996)
//자료형설계
typedef signed long int Long;
//함수선언
int main(int argc, char *argv[]);
void ArrangeNumbers4(Long(*numbers)[COLUMNS]);
void Output(Long(*numbers)[COLUMNS]);
//함수정의
int main(int argc, char *argv[])
{
	Long numbers[ROWS][COLUMNS];
	ArrangeNumbers4(numbers);
	Output(numbers);
	return 0;
}
/*
함수이름:ArrangeNumbers4
기능:규칙성을 찾아 수를 입력한다
입력:X
출력:이미지
*/
void ArrangeNumbers4(Long(*numbers)[COLUMNS])
{
	Long i;
	Long j;
	Long remainber;
	Long number = 1;
	for (j = 1; j < ROWS + 1; j++)
	{
		remainber = j % 2;
		if (remainber == 0)
		{
			i = COLUMNS - 1;
			while (i >= 0)
			{
				numbers[j - 1][i] = number;
				number++;
				i--;
			}

		}
	
		else
		{
			i = 0;
			while (i < COLUMNS)
			{
				numbers[j - 1][i] = number;
				number++;
				i++;
			}

		}
	}

}
/*
함수이름:Output
기능:정렬된수들을 입력받아 모니터로 출력한다
입력:수들
출력:X
*/
void Output(Long(*numbers)[COLUMNS])
{
	Long i;
	for (i = 0; i < ROWS; i++)
	{
		printf("%2d %2d %2d %2d %2d\n", numbers[i][0], numbers[i][1], numbers[i][2], numbers[i][3], numbers[i][4]);
	}
}