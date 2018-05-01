//AscendingNumbers.c
/*
파일명칭:AscendingNumbers.c
기능:수들을 입력받아 삽입정렬로 오름차순을 만든다
작성자:박상민
작성일자:2017년5월23일
*/
//매크로선언
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//자료형설계
typedef signed long int ULong;
//함수선언
int main(int argc, char *argv[]);
void Input(ULong(*numbers));
void AscendingNumbers(ULong(*numbers), ULong(*ascendingNumbers));
void Output(ULong(*numbers), ULong(*ascendingNumbers));
//함수정의
int main(int argc, char *argv[])
{
	ULong numbers[MAX];
	ULong ascendingNumbers[MAX];
	Input(numbers);
	AscendingNumbers(numbers, ascendingNumbers);
	Output(numbers, ascendingNumbers);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 수들을 입력받는다
입력:X
출력:수들
*/
void Input(ULong(*numbers))
{
	ULong i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", numbers + i);
	}
}
/*
함수이름:AscendingNumbers
기능:입력된수들을 삽입정렬을이용해 오름차순으로 만든다
입력:수들
출력:정렬된수들
*/
void AscendingNumbers(ULong(*numbers), ULong(*ascendingNumbers))
{
	ULong i;
	ULong j;
	ULong temp;
	for (i = 0; i < MAX; i++)
	{
		ascendingNumbers[i] = numbers[i];
	}
	for (j = 1; j < MAX; j++)
	{
		i = j - 1;
		temp = ascendingNumbers[j];
		while (i>=0&&temp<ascendingNumbers[i])
		{
			ascendingNumbers[i + 1] = ascendingNumbers[i];
			i--;
		}
		ascendingNumbers[i + 1] = temp;
	}
}
/*
함수이름:Output
기능:정렬된수들을 입력받아 모니터로 출력한다
입력:수들,정렬된수들
출력:X
*/
void Output(ULong(*numbers), ULong(*ascendingNumbers))
{
	ULong i;
	printf("입력한수:");
	for (i = 0; i < MAX; i++)
	{
		printf("%d ",numbers[i]);
	}
	printf("정렬된수:");
	for (i = 0; i < MAX; i++)
		
		printf("%d ", ascendingNumbers[i]);
}