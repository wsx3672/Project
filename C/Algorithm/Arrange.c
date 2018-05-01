//Arrange.c
/*
파일명칭:Arrange.c
기능:수들을 입력받아 큰수대로 정렬한다
작성자:박상민
작성일자:2017년5월19일
*/
//매크로선언
#include <stdio.h>
#define MAX 3
#pragma warning (disable:4996)
//자료형선언
typedef signed long int Long;
//함수선언
int main(int argc, char *argv[]);
void Input(Long(*numbers));
void Arrange(Long(*numbers));
void Output(Long(*numbers));
//함수정의
int main(int argc, char *argv[])
{
	Long numbers[MAX];
	Input(numbers);
	Arrange(numbers);
	Output(numbers);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 수들을 입력받는다
입력:X
출력:수들
*/
void Input(Long(*numbers))
{
	Long i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", numbers+i);

	}

}
/*
함수이름:Arrange
기능:입력된수들을 큰수대로 정렬한다
입력:수들
출력:수들(정렬된)
*/
void Arrange(Long(*numbers))
{
	Long i;
	Long j;
	Long temp;
	for (i = 0; i < MAX - 1; i++)
	{
		for (j = i + 1; j < MAX; j++)
		{
			if (numbers[i] < numbers[j])
			{
				temp = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = temp;
			}
		}
	}
}
/*
함수이름:Output
기능:정렬된 수들을 입력받아 모니터로 출력한다
입력:수들(정렬된)
출력:X
*/
void Output(Long(*numbers))
{
	Long i;
	for (i = 0; i < MAX; i++)
	{
		printf("%d\n", numbers[i]);
	}
}