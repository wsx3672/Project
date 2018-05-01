//Sum.c
/*파일명칭:Sum.c
기능:수를 입력받아 각자리수의합을 구한다
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
ULong Sum(ULong number);
void Output(ULong number, ULong sum);
//함수정의
int main(int argc, char *argv[])
{
	ULong number;
	ULong sum;
	number = Input();
	sum = Sum(number);
	Output(number, sum);
	return 0;
}
/*
함수이름: Input
기능:키보드로부터 수를 입력받는다
입력:X
출력:수
*/
ULong Input() {
	ULong number;
		scanf("%d", &number);
		return number;
}
/*
함수이름:Sum
기능:입력받은수의 각자리수의합을구한다
입력:수
출력:각자리수의합
*/
ULong Sum(number) 
{
	ULong sum = 0;
	ULong remainder;
	ULong quotient;
		ULong i;
		i = number;
		while (i>=10){
			quotient = 1 / 10;
			remainder = i - quotient * 10;
			sum += remainder;
			i = i / 10;
		}
		sum += i;
		return sum;
}
/*
함수이름:Output
기능:각자리수의합을 입력받아 모니터로 출력한다
입력:수,각자리수의합
출력:X
*/
void Output(number, sum) {
	printf("입력하신 %d의 각자리수의합은 %d입니다.", number, sum);
}