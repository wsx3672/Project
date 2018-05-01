//BackWards.c
/*
파일명칭:BackWards.c
기능:입력된수들을 거꾸로 정렬한다
작성아:박상민
작성일자:2017년5월19일
*/
//매크로선언
#include <stdio.h>
#define MAX 1000
#pragma warning (disable:4996)
//자료형설계
typedef signed long int Long;
//함수선언
int main(int argc, char *argv[]);
void Input(Long *count, Long(*numbers));
void BackWards(Long count, Long(*numbers));
void Output(Long count, Long(*numbers));
//함수정의
int main(int argc, char *argv[])
{
	Long count;
	Long numbers[MAX];
	Input(&count, numbers);
	BackWards(count, numbers);
	Output(count, numbers);
}
/*
함수이름:Input
기능:키보드로부터 수들을 입력받는다
입력:X
출력:수의개수,수들
*/
void Input(Long *count, Long(*numbers))
{
	Long i = 0;
	printf("수의개수를 입력하시오");
	scanf("%d", count);
	while (i < *count)
	{
		scanf("%d", numbers + i);
		i = i + 1;
	}
}
/*
함수이름:BackWards
기능:입력된수들을 거꾸로 정렬한다
입력:수의개수,수들
출력:수들(정렬된)
*/
void BackWards(Long count, Long(*numbers))
{
	Long i = 0;
	Long j;
	Long temp;
	j = count - 1;
	while (i <= count / 2)
	{
		temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;
		j--;
		i++;
	}
}
/*
함수이름:Output
기능:정렬된수들을 입력받아 모니터로 출력한다
입력:수의개수,수들
출력:X
*/
void Output(Long count, Long(*numbers))
{
	Long i = 0;
	while (i < count)
	{
		printf("%d ", numbers[i]);
		i = i + 1;
	}
}