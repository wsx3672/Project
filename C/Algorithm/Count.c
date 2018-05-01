//Count.c
/*
파일명칭:Count.c
기능:1부터10000까지의수증 7의개수를 센다
작성자:박상민
작성일자:2017년5월15일
*/
//매크로선언
#include <stdio.h>
#pragma warning (disable:4996 )
//함수선언
int main(int argc, char*argv[]);
int Count();
void Output(int count);
//함수정의
int main(int argc, char*argv[])
{
	int count;
	count = Count();
	Output(count);
	return 0;
}
/*
함수이름:count
기능:1부터 10000까지의수중 7의개수를 센다
입력:X
출력:7의개수
*/
int count()
{
	int startNumber;
	int count = 0;
	int quotient ;
	int remainder;
	int i;
	for (startNumber = 1; startNumber <= 10000; startNumber++)
	{
		i = startNumber;
		while (i >= 10)
		{
			remainder = i % 10;
			if (remainder == 7) {
				count++;
			}
			i = i / 10;
		}
		if (i == 7) {
			count++;
		}
	}
	return count;
}
/*
함수이름:Output
기능:7의개수를 모니터로출력한다
입력:7의개수
출력:X
*/
void Output(count)
{
	printf("1부터 10000까지의 수중 7의개수는 %d입니다.", count);
}