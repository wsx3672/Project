//HighNumber.c
/*
파일명칭:HighNumber.c
기능:수를 입력받아 가장큰수대로 출력한다
작성자:박상민
작성일자:2017년5월16일
*/
//매크로선언
#include <stdio.h>
#pragma warning (disable:4996)
//자료형설계
typedef unsigned long int ULong;
//함수선언
int main(int argc, char*argv[]);
ULong Input();
ULong HighNumber(ULong number);
void Output(ULong number, ULong highNumber);
//함수정의
int main(int argc, char*argv[])
{
	ULong number;
	ULong highNumber;
	number = Input();
	highNumber = HighNumber(number);
	Output(number, highNumber);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 수를 입력받는다
입력:X
출력:수
*/
ULong Input()
{
	ULong number;
	scanf("%d", &number);
	return number;
}
/*
함수이름:HighNumber
기능:입력받은수를 가장큰수대로 출력한다
입력:수
출력:가장큰수
*/
ULong HighNumber(ULong number)

{
	ULong highNumber = 0;
	ULong i;
	ULong temp;
	ULong count = 0;
	ULong exponent;
	ULong j = 1;
	temp = number;
	while (temp > 0)
	{
		count++;
		temp = temp / 10;
	}
	for (i = 9; i > 0; i--)
	{
		j = 1;
		temp = number;
		exponent = temp - temp / 10 * 10;
		while (j <= count)
		{
			if (exponent == i)
			{
				highNumber = highNumber * 10 + exponent;
			}
			temp = temp / 10;
			exponent = temp % 10;
			j++;
		}
	}
	return highNumber;
}
/*
함수이름:Output
기능:가장큰수를입력받아모니터로출력한다
입력:수,가장큰수
출력:X
*/
void Output(ULong number, ULong highNumber)

{
	printf("입력한수:%d\n", number);
	printf("가장큰수:%d", highNumber);
}
