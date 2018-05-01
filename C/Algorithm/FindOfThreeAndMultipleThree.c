//FindOfThreeAndMultipleThree.c
/*
파일명칭:FindOfThreeAndMultipleThree.c
기능:1부터 입력받은 수까지 3의배수와3의여부를구해 clap으로 구분한다
작성자:박상민
작성일자:2017년5월22일
*/
//매크로선언
#include <stdio.h>
#define MAX 1000
#pragma warning (disable:4996)
//자료형설계
typedef unsigned long int ULong;
//함수선언
int main(int argc, char *argv[]);
ULong Input();
void FindOfThreeAndMultipleThree (ULong number, ULong (*numbers));
void Output(ULong number, ULong (*numbers));
//함수정의
int main(int argc, char *argv[])
{
	ULong number;
	ULong numbers[MAX];
	number = Input();
	FindOfThreeAndMultipleThree(number, numbers);
	Output(number, numbers);
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
함수이름:FindOfThreeAndMultipleThree
기능:1부터 입력받은수까지 3의배수와3의여부를 구한다
입력:수
출력:수들
*/
void FindOfThreeAndMultipleThree(ULong number, ULong(*numbers))
{
	ULong count;
	ULong quotient;
	ULong remainder;
	ULong i = 0;
	while (i < number)
	{
		count = 0;
		numbers[i] = i + 1;
		remainder = numbers[i] % 3;
		if (remainder == 0)
		{
			count++;
		}
		else
		{
			quotient = numbers[i];
			while (quotient > 0 && count == 0)
			{
				remainder = quotient % 10;
				if (remainder == 3)
				{
					count++;
				}
				quotient = quotient / 10;
			}
		}
		if (count > 0)
		{
			numbers[i] = 0;
		}
		i++;
	}
}
/*
함수이름:Output
기능:수들을 입력받아 배열의 요소가 0인경우 clap 으로 바꾸어준다
입력:수,수들
출력:X
*/
void Output(ULong number, ULong(*numbers))
{
	ULong i = 0;
	while (i < number)
	{
		if (numbers[i] == 0)
		{
			printf("clap ");
		}
		else
		{
			printf("%d ", numbers[i]);
		}
		i++;
	}
}