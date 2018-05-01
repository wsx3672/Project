//Key.c
/*
파일명칭:Key.c
기능:10개의정수를 입력받고 찾고자하는 값을 입력받아 그위치를 구한다
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
int main(int argc, char *argv[]);
void Input(Long(*numbers), Long *key);
void Key(Long(*numbers), Long key, Long *count, Long(*positions));
void Output(Long(*numbers), Long key, Long count, Long(*positions));
//함수정의
int main(int argc, char *argv[])
{
	Long numbers[MAX];
	Long positions[MAX];
	Long key;
	Long count;
	Input(numbers, &key);
	Key(numbers, key, &count, positions);
	Output(numbers, key, count, positions);
}
/*
함수이름:Input
기능:키보드로부터 수들을 입력받는다
입력:X
출력:수들,찾고자하는값
*/
void Input(Long(*numbers), Long *key)
{
	Long i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", numbers + i);
	}
	printf("찾고자하는값:");
	scanf("%d", key);
}
/*
함수이름:Key
기능:입력받은수중에서 찾고자하는값을 찾고 그 위치를 구한다
입력:수들,찾고자하는값
출력:위치들
*/
void Key(Long(*numbers), Long key, Long *count, Long(*positions))
{
	Long i;
	Long j = 0;
	*count = 0;
	for (i = 0; i < MAX; i++)
	{
		if (numbers[i] == key)
		{
			positions[j] = i ;
			j = j + 1;
			*count = *count + 1;
		}
	}
}
/*
함수이름:Output
기능:위치들을입력받아 모니터로 출력한다
입력:수들,찾고자하는값,위치들
출력:X
*/
void Output(Long(*numbers), Long key, Long count, Long(*positions))
{
	Long i = 0;
	if (count != 0)
	{
		printf("위치값:");
		while (i < count)
		{

			printf("%d ", positions[i]+1);
			i = i + 1;
		}
	}
	else
	{
		printf("찾고자하는값이없습니다.");
	}
}