//PalindromeNumber.c
/*
파일명칭:PalindromeNumber.c
기능:수를 입력받아 회문수로 만든다
작성자:박상민
작성일자:2017년5월15일
*/
//매크로선언
#include <stdio.h>
#pragma warning (disable:4996)
//자료형설계
typedef unsigned long int ULong;
//함수선언
int main(int argc, char*argv[]);
ULong Input();
ULong PalindromeNumber(ULong Number);
void Output(ULong number, ULong palindromeNumber);
//함수정의
int main(int argc, char*argv[])
{
	ULong number;
	ULong palindromeNumber;
	number = Input();
	palindromeNumber = PalindromeNumber(number);
	Output(number, palindromeNumber);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 수를 입력받는다
입력:X
출력:추
*/
ULong Input()
{
	ULong number;
	scanf("%d", &number);
	return number;
}
/*
함수이름:PalindromeNumber
기능:입력받은수를 회문수로 만든다
입력:수
출력:회문수
*/
ULong PalindromeNumber(ULong number)
{
	ULong palindromeNumber;
	ULong reverseNumber = 0;
	ULong quotient;
	ULong remainder;
	palindromeNumber = number;
	while (palindromeNumber != reverseNumber)
	{
		palindromeNumber += reverseNumber;
		quotient = palindromeNumber;
		reverseNumber = 0;
		while (quotient > 0)
		{
			remainder = quotient % 10;
			reverseNumber = reverseNumber * 10 + remainder;
			quotient = quotient / 10;
		}
	}
	return palindromeNumber;
}
/*
함수이름:Output
기능:회문수를 모니터로 출력한다.
입력:수,회문수
출력:X
*/
void Output(ULong number, ULong palindromeNumber)
{
	printf("입력한수:%d\n", number);
	printf("회문수:%d", palindromeNumber);
}

