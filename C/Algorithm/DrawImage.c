//DrawImage.c
/*
파일명칭:DrawImage.c
기능:규칙성을 찾아 이미지를 구한다
작성자:박상민
작성일자:2017년5월25일
*/
//매크로선언
#include <stdio.h>
#define ROWS 5
#define COLUMNS 5
#pragma warning (disable:4996)
//자료형선언
typedef unsigned long int ULong;
//함수선언
int main(int argc, char *argv[]);
void DrawImage(char(*image)[COLUMNS]);
void Output(char(*image)[COLUMNS]);
//함수정의
int main(int argc, char *argv[])
{
	char image[ROWS][COLUMNS];
	DrawImage(image);
	Output(image);
	return 0;
}
/*
함수이름:DrawImage
기능:규칙성을 찾아 이미지를 만든다
입력;X
출력:이미지
*/
void DrawImage(char(*image)[COLUMNS])
{
	ULong i;
	ULong j;
	for (j=0;j<ROWS;j++ )
	{
		for (i = 0; i < COLUMNS; i++)
		{
			if ( j+i== COLUMNS - 1 || j == i)
			{
				image[j][i] = '*';
			}
			else
			{
				image[j][i] = ' ';
			}
	  }
	}
}
/*
함수이름:Output
기능:이미지를 입력받아 모니터에 출력한다
입력:이미지
출력:X
*/
void Output(char(*image)[COLUMNS])
{
	ULong i;
	for (i = 0; i < ROWS; i++)
	{
		printf("%2c%2c%2c%2c%2c\n", image[i][0], image[i][1],image[i][2],image[i][3], image[i][4]);
	}
}
