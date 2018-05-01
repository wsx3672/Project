//Distinguish.c
/*
파일명칭:Distinguish.c
기능:수들을 입력받아 음의정수의개수,양의정수의개수,짝수의개수,홀수의개수를 구한다
작성자:박상민
작성일자:2017년5월19일
*/
//매크로선언
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//자료형설계
typedef signed long int Long;
//함수선언
int main(int argc, char *argv);
void Input(Long(*numbers));
void Distinguish(Long(*numbers), Long *negativeInteger, Long *positiveInteger, Long *evenNumber, Long *oddNumber);
void Output(Long(*numbers), Long negativeInteger, Long positiveInteger, Long evenNumber, Long oddNumber);
//함수정의
int main(int argc, char *argv)
{
	Long numbers[MAX];
	Long negativeInteger;
	Long positiveInteger;
	Long evenNumber;
	Long oddNumber;
	Input(numbers);
	Distinguish(numbers, &negativeInteger, &positiveInteger, &evenNumber, &oddNumber);
	Output(numbers, negativeInteger, positiveInteger, evenNumber, oddNumber);

}
/*함수이름:Input
기능:키보드로부터 수들을 입력받는다
입력:X
출력;수들
*/
void Input(Long(*numbers))
{
	Long i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", numbers + i);
	}
}
/*
함수이름:Distinguish
기능:입력받은수들을 판단하여 음의정수의개수,양의정수의개수,짝수의개수,홀수의개수를 센다
입력:수들
출력:음의정수의개수,양의정수의개수,짝수의개수,홀수의개수
*/
void Distinguish(Long(*numbers), Long *negativeInteger, Long *positiveInteger, Long *evenNumber, Long *oddNumber)
{
	Long i;
	Long remainder;
	*negativeInteger = 0;
	*positiveInteger = 0;
	*evenNumber = 0;
	*oddNumber = 0;
	for (i = 0; i < MAX; i++)
	{
		if (numbers[i]>0)
		{
			*positiveInteger = *positiveInteger + 1;
			remainder = numbers[i] % 2;
			if (remainder == 0)
			{
				*evenNumber = *evenNumber + 1;
			}
			else
			{
				*oddNumber = *oddNumber + 1;
			}
		}
		else
		{
			if (numbers[i] < 0)
			{
				*negativeInteger = *negativeInteger + 1;
			}
		}

	}
}
/*
함수이름:Output
기능:음의정수의개수,양의정수의개수,짝수의개수,홀수의개수를입력받아 모니터로 출력한다
입력:수들,음의정수의개수,양의정수의개수,짝수의개수,홀수의개수
출력:x
*/
void Output(Long(*numbers), Long negativeInteger, Long positiveInteger, Long evenNumber, Long oddNumber)
{
	
	printf("음의정수의개수:%d\n양의정수의개수:%d\n짝수의개수:%d\n홀수의개수:%d", negativeInteger, positiveInteger, evenNumber, oddNumber);
}
