/*
파일명칭:Days.c
기능:달팽이가 우물 밖으로 나오는데 걸리는 일자를 구한다
작성자:박상민
작성일자:2017년5월15일
오류수정:2017년5월26일
오류내용:함수선언과함수정의가 잘못되어있고 Days함수에서 리턴문법이 잘못되어있었다.
*/
//매크로선언
#include <stdio.h>
#pragma warning (disable:4996)
//자료형설계
typedef unsigned long int ULong;
//함수선언
int main(int argc, char* argv[]);
ULong Input();
ULong Days(ULong depth);
void Output(ULong depth, ULong days);
//함수정의
int main(int argc, char *argv[])
{
	ULong depth;
	ULong days;
	depth = Input();
	days = Days(depth);
	Output(depth,days);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 수를 입력받는다
입력:X
출력:깊이
*/
ULong Input()
{
	ULong depth;
	scanf("%d", &depth);
	return depth;
}
/*
함수이름:days.c
기능:달팽이가 우물밖으로 나오는데 걸리는 일자를 구한다
입력:깊이
출력:일자
*/
ULong Days(ULong depth)
{
	ULong days = 1;
	ULong snail = 3;
	while (snail < depth) {
		snail -= 2;
		days++;
		snail += 3;
	}
	return days;
}
/*
함수이름:Output
기능:걸리는일자를 입력받아 모니터로 출력한다
입력:깊이,일자
출력:X
*/
void Output(ULong depth, ULong days) 
{
	printf("달팽이가 우물의 깊이인 %d를 빠져나오는데 걸리는 일자는 %d입니다.\n ", depth, days);
}




