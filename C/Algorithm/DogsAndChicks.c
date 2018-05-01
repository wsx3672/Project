//DogsAndChicks.c
/*
파일명칭:DogsAndChicks.c
기능:강아지와병아리의합과다리의수를입력받아 강아지와 병아리가 각각 몇마리인지 구한다
작성자:박상민
작성일자:2017년5월17일
*/
//매크로선언
#include <stdio.h>
#pragma warning (disable:4996)
//자료형설계
typedef signed long int ULong;
//함수선언
int main(int argc, char *argv[]);
void Input(ULong *sum, ULong *legs);
void DogsAndChicks(ULong sum, ULong legs, ULong *dogs, ULong *chicks);
void Output(ULong sum, ULong legs, ULong dogs, ULong chicks);
//함수정의
int main(int argc, char *argv[])
{
	ULong sum;
	ULong legs;
	ULong dogs;
	ULong chicks;
	Input(&sum, &legs);
	DogsAndChicks(sum, legs, &dogs, &chicks);
	Output(sum, legs, dogs, chicks);
	return 0;
}
/*
함수이름;Input
기능:키보드로부터 강아지와병아리의합과 다리수를 입력받는다
입력:X
출력:강아지와병아리의합,다리의수
*/
void Input(ULong *sum, ULong *legs)
{
	scanf("%d%d", sum, legs);
}
/*
함수이름:DogsAndChicks
기능:강아지와병아리가 몇마리인지 구한다
입력:강아지와병아리의합,다리의수
출력:강아지의수,병아리의수
*/
void DogsAndChicks(ULong sum, ULong legs, ULong *dogs, ULong *chicks)
{

	ULong count;

	*dogs = 0;
	*chicks = sum;
	count = *chicks * 2;
	while (count != legs && chicks >= 0)
	{
		*dogs = *dogs + 1;
		*chicks = *chicks - 1;
		count = 2 * *chicks + 4 * *dogs;
	}
	if (chicks < 0)
	{
		*dogs = 0;
		*chicks = 0;
	}
}
/*
함수이름:Output
기능:강아지의수와병아리의수를 입력받아 모니터로 출력한다
입력:강아지와병아리의합,다리의수,강아지의수,병아리의수
출력:X
*/
void Output(ULong sum, ULong legs, ULong dogs, ULong chicks)
{
	printf("입력하신 강아지와 병아리의합:%d\n입력하신다리의수:%d\n강아지의수:%d\n병아리의수:%d", sum, legs, dogs, chicks);
}

