//Boxs.c
/*
파일명칭:Boxs.c
기능:설탕의무게를 입력받아 5kg박스수와 3kg박스수로 구할수있는 최소박스수를 구한다
작성자:박상민
작성일자:2017년5월17일
*/
#include <stdio.h>
#pragma warning (disable:4996)
//자료형설계
typedef signed long int Long;
//함수선언
int main(int argc, char *argv[]);
Long Input();
void Boxs(Long sugarWeight, Long *sum, Long *fiveBoxs, Long *threeBoxs);
void Output(Long sugarWeight, Long sum, Long fiveBoxs, Long threeBoxs);
//함수정의
int main(int argc, char *argv[])
{
	Long sugarWeight;
	Long sum;
	Long fiveBoxs;
	Long threeBoxs;
	sugarWeight = Input();
	Boxs(sugarWeight, &sum, &fiveBoxs, &threeBoxs);
	Output(sugarWeight, sum, fiveBoxs, threeBoxs);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 설탕의무게를 입력받는다
입력:X
출력:설탕의무게
*/
Long Input()
{

	Long sugarWeight;
	scanf("%d", &sugarWeight);
	return sugarWeight;
}
/*
함수이름:Boxs
기능:최소박스수와5kg박스수와3kg박스수를구한다
입력;설탕의무게
출력:최소박스수,5kg박스수,3kg박스수
*/
void Boxs(Long sugarWeight, Long *sum, Long *fiveBoxs, Long *threeBoxs)
{
	*threeBoxs = 0;
	*fiveBoxs = sugarWeight / 5;
	sugarWeight = sugarWeight % 5;
	while (sugarWeight > 0)
	{
		if (sugarWeight<3)
		{
			*fiveBoxs = *fiveBoxs - 1;
			sugarWeight = sugarWeight + 5;
		}
		*threeBoxs = *threeBoxs + 1;
		sugarWeight -= 3;
	}
	if (*fiveBoxs < 0)
	{
		*threeBoxs = 0;
		*fiveBoxs = 0;
	}
	*sum = *fiveBoxs + *threeBoxs;
}
/*
함수이름:Output
기능:최소박스수,5kg박스수와3kg박스수를 입력받아 모니터로 출력한다
입력:최소박스,5kg박스수,3kg박스수
출력:X
*/
void Output(Long sugarWeight, Long sum, Long fiveBoxs, Long threeBoxs)
{
	if (sum != 0) {
		printf("최소박스수:%d\n5kg박스수:%d\n3kg박스수:%d", sum, fiveBoxs, threeBoxs);
	}
	else {
		printf("ERROR DATE");
	}
}		