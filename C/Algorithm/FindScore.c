//FindScore.c
/*
파일명칭:FindScore.c
기능:버섯들을 입력받아 100점과 가까운 점수를 구한다. 단 두가지 답이 나올경우 더 높은 점수를 선택한다
작성자:박상민
작성일자:2017년 5월23일
*/
//매크로선언
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//자료형설계
typedef signed long int Long;
//함수선언
int main(int argc, char *argv[]);
void Input(Long(*mushrooms));
Long FindScore(Long(*mushrooms));
void Output(Long(*mushrooms), Long score);
//함수정의
int main(int argc, char *argv[])
{
	Long mushrooms[MAX];
	Long score;
	Input(mushrooms);
	score = FindScore(mushrooms);
	Output(mushrooms, score);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 버섯들의점수들을 입력받는다
입력:X
출력:버섯들
*/
void Input(Long(*mushrooms))
{
	Long i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d",mushrooms + i);
	}
}
/*
함수이름:FindScore
기능:100점과 가까운 점수를 구한다.단 두가지 답이 나올경우 더 높은 점수를 선택한다
입력:버섯들
출력:점수
*/
Long FindScore(Long(*mushrooms))
{
	Long previous = 0;
	Long i = 0;
	Long score = 0;
	Long gap1;
	Long gap2;
	while (i<=MAX&&score<100)
	{
		score += mushrooms[i];
		if (score < 100)
		{
			previous = score;
		}
		i++;
	}
	gap1 = 100 - previous;
	gap2 = score - 100;
	if (gap1 < gap2)
	{
		score = previous;
	}
	return score;
}
/*
함수이름:Output
기능:점수를 입력받아 모니터에 출력한다
입력:버섯들,점수
출력:X
*/
void Output(Long(*mushrooms), Long score)
{
	printf("100점과가장가까운점수는 %d입니다", score);
}