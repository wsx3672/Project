//ArrangeNumbers5.c
/*
파일명칭:ArrangeNumbers5.c
기능:규칙성을 찾아 수들을 입력한다
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
void ArrangeNumbers5(Long(*numbers)[COLUMNS]);
void Output(Long(*numbers)[COLUMNS]);
//함수정의
int main(int argc, char *argv[])
{
	Long numbers[ROWS][COLUMNS];
	ArrangeNumbers5(numbers);
	Output(numbers);
	return 0;
}
/*
함수이름:ArrangeNumbers5
기능:규칙성을 찾아 수를 입력한다
입력:X
출력:이미지
*/
void ArrangeNumbers5(Long(*numbers)[COLUMNS])
{
	Long i = 0;
	Long j = 0;
	Long k;
	Long number = 1;
	Long remainder;
	for (k = 1; k <= ROWS; k++)
	{
		remainder = k % 2;
		if (remainder == 1)
		{
			while (i<k-1)
			{
				numbers[i][j] = number;
				number++;
				i++;
			}
			while (j>=0)
			{
				numbers[i][j] = number;
				number++;
				j--;
			}
		}
		else
		{
			while (j < k - 1)
			{
				numbers[i][j] = number;
				number++;
				j++;

			}
			while (i >= 0)
			{
				numbers[i][j] = number;
				number++;
				i--;
			}
		}
		j++;
		i++;
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