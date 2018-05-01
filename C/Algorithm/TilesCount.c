//TilesCount.c
/*
파일명칭:TilesCount.c
기능:가로와세로의크기를 입력받아 온전한타일의수와 잘라서사용한 타일의수를 구한다
작성자:박상민
작성일자:2017년5월17일
*/
#include <stdio.h>
#pragma warning (disable:4996)
//자료형설계
typedef unsigned long int ULong;
//함수선언
int main(int argc, char *argv[]);
void Input(ULong *widthSize, ULong *lengthSize);
void TilesCount(ULong widthSize, ULong lengthSize, ULong *wholeTiles, ULong *partTiles);
void Output(ULong widthSize, ULong lengthSize, ULong wholeTiles, ULong partTiles);
//함수정의
int main(int argc, char *argv[])
{
	ULong widthSize;
	ULong lengthSize;
	ULong wholeTiles;
	ULong partTiles;
	Input(&widthSize, &lengthSize);
	TilesCount(widthSize, lengthSize, &wholeTiles, &partTiles);
	Output(widthSize, lengthSize, wholeTiles, partTiles);
	return 0;
}
/*
함수정의:Input
기능:키보드로부터 가로의크기와세로의크기를 입력받는다
입력:X
출력:가로의크기,세로의크기
*/
void Input(ULong *widthSize, ULong *lengthSize)
{
	printf("가로의크기 세로의크기\n");
	scanf("%d %d", widthSize, lengthSize);
}
/*
함수이름:TilesCount
기능:방의크기에 맞게 사용되어야할 온전한타일의수와잘라서사용할타일의수를 구한다
입력:가로의크기,세로의크기
출력:온전한타일수,잘라서사용한타일수
*/
void TilesCount(ULong widthSize, ULong lengthSize, ULong *wholeTiles, ULong *partTiles)
{
	ULong widthTiles;
	ULong lengthTiles;
	ULong i;
	ULong j;
	widthTiles =  widthSize / 8;
	i = widthSize - widthTiles * 8;
	if (i != 0)
	{
		i = 1;
	}
	lengthTiles = lengthSize / 8;
	j = lengthSize - lengthTiles * 8;
	if (j != 0)
	{
		j = 1;
	}
	if (i == j&&i == 1)
	{
		*wholeTiles = widthTiles*lengthTiles;
		*partTiles = i*lengthTiles + j*widthTiles + 1;
	}
	else
	{
		*wholeTiles = widthTiles*lengthTiles;
		*partTiles = i*lengthTiles + j*widthTiles;
	}
}
/*
함수이름:Output
기능:완전한타일수와잘라서사용한타일수를입력받아모니터로출력한다
입력:가로의크기,세로의크기,온전한타일수,잘라서사용한타일수
출력:X
*/
void Output(ULong widthSize, ULong lengthSize, ULong wholeTiles, ULong partTiles)
{
	printf("가로의크기%d   세로의크기%d\n온전한타일수:%d   잘라서사용한타일수:%d", widthSize, lengthSize, wholeTiles, partTiles);
}