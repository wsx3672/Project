//Change.c
/*
파일이름:Change.c
기능:거스름돈으로 줘야할 동전의개수를 센다
작성자:박상민
작성일자:2017년5월17일
*/
#include <stdio.h>
#pragma warning (disable:4996)
//자료형설계
typedef unsigned short Short;
//함수선언
int main(int argc, char *argv[]);
Short Input();
void Charge(Short price, Short *fiveHundred, Short *hundred, Short *fifty, Short *ten);
void Output(Short price, Short fiveHundred, Short hundred, Short fifty, Short ten);
//함수정의
int main(int argc, char *argv[])
{
	Short price;
	Short fiveHunderd;
	Short hundred;
	Short fifty;
	Short ten;
	price = Input();
	Charge (price,&fiveHunderd, &hundred, &fifty, &ten);
	Output (price,fiveHunderd, hundred, fifty, ten);
	return 0;
}
/*
함수이름:Input
기능:키보드로부터 수를 입력받는다
입력:X
출력:물건값
*/
Short Input()
{
	Short price;
	scanf("%hd", &price);
	return price;
}
/*
함수이름:Change
기능:거스름돈으로 줘야할 동전의 개수를 구한다
입력:물건값
출력:500원,100원,50원,10원
*/
void Charge(Short price, Short *fiveHundred, Short *hundred, Short *fifty, Short *ten)
{
	Short change;
	change = 1000 - price;
	*fiveHundred = change / 500;
	change = change - *fiveHundred * 500;
	*hundred = change / 100;
	change = change - *hundred * 100;
	*fifty = change / 100;
	change = change - *fifty * 50;
	*ten = change / 10;
	change = change - *ten * 10;
}
/*
함수이름:Output
기능:500원,100원,50원,10원을 입력받아 모니터로 출력한다
입력:물건값,500원,100원,50원,10원
출력:X
*/
void Output(Short price, Short fiveHundred, Short hundred, Short fifty, Short ten)
{
	printf("물건값:%d\n500원:%d\n100원:%d\n50원:%d\n10원:%d", price, fiveHundred, hundred, fifty, ten);
}
