//ArrangeNumbers6.c
/*
파일명칭:ArrangeNumbers6.c
기능:규칙성을 찾아 대칭을 이용하여 수들을 입력한다
작성자:박상민
작성일자:2017년5월25일
*/
//매크로선언
#include <stdio.h>
#define ROWS 5
#define COLUMNS 5
#pragma warning (disable:4996)
//자료형설계
typedef unsigned long int ULong;
//함수선언
int main(int argc, char *argv[]);
void ArrangeNumbers6(ULong(*numbers)[COLUMNS]);
void Output(ULong(*numbers)[COLUMNS]);
//함수정의
int main(int argc, char *argv[])
{
	ULong numbers[ROWS][COLUMNS];
	ArrangeNumbers6(numbers);
	Output(numbers);
	return 0;
}
/*
함수이름:ArrangeNumbers6
기능:규칙성을 찾아 대칭을 이용하여 수들를 입력한다
입력:X
출력:이미지
*/
void ArrangeNumbers6(ULong(*numbers)[COLUMNS])
{
	ULong i;
	ULong j;
	for (i = 0; i <(ROWS +1)/ 2; i++)
	{
		for (j = 0; j<(COLUMNS+1) / 2; j++)
		{
			if (i + j < 2)
			{
				numbers[i][j] = 0;
			}
			else
			{
				numbers[i][j] = i + j - 1;
			}
			if (i != 2 && j != 2)
			{
				numbers[ROWS-1 - i][j] = numbers[i][j];
				numbers[i][COLUMNS-1 - j] = numbers[i][j];
				numbers[ROWS-1 - i][COLUMNS-1 - j] = numbers[i][j];
			}
			if (i == 2 && j != 2)
			{
				numbers[i][COLUMNS-1 - j] = numbers[i][j];
			}
			if (i != 2 && j == 2)
			{
				numbers[ROWS-1 - i][j] = numbers[i][j];
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
void Output(ULong(*numbers)[COLUMNS])
{
	ULong i;
	for (i = 0; i < ROWS; i++)
	{
		printf("%2d %2d %2d %2d %2d\n", numbers[i][0], numbers[i][1], numbers[i][2], numbers[i][3], numbers[i][4]);
	}
}