//SeekLank.c
/*
파일명칭:SeekLank.c
기능:번호와총점들을 입력받아 석차들을 구한다
작성자:박상민
작성일자:2017년5월23일
*/
//매크로선언
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//자료형설계
typedef unsigned long int ULong;
//함수선언
int main(int argc, char *argv[]);
void Input(ULong(*numbers), ULong(*totalScores));
void SeekLank(ULong(*totalScores), ULong(*ranks));
void Output(ULong(*totalScores), ULong(*numbers), ULong(*ranks));
//함수정의
int main(int argc, char *argv[])
{
	ULong numbers[MAX];
	ULong totalScores[MAX];
	ULong ranks[MAX];
	Input(numbers, totalScores);
	SeekLank(totalScores, ranks);
	Output(totalScores, numbers, ranks);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 번호와총점들을 입력받는다
입력:x
출력:총점들,번호
*/
void Input(ULong(*numbers), ULong(*totalScores))
{

	ULong i;
	printf("총점들을 입력하세요\n");
	for (i = 0; i < MAX; i++)

	{
		numbers[i] = i + 1;
		scanf("%d",totalScores + i);
	}
}
/*
함수이름:SeekLanks
기능:석차들을 구한다
입력:총점들
출력:석차들
*/
void SeekLank(ULong(*totalScores), ULong(*ranks))
{
	ULong i;
	ULong j = 0;
	ULong k;
	for (i = 0; i < MAX; i++)
	{
		ranks[i] = 1;
	}
	while (j <= MAX - 1)
	{
		k = j + 1;

		while (k < MAX)
		{
			if (totalScores[j] != totalScores[k])
			{
				if (totalScores[j] < totalScores[k])
				{
					ranks[j] = ranks[j] + 1;
				}
				else
				{
					ranks[k] = ranks[k] + 1;
				}
			}
			k++;
		}
		j++;
	}
}
/*
함수이름:Output
기능:번호,총점들,석차들을 입력받아 모니터로출력한다
입력:번호,총점들,석차들
출력;X
*/
void Output(ULong(*totalScores), ULong(*numbers), ULong(*ranks))
{
	ULong i;
	printf("번호 총점 석차\n");
	for (i = 0; i < MAX; i++)
	{
		printf("%d %d %d\n", numbers[i], totalScores[i], ranks[i]);
	}
}