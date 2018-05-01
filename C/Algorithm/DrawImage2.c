//DrawImage2.c
/*
파일명칭:DrawImage2.c
기능:규칙성을 찾아 이미지를 그린다
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
void DrawImage2(char(*image)[COLUMNS]);
void Output(char(*image)[COLUMNS]);
//함수정의
int main(int argc, char *argv[])
{
	char image[ROWS][COLUMNS];
	DrawImage2(image);
	Output(image);
	return 0;
}
/*
함수이름:DrawImage2
기능:규칙성을 찾아 이미지를 그린다
입력:X
출력:이미지
*/
void DrawImage2(char(*image)[COLUMNS])
{
	ULong i;
	ULong j;
	ULong remainder;
	for (j = 1; j < ROWS + 1; j++)
	{
		remainder = j % 2;
		i = 1;
		if (remainder == 0)
		{
			while (i < COLUMNS + 1)
			{
				remainder = i % 2;
				if (remainder == 0)
				{
					image[j - 1][i - 1] = '*';
					
				}
				else
				{
					image[j - 1][i - 1] = ' ';
				}
				i++;
			}
		}
		else 
		{
			while (i < COLUMNS + 1)
			{
				remainder = i % 2;
				if (remainder == 1)
				{
					image[j - 1][i - 1] = '*';
				}
				else
				{
					image[j - 1][i - 1] = ' ';
				}
				i++;
			}
		}
	}	

}
/*
함수이름:Output
기능:이미지를 입력받아 모니터로 출력한다
입력:이미지
출력:X
*/
void Output(char(*image)[COLUMNS])
{
	{
		ULong i;
		for (i = 0; i < ROWS; i++)
		{
			printf("%2c%2c%2c%2c%2c\n", image[i][0], image[i][1], image[i][2], image[i][3], image[i][4]);
		}
	}

}