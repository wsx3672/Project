//PrimeNumberSum.c
/*
파일명칭:PrimeNumberSum.c
기능:입력받은 두수사이의 소수들의 합을 구한다
작성자:박상민
작성일자:2017년5월18일
*/
#include <stdio.h>
#pragma warning (disable:4996)
//자료형설계
typedef unsigned long int ULong;
//함수선언
int main(int argc, char *argv[]);
void Input(ULong *frontNumber, ULong *backNumber);
ULong PrimeNumberSum(ULong frontNumber, ULong backNumber);
void Output(ULong frontNumber, ULong backNumber, ULong sum);
//함수정의
int main(int argc, char *argv[])
{
	ULong frontNumber;
	ULong backNumber;
	ULong sum;
	Input(&frontNumber, &backNumber);
	sum = PrimeNumberSum(frontNumber, backNumber);
	Output(frontNumber, backNumber, sum);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 두수를 입력받는다
입력:X
출력:앞의수,뒤의수
*/


void Input(ULong *frontNumber, ULong *backNumber)
{
	scanf("%d %d", frontNumber, backNumber);
}
/*
함수이름:PrimeNumberSum
기능:입력받은 두수사이의 소수들의 합을 구한다
입력:앞의수,뒤의수
출력:소수들의합
*/
ULong PrimeNumberSum(ULong frontNumber, ULong backNumber)
{
	ULong remainder;
	ULong count;
	ULong number;
	ULong i;
	ULong factor;
	ULong sum = 0;
	number = frontNumber;
	while (number <= backNumber)
	{
		i = 1;
		count = 0;
		factor = 0;
		while (i <= number)
		{
			factor++;
			remainder = number%factor;
			if (remainder == 0)
			{
				count++;
			}
			i++;
		}
		if (count == 2)
		{
			sum = sum + number;
		}
		number++;
	}
	return sum;
}
/*
함수이름:Output
기능:소수들의합을 입력받아 모니터로 출력한다
입력:첫번째수,두번째수,소수들의합
출력:X
*/
void Output(ULong frontNumber, ULong backNumber, ULong sum)
{
	printf("입력하신수:%d %d\n두수사이의소수들의합:%d", frontNumber, backNumber, sum);
}
