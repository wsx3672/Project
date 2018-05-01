//ReverseNumber.c
/*
파일명칭:ReverseNumber.c
기능:입력받은수를 뒤집는다.
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
ULong ReverseNumber(ULong number);
void Output(ULong number, ULong reverseNumber);
//함수정의
int main (int argc, char*argv[])
{
	ULong number;
    ULong reverseNumber;
	number = Input();
	reverseNumber = ReverseNumber(number);
	Output(number, reverseNumber);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터수를입력받는다
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
함수이름:ReverseNumber
기능:입력받은수를 뒤집는다
입력:수
출력:뒤집은수
*/
ULong ReverseNumber(ULong number)
{
	ULong reverseNumber = 0;
	ULong remainNumber;
	ULong backNumber;
	remainNumber = number;
	while (remainNumber >= 10)
	{
		backNumber = remainNumber - remainNumber / 10 * 10;
		reverseNumber = (reverseNumber * 10) + (backNumber * 10);
		remainNumber = remainNumber / 10;
	}
	reverseNumber += remainNumber;
	return reverseNumber;
}
/*
함수이름:Output
기능:뒤집은수를 모니터에 출력한다
입력:수,뒤집은수
출력:X
*/
void Output(ULong number, ULong reverseNumber)
{
	printf("입력받은수:%d\n", number);
	printf("뒤집은수:%d", reverseNumber);
}
